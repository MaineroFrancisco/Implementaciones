#ifndef FEATURES_H
#define FEATURES_H

#include "auxiliares.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <ctime>

using namespace std;
using namespace cv;
///-------------------------------------------------------------------------
///Mascaras gaussianas para derivadas (Prewitt)

/// el tamanio necesita variar si voy a jugar Con multiples resoluciones de una misma foto, completar todo primero luego probar
/// Probar otras mascaras (Ej.: Sobel) 

/// SOBEL
// Dx
const Mat dx = (Mat_<float>(3, 3) << -1.0f, 0.0f, 1.0f,
				-2.0f,  0.0f,  2.0f,
				-1.0f,  0.0f,  1.0f);

//Dy
const Mat dy = (Mat_<float>(3, 3) << -1.0f, -2.0f, -1.0f,
				0.0f,  0.0f,  0.0f,
				1.0f,  2.0f,  1.0f);

///// PREWIT
//// Dx
//const Mat dx = (Mat_<float>(3, 3) << -1.0f, 0.0f, 1.0f,
//				-1.0f,  0.0f,  1.0f,
//				-1.0f,  0.0f,  1.0f);
//
////Dy
//const Mat dy = (Mat_<float>(3, 3) << -1.0f, -1.0f, -1.0f,
//				0.0f,  0.0f,  0.0f,
//				1.0f,  1.0f,  1.0f);

/// NORMAL
//// Dx
//const Mat dx = (Mat_<float>(1, 3) << -1.0f, 0.0f, 1.0f);
////Dy
//const Mat dy = (Mat_<float>(3, 1) << -1.0f, 0.0f, 1.0f);

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

///-----------------------------------------------------------------------------
/// Feature Detection
///-----------------------------------------------------------------------------

/// vecindad -> para plicar non-maximal supression
Mat harris_score_image(Mat img, Size vecindad, Mat mask, score_type tipo = HARRIS_STEPHENS)
{
	/// Variables
	Size size_img = img.size();	//tamanio de la imagen
	
	Size s = vecindad;				// tamanio de la ventana gaussiana
	
//	double sigma = 1.5f;		// desvio de la ventana gaussiana
	double sigma = 0.5f;		///Analizar el cambio del desvio para reducir problema de punto cercanos...
	
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
	filter2D(img, iDx,-1,dx,cv::Point(-1,-1), 0, cv::BORDER_REPLICATE);
	
	//Calculate Dx^2
	multiply(iDx, iDx,iDx2);
	
	//Calculate Dy
	filter2D(img, iDy,-1,dy,cv::Point(-1,-1), 0, cv::BORDER_REPLICATE);
	
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
		
		// Calculate Corner Score by "HARRIS_STEPHENS formula"
		Scalar k(0.04);
		pow(trace,2,trace);
		multiply(trace,k,trace);
		subtract(det,trace,corner_score);	
		
//		//Eliminar negativas
//		filtro = corner_score > 0;
//		corner_score.copyTo(filtro,filtro);
//		
//		corner_score = filtro;
//		minMaxLoc(corner_score,&minVal,&maxVal);
//		cout<< minVal<<" "<< maxVal;
//		
//		imshow("filtrada", corner_score);
//		waitKey(0);
	}
	
	/// Non-Maximal Supression
	/// CAMBIANDO EL SIZE DE LA VECINDAD FILTRO LAS FEATURES CERCANAS
	
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
	normalize(output,output,0,1,cv::NORM_MINMAX);
	
	return output;
	
}

///-----------------------------------------------------------------------------
/// DEFINIR PROFUNDIDAD DE BITS PARA FILTRAR, TRABAJAR TODO EN FLOTANTES? 
// DE LA ORIENTACION SE ENCARGA XCLUSIVAMENTE EL DESCRIPTOR... PUEDE HABER MAS DE UN DESCRIPTOR POR FEATURE
vector<Point2f> harris_threshold(Mat corner_score, float thresh = 100.0f)
{
	Mat filtrada, sin_modificar = corner_score.clone();
	Size corner_size = corner_score.size();
	
	vector<Point2f> features;
	
//	sin_modificar.convertTo(sin_modificar, CV_16U,65535);
	normalize(sin_modificar,sin_modificar, 0, 10000,cv::NORM_MINMAX);
	filtrada = sin_modificar > thresh;	// imagen binaria (unsigned char 0 a 255)

//	corner_score.convertTo(corner_score, CV_8U,255);
//	threshold(corner_score,filtrada,thresh,255,0);	// 0: thresh binario
	
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
	
//	normalize(corner_score,corner_score,1,0,cv::NORM_MINMAX);
//	show_mat(corner_score,IMAGEN,0);
//	waitKey(0);
	
	return features;
}

///-----------------------------------------------------------------------------
/// Feature Descriptors
///-----------------------------------------------------------------------------

struct descriptor
{
	Point2f pos_feature;
	vector<float> orientation;
	
	vector<Mat> HOG;	//Mat::zeros(128,1)
};

//gris -> imagen grayscale;
vector<descriptor> generate_descriptor(Mat gris, vector<Point2f> features)
{
	vector<descriptor> desc_f;
	Mat iDx, iDy;
	
	gris.convertTo(gris, CV_32F);
	
	/// Calculo las derivadas
	
	//Calculate Dx
	filter2D(gris, iDx,-1,dx,cv::Point(-1,-1), 0, cv::BORDER_REPLICATE);
	
	//Calculate Dy
	filter2D(gris, iDy,-1,dy,cv::Point(-1,-1), 0, cv::BORDER_REPLICATE);
	
	double minVal,maxVal;

//	double desvio = 1.6f;
//
//	GaussianBlur(iDx,iDx,Size(),desvio,desvio);
//	GaussianBlur(iDy,iDy,Size(),desvio,desvio);
	
	Mat m, phi;

	// Calculate gradient magnitude and direction (in degrees)
	cartToPolar(iDx, iDy, m, phi, 1); 
	
	/// Histogram of Oriented Gradients - HOG
	// Caracteristicas - por feature: ventanas de 16x16, divididas en regiones de 4x4 para calcular HOG -> 16 regiones (4x4) de 8 bin cada una 
	//				-> vector de 12 elementos para analizar todo -> las orientaciones deben ser relativas a la orientacion general de la feature
	
	Point2f centro_f;
	Size grad_window(4,4);		// tamanio subregion HOG para las features
	Mat hog_p, hog_m;
	
	vector<descriptor> features_descrp;
	descriptor temp;
	Mat f_pendiente, f_orient, f_hist = Mat::zeros(36,1,CV_32F), d_hist;
	
	// 0 a 360? o 0 a 180? 8 bins, tomo de 0 a 360, se pule despues, de a 45 grados.  
	float pos, factor, in_pos, h_1, h, h_m1, orientation;
	
	Mat gauss_x, gauss_y, gauss;
	///Aplico gaussiana a las pendientes, para reducir la contribuccion de pixeles lejanos a las features
	gauss_y = getGaussianKernel(9, 1.6f, CV_32F );
	transpose(gauss_y,gauss_x);
	
	gauss = gauss_y*gauss_x;
	normalize(gauss,gauss,0,1,cv::NORM_MINMAX);
	
	for(int f=0;f<features.size();f++)
	{
		
		/// CALCULAR ORIENTACION DE LA FEATURE
		/// DOS ENFOQUES PARA ENCONTRAR LA ORIENTACION DE LA FEATURE:
		///			ANALISIS DEL HISTOGRAMA (HECHO)
		///			EXTRACCION DE EIGENVECTORES DE LA MATRIZ DE HARRIS (PROBAR)
		
		/// Controles de tamanio para las ventanas
		if((features[f].x-8)<0 || (features[f].x+8)>gris.cols || (features[f].y-8)<0 || (features[f].y+8)>gris.rows )
		{
			continue;
		}
		
		// ventana orientacion general ( 9 x 9 )
		// ventana mas chica centrada en al feature, histograma de gradientes a toda la region, normalizar, tomar los valores mas alto como orientacion para descriptores ( puede salir mas de 1 )
		f_pendiente = m(Rect(features[f].x-5,features[f].y-5,9,9)).clone();
		f_orient = phi(Rect(features[f].x-5,features[f].y-5,9,9)).clone();
		
		multiply(f_pendiente,gauss,f_pendiente);
		
		// Histograma
		// n_bin para el histograma general:  36, mas preciso.
		for(int i=0;i<9;i++) 
		{
			for(int j=0;j<9;j++) 
			{  
				pos = f_orient.at<float>(j,i)/10.0f;	// Deduzco posicion dentro del histograma segun su orientacion (angulo)
				factor = modf(pos, &in_pos);		// La descompongo en parte entera y parte decimal
				
				if(factor > 0.05f)		// reviso si existe efectivamente parte decimal, threshold de 0.01 por las dudas, evitar problemas de exactitud
				{
					// De existir parte decimal descompongo la contribucion de la pendiente de ese punto al histograma segun la diferencia para las dos columnas a las que pertenesca
					f_hist.at<float>(in_pos) += f_pendiente.at<float>(j,i)*(1-factor);			///Esto falla si hay angulos negativos, no deberia, cartToPolar devuelve el angulo entre 0 a 360
					if(in_pos < 35)
					{
						f_hist.at<float>( in_pos+1 ) += f_pendiente.at<float>(j,i)*factor;
					}
					else
					{
						f_hist.at<float>(0) += f_pendiente.at<float>(j,i)*factor;
					}
				}
				else
				{
					f_hist.at<float>(in_pos) += f_pendiente.at<float>(j,i);
				}
			}
		}
		
		// Hallar maximo del histograma
		float max = 0;
		for(int i=0;i<36;i++) 
		{
			if(f_hist.at<float>(i)>max)
			{
				max = f_hist.at<float>(i);
			}
		}
		
		///Falta inicializar cosas
		/// Construir descriptor 
		temp.pos_feature = features[f];
		
//		///PLOT
//		histograma(f_hist,36);
//		waitKey(0);
//		
		// Suavizado del histograma? figuraba en la documentacion, no estoy seguro porque o como
		
		// Extraccion de direccion dominante
		float t = 0.8f; // factor de referencia sobre el histograma
		for(int i=1;i<36;i++) 
		{
			h_1 = f_hist.at<float>(i-1);
			h = f_hist.at<float>(i);
			if(i < 35)
			{
				h_m1 = f_hist.at<float>(i+1);
			}
			else
			{
				h_m1 = f_hist.at<float>(0);
			}
			
			/// PUEDE HABER MAS DE UN DESCRIPTOR POR FEATURE, PUEDE SER NECESARIO UN ID DE FEATURE, O SE PUEDE DEDUCIR DE LA POSICION
			if(h > h_m1 && h > h_1 && h>t*max)	// los bins siguiente y anterior son mas chicos (es decir es un pico en el histograma), y su magnitud es t veces la maxima (threshold) -> es una orientacion valida para un descriptor 
			{
				/// Interpolar correcta orientacion -> Almacenada en grados
				// (i*10) = angulo representado en el histograma,  (CV_PI/n_bins) -> factor de interpolacion (REVISAR DE DONDE SALE, APUNTE NO DICE),	resto -> interpolacion valores de pendiente acumulados en el histograma;
				orientation = (i*10) + (CV_PI/36) * ((h_1 - h_m1) / (h_1 - 2*h + h_m1)) ;
				temp.orientation.push_back(orientation);
				
				/// Definir HOG
				// ORIENTAR LA IMAGEN SEGUN LA ORIENTACION GENERAL DE LA FEATURE, ASI OBTENER LA ROI CORRECTAMENTE
				Mat rot_p, rot_m, m_rot;
				
				m_rot = getRotationMatrix2D(features[f], orientation, 1);
				
				warpAffine(phi, rot_p, m_rot,phi.size());
				warpAffine(m, rot_m, m_rot, m.size());
				
				d_hist = Mat::zeros(16*8,1,CV_32F);
				for(int reg=0;reg<16;reg++) 
				{
					// Ventana total de la feature (16 x 16)
					centro_f = features[f];
					centro_f.x = centro_f.x-8;
					centro_f.y = centro_f.y-8;
					
					
					centro_f.x = centro_f.x + 4*(reg%4);
					centro_f.y = centro_f.y + 4*(reg/4);
					
					/// ACA ME MUEVO EN LA REGION
					// Subventanas de la feature, regiones para HOG (4 x 4)
					// angulo
					hog_p = rot_p(Rect(centro_f.x, centro_f.y, grad_window.width, grad_window.height));
					
					for(int i=0;i<hog_p.cols;i++) 
					{
						for(int j=0;j<hog_p.rows;j++) 
						{
							hog_p.at<float>(j,i) -= orientation;
							if(hog_p.at<float>(j,i)<0)
							{
								hog_p.at<float>(j,i) += 360;
							}
						}
					}
					
					//pendiente
					hog_m = rot_m(Rect(centro_f.x, centro_f.y, grad_window.width, grad_window.height));
					
					for(int j=0;j<4;j++) 
					{
						for(int k=0;k<4;k++) 
						{
							pos = hog_p.at<float>(k,j)/45.0f;
							factor = modf(pos, &in_pos);
							
							if(factor > 0.05f)
							{
								d_hist.at<float>(reg*8 + in_pos) += hog_m.at<float>(k,j)*(1-factor);
								if(in_pos < 7)
								{
									d_hist.at<float>(reg*8 + in_pos + 1) += hog_m.at<float>(k,j)*factor;
								}
								else
								{
									d_hist.at<float>(reg*8) += hog_m.at<float>(k,j)*factor;
								}
							}
							else
							{
								d_hist.at<float>(reg*8 + in_pos) += hog_m.at<float>(k,j);
							}
						}
					}
				}
				
				/// NORMALIZAR PARA MATCHEAR DESPUES -> reduce problemas por iluminacion
				normalize(d_hist,d_hist,0,1,cv::NORM_MINMAX);
				
//				d_hist.convertTo(d_hist,CV_8UC1,255.0f);
				temp.HOG.push_back(d_hist.clone());
				
//				/// PLOTEO
//				show_hog(gris,temp.pos_feature,temp.orientation, temp.HOG[temp.HOG.size()-1]);
//				waitKey(0);
				
				/// Almacenar descriptor
			}
		}
		
		features_descrp.push_back(temp);
		
		/// LIMPIAR VARIABLE AUXILIAR
		temp.orientation.clear();
		temp.HOG.clear();
		
		f_hist = Mat::zeros(36,1,CV_32F);
		
	}
	
	return features_descrp;
}

/// Matching Featurse

/// PROBAR CON OTRAS COSAS, PUEDE SER QUE LAS IMAGENES DE POR SI SEAN MUY CHOTAS... REVISAR COMO DESCARTAR FEATURES ...
//vector<Mat> feature_matching(vector<descriptor> d, vector<descriptor> d2)
vector<Mat> feature_matching(vector<descriptor> d, vector<descriptor> d2, float relative_thresh = 0.6f, float thresh_ransac=40.0f)
{
	Mat diff;
	float mag;
	vector<Mat> vm;	// Mat4f
	
	float min_dist, scd_min;
	int prim_cerc = 0, seg_cerc = 0, pri_d_hist = 0, seg_d_hist = 0, pri_d2_hist = 0, seg_d2_hist = 0;
//	float absolute_thresh = 250;
//	float relative_thresh = 0.6;
	
	for(int i=0;i<d.size();i++) 
	{
		min_dist = FLT_MAX; scd_min = FLT_MAX;
		for(int j=0;j<d2.size();j++) 
		{
			/// Buscar en d2, los dos mas proximos a d, limitado por thresholds
			
			for(int k=0;k<d[i].HOG.size();k++) 
			{
				for(int l=0;l<d2[j].HOG.size();l++) 
				{
					////				
					Mat b1 = Mat::zeros(128,1,CV_32FC1);
					d[i].HOG[k].copyTo(b1);
					
//					Mat b1 = Mat::zeros(130,1,CV_32F);
////					b1.at<float>(0) = d[i].pos_feature.x/640.0f;
////					b1.at<float>(1) = d[i].pos_feature.y/480.0f;
//					b1.at<float>(0) = d[i].pos_feature.x;
//					b1.at<float>(1) = d[i].pos_feature.y;
//					d[i].HOG[k].copyTo(b1(Rect(0,2,1,128)));
					
					
					Mat b2 = Mat::zeros(128,1,CV_32FC1);
					d2[j].HOG[l].copyTo(b2);
					
//					Mat b2 = Mat::zeros(130,1,CV_32F);
////					b2.at<float>(0) = d2[j].pos_feature.x/640.0f;
////					b2.at<float>(1) = d2[j].pos_feature.y/480.0f;
//					b2.at<float>(0) = d2[j].pos_feature.x;
//					b2.at<float>(1) = d2[j].pos_feature.y;
//					d2[j].HOG[l].copyTo(b2(Rect(0,2,1,128)));
					
					diff = b1 - b2;					
					mag = norm(diff);
//					mag = mag*mag;
					
//					pow(diff,2,diff);
//					mag = sum(diff).val[0];
					
					if(mag < min_dist)
					{
						scd_min = min_dist;
						min_dist = mag;
						prim_cerc = j;
					}
					else
					{
//						if(mag < scd_min && mag!=min_dist)
						if(mag < scd_min)
						{
							scd_min = mag;
						}
					}
				}	
			}
		}
		
		if(min_dist/scd_min < relative_thresh)
		{			
			
			Mat m(4,1,CV_32F);
			m.at<float>(0) = d[i].pos_feature.x;
			m.at<float>(1) = d[i].pos_feature.y;
			m.at<float>(2) = d2[prim_cerc].pos_feature.x;
			m.at<float>(3) = d2[prim_cerc].pos_feature.y;
			vm.push_back(m.clone());
		}
		
	}

//////	cout<<"ANTES RANSAC: "<< vm.size()<<endl;
//////	///FALTA VALIDACION DE FEATURES, RANSAC, CORREGIR...
//////	// Elegir K features random de las matcheadas
//////	// Calcular homografia entre imagenes
//////	// contar cuantas features matchadas se corresponden con algun criterio al mapeo de esa homografia
//////	// repetir proceso L veces, buscando la mayor cantidad de matches
//////	// Deshacerme de las features que no se mapearon correctamente.
//////	int cant_f=4;
//////	vector<Point2f> v1(cant_f), v2(cant_f);
//////	Mat aux_v1,  aux_v2;
//////	Mat H, max_H;
//////	int k, inliers, max_inliers =0;
//////	int L = 20;
//////	srand (time(NULL));
////////	float thresh_ransac = 35.0f;
//////	for(int l=0; l<L; l++) {
//////		for(int i=0;i<cant_f;i++) 
//////		{
//////			k =rand()%vm.size();
//////			
//////			v1[i] = Point2f(vm[k].at<float>(0), vm[k].at<float>(1));
//////			v2[i] = Point2f(vm[k].at<float>(2), vm[k].at<float>(3));
//////		}
//////		
//////		// v1 = H*v2
//////		H = estimate_homography(v1, v2);
//////		
////////		cout<< "L: "<<l<< " H: "<< norm(diff) <<endl;
////////		show_mat(H);
////////		show_mat(H,IMAGEN,0);
////////		waitKey(0);
//////		
//////		inliers = 0;
//////		for(int i=0;i<vm.size();i++) 
//////		{
//////			aux_v1 =(Mat_<float>(3,1)<<
//////						vm[i].at<float>(0),
//////						vm[i].at<float>(1), 
//////						1.0f
//////					);
//////			
//////			aux_v2 =(Mat_<float>(3,1)<<
//////					 vm[i].at<float>(2),
//////					 vm[i].at<float>(3), 
//////					 1.0f
//////					 );		
//////			
////////			Mat aux_v1t;
////////			transpose(aux_v1,aux_v1);
////////			diff = aux_v1*H*aux_v2;
//////			diff = aux_v1 - H*aux_v2;
//////			
////////			if(norm(diff)<thresh_ransac)
//////			if(norm(diff)<thresh_ransac)
//////			{
//////				inliers++;
//////			}
//////		}
//////		
//////		if(inliers>max_inliers)
//////		{
//////			max_inliers = inliers;
//////			max_H = H.clone();
//////		}
//////	}
//////	
//////	cout<<max_inliers<<endl;
//////	for(int i=0;i<vm.size();i++) 
//////	{
//////		aux_v1 =(Mat_<float>(3,1)<<
//////				 vm[i].at<float>(0),
//////				 vm[i].at<float>(1), 
//////				 1.0f
//////				 );
//////		
//////		aux_v2 =(Mat_<float>(3,1)<<
//////				 vm[i].at<float>(2),
//////				 vm[i].at<float>(3), 
//////				 1.0f
//////				 );		
//////		
////////		transpose(aux_v1,aux_v1);
////////		diff = aux_v1*max_H*aux_v2;
//////		
//////		diff = aux_v1 - max_H*aux_v2;
//////		
//////		if(norm(diff)>=thresh_ransac)
//////		{
//////			vm[i] = vm[vm.size()-1];
//////			vm.pop_back();
//////			
//////			i--;
//////		}
//////	}
//////	
//////	cout<<"VM_RANSAC: "<<vm.size()<<endl;
	return vm;
	
}

///

void fourier(Mat I)
{
	Mat padded;                            //expand input image to optimal size
	int m = getOptimalDFTSize( I.rows );
	int n = getOptimalDFTSize( I.cols ); // on the border add zero values
	copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
	
	Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
	Mat complexI;
	merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
	
	dft(complexI, complexI);            // this way the result may fit in the source matrix
	
	// compute the magnitude and switch to logarithmic scale
	// => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
	split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
	magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
	Mat magI = planes[0];
	
	magI += Scalar::all(1);                    // switch to logarithmic scale
	log(magI, magI);
	
	// crop the spectrum, if it has an odd number of rows or columns
	magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
	
	// rearrange the quadrants of Fourier image  so that the origin is at the image center
	int cx = magI.cols/2;
	int cy = magI.rows/2;
	
	Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
	Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
	Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
	Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right
	
	Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
	q0.copyTo(tmp);
	q3.copyTo(q0);
	tmp.copyTo(q3);
	
	q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
	q2.copyTo(q1);
	tmp.copyTo(q2);
	
	normalize(magI, magI, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
	// viewable image form (float between values 0 and 1).
	
	imshow("Input Image"       , I   );    // Show the result
	imshow("spectrum magnitude", magI);
	waitKey();
}


///-----------------------------------------------------------------------------
/// Correlacion?(NO, muy choto) , CORRESPONDENCIAS DENSAS, trabajo con las imagenes rectificadas? (SI)
///-----------------------------------------------------------------------------
/// phase/magnitude OR Intensity(x,y) ??


/// SSD - SUM OF SQUARE DIFFERENCES
int ssd(Mat left, Mat right)
{
	Mat diff;
	
	diff = left - right;
	pow(diff, 2, diff);
	
	int value = sum(diff).val[0];
	
	return value;
}

/// SAD - SUM OF ABSOLUTE DIFFERENCES
int sad(Mat left, Mat right)
{
	Mat diff;
	
	diff = left - right;
	diff = abs(diff);
	
//	int value = sum(diff).val[0];
	int value = norm(sum(diff));
	
//	cout<<sum(diff)<<endl;
//	show_mat(diff,IMAGEN,0);
//	waitKey(0);
//	
	return value;
}

int normalize_cross_correlation(Mat left, Mat right)
{
	Mat temp_l = left.clone();
	Mat temp_r = right.clone();
	Scalar mean, stddev;
	
	meanStdDev(left, mean, stddev);
	temp_l = (left - mean.val[0])/stddev.val[0];
	
	meanStdDev(right, mean, stddev);
	temp_r = (right - mean.val[0])/stddev.val[0];

	int val = 0;
	for(int i=0;i<left.cols;i++) 
	{
		for(int j=0;j<left.rows;j++) 
		{
			val += temp_l.at<float>(j,i)*temp_r.at<float>(j,i);
		}
	}
	
	return -val;
	
}
///
///
///

Mat disparity_nr(Mat c1, Mat c2, int half_block_size, int search_limits)
{
	Mat temp1 = c1.clone(), temp2 = c2.clone();
	cvtColor(temp1,temp1,CV_BGR2GRAY);
	cvtColor(temp2,temp2,CV_BGR2GRAY);
	
	temp1.convertTo(temp1,CV_32F, 1.0f/255.0f);
	temp2.convertTo(temp2,CV_32F, 1.0f/255.0f);
	
	Mat disparity = Mat::zeros(temp1.size(),CV_32F);
	
	/// VARIABLES PARA SAD O SSD
	int block_size = 2*half_block_size +1;
	
	int img_height = c1.rows, img_width = c1.cols;
	
	int offset_left, offset_right;		/// Cantidad de pixeles 
//	int num_bloques; 										/// Numero de bloques a buscar para cierta ROI
	
	int left, right, top, bot, pos;
	int val_sad, min_sad;
	
	Mat roi, search;
	// Primero Filas
	for(int j=0;j<img_height;j++) 
	{
		
		top = max(0, j - half_block_size);
		bot = min(img_height - 1, j + half_block_size);
		
		// Despues Columnas
		for(int i=0;i<img_width;i++) 
		{
			// Preparativos
			left = max(0, i - half_block_size);
			right = min(img_width - 1, i + half_block_size);
			
			offset_left = max(0, i - (half_block_size + search_limits));
			offset_right  = min(img_width - 1, i + (half_block_size + search_limits));
			
			// Region de la Imagen 1 (Left) que se va a buscar en la Imagen 2 (Right)
			roi = temp1(Rect(left,top, right - left, bot - top));
			
///-----------------------------------------------------------------------------
/// BUSCO LA MEJOR CORRESPONDENCIA ENTRA UNA ZONA DE BUSQUEDA ACOTADA (LOCAL SEARCH)
/// Metodo de analisis de correspondencia: SAD
///-----------------------------------------------------------------------------
			
			// Itero sobre la segunda imagen, busco bloques, calculo SAD, obtengo mejor coincidencia 
			min_sad = INT_MAX; pos = 0;
			for(int k=offset_left; k<offset_right-(right-left); k++) 
			{
				search = temp2( Rect(k,top, (right - left), (bot - top)) );
				
				//roi - search;
				val_sad = sad(roi,search);
//				val_sad = ssd(roi,search);
//				val_sad = normalize_cross_correlation(roi,search);
				
				// guardo el menor valor de SAD y el offset correspondiente
				if(val_sad < min_sad)
				{
					min_sad = val_sad;
					pos = k;
				}
				
			}
			
			disparity.at<float>(j,i) = left - pos;
			
		}
	}
	
	return disparity;
/////-----------------------------------------------------------------------------
///// PLOT MAPA DISPARIDAD
/////-----------------------------------------------------------------------------
//	
//	double min, max;
//	Mat d = disparity.clone();
//	d = abs(d);
//	
//	minMaxLoc(d,&min,&max);
//	d = d/max;
//
//	show_mat(d,IMAGEN,0);
//	show_mat(c1,IMAGEN,1);
//	show_mat(c2,IMAGEN,2);
//	
//	waitKey(0);
}

///
///
///

void disparity_r_call(Mat c1, Mat c2, Point2f l1, Point2f l2, Point2f r1, Point2f r2, int block_division, int search_limits_x , int search_limits_y,  Mat disparity, int iter)
{
	
	int img_w = c1.cols, img_h = c1.rows;
	int dx = ceil((l2.x-l1.x)/block_division), dy = ceil((l2.y-l1.y)/block_division);
	
//	if(dx < 4 || dy < 4 || iter==4){
	if(iter==5){
		return; 
	}
	
	++iter;
	Mat roi, search;
	
	int top, bot, left, right;
	int offs_l, offs_r;
	int offs_t, offs_b;
	int value_sad, min_sad = INT_MAX, pos;
	
	for(int j=0;j<block_division;j++) 
	{
		top = (int)l1.y + j*dy;
		bot = min(img_h-1, (int)l1.y + (j+1)*dy);
		
		for(int i=0;i<block_division;i++) 
		{
			left = (int)l1.x + i*dx;
			right = min(img_w - 1, (int)l1.x + (i+1)*dx);
			
			roi = c1(Rect(left,top,right-left,bot-top));
			
			offs_l = max(0, (int)r1.x + i*dx - search_limits_x);
			offs_r = min(img_w-1, (int)r1.x + (i+1)*dx + search_limits_x);
			offs_t = max(0, (int)r1.y + j*dy - search_limits_y);
			offs_b = min(img_h-1, (int)r1.y + (j+1)*dy + search_limits_y);
			
			min_sad = INT_MAX; 
			pos = offs_l;
//			for(int l=offs_t;l<offs_b-(bot-top);l++) {
				for(int k=offs_l;k<offs_r-(right-left);k++) 
				{
					search = c2(Rect(k,top,right-left,bot-top));
					
	//				show_mat(roi,IMAGEN,0);
	//				show_mat(search,IMAGEN,1);
	//				waitKey(0);
					
					value_sad = sad(roi,search);
	//				value_sad = ssd(roi,search);
	//				value_sad = normalize_cross_correlation(roi,search);
					
					if(value_sad < min_sad)
					{
						min_sad = value_sad;
						pos = k;
					}
				}
//			}
			for(int k=left;k<right;k++) 
			{
				for(int l=top;l<bot;l++) 
				{
					disparity.at<float>(l,k) = left - pos;
				}
			}
			
			/// Display
//			cout<< left<<" "<<pos<<endl;
//			if(iter==3){
//				Mat t1, t2;
//				t1 = c1.clone();
//				t2 = c2.clone();
//				rectangle(t1,Point2f(left,top),Point2f(right,bot), Scalar(255),2);
//				rectangle(t2,Point2f(offs_l,offs_t),Point2f(offs_r,offs_b), Scalar(255),2);
//				rectangle(t1,l1,l2, Scalar(255),2);
//				rectangle(t2,r1,r2, Scalar(255),2);
//				rectangle(t2,Point2f(pos,top),Point2f(pos + (right-left),bot), Scalar(0),2);
//				
//				show_mat(t1,IMAGEN,0);
//				show_mat(t2,IMAGEN,1);
//				waitKey(0);
//			}
			
//			disparity_r_call(
//							 c1, c2, Point2f(left,top), Point2f(right,bot), 
//							 Point2f(pos,top), Point2f(pos+(right-left), bot),
//							 block_division, search_limits,  disparity
//							 );
			
			/// LLAMADA RECURSION
			disparity_r_call(
							 c1, c2, Point2f(left,top), Point2f(right,bot), 
							 Point2f(pos,top), Point2f(pos+(right-left), bot),
							 block_division, search_limits_x,search_limits_y,  disparity, iter
							 );
			
//			boxFilter(disparity,disparity,-1,	Size(3,3));
//			GaussianBlur(disparity,disparity,Size(3,3),0.3f);
			
//			Mat d = disparity.clone();
//			d.convertTo(d,CV_8UC1);
//			show_mat(d,IMAGEN,0);
//			waitKey(0);
		}
	}
}

Mat disparity_r(Mat c1, Mat c2, int block_division, int search_limits_x, int search_limits_y)
{
	
	
	Mat disparity = Mat::zeros(c1.size(), CV_32F);
	
	Mat temp1 = c1.clone();
	cvtColor(temp1,temp1, CV_BGR2GRAY);
	temp1.convertTo(temp1,CV_32F,1.0f/255.0f);

	Mat temp2 = c2.clone();
	cvtColor(temp2,temp2, CV_BGR2GRAY);
	temp2.convertTo(temp2,CV_32F,1.0f/255.0f);
	
	///RECURSIVA
	disparity_r_call(
					 temp1,temp2,
					 Point2f(0,0),Point2f(temp1.cols,temp1.rows),
					 Point2f(0,0),Point2f(temp2.cols,temp2.rows),
					 block_division,search_limits_x,search_limits_y, disparity,0
					 );
	
	/// NO RECURSIVA
	
//////	int top, bot, left, right;
//////	int offs_l, offs_r;
//////	int value_sad, min_sad = INT_MAX, pos;
//////	
//////	int img_w = c1.cols, img_h = c1.rows;
//////	int dx = img_w/block_division, dy = img_h/block_division;
//////	Mat roi, search;
//////	
//////	for(int j=0;j<block_division;j++) 
//////	{
//////		top = j*dy;
//////		bot = min(img_h-1,(j+1)*dy);
//////		
//////		for(int i=0;i<block_division;i++) 
//////		{
//////			left = i*dx;
//////			right = min(img_w - 1, (i+1)*dx);
//////			
//////			roi = temp1(Rect(left,top,right-left,bot-top));
//////			
//////			offs_l = max(0, left - search_limits);
//////			offs_r = min(img_w-1, right + search_limits);
//////			
//////			min_sad = INT_MAX; 
//////			pos = offs_l;
//////			for(int k=offs_l;k<offs_r-(right-left);k++) 
//////			{
//////				search = temp2(Rect(k,top,right-left,bot-top));
//////				
////////				show_mat(roi,IMAGEN,0);
////////				show_mat(search,IMAGEN,1);
////////				waitKey(0);
//////				
//////				value_sad = sad(roi,search);
//////				if(value_sad < min_sad)
//////				{
//////					min_sad = value_sad;
//////					pos = k;
//////				}
//////			}
//////			
//////			for(int k=left;k<right;k++) 
//////			{
//////				for(int l=top;l<bot;l++) 
//////				{
//////					disparity.at<float>(l,k) = left - pos;
//////				}
//////			}
//////			
////////			cout<< left<<" "<<pos<<endl;
////////			/// Display
////////			Mat t1, t2;
////////			t1 = temp1.clone();
////////			t2 = temp2.clone();
////////			rectangle(t1,Point2f(left,top),Point2f(right,bot), Scalar(0),2);
////////			rectangle(t2,Point2f(offs_l,top),Point2f(offs_r,bot), Scalar(0),2);
////////			rectangle(t2,Point2f(pos,top),Point2f(pos + (right-left),bot), Scalar(255),2);
////////			
////////			show_mat(t1,IMAGEN,0);
////////			show_mat(t2,IMAGEN,1);
////////			waitKey(0);
//////
//////		}
//////	}
	
	return disparity;
}

#endif
