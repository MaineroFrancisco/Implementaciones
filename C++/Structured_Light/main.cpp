#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "auxiliares.h"

int main(int argc, char** argv) 
{
	
//	string path = argv[1];
//	
//	sistema_completo(path,true);

	///
//	string path_img = "D:\\Facultad\\Proyecto\\Structured_Light\\Camera Captures\\Img\\",
//		mask_path = "D:\\Facultad\\Proyecto\\Structured_Light\\Camera Captures\\Mask\\",
//		path_calib = "D:\\Facultad\\Proyecto\\Structured_Light\\Camera Captures\\Calib\\";
	
//	VideoCapture c2("http://192.168.1.106:4747/mjpegfeed?640x480");
	
//	load_images(path_calib, path_img, mask_path);
	
	///
//	VideoCapture c1("http://192.168.1.103:4747/mjpegfeed?640x480");
//	string path = "D:\\Facultad\\Proyecto\\Fotos\\11012018\\";
//	save_images(path, c1, 5);
	
	///
//	interseccion_prueba();

	///
//	prueba_chessboard("D:\\Facultad\\Proyecto\\Implementaciones\\C++\\Imagenes_Prueba\\Prueba_Completo\\Calib\\cam_2\\");
//	prueba_chessboard("D:\\Facultad\\Proyecto\\Fotos\\11012018\\");
	
	///
	Mat img = imread("D:\\Facultad\\Proyecto\\Fotos\\11012018\\cap_6.png",CV_LOAD_IMAGE_GRAYSCALE );
	
	Mat mask = Mat::ones(480,640,CV_8UC1)*255;
	for(int i=0;i<15;i++) 
	{
		for(int j=0;j<640;j++) 
		{
			mask.at<unsigned char>(i,j) = 0;
		}
	}
	
	Mat harris = harris_score_image(img,Size(11,11),mask,HARRIS_NOBEL);
	vector<Point2f> v = harris_threshold(harris,20000);
	
	generate_descriptor(img, v);
	
	for(int i=0;i<v.size();i++) 
	{
		circle(img,v[i],5,Scalar(0,255,0));
	}
	
	imshow("Imagen", img);
	
	
//	fourier(img);
	///
	
	
	waitKey(0);
	return 0;
} 
