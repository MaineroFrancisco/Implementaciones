#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

//#include "auxiliares.h"
#include "test.hpp"

int main(int argc, char** argv) 
{
///-----------------------------------------------------------------------------
///		PATH POR ARGUMENTO
///-----------------------------------------------------------------------------	
//	string path = argv[1];	
//	sistema_completo(path,true);
	
///-----------------------------------------------------------------------------
///		CARGA CONTINUA IMAGENES, PATH
///-----------------------------------------------------------------------------
//	load_images(path_calib, path_img, mask_path);
	
///-----------------------------------------------------------------------------
///		CAPTURA CONTINUA, GUARDAR IMAGENES
///-----------------------------------------------------------------------------	
//	VideoCapture c1("http://192.168.1.103:4747/mjpegfeed?640x480");
//	string path = "D:\\Facultad\\Proyecto\\Fotos\\11012018\\";
//	save_images(path, c1, 5);
	
///-----------------------------------------------------------------------------
///		TEST: TRIANGULACION E INTERSECCION
///-----------------------------------------------------------------------------	
//	interseccion_prueba();

///-----------------------------------------------------------------------------
///		TEST CHESSBOARD COMPLETO
///-----------------------------------------------------------------------------
//	prueba_chessboard("D:\\Facultad\\Proyecto\\Implementaciones\\C++\\Imagenes_Prueba\\Prueba_Completo\\Calib\\cam_2\\");
	prueba_chessboard("D:\\Facultad\\Proyecto\\Fotos\\11012018\\");
	
///-----------------------------------------------------------------------------
/// 	TEST FEATURES COMPLETO
///-----------------------------------------------------------------------------
//	Mat org = imread("D:\\Facultad\\Proyecto\\Fotos\\11012018\\cap_6.png",CV_LOAD_IMAGE_ANYCOLOR );
//	Mat org2 = imread("D:\\Facultad\\Proyecto\\Fotos\\11012018\\cap_5.png",CV_LOAD_IMAGE_ANYCOLOR );
//	
//	test_features_completo(org, org2);
	
///-----------------------------------------------------------------------------
//	fourier(img);
	
	waitKey(0);
	return 0;
} 
