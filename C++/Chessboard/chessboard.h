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

Mat harris_corner_score(Mat img, Mat mask, score_type tipo = HARRIS_STEPHENS)
{
	/// Variables
	Size size_img = img.size();	//tamanio de la imagen
	
	Size s(3,3);				// tamanio de la ventana gaussiana
	double sigma = 1.5f;		// desvio de la ventana gaussiana
	
	double minVal, maxVal;
	
	
//	Mat iDx = Mat::zeros(img.size(),CV_32F); 
//	Mat iDy = Mat::zeros(img.size(),CV_32F);
	Mat iDx, iDy, iDx2, iDy2, iDxDy;
	
	
	Mat corner_score = Mat::zeros(size_img,CV_32FC1);
	Mat det, trace, iDxDy2;
	
	Mat NMS;
	int ult_x = size_img.width-1;
	int ult_y = size_img.height-1;
	
	int nms_height, nms_width, pos_x, pos_y;
	
	Mat output;
	
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
			
//			for(int i=0;i<size_img.width;i++)
//			{
//				for(int j=0;j<size_img.height;j++) 
//				{
//					
//				}
//			}
//			
			
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
			
			break;
	}
	
	/// Devolver imagen en rango 0 a 1
	minMaxLoc(corner_score, &minVal, &maxVal);
	
	maxVal = (maxVal+abs(minVal));
	
	corner_score = corner_score+abs(minVal);
	corner_score = corner_score/maxVal;
	
	if(!mask.empty())
	{
		corner_score.copyTo(output,mask);
	}
	else
	{
		corner_score.copyTo(output);
	}

	/// Non-Maximal Supression -> con vecindades de 3x3... revisar luego...
	for( int i = 0; i<=ult_x; i++)
	{
		if(i == 0)
		{
			nms_width = 2;
			pos_x = i;
		}
		else{
			if(i == ult_x)
			{
				nms_width = 2;
				pos_x = i-1;
			}
			else{
				nms_width = 3;
				pos_x = i-1;
			}
		}
		
		for( int j = 0; j<=ult_y; j++)
		{				
			if(j == 0)
			{
				nms_height = 2;
				pos_y = j;
			}
			else{
					if(j == ult_y)
					{
						nms_height = 2;
						pos_y = j-1;
					}
					else{
						nms_height = 3;
						pos_y = j-1;
					}
			}
			
			NMS = corner_score(Rect(pos_x,pos_y,nms_width,nms_height));
			
			minMaxLoc(NMS,&minVal,&maxVal);
			
			if (corner_score.at<float>(j,i) < maxVal)
			{
				output.at<float>(j,i) = 0.0f;	
			}
		}
	}

	return output;
}

///----------------------------------------------------------------------------
// NOTA: CAMBIAR LIMITE DE FEATURES POR THRESHOLD!... REVISAR COMO CONTROLAR LIMITES PARA LAS FEATURES...

///
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
					// Si el arreglo no llego al limite, agregar el valor y cortar
					if(num_f<limite_features)
					{
						features.push_back(features[num_f-1]);
						score.push_back(score[num_f-1]);
						break;
					}
	
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
				
				features[k] = (features[k]+features[l])/2;
				
				for( c=l;c<limite_features-1;c++) 
				{
					features[c] = features[c+1];
					score[c] = score[c+1];
				}
				l--;
				
				features.pop_back();
				score.pop_back();
				
				limite_features--;
			}
		}
	}	
	
	return features;
}

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
vector<Point2i> chessboard_features(Mat img,Size grid_features, Mat mask)
{
	Mat gris, feature, r1, r2;
	Mat diff;
	Mat msk1, msk2;
	Point2i center;
	vector<Point2i> features;
	
	double angle, best_angle, minVal, maxVal, const_thresh = 0.70 ;
	int cant_features, best_features = 0;
	
	cvtColor(img,gris,CV_BGR2GRAY);
//	if(mask.empty())
//	{
		feature = harris_corner_score(gris,mask);
//	}
//	else
//	{
//		feature = harris_corner_score(gris);
//	}
	
	features = filter_features(feature, 500, 10);
	
	angle=0.0f;
//	Scalar media_global = mean(gris);
	
	threshold(gris,gris,mean(gris).val[0],255,CV_THRESH_BINARY);
	while(angle<360.0f)
	{
		msk1 = rotate_mask(checkb_mask,angle);
		msk2 = rotate_mask(checkb_mask_ops,angle);
		
		filter2D(gris,r1,CV_32FC1,msk1);
		filter2D(gris,r2,CV_32FC1,msk2);
		
		minMaxLoc(r1, &minVal, &maxVal);
		
		r1 = r1 + abs(minVal);
		r1 = r1 / (abs(minVal)+maxVal);

		minMaxLoc(r2, &minVal, &maxVal);
		
		r2 = r2 + abs(minVal);
		r2 = r2 / (abs(minVal)+maxVal);
		
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
		
		if(cant_features > best_features){
			best_angle = angle;
			best_features = cant_features;
		}
		
		angle+=10.0f;
		
	}
	
	msk1 = rotate_mask(checkb_mask,angle);
	msk2 = rotate_mask(checkb_mask_ops,angle);
	
	filter2D(gris,r1,CV_32FC1,msk1);
	filter2D(gris,r2,CV_32FC1,msk2);
	
	minMaxLoc(r1, &minVal, &maxVal);
	
	r1 = r1 + abs(minVal);
	r1 = r1 / (abs(minVal)+maxVal);
	
	minMaxLoc(r2, &minVal, &maxVal);
	
	r2 = r2 + abs(minVal);
	r2 = r2 / (abs(minVal)+maxVal);
	
	diff = r1-r2;
	diff = abs(diff);
	
	threshold(diff,diff,const_thresh,1.0f,CV_THRESH_BINARY);

	cant_features = 0;
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
	
	return features;
	
}
#endif
