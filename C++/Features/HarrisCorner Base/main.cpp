#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "harris_corner.h"

#include <iostream>

using namespace cv;
using namespace std;

void use_harris(int id_cam, Mat c1, Mat mask)
{
	
	Mat img;
	cvtColor(c1,img,CV_BGR2GRAY);
	
	Mat corner_score = harris_corner_score(img,mask);
	
	ostringstream os;
	os<<id_cam;
	namedWindow("camara "+os.str(),1);
	
	int maxcant=1000, value1 = 10, value2 = 10;
	createTrackbar("Features","camara "+os.str(),&value1,maxcant);
	
	Point2f* features = filter_features(corner_score,maxcant);
	
	Mat show;
	
	while(waitKey(5)!= 27){
		c1.copyTo(show);
		
		value1 = getTrackbarPos("Features","camara "+os.str());
		
		for(int i=0;i<value1;i++) 
		{
			circle(show,features[i],5,Scalar(0,255,0));
		}
		
		imshow("camara "+os.str(),show);
	}
}

int main(int argc, char** argv) {

	///
	//write text on the matrix:
	//	Mat c1 = cv::imread("D:\\Facultad\\Proyecto\\Structured_Light\\Camera Captures\\Calib\\cam_1\\cap_1.png",CV_LOAD_IMAGE_GRAYSCALE);
	//	Mat c2 = cv::imread("D:\\Facultad\\Proyecto\\Structured_Light\\Camera Captures\\Calib\\cam_2\\cap_1.png",CV_LOAD_IMAGE_GRAYSCALE);
	
	Mat img = cv::imread("D:\\Facultad\\Proyecto\\Implementaciones\\C++\\Imagenes_Prueba\\Prueba_Completo\\Calib\\cam_1\\cap_1.png",CV_LOAD_IMAGE_ANYCOLOR);
////	Mat c2 = cv::imread("D:\\Facultad\\Proyecto\\Structured_Light\\Calibration\\Pruebas\\Matlab\\Caja_Cubo\\c2_1.jpeg",CV_LOAD_IMAGE_ANYCOLOR);
////	
////	use_harris(1,c1);
////	use_harris(2,c2);
////
	
	///
////////	VideoCapture c("http://192.168.1.104:4747/mjpegfeed?640x480");
////////	
////////	Mat img, hsv, mask;
////////	Mat out;
////////	int v=0, vmax=255;
////////	
////////	Scalar lower_bound, upper_bound;
////////	
////////	namedWindow("HSV",1);
////////	createTrackbar("v","HSV",&v,vmax,NULL);
////////	while(waitKey(5)!= 27)
////////	{
////////		c >> img;
////////		
////////		cvtColor(img,hsv,CV_BGR2HSV);
////////		
////////		v = getTrackbarPos("v","HSV");
////////		
//////////		lower_bound = Scalar(0,0,v);
//////////		upper_bound = Scalar(359,255,255);
////////		lower_bound = Scalar(0,0,0);
////////		upper_bound = Scalar(359,255,v);
////////		
////////		inRange(hsv,lower_bound,upper_bound, mask);
////////		
////////		imshow("Mask", mask);
////////		
////////		out = Mat::zeros(img.size(),CV_8UC3);
////////		img.copyTo(out,mask);
////////		
////////		imshow("HSV",out);
////////		
////////	}
////////	
////////	use_harris(3,img,mask);
	
	Mat mask = Mat::ones(img.size(),CV_8UC1)*255;
	
	for(int i=0;i<15;i++) 
	{
		for(int j=0;j<mask.size().width;j++) 
		{
			mask.at<unsigned char>(i,j)= 0;
		}
	}
	
	imshow("mask",  mask);
	waitKey(0);
	
	
	Mat c1;
	img.copyTo(c1);
	int id_cam = 3;
	cvtColor(c1,img,CV_BGR2GRAY);
	
	Mat corner_score = harris_corner_score(img,mask);
	
	ostringstream os;
	os<<id_cam;
	namedWindow("camara "+os.str(),1);
	
	int maxcant=1000, value1 = 10, value2 = 10;
	createTrackbar("Features","camara "+os.str(),&value1,maxcant);
	
	Point2f* features = filter_features(corner_score,maxcant);
	
	Mat show;
	
	while(waitKey(5)!= 27){
		c1.copyTo(show);
		
		value1 = getTrackbarPos("Features","camara "+os.str());
		
		for(int i=0;i<value1;i++) 
		{
			circle(show,features[i],5,Scalar(0,255,0));
		}
		
		imshow("camara "+os.str(),show);
	}
	
	
	//wait for the user to press any key:
	waitKey(0);
	return 0;
} 


///
/// FALTA!!!!
/*
	Discriminar las features para la CheckBoard
	Formar descriptores
	Matching de features
	Escalado de SIFT
*/
///
