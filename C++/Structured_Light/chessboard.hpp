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
///		  -> RELACIONAR CON LOS PUNTOS DE REFERENCIA REALES	(PASADOS COMO PARAMETRO) ->  RESUELTO: EN REALIDAD SE HACE AL CALIBRAR CON LA PLANILLA
///		  -> PROBAR USARLA PARA CALIBRAR 1 CAMARA RESPECTA A LA CHESSBOARD PRIMERO, LUEGO 2 CAMARAS RESPECTO A LA CHESSBOARD VISTA AL MISMO TIEMPO,
///				Y FINALMENTE CALIBRAR SOLO PARAMETROS INTERNOS Y DEDUCIR LA POSICION DE LA CAMARAS RELATIVAS ENTRE SI (REQUIERE UNION CON FEATURES MAS COMPLEJA)

int dividir(vector<Point2f> &array, int start, int end) {
	int left;
	int right;
	Point2f pivote, temp;
	
	pivote = array[start];
	left = start;
	right = end;
	
	// Mientras no se cruzen los índices
	while (left < right) {
		while (norm(array[right]) > norm(pivote)) {
			right--;
		}
		
		while ((left < right) && (norm(array[left]) <= norm(pivote))) {
			left++;
		}
		
		// Si todavía no se cruzan los indices seguimos intercambiando
		if (left < right) {
			temp = array[left];
			array[left] = array[right];
			array[right] = temp;
		}
	}
	
	// Los índices ya se han cruzado, ponemos el pivot en el lugar que le corresponde
	temp = array[right];
	array[right] = array[start];
	array[start] = temp;
	
	// La nueva posición del pivot
	return right;
}

void quicksort_points(vector<Point2f> &array, int start, int end)
{
	int pivote;
	
	if(start < end)
	{
		pivote = dividir(array,start,end);
		
		quicksort_points(array, start, pivote-1);
		quicksort_points(array, pivote+1, end);
	}
}

vector<Point2f> chessboard_features(Mat img,Size grid_features, Size size_nms, float thresh, Mat mask)
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
		return features;
	}
	
	/// ASOCIO LAS FEATURES DESCUBIERTAS CON LOS PUNTOS DEL MUNDO REAL PASADOS COMO PARAMETROS.
	// Las posiciones vienen: de abajo para arriba, de izquierda a derecha, 
	//		en un solo vector alargado de tamanio de la grilla (grilla.x*grilla.y) 
	vector<Point2f> ordenado(grid_features.width * grid_features.height);
	vector<Point2f> linea;
	
	int indice;
	float dist;
	double cross, mag;
	Point2f o, aux_p,  p1, p2;	
	
	
	// Obtengo el origen
	dist = gris.rows;
	for(int i=0;i<features.size();i++) 
	{
		if(norm(features[i])<dist)
		{
			indice = i;
			dist = norm(features[i]);
		}
	}
	
	o = features[indice];	// Punto mas cercano al origen de la fotografia
	features[indice] = features[features.size()-1];		// Lo borro de features
	features.pop_back();
	
	// Obtengo linea mas izquierda
	indice = 0;
	for(int i=1;i<features.size();i++) 
	{
		p1 = features[i] - o;
		p2 = features[indice] - o;
		cross = p1.cross(p2);
		
		if(cross<0)
		{
			indice = i;
		}
		
	}
	
	aux_p = features[indice];
	features[indice] = features[features.size()-1];		// Elimino de las Features
	features.pop_back();
		
	// Saco puntos de la linea mas izquierda
	linea.push_back(o);
	linea.push_back(aux_p);
	for(int i=0;i<features.size();i++) 
	{
		p1 = aux_p - o;
		p2 = features[i] - o;
		
		cross = p1.cross(p2);	// Area paralelogramo
		mag = norm(p1);			// Base paralelogramo
		
		if(abs(cross/mag)<10.0f)
		{
			
			linea.push_back(features[i]);									// Agrego al arreglo para ordenar
			
			features[i] = features[features.size()-1];						// Elimino el punto de Features
			features.pop_back();
			
			i--;															// Corrigo posicion del arreglo
		}
	}
	
	/// REVISAR EL LARGO SEA EL CORRECTO (grid_features.height)
	
	// Ordeno lo anterior
	for(int i=0;i<linea.size();i++) 
	{
		linea[i] = linea[i] - o;	
	}
	
	quicksort_points(linea,0,linea.size()-1);
	
	for(int i=0;i<linea.size();i++) 
	{
		ordenado[i*grid_features.width] = linea[i] + o;	
	}

	linea.clear();
	//
	for(int i=0;i<grid_features.height;i++) 
	{
		
		// Obtengo linea mas derecha
		indice = 0;
		o = ordenado[i*grid_features.width];
		for(int j=0;j<features.size();j++) 
		{
			p1 = features[j] - o;
			p2 = features[indice] - o;
			cross = p1.cross(p2);
			
			if(cross>0)
			{
				indice = j;
			}
			
		}
		
		aux_p = features[indice];
		features[indice] = features[features.size()-1];		// Elimino de las Features
		features.pop_back();
		
		// Saco puntos de la linea mas derecha
		linea.push_back(o);
		linea.push_back(aux_p);
		for(int j=0;j<features.size();j++) 
		{
			p1 = aux_p - o;
			p2 = features[j] - o;
			
			cross = p1.cross(p2);	// Area paralelogramo
			mag = norm(p1);			// Base paralelogramo
			
			if(abs(cross/mag)<10.0f)
			{
				
				linea.push_back(features[j]);									// Agrego al arreglo para ordenar
				
				features[j] = features[features.size()-1];						// Elimino el punto de Features
				features.pop_back();
				
				j--;															// Corrigo posicion del arreglo
			}
		}
		
		
		// Ordeno lo anterior
		for(int j=0;j<grid_features.width;j++)
		{
			linea[j] = linea[j] - o;	
		}
		
		quicksort_points(linea,0,linea.size()-1);
		
		for(int j=0;j<grid_features.width;j++) 
		{
			ordenado[i*grid_features.width + j] = linea[j] + o;	
		}
		
		linea.clear();
	}
	
	
	///
//	Mat copy = img.clone();
//	for(int i=0;i<ordenado.size();i++) 
//	{
//		circle(copy,ordenado[i],5,Scalar(0,255,0));
//		show_mat(copy,IMAGEN,0);
//		waitKey(0);
//	}
//	
//	line(copy,o,izq,Scalar(0,255,0));
//	line(copy,o,der,Scalar(0,255,0));
	
	
//	circle(img,izq,5,Scalar(0,255,0));
//	line(img,o,izq,Scalar(0,255,0));
	
	///
	return ordenado;
	
}
#endif

/// REVISAR SIFT DENUEVO, HABIA UN NORM() AL REVES! POR ESO ESTABA DADO VUELTA.
