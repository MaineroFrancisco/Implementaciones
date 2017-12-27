#ifndef HARRIS_CORNER_H
#define HARRIS_CORNER_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <vector>
#include "b_tree.h"
using namespace std;
using namespace cv;

b_tree features_tree;

#define PI 3.14159265

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
	
	double minVal, maxVal;
	minMaxLoc(corner_score, &minVal, &maxVal);
	
	corner_score = corner_score+abs(minVal);
	cout<<minVal+abs(minVal)<<" "<<maxVal+abs(minVal)<<endl;
	
	Mat output;
	corner_score.copyTo(output,mask);
	
//	imshow("Output",output);
//	waitKey(0);
	
	
//	return corner_score;
	return output;
}

Point2i* filter_features(Mat corner_score, int cantidad_features = 500){
	///Ordering
	
	Mat bin = Mat::zeros(corner_score.size(),CV_8UC1);

	Point2i* features; 
	double score[cantidad_features];
	
	bool close;
	int i, j, k, c;
	int num_f = 0;
	int thresh = 10;
	for( i=0;i<corner_score.size().width;i++) 
	{
		for( j=0;j<corner_score.size().height;j++) 
		{
			features_tree.insert(Point2i(i,j), corner_score.at<float>(j,i));
		}
		cout<<i<<" " <<j<<endl;
	}
	
	cout<<cantidad_features<<endl;
	
	features = new Point2i[features_tree.get_size()];
	
	vector<Point2i> vp;
	
	vp = features_tree.get_tree();
	
	
	for(i=0;i<features_tree.get_size();i++) 
	{
		features[i] = vp[i];
	}
	
	cout<< "Vector: "<<vp.size()<<endl;
	
	return features;
}

///----------------------------------------------------------------------------


Point2i* filter_features_vector(Mat corner_score, int cantidad_features = 500){
	///Ordering
	
	double minVal, maxVal;
	minMaxLoc(corner_score, &minVal, &maxVal);
	
	corner_score = corner_score+abs(minVal);
	cout<<minVal+abs(minVal)<<" "<<maxVal+abs(minVal)<<endl;
	
	Mat bin = Mat::zeros(corner_score.size(),CV_8UC1);
	
	Point2i* features = new Point2i[cantidad_features];
	double score[cantidad_features];
	for(int i=0;i<cantidad_features;i++) 
	{
		features[i] = Point2f(0,0);
		score[i] = 0;
	}
	
	bool close;
	int i, j, k, c;
	int num_f = 0;
	int thresh = 10;
	for( i=0;i<corner_score.size().width;i++) 
	{
		for( j=0;j<corner_score.size().height;j++) 
		{
			float corner = corner_score.at<float>(j,i);
			Point2f position(i,j);
			for( k=0;k<cantidad_features;k++) 
			{		
				
				if(corner > score[k])
				{
					
					for(int l=cantidad_features-1;l>k;l--) 
					{
						features[l] = features[l-1];
						score[l] = score[l-1];
					}
					
					score[k] = corner;
					features[k] = position;
					break;	
				}
			}
		}
		cout<<i<<" " <<j<<endl;
	}
	
//		Eliminar similares
	for( k=0;k<cantidad_features;k++) 
	{
		for( int l=0;l<cantidad_features;l++) 
		{
			if(norm(features[k]-features[l])<thresh && k!=l)
			{
				if (score[k]<score[l])
				{
					features[l] = (features[k]+features[l])/2;
					score[l] = (score[k]+score[l])/2;
					
					for(int c=k;c<cantidad_features-1;c++) 
					{
						features[c] = features[c+1];
						score[c] = score[c+1];
					}
					k--;
				}
				else
				{
					features[k] = (features[k]+features[l])/2;
					score[k] = (score[k]+score[l])/2;
					
					for(int c=l;c<cantidad_features-1;c++) 
					{
						features[c] = features[c+1];
						score[c] = score[c+1];
					}
					l--;
				}
				
				features[cantidad_features-1] = Point2f(0,0);
				score[cantidad_features-1] = 0;
				
				cantidad_features--;
			}
		}
	}	

	cout<<cantidad_features<<endl;
	
	return features;
}

///----------------------------------------------------------------------------


Mat checkb_mask = (Mat_<float>(11,11) <<  
				   1.0f, 1.0f, 1.0f, 1.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				   1.0f, 1.0f, 1.0f, 1.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				   1.0f, 1.0f, 1.0f, 1.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				   1.0f, 1.0f, 1.0f, 1.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				   
				   0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				   
				   0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				   0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				   0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				   0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f
				   );

//Mat checkb_mask = (Mat_<float>(9,9) <<  
//				   0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//				   0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//				   0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//				   
//				   1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//				   1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//				   1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
//				   
//				   1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//				   1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
//				   1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
//				   );

Mat checkb_mask_ops = (Mat_<float>(11,11) <<  
					
				   0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				   0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				   0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				   0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
					
				   0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 0.0f, 0.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				   
				   1.0f, 1.0f, 1.0f, 1.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				   1.0f, 1.0f, 1.0f, 1.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				   1.0f, 1.0f, 1.0f, 1.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				   1.0f, 1.0f, 1.0f, 1.0f,0.0f,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
				   
				   );

void show_mat(Mat img)
{
	cv::Size s = img.size();
	
	for(int i=0;i<s.height;i++) 
	{
		ostringstream os;
		for(int j=0;j<s.width;j++)
		{
			float im = img.at<float>(i,j);
			
			os << img.at<float>(i,j);
			os << ", ";
			
		}
		cout << os.str() <<endl;
		
		os.clear();
		os<<"";
	}
}

///Radianes o Angulos?
Mat rotate_mask(Mat mask, double angle)
{
	Size s = mask.size();
	
	Point2f center( s.width/2, s.height/2);
	
	Mat R(2,3,CV_32F);
	
	R.at<float>(0,0) = cos(angle*180.0f/PI);
	R.at<float>(1,0) = -sin(angle*180.0f/PI);

	R.at<float>(0,1) = sin(angle*180.0f/PI);
	R.at<float>(1,1) = cos(angle*180.0f/PI);

	R.at<float>(0,2) = (1-cos(angle*180.0f/PI))*center.x - sin(angle*180.0f/PI)* center.y;
	R.at<float>(1,2) = sin(angle*180.0f/PI)*center.x + (1-cos(angle*180.0f/PI))* center.y;
	
	Mat output;
	warpAffine(mask,output,R,s);
	
	return output;
}

///UNA CAGADA, DEJA DE BOLUDEAR CON PUNTEROS ASI CAGAS MEMORIA Y ES MAS DIFICIL
//img en GRAYSCALE
// Cambiar b_tree por quadtree, arreglarselas despues con los Score, los duplicados joden mas  y son mas complicados.
void checkboard_features(Mat img,b_tree features_tree, Point2f* features, int maxcant)
{
	
	Point2i center;
	Mat region, reg_result;
	int angle;
	Scalar measure;
	for(int i=0;i<maxcant;i++) 
	{
		center = features[i];
		region = Mat(img, Rect(center.x-4,center.y-4,9,9));
		
		angle=0.0f;
		while(angle<360.0f)
		{
			rotate_mask(checkb_mask,angle);
			
			bitwise_xor(checkb_mask, region,reg_result);
			
			measure = mean(reg_result);
			
//			if(measure < /*some number a determinar*/)
//			{
				features_tree.erase(features[i]);
//			}
			
			angle+=25.0f;
		}
		
	}
	
	
	
	
}
#endif
