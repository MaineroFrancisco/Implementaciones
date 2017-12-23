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
	string path_img = "D:\\Facultad\\Proyecto\\Structured_Light\\Camera Captures\\Img\\",
		mask_path = "D:\\Facultad\\Proyecto\\Structured_Light\\Camera Captures\\Mask\\",
		path_calib = "D:\\Facultad\\Proyecto\\Structured_Light\\Camera Captures\\Calib\\";
	
//	VideoCapture c1("http://192.168.1.105:4747/mjpegfeed?640x480");
//	VideoCapture c2("http://192.168.1.106:4747/mjpegfeed?640x480");
//	saving_images(path_calib, path_img, mask_path, c1, c2);
	
//	load_images(path_calib, path_img, mask_path);
		
	
	interseccion_prueba();
	waitKey(0);
	return 0;
} 
