#ifndef HARRIS_CORNER_H
#define HARRIS_CORNER_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "features.hpp"

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

#define PI 3.14159265

///-----------------------------------------------------------------------------
const Mat checkb_mask = (Mat_<float>(11,11) <<  
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

const Mat checkb_mask_ops = (Mat_<float>(11,11) <<  
					
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

///-----------------------------------------------------------------------------
///
///Laburar en Radianes
Mat rotate_mask(Mat mask, double angle)
{
	Size s = mask.size();
	
	Point2f center( s.width/2, s.height/2);
	
	Mat R(2,3,CV_32F);
	
	R.at<float>(0,0) = cos(angle*PI/180.0f);
	R.at<float>(1,0) = -sin(angle*PI/180.0f);

	R.at<float>(0,1) = sin(angle*PI/180.0f);
	R.at<float>(1,1) = cos(angle*PI/180.0f);

	R.at<float>(0,2) = (1-cos(angle*PI/180.0f))*center.x - sin(angle*PI/180.0f)* center.y;
	R.at<float>(1,2) = sin(angle*PI/180.0f)*center.x + (1-cos(angle*PI/180.0f))* center.y;
	
	Mat output;
	warpAffine(mask,output,R,s);
	
	return output;
}

///
//		4*1
///FALTA! -> AJUSTAR EL THRESHOLD DINAMICO HASTA ENCONTRAR LA CANTIDAD DE PUNTOS DE LA CHESSBOARD O LOS MAS POSIBLES (POSIBLEMENTE DEDUCIR EL RESTO
///		  -> RELACIONAR CON LOS PUNTOS DE REFERENCIA REALES	(PASADOS COMO PARAMETRO)
///		  -> PROBAR USARLA PARA CALIBRAR 1 CAMARA RESPECTA A LA CHESSBOARD PRIMERO, LUEGO 2 CAMARAS RESPECTO A LA CHESSBOARD VISTA AL MISMO TIEMPO,
///				Y FINALMENTE CALIBRAR SOLO PARAMETROS INTERNOS Y DEDUCIR LA POSICION DE LA CAMARAS RELATIVAS ENTRE SI (REQUIERE UNION CON FEATURES MAS COMPLEJA)
vector<Point2f> chessboard_features(Mat img,Size grid_features, Size size_nms, float thresh, Mat mask)
//vector<Mat> chessboard_features(Mat img,Size grid_features, vector<Point2f> obj_position, Size size_nms, int thresh, Mat mask)
{
	Mat gris, feature, r1, r2;
	Mat diff;
	Mat msk1, msk2;
	Point2f center;
	vector<Point2f> features;
	vector<Mat> chessboard_f;
	
	double angle, best_angle = -1.0f, const_thresh = 0.70 ;
	int cant_features;
	
	cvtColor(img,gris,CV_BGR2GRAY);
//	if(mask.empty())
//	{
	feature = harris_score_image(gris, size_nms, mask, SHI_TOMASI);
//	}
//	else
//	{
//		feature = harris_corner_score(gris,size_nms,HARRIS_NOBEL);
//	}
	
	///
	features = harris_threshold(feature, thresh);	/// THRESH ENTER 0 Y 10000
	
	///
	angle=0.0f;
//	Scalar media_global = mean(gris);
	
	///EXTRA AUX VARS, BORRAR LUEGO, SON SOLO PARA PROBAR COSAS
	double minVal, maxVal;
	
	threshold(gris,gris,mean(gris).val[0],255,CV_THRESH_BINARY);
	
	while(angle<90.0f)
	{
		msk1 = rotate_mask(checkb_mask,angle);
		msk2 = rotate_mask(checkb_mask_ops,angle);
		
		filter2D(gris,r1,CV_32FC1,msk1);
		filter2D(gris,r2,CV_32FC1,msk2);
		
		normalize(r1,r1,0,1,cv::NORM_MINMAX);
		normalize(r2,r2,0,1,cv::NORM_MINMAX);
		
		diff = r1-r2;
		diff = abs(diff);
		
		threshold(diff,diff,const_thresh,1.0f,CV_THRESH_BINARY);
		
		cant_features = 0;
		for(int i=0;i<features.size();i++) 
		{
			center = features[i];
			
			if(diff.at<float>(center.y,center.x) == 1.0f)
			{
				cant_features++;
			}
			
		}
		
		if(cant_features == (grid_features.width*grid_features.height))
		{
			best_angle = angle;
			break;
		}
		
		angle+=15.0f;
		
	}
	
	/// SI NO ENCONTRO TODOS LOS PUNTOS DE LA GRILLA, DEVUELVE UN VECTOR VACIO, ERA MUY COSTOSO UN THRESH ADAPTATIVO
	if(best_angle != -1.0f)
	{
		
		for(int i=0;i<features.size();i++) 
		{
			center = features[i];
			
			if(diff.at<float>(center.y,center.x) != 1.0f)
			{
				features[i] = features[features.size()-1];
				features.pop_back();
				i--;
			}
			
		}
		
	}
	else
	{
		features.clear();
	}
	
	/// ASOCIO LAS FEATURES DESCUBIERTAS CON LOS PUNTOS DEL MUNDO REAL PASADOS COMO PARAMETROS.
	// Las posiciones vienen: de abajo para arriba, de izquierda a derecha, 
	//		en un solo vector alargado de tamanio de la grilla (grilla.x*grilla.y) 
	
	
	
	return features;
	
}
#endif



/// REVISAR SIFT DENUEVO, HABIA UN NORM() AL REVES! POR ESO ESTABA DADO VUELTA.
