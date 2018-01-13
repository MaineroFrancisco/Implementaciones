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
	
	ostringstream os;
	os<<id_cam;
	namedWindow("camara "+os.str(),1);
	
	Mat corner_score = harris_score_image(img, Size(9,9),mask);
	
	
	int maxcant= 1000, value1 = 150, value2 = 0;
	createTrackbar("Threshold","camara "+os.str(),&value1,maxcant);
	
	
	Mat show;
	vector<Point2f> features;
	while(waitKey(5)!= 27){
		c1.copyTo(show);
		
		value1 = getTrackbarPos("Threshold","camara "+os.str());
		
		if(value1 != value2)
		{
			features = harris_threshold(corner_score,value1);
			value2 = value1;
		}
		
		for(int i=0;i<features.size();i++) 
		{
			circle(show,features[i],5,Scalar(0,255,0));
		}
		
		imshow("camara "+os.str(),show);
	}
}

int main(int argc, char** argv) {

	Mat img = cv::imread("D:\\Facultad\\Proyecto\\Implementaciones\\C++\\Imagenes_Prueba\\Prueba_Completo\\Calib\\cam_1\\cap_1.png",CV_LOAD_IMAGE_ANYCOLOR);
////	Mat c2 = cv::imread("D:\\Facultad\\Proyecto\\Structured_Light\\Calibration\\Pruebas\\Matlab\\Caja_Cubo\\c2_1.jpeg",CV_LOAD_IMAGE_ANYCOLOR);

	
	///
////////	VideoCapture c("http://192.168.1.104:4747/mjpegfeed?640x480");

	
	Mat mask = Mat::ones(img.size(),CV_8UC1)*255;
	
	for(int i=0;i<15;i++) 
	{
		for(int j=0;j<mask.size().width;j++) 
		{
			mask.at<unsigned char>(i,j)= 0;
		}
	}
	
	use_harris(3,img,mask);
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
