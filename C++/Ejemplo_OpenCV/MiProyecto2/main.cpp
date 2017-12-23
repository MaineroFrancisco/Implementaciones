#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	//create a gui window:
	//	namedWindow("Original",1);
	
	//write text on the matrix:
	Mat img = imread("iglesia.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	
	imshow("Original", img);
	
	///Mascaras gaussianas para derivadas
	
	// Dx
	Mat dx = (Mat_<float>(3, 3) << -1.0f, 0.0f, 1.0f,
			  -2.0f,  0.0f,  2.0f,
			  -1.0f,  0.0f,  1.0f);
	
	//Dy
	Mat dy;
	transpose(dx,dy);
	
	// Imagen de la Dx
	Mat idx = Mat::zeros(img.size(),CV_32FC1);
	filter2D(img, idx,-1,dx,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	
	
	//Computar idx2
	Mat idx2;
	multiply(idx, idx,idx2);
	//	imshow("idx2", idx2);
	
	// Imagen de la Dy
	Mat idy = Mat::zeros(img.size(),CV_32FC1);
	filter2D(img, idy,-1,dy,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	
	//Computar idy2
	Mat idy2;
	multiply(idy, idy,idy2);
	//	imshow("idy2", idy2);
	
	//Computar idxdy
	Mat idxdy;
	multiply(idx, idy,idxdy);
	//	imshow("idxdy", idxdy);
	
	///Applying gaussian filter
	
//	Mat kernel = (Mat_<float>(3, 3) << 1.0f, 1.0f, 1.0f,
//				  1.0f,  1.0f,  1.0f,
//				  1.0f,  1.0f,  1.0f);
	
	Mat kernel = getGaussianKernel(3,1.0f,CV_32F);
	
	filter2D(idx2, idx2,-1,kernel,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	filter2D(idy2, idy2,-1,kernel,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	filter2D(idxdy, idxdy,-1,kernel,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	
	/// Creating harris Matrix
	Mat harris_matrix = Mat::zeros(img.rows*2, img.cols*2,CV_32FC1);
	Size size_img = img.size();
	
	Rect roi_dx_2 = Rect(0,0,size_img.width,size_img.height);
	Rect roi_dy_2 = Rect(size_img.width,size_img.height,size_img.width,size_img.height);
	Rect roi_dy_dx = Rect(0,size_img.height,size_img.width,size_img.height);
	Rect roi_dx_dy = Rect(size_img.width,0,size_img.width,size_img.height);
	
	
	idx2.copyTo(harris_matrix(roi_dx_2));
	idy2.copyTo(harris_matrix(roi_dy_2));
	idxdy.copyTo(harris_matrix(roi_dy_dx));
	idxdy.copyTo(harris_matrix(roi_dx_dy));
//	imshow("Harris", harris_matrix);		
	
	/// Computing corner Score
	Mat det = Mat::zeros(size_img,CV_32FC1);
	
	Mat idxdy2;
	multiply(idxdy,idxdy,idxdy2);
//	imshow("test", idxdy2);	
	
	
	//Original Method
	multiply(idx2,idy2,det);
//	imshow("corner", det);
	
	
	subtract(det,idxdy2,det);
	imshow("corner", det);
	
	Mat trace;
	add(idx2,idy2,trace);
//	multiply(trace,trace, trace);
	
	Scalar k(0.4);
	
	multiply(trace,k,trace);
	
	imshow("idxdy2", trace);
	
	Mat corner_score;
//	divide(det,trace,corner_score);
	subtract(det,trace,corner_score);
	
	imshow("Corner Score", corner_score);
	
	///D

	double minVal, maxVal;
	minMaxLoc(corner_score, &minVal, &maxVal);
	
	cout<<minVal<<" "<<maxVal;
	
	//wait for the user to press any key:
	
//	imshow("Filtrado", corner_score);
	
	///Orden
	Mat se = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(corner_score, corner_score, se);
	erode(corner_score, corner_score, se);
	
	threshold( corner_score, corner_score, 220, maxVal, CV_THRESH_TOZERO);
	
	imshow("Orden", corner_score);
	
	waitKey(0);
	return 0;
} 
