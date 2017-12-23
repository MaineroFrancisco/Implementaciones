#ifndef HARRIS_CORNER_H
#define HARRIS_CORNER_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
using namespace std;
using namespace cv;
Mat harris_corner_score(Mat img, Mat mask)
{
	///-------------------------------------------------------------------------
	///Mascaras gaussianas para derivadas
	
	// Dx
	Mat dx = (Mat_<float>(3, 3) << -1.0f, 0.0f, 1.0f,
			  -1.0f,  0.0f,  1.0f,
			  -1.0f,  0.0f,  1.0f);
	
	//Dy
	Mat dy;
	transpose(dx,dy);
	
	//Calculate Dx
	img.convertTo(img, CV_32F);
	
	Mat iDx = Mat::zeros(img.size(),CV_32F);
	filter2D(img, iDx,-1,dx,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	
	//Calculate Dx^2
	Mat iDx2;
	multiply(iDx, iDx,iDx2);
	
	//Calculate Dy
	Mat iDy = Mat::zeros(img.size(),CV_32F);
	filter2D(img, iDy,-1,dy,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	
	//Calculate Dy^2
	Mat iDy2;
	multiply(iDy, iDy,iDy2);
	
	//Calculate DxDy
	Mat iDxDy;
	multiply(iDx, iDy,iDxDy);
	
	///-------------------------------------------------------------------------
	///Applying gaussian filter
	int size = 3;
	double sigma = 1.5f;
	
	//	Mat kernel ={Mat<float>(3,3) << 1.0f, 1.0f, 1.0f,
	//									1.0f, 1.0f, 1.0f,
	//									1.0f, 1.0f, 1.0f
	//				}
	
	Mat kernel = getGaussianKernel(size,sigma,CV_32F);
	//Kernel Gaussiano de Integracion (Explicacion)
	/**/
	filter2D(iDx2,iDx2, -1, kernel, cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	
	filter2D(iDy2,iDy2, -1, kernel, cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	filter2D(iDxDy,iDxDy, -1, kernel, cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	
	///-------------------------------------------------------------------------
	/// Creating harris Matrix
	Mat harris_matrix = Mat::zeros(img.rows*2, img.cols*2,CV_32F);
	Size size_img = img.size();
	
	Rect roi_dx_2 = Rect(0,0,size_img.width,size_img.height);
	Rect roi_dy_2 = Rect(size_img.width,size_img.height,size_img.width,size_img.height);
	Rect roi_dy_dx = Rect(0,size_img.height,size_img.width,size_img.height);
	Rect roi_dx_dy = Rect(size_img.width,0,size_img.width,size_img.height);
	
	
	iDx2.copyTo(harris_matrix(roi_dx_2));
	iDy2.copyTo(harris_matrix(roi_dy_2));
	iDxDy.copyTo(harris_matrix(roi_dy_dx));
	iDxDy.copyTo(harris_matrix(roi_dx_dy));
	//	imshow("Harris", harris_matrix);		
	//	waitKey(0);
	
	/// Computing corner Score		|| Formula 1: det - k*(trace)^2		|| Formula 2: det / trace
	Mat corner_score = Mat::zeros(size_img,CV_32FC1);
	Mat det;
	Mat trace;
	
	// Calculate the Determinant
	Mat iDxDy2;
	multiply(iDxDy,iDxDy,iDxDy2);
	multiply(iDx2,iDy2,det);	
	subtract(det,iDxDy2,det);
	
	//Calculate the trace
	Scalar k(0.04);
	add(iDx2,iDy2,trace);
	
	// Calculate Corner Score by "Formula 1"
	multiply(trace,trace, trace);
	multiply(trace,k,trace);
	subtract(det,trace,corner_score);
	
	Mat output;
	corner_score.copyTo(output,mask);
	
//	return corner_score;
	return output;
}

Point2f* filter_features(Mat corner_score, int cantidad_features = 500){
	///Ordering
	
	double minVal, maxVal;
	minMaxLoc(corner_score, &minVal, &maxVal);
	
	corner_score = corner_score+abs(minVal);
	cout<<minVal+abs(minVal)<<" "<<maxVal+abs(minVal)<<endl;
	//	namedWindow("Filtrada",1);
	//	createTrackbar("corner_score","Filtrada",&minim,INT_MAX,NULL);
	
	Mat bin = Mat::zeros(corner_score.size(),CV_8UC1);
	
	Point2f* features = new Point2f[cantidad_features];
	double score[cantidad_features];
	for(int i=0;i<cantidad_features;i++) 
	{
		features[i] = Point2f(0,0);
		score[i] = minVal;
	}
	
	bool no_close;
	for(int i=0;i<corner_score.size().height;i++) 
	{
		for(int j=0;j<corner_score.size().width;j++) 
		{
			
			for(int k=0;k<cantidad_features;k++) 
			{
				
				if(corner_score.at<float>(i,j)>=score[k])
				{
					for(int l=cantidad_features-1;l>k; l--)
					{
						features[l] = features[l-1];
						score[l] = score[l-1];
					} 	
					score[k] = corner_score.at<float>(i,j);
					features[k] = Point2f(j,i);
					break;
				}
			}
		}
		
	}
	
	for(int i=0;i<cantidad_features;i++) 
	{
		for(int j=0;j<cantidad_features;j++) 
		{
			if( norm(features[i] - features[j]) < 20 && i!=j)
			{
				if(score[i]<score[j])
				{
					for(int l=i;l<cantidad_features; l++)
					{
						features[l] = features[l+1];
						score[l] = score[l+1];
					} 
				}
				else
				{
					for(int l=j;l<cantidad_features; l++)
					{
						features[l] = features[l+1];
						score[l] = score[l+1];
					} 
				}
				
				
				features[cantidad_features-1] = Point2f(0,0);
				score[cantidad_features-1] = 0;
				
				cantidad_features--;
				
			}
		}
	}
			
	return features;
}

void checkboard_features(Point2f* features)
{
	
}

#endif
