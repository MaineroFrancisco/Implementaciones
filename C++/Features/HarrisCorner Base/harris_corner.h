#ifndef HARRIS_CORNER_H
#define HARRIS_CORNER_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
using namespace std;
using namespace cv;
///-------------------------------------------------------------------------
///Mascaras gaussianas para derivadas

/// el tamanio necesita variar si voy a jugar ocn multiples resoluciones de una misma foto, completar todo primero luego probar
// Dx
const Mat dx = (Mat_<float>(3, 3) << -1.0f, 0.0f, 1.0f,
				-1.0f,  0.0f,  1.0f,
				-1.0f,  0.0f,  1.0f);

//Dy
const Mat dy = (Mat_<float>(3, 3) << -1.0f, -1.0f, -1.0f,
				0.0f,  0.0f,  0.0f,
				1.0f,  1.0f,  1.0f);

///-------------------------------------------------------------------------

enum score_type {
	HARRIS_NOBEL,
	HARRIS_STEPHENS,
	SHI_TOMASI
};

///-------------------------------------------------------------------------
/// Funcion auxiliar para establecer ROI en las imagenes, 
/// controlando cuando se van de rango (Recorta el tamanio de la ROI)
///-------------------------------------------------------------------------
Mat format_roi(Mat img, Size vecindad, int x, int y )
{
	int pos_x, pos_y, nms_width, nms_height;
	
	if(x < vecindad.width/2)
	{
		nms_width = vecindad.width/2 + x;
		pos_x = 0;
	}
	else{
		if((x+vecindad.width/2) > (img.size().width-1))
		{
			nms_width = vecindad.width - ((x + vecindad.width/2) - (img.size().width-1));
			pos_x = x - vecindad.width/2;
		}
		else{
			nms_width = vecindad.width;
			pos_x = x - nms_width/2;
		}
	}
	
	if(y < vecindad.height/2)
	{
		nms_height = vecindad.height/2 + y;
		pos_y = 0;
	}
	else{
		if((y + vecindad.height/2) > (img.size().height-1))
		{
			nms_height = vecindad.height - ((y + vecindad.height/2) - (img.size().height-1));
			pos_y = y - vecindad.height/2;
		}
		else{
			nms_height = vecindad.height;
			pos_y = y - nms_height/2;
		}
	}
	
	return img(Rect(pos_x,pos_y,nms_width,nms_height));
}



/// vecindad -> para plicar non-maximal supression
Mat harris_score_image(Mat img, Size vecindad, Mat mask, score_type tipo = HARRIS_STEPHENS)
{
	/// Variables
	Size size_img = img.size();	//tamanio de la imagen
	
	Size s(3,3);				// tamanio de la ventana gaussiana
	double sigma = 1.5f;		// desvio de la ventana gaussiana
	
	double minVal, maxVal;
	double l1,l2;	// Autovalores para SHI_TOMASI
	
	Mat iDx, iDy, iDx2, iDy2, iDxDy;
	
	Mat corner_score = Mat::zeros(size_img,CV_32FC1);
	Mat det, trace, iDxDy2;
	
	Mat NMS, output;
	
	int nms_height, nms_width, pos_x, pos_y;
	
	img.convertTo(img, CV_32F);
	
	/// Calculo las derivadas
	
	//Calculate Dx
	filter2D(img, iDx,-1,dx,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	
	//Calculate Dx^2
	multiply(iDx, iDx,iDx2);
	
	//Calculate Dy
	filter2D(img, iDy,-1,dy,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	
	//Calculate Dy^2
	multiply(iDy, iDy,iDy2);
	
	//Calculate DxDy
	multiply(iDx, iDy,iDxDy);
	
	///-------------------------------------------------------------------------
	///Applying gaussian filter
	
	//Kernel Gaussiano de Integracion (Explicacion)
	/**/
	GaussianBlur(iDx2,iDx2,s,sigma,sigma);
	GaussianBlur(iDy2,iDy2,s,sigma,sigma);
	GaussianBlur(iDxDy,iDxDy,s,sigma,sigma);
	
	///-------------------------------------------------------------------------
	/// Calculo el puntaje para cada pixel de la imagen, mayor puntaje -> mejor feature
	
	/// Computing corner Score		|| Formula 1: det - k*(trace)^2		|| Formula 2: det / trace	|| Shi-Tomasi: min(Dx,Dy)
	switch(tipo){
		
	case HARRIS_NOBEL:
		// Calculate the Determinant
		multiply(iDxDy,iDxDy,iDxDy2);
		multiply(iDx2,iDy2,det);	
		subtract(det,iDxDy2,det);
		
		//Calculate the trace
		add(iDx2,iDy2,trace);
		
		divide(det,trace,corner_score);
		
		break;
	case SHI_TOMASI:
		/// MAL!! CALCULAR EIGENVALORES NO COMPARAR DIRECTAMENTE.. forma la matrix de 2x2 y sacalos
		// Calcular el Determinante
		multiply(iDxDy,iDxDy,iDxDy2);
		multiply(iDx2,iDy2,det);	
		subtract(det,iDxDy2,det);
		
		// Calcular la traza
		add(iDx2,iDy2,trace);	
		
		// Aplicar la resolvente para sacar los autovalores
		double b, c;
		for(int i=0;i<size_img.width;i++)
		{
			for(int j=0;j<size_img.height;j++) 
			{
				
				/// RECETA MAGICA DE INTERNER... REVISAR PORQUE PUTA ES ASI
				b = trace.at<float>(j,i);
				c = det.at<float>(j,i);
				l1 = b/2 + sqrt(b*b/4 - c);
				l2 = b/2 - sqrt(b*b/4 - c);
				
				corner_score.at<float>(j,i) = min(l1,l2);
			}
		}
		
		
		break;
	case HARRIS_STEPHENS:
		
		// Calculate the Determinant
		multiply(iDxDy,iDxDy,iDxDy2);
		multiply(iDx2,iDy2,det);	
		subtract(det,iDxDy2,det);
		
		//Calculate the trace
		add(iDx2,iDy2,trace);
		
		// Calculate Corner Score by "Formula 1"
		Scalar k(0.04);
		multiply(trace,trace, trace);
		multiply(trace,k,trace);
		subtract(det,trace,corner_score);	
		
		/// Cambiar rango de la imagen, 0 a Inf
		minMaxLoc(corner_score, &minVal, &maxVal);
		corner_score = corner_score + abs(minVal);
		
		break;
	}
	
	/// Non-Maximal Supression
	/// CAMBIANDO EL SIZE DE LA VECINDAD FILTRO LAS FEATURES CERCANAD
	for( int i = 0; i<size_img.width; i++)
	{
		for( int j = 0; j<size_img.height; j++)
		{	
			
			NMS = format_roi(corner_score,vecindad,i,j);
			
			minMaxLoc(NMS,&minVal,&maxVal);
			
			if (corner_score.at<float>(j,i) < maxVal)
			{
				corner_score.at<float>(j,i) = 0.0f;	
			}
		}
	}
	
	/// Mascara al final
	if(!mask.empty())
	{
		corner_score.copyTo(output,mask);
	}
	else
	{
		corner_score.copyTo(output);
	}
	
	///NORMALIZAR -> Rango final de la imagen: 0 a 1
	
	minMaxLoc(output, &minVal, &maxVal);	
	output = output/maxVal;
	
	return output;
	
}

///----------------------------------------------------------------------------

vector<Point2f> harris_threshold(Mat corner_score, int thresh = 100)
{
	Mat filtrada;
	Size corner_size = corner_score.size();
	
	vector<Point2f> features;
	
	corner_score.convertTo(corner_score, CV_8U,255);
	threshold(corner_score,filtrada,thresh,255,0);	// 0: thresh binario
	
	for(int i=0;i<corner_size.width;i++) 
	{
		for(int j=0;j<corner_size.height;j++) 
		{
			if(filtrada.at<unsigned char>(j,i) != 0)
			{
				features.push_back(Point2f(i,j));
			}
		}
	}
	
	return features;
}

#endif
