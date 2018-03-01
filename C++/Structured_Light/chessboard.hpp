#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "features.hpp"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

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
	
	R.at<float>(0,0) = cos(angle*CV_PI/180.0f);
	R.at<float>(1,0) = -sin(angle*CV_PI/180.0f);

	R.at<float>(0,1) = sin(angle*CV_PI/180.0f);
	R.at<float>(1,1) = cos(angle*CV_PI/180.0f);

	R.at<float>(0,2) = (1-cos(angle*CV_PI/180.0f))*center.x - sin(angle*CV_PI/180.0f)* center.y;
	R.at<float>(1,2) = sin(angle*CV_PI/180.0f)*center.x + (1-cos(angle*CV_PI/180.0f))* center.y;
	
	Mat output;
	warpAffine(mask,output,R,s);
	
	return output;
}

///
///		  -> RELACIONAR CON LOS PUNTOS DE REFERENCIA REALES	(PASADOS COMO PARAMETRO) ->  RESUELTO: EN REALIDAD SE HACE AL CALIBRAR CON LA PLANILLA
///		  -> PROBAR USARLA PARA CALIBRAR 1 CAMARA RESPECTA A LA CHESSBOARD PRIMERO, LUEGO 2 CAMARAS RESPECTO A LA CHESSBOARD VISTA AL MISMO TIEMPO,
///				Y FINALMENTE CALIBRAR SOLO PARAMETROS INTERNOS Y DEDUCIR LA POSICION DE LA CAMARAS RELATIVAS ENTRE SI (REQUIERE UNION CON FEATURES MAS COMPLEJA)

int leftmost_rightmost(vector<Point2f> &features, int indice_o, bool left_right)
{
	Point2f p1,p2;
	double cross;
	
//	int indice = (indice_o)? 0 : 1;
	int indice;
	for(int i=0;i<features.size();i++) 
	{
		
		if(features[i].x != -1 && i != indice_o)
		{
			indice = i;
		}
	}
	
	// Obtengo linea mas Derecha
	for(int i=0;i<features.size();i++) 
	{
		if(i == indice || i == indice_o || features[i].x == -1) continue;
		
		p1 = features[i] - features[indice_o];
		p2 = features[indice] - features[indice_o];
		cross = p1.cross(p2);
		
//		cout<<"Indice: "<< indice<<" "<< i <<endl;
//		cout<<"Cross: "<< cross<<endl;
		// verdadero = left | falso = right
		if( (left_right && cross<0)  ||  (!left_right && cross>0) )
		{
			indice = i;
		}
	}
	
	return indice;
}

vector<int> get_lined_points(vector<Point2f> &features, int indice_o, int indice, bool b =false)
{
	vector<int> ind;
	Point2f p1, p2;
	double cross, mag;
	
	Point2f o = features[indice_o];
	Point2f in = features[indice];
	
	for(int i=0;i<features.size();i++) 
	{
		if(features[i].x == -1.0f) continue;
		p1 = in - o;
		p2 = features[i] - o;
		
		cross = p1.cross(p2);	// Area paralelogramo
		mag = norm(p1);			// Base paralelogramo
		
		if(abs(cross/mag)<10.0f)
		{
			ind.push_back(i);									// Agrego al arreglo para ordenar
		}
	}
//	
//	if(b)
//	{
//		Mat copy=Mat::zeros(480, 640,CV_8UC3);
//		for(int i=0;i<ind.size();i++) 
//		{
//			circle(copy,features[ind[i]],5,Scalar(0,255,0));
//			circle(copy,o,5,Scalar(0,0,255));
//	//		line(copy,o,in,Scalar(255));
//	//		line(copy,o,features[i],Scalar(255));
//		}
//		show_mat(copy,IMAGEN,0);
//		waitKey(0);
//	} 
//	
	return ind;
}

int dividir(vector<Point2f> &array, vector<int> &indices, int indice_o, int start, int end) 
{
	int left, right, temp;
	Point2f pivote;
	
	pivote = array[indices[start]] - array[indice_o];
	left = start;
	right = end;
	
	// Mientras no se cruzen los índices
	while (left < right) {
		while (norm(array[ indices[right] ] - array[indice_o] ) > norm(pivote)) 
		{
			right--;
		}
		
		while ((left < right) && (norm(array[ indices[left] ] - array[indice_o]) <= norm(pivote))) 
		{
			left++;
		}
		
		// Si todavía no se cruzan los indices seguimos intercambiando
		if (left < right) 
		{
//			temp = array[left];
//			array[left] = array[right];
//			array[right] = temp;
			temp = indices[left];
			indices[left] = indices[right];
			indices[right] = temp;
		}
	}
	
	// Los índices ya se han cruzado, ponemos el pivot en el lugar que le corresponde
//	temp = array[right];
//	array[right] = array[start];
//	array[start] = temp;
	temp = indices[right];
	indices[right] = indices[start];
	indices[start] = temp;
	
	// La nueva posición del pivot
	return right;
}

void quicksort_points(vector<Point2f> &array, vector<int> &indices, int indice_o, int start, int end)
{
	int pivote;
	
	if(start < end)
	{
		pivote = dividir(array, indices, indice_o, start,end);
		
		quicksort_points(array, indices, indice_o, start, pivote-1);
		quicksort_points(array, indices, indice_o, pivote+1, end);
	}
}


void eliminar_ordenados(vector<Point2f> &features)
{
	int i = 0, k = features.size() - 1;
	while(i<features.size()) 
	{
		if(features[i].x == -1.0f)
		{
			if(features[k].x != -1.0f)
			{
				features[i] = features[k];
			}
			else
			{
				i--;
			}
			
			features.pop_back();
			k--;
		}
		
		i++;
	}
}

///
vector<Point2f> chessboard_features_fix(Mat img,Size grid_features, Size size_nms, float thresh, Mat mask)
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
	
	feature = harris_score_image(gris, size_nms, mask, SHI_TOMASI);
	///
	features = harris_threshold(feature, thresh);	/// THRESH ENTER 0 Y 10000
	
	///
	angle=0.0f;
	
	///EXTRA AUX VARS, BORRAR LUEGO, SON SOLO PARA PROBAR COSAS
	double minVal, maxVal;
	
	threshold(gris,gris,mean(gris).val[0],255,CV_THRESH_BINARY);
	bitwise_and(gris,mask,gris);
	
	while(angle<45.0f)
	{
		msk1 = rotate_mask(checkb_mask,angle);
		msk2 = rotate_mask(checkb_mask_ops,angle);
		
		filter2D(gris,r1,CV_32FC1,msk1);
		filter2D(gris,r2,CV_32FC1,msk2);
		
		normalize(r1,r1,0,1,cv::NORM_MINMAX);
		normalize(r2,r2,0,1,cv::NORM_MINMAX);
		
		diff = r1-r2;
		diff = abs(diff);
		normalize(diff,diff,0,1,cv::NORM_MINMAX);
		
		threshold(diff,diff,const_thresh,1.0f,CV_THRESH_BINARY);
		
		//		show_mat(r1,IMAGEN,0);
		//		show_mat(r2,IMAGEN,1);
		//		show_mat(diff,IMAGEN,2);
		//		waitKey(0);
		
		cant_features = 0;
//		vector<Point2f> aux_p;
		for(int i=0;i<features.size();i++) 
		{
			center = features[i];
			
			if(diff.at<float>(center.y,center.x) == 1.0f)
			{
//				aux_p.push_back(features[i]);
				cant_features++;
			}
			
		}
		
//			Mat copy;
//			copy = img.clone();
//			for(int i=0;i<aux_p.size();i++) 
//			{
//				circle(copy,aux_p[i],5,Scalar(0,255,0));
//			}
//			show_mat(copy,IMAGEN,0);
//			waitKey(0);
		
		if(cant_features == (grid_features.width*grid_features.height))
		{
			best_angle = angle;
			break;
		}
		
		angle+=5.0f;
		
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
	
	/// ASOCIO LAS FEATURES DESCUBIERTAS SEGUN EL TAMANIO DE LA GRILLA
	// Las posiciones deben terminar: de abajo para arriba, de izquierda a derecha, 
	//		en un solo vector alargado de tamanio de la grilla (grilla.x*grilla.y) 
	
	//Elijo feature mas cercana a 0,0
	vector<int> ind, aux;
	Point2f o, p1, p2;
	
	double cross;
	int indice_o = 0, indice;
	
	for(int i=1;i<features.size();i++) 
	{  
		if(norm(features[i]) < norm(features[indice_o]))
		{
			indice_o = i;
		}
	}
	
	o = features[indice_o];
	
	// Obtengo linea mas Derecha
	indice = leftmost_rightmost(features, indice_o, 0);
	
	// Obtengo los puntos sobre esta linea
	ind = get_lined_points(features, indice_o, indice);
	
	if(ind.size() != grid_features.width)
	{
		features.clear();
		return features;
	}
	
	int leftmost = ind[0];
	for(int i=1;i<ind.size();i++)
	{
		if(features[ind[i]].x < features[leftmost].x)
		{
			leftmost = ind[i];
		}
	}
	
	// Obtengo el verdadero origen de la fotografia
	indice_o = leftmost;
	o = features[leftmost];
	
	// Busco linea mas Izquierda 
	indice = leftmost_rightmost(features, indice_o, 1);
	
	// Obtengo los puntos de esta linea
	ind = get_lined_points(features, indice_o, indice, 1);
	
	/// REVISAR EL LARGO SEA EL CORRECTO (grid_features.height)
	if (ind.size() != grid_features.height) 
	{
		features.clear();
		return features;
	}
	
	// Ordeno lo anterior
	quicksort_points(features, ind, indice_o, 0 ,ind.size()-1);
	
	vector<Point2f> ordenado(grid_features.width*grid_features.height);
	for(int i=0;i<ind.size();i++) 
	{
		ordenado[i*grid_features.width] = features[ind[i]];	
	}
	
	// Voy fila por fila, acorde a los nodos de la linea mas izquierda, y guardo en el arreglo en orden
	for(int i=0;i<grid_features.height;i++) 
	{
		// Obtengo linea mas derecha
		indice_o = ind[i];
		indice = leftmost_rightmost(features, indice_o, 0);
		
//		aux_p = features[indice];
//		features[indice] = features[features.size()-1];		// Elimino de las Features
//		features.pop_back();
//		
		// Saco puntos de la linea mas derecha
		
		aux = get_lined_points(features, indice_o, indice);	// TENGO QUE ELIMINAR LOS -1	
		
		// Chequeo si tiene el tamanio correspondiente
		if(aux.size() != grid_features.width)
		{
			
			cout<< "error aux_size: "<<aux.size()<<" fila: "<<i<<endl;
			features.clear();
			return features;
		}
		
		// Ordeno lo anterior
		quicksort_points(features, aux, indice_o, 0, aux.size()-1);
		
		for(int j=0;j<grid_features.width;j++) 
		{
			ordenado[i*grid_features.width + j] = features[aux[j]];	
		}
		
		// Elimino esa linea de features
		for(int j=0;j<aux.size();j++) 
		{
			// MARCO PARA ELIMINAR
			features[aux[j]].x = -1.0f;
		}
		
//		eliminar_ordenados(features);
		aux.clear();
//		
//		Mat copy = img.clone();
//		for(int i=0;i<features.size();i++) 
//		{
//			circle(copy,features[i],5,Scalar(0,255,0));
//		}
//		
//		//		line(img,features[indice_o], features[indice],Scalar(0,255,0));
//		show_mat(copy,IMAGEN,0);
//		waitKey(0);		
		
	}
	
	///
	return ordenado;
}

/// REVISAR SIFT DENUEVO, HABIA UN NORM() AL REVES! POR ESO ESTABA DADO VUELTA.
#endif
