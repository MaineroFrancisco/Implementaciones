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
	
	Mat corner_score = harris_score_image(img, Size(3,3),mask,SHI_TOMASI);
	
	ostringstream os;
	os<<id_cam;
	namedWindow("camara "+os.str(),1);
	
	int maxcant=1000, value1 = 10, value2 = 10;
	createTrackbar("Features","camara "+os.str(),&value1,maxcant);
	
	vector<Point2i> features = filter_features(corner_score,maxcant);
	
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
	
//	Mat img = cv::imread("D:\\Facultad\\Proyecto\\Implementaciones\\Matlab\\Cajas\\c1_4.jpeg",CV_LOAD_IMAGE_ANYCOLOR);
	Mat img = cv::imread("D:\\Facultad\\Proyecto\\Implementaciones\\C++\\Imagenes_Prueba\\Planillas_Calibrar\\calib_chessboard.jpg",CV_LOAD_IMAGE_ANYCOLOR);
//	Mat img = cv::imread("D:\\Facultad\\Proyecto\\Implementaciones\\C++\\Imagenes_Prueba\\Prueba_Completo\\Calib\\cam_1\\cap_1.png",CV_LOAD_IMAGE_ANYCOLOR);

////	Mat mask = Mat::ones(img.size(),CV_8UC1)*255;
////	
////	for(int i=0;i<15;i++) 
////	{
////		for(int j=0;j<mask.size().width;j++) 
////		{
////			mask.at<unsigned char>(i,j)= 0;
////		}
////	}
////	
////	Mat c1;
////	img.copyTo(c1);
////	int id_cam = 3;
////	cvtColor(c1,img,CV_BGR2GRAY);
////	
////	Mat corner_score = harris_score_image(img, Size(11,11),mask,HARRIS_STEPHENS);
////	
////	ostringstream os;
////	os<<id_cam;
////	namedWindow("camara "+os.str(),1);
////	
////	int maxcant=1000, value1 = 10, value2 = 10;
////////	vector<Point2i> features = filter_features(corner_score,maxcant,10);
////////	
////	vector<Point2f> features = harris_threshold(corner_score);
////	createTrackbar("Features","camara "+os.str(),&value1,features.size());
////	
////	
////	Mat show;
////	
////	while(waitKey(5)!= 27){
////		c1.copyTo(show);
////		
////		value1 = getTrackbarPos("Features","camara "+os.str());
////		
////		for(int i=0;i<value1;i++) 
////		{
////			circle(show,features[i],5,Scalar(0,255,0));
////		}
////		
////		imshow("camara "+os.str(),show);
////	}
////	
	
	sift_feature_detection(img,3,4);
	
	
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
