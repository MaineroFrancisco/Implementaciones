#ifndef HARRIS_CORNER_H
#define HARRIS_CORNER_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

#define PI 3.14159265
/// EXTRAS
void show_mat(Mat img)
{
	cv::Size s = img.size();
	
	for(int i=0;i<s.height;i++) 
	{
		ostringstream os;
		for(int j=0;j<s.width;j++)
		{
			float im = img.at<float>(i,j);
			
			os << img.at<float>(i,j);
			os << ", ";
			
		}
		cout << os.str() <<endl;
		
		os.clear();
		os<<"";
	}
}

/// Funciones

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
// NOTA: CAMBIAR LIMITE DE FEATURES POR THRESHOLD!... REVISAR COMO CONTROLAR LIMITES PARA LAS FEATURES...

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

/// MAL ... NO ME ESTARIA SIRVIENDO TANTO... USAR LA DE THRESHOLD Y CORREGIR ESTA
vector<Point2i> filter_features(Mat corner_score, int limite_features = 500, int feature_dist = 0)
{
	///Ordering
	
	Mat bin = Mat::zeros(corner_score.size(),CV_8UC1);
	
	vector<Point2i> features;
	vector<float> score;
	
	Point2f position;
	float corner;
	int num_f;
	
	int i, j, k, l, c;	// constantes basura, solo para los FOR
	for( i=0;i<corner_score.size().width;i++) 
	{
		for( j=0;j<corner_score.size().height;j++) 
		{
			corner = corner_score.at<float>(j,i);
			position.x = i;
			position.y = j;
			
			// Si no hay elementos en l arreglo, agrego y continuo0
			if(features.empty())
			{
				features.push_back(position);
				score.push_back(corner);
			}
			else
			{
				num_f = features.size();
				for( k=0;k<num_f;k++) 
				{
					
					// Si el puntaje es mas grande que alguno en el arreglo lo agrego donde corresponde
					// obtengo al final 2 arreglos confeatures ordenadas de mayor puntaje a menor
					if(corner > score[k])
					{
						// Muevo todo el arreglo para no perder valores y poder ubicar el nuevo valor
						for(l=num_f-1;l>k;l--) 
						{
							features[l] = features[l-1];
							score[l] = score[l-1];
						}
						
						// Inserto el nuevo valor en la posicion correspondiente
						score[k] = corner;
						features[k] = position;
						
						break;	
					}
					
					// Si el arreglo no llego al limite, agregar el valor y cortar
					if(num_f<limite_features)
					{
						features.push_back(features[num_f-1]);
						score.push_back(score[num_f-1]);
						break;
					}
				}
			}
		}
	}
	
	//	Eliminar similares
	for( k=0;k<limite_features;k++) 
	{
		for( l=k+1;l<limite_features;l++) 
		{
			
			// Revisar que alguna de las features en el arreglo no este muy cerca
			// de ser asi se ponderan sus posiciones.
			// Esto se hace con el fin de mejorar la distribucion y quitar similares
			if(norm(features[k]-features[l])<feature_dist)
			{
				
				for( c=l;c<limite_features-1;c++) 
				{
					features[c] = features[c+1];
					score[c] = score[c+1];
				}
				
				features.pop_back();
				score.pop_back();
				
				k--;
				limite_features--;
				break;
			}
		}
	}	
	
	return features;
}

///
Mat normalizar(Mat img_gris, double scale = 1)
{
	Mat normalizada = img_gris.clone();
	double minVal, maxVal;
	minMaxLoc(normalizada,&minVal,&maxVal);
	normalizada = normalizada + abs(minVal);
	normalizada = normalizada/(maxVal + abs(minVal));
	
	normalizada = normalizada*scale;
	
	return normalizada;
}


/// n_escalas = cantidad de ajustes (reduccion / scale_space) de resolucion 
/// n_blur = cantidad de borroneos con distintos tamanios de gaussianas
//vector<Mat> scale_space_definition(Mat img, int n_escalas, int n_blur)
vector<Point2f> sift_feature_detection(Mat img, int n_escalas, int n_blur)	/// Mal -> n_escalas = n_ovtavas y n_blur = n_escalas
{
	Mat blur, gris;
	
	cvtColor(img,gris,CV_BGR2GRAY);
	
	vector<vector<Mat>> scale_space(n_escalas);
	
	Mat escala;
	gris.copyTo(escala);
	int mag_escala = 2, mag_desvio = 1;
	double desvio = sqrt(2); // incremento_desvio = sqrt(2);
	int i,j;
	for(i=0;i<n_escalas;i++) 
	{
		
		scale_space[i].push_back(escala.clone());
		
		for(j=1;j<n_blur;j++) 
		{
			GaussianBlur(scale_space[i][j-1],blur,Size(), desvio);
			scale_space[i].push_back(blur.clone());
		}
		
		GaussianBlur(scale_space[i][0],blur,Size(), desvio);
		resize(scale_space[i][0],escala,scale_space[i][0].size()/mag_escala);
	}
	
	
//	for(int i=0;i<n_escalas;i++) 
//	{
//		for(int j=0;j<n_blur;j++) 
//		{
//			imshow("blur", scale_space[i][j]);
//			waitKey(0);
//		}
//	}
	
	vector<vector<Mat>> DOG(n_escalas);
	for(int i=0;i<n_escalas;i++) 
	{
		
		for(int j=0;j<n_blur-1;j++) 
		{
			
			Mat nuevo = scale_space[i][j+1] - scale_space[i][j];
			DOG[i].push_back(nuevo.clone());
			
//			imshow("blur", DOG[i][j]);
//			waitKey(0);
		}
		
	}
	
	/// Local Maxima y Minimo - EXTREME SUPRESSION

	vector<vector<Mat>> keypoints(n_blur-1);
	Size vecindad(3,3);
	
	Mat pre_scale, act_scale, post_scale, act_roi, pre_roi, post_roi;
	Point2i pre_pos, act_pos, post_pos;
	
	unsigned char act_value;
	double max_act, max_pre, max_post, min_act, min_pre, min_post;
	
	for(int i=0;i<n_escalas;i++) ///
	{
		for(int j=1;j<n_blur-2;j++) /// -1 para las DOG
		{
			pre_scale = DOG[i][j-1];
			act_scale = DOG[i][j];
			post_scale = DOG[i][j+1];
			
			keypoints[i].push_back(act_scale.clone());
			
			for(int l=0;l<act_scale.size().width;l++) 
			{
				for(int k=0;k<act_scale.size().height;k++)
				{
					
					act_pos = Point2i(l,k);
					pre_pos = Point2i(l,k);
					post_pos = Point2i(l,k);
//					pre_pos = Point2i(l,k)*mag_escala;
//					post_pos = Point2i(l,k)/mag_escala;
					
					act_roi = format_roi(act_scale, vecindad, act_pos.x, act_pos.y);
					pre_roi = format_roi(pre_scale, vecindad, pre_pos.x, pre_pos.y);
					post_roi = format_roi(post_scale, vecindad, post_pos.x, post_pos.y);
					
					act_value = act_scale.at<unsigned char>(act_pos.y, act_pos.x);
					
					minMaxLoc(act_roi, &min_act, &max_act);
					minMaxLoc(pre_roi, &min_pre, &max_pre);
					minMaxLoc(post_roi, &min_post, &max_post);
					
					if( (act_value < max_act  && act_value < max_pre && act_value < max_post) && 
						(act_value > min_act  && act_value > min_pre && act_value > min_post) )
					{
//						keypoints[j][i-1].at<unsigned char>(k,l) = 0;	
						keypoints[i][j-1].at<unsigned char>(k,l) = 0;	
					}
				}
			}
			
		}
	}

	
	for(int i=0;i<n_escalas;i++) 
	{
		for(int j=0;j<n_blur-3;j++) 
		{
			imshow("blur", keypoints[i][j]);
			waitKey(0);
		}
	}
	
	
	
	/// REVISAR ESTA PARTE
///-----------------------------------------------------------------------------
///		Threshold keypoints Minimos
///-----------------------------------------------------------------------------
	Mat minimo, min_mask, iDx, iDy, iDx2, iDy2, iDxDy, iDxDy2;
	Mat det, trace, edge_response;
	float r = 10;
	double minVal, maxVal;
	
	for(int i=0;i<n_escalas;i++) ///
	{
		for(int j=0;j<n_blur-3;j++) /// -1 para las DOG
		{
			minimo = keypoints[i][j].clone();
			
			
//			imshow("edge_mask", keypoints[i][j] > 0);
//			waitKey(0);
			
			threshold(keypoints[i][j],keypoints[i][j],7,255,3);	// 3 : THRESH TO ZERO			
			
//			imshow("edge_mask", keypoints[i][j] > 0);
//			waitKey(0);
			
		}
	}
	
///-----------------------------------------------------------------------------
///		Threshold Derivate -> para bordes
///-----------------------------------------------------------------------------
//	Mat float_image;
//	for(int i=0;i<n_escalas;i++) ///
//	{
//		for(int j=0;j<n_blur-3;j++) /// -1 para las DOG
//		{
//			
//			
//			imshow("edge_mask", keypoints[i][j] > 0);
//			waitKey(0);
//			
//			keypoints[i][j].convertTo(float_image,CV_32F,1.0f/255.0f);
//			
//			//Calculate Dx
//			filter2D(float_image, iDx,-1,dx,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
//			
//			//Calculate Dx^2
//			filter2D(iDx, iDx2,-1,dx,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
//			
//			//Calculate Dy
//			filter2D(float_image, iDy,-1,dy,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
//			
//			//Calculate Dy^2
//			filter2D(iDy, iDy2,-1,dy,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
//			
//			//Calculate DxDy
//			filter2D(iDx, iDxDy,-1,dy,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
//			
//			// Calculate the Determinant
////			iDx2 = abs(iDx2);
////			iDy2 = abs(iDy2);
////			iDxDy = abs(iDxDy);
//			pow(iDxDy,2,iDxDy2);
//			multiply(iDx2,iDy2,det);	
//			subtract(det,iDxDy2,det);
//			
//			//Calculate the trace
//			add(iDx2,iDy2,trace);
//
//			/// MAL REVISAR
////			det = abs(det);
//			Mat trace2;
//			pow(trace,2,trace2);
//			divide(trace2,det,edge_response);
//			
//			
////			edge_response = normalizar(edge_response);
////			edge_response = abs(edge_response);
////			imshow("edge_response", edge_response);
////			waitKey(0);
//			
//			minMaxLoc(edge_response, &minVal, &maxVal);
//			cout<< minVal<<" "<<maxVal<<endl;
//			
////			cout<< ((r+1)*(r+1))/r<<endl;
//			for(int l=0;l<edge_response.size().width;l++) 
//			{
//				for(int k=0;k<edge_response.size().height;k++)
//				{
//					///MAL REVISAR
//					if(edge_response.at<float>(k,l) > ((r+1)*(r+1))/r)
//					{
//						keypoints[i][j].at<unsigned char>(k,l) = 0;	
//					}
//				}
//			}
//			
//			Mat test = normalizar(keypoints[i][j],255);
//			imshow("edge_mask", test);
//			waitKey(0);
//		}
//	}	
//	
//	
	
///-----------------------------------------------------------------------------
///
///-----------------------------------------------------------------------------
	
	for(int i=0;i<n_escalas;i++) 
	{
		for(int j=0;j<n_blur-3;j++) 
		{
			imshow("blur", keypoints[i][j]);
			waitKey(0);
		}
	}
	
	
//	return escalas;
}

#endif
