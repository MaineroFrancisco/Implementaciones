#ifndef HARRIS_CORNER_H
#define HARRIS_CORNER_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <vector>
#include "b_tree.h"

using namespace std;
using namespace cv;

b_tree features_tree;

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
Mat dx = (Mat_<float>(3, 3) << -1.0f, 0.0f, 1.0f,
		  -1.0f,  0.0f,  1.0f,
		  -1.0f,  0.0f,  1.0f);

//Dy
Mat dy = (Mat_<float>(3, 3) << -1.0f, -1.0f, -1.0f,
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
	img.convertTo(img, CV_32F);
	
	/// Calculo las derivadas
	
	Mat iDx = Mat::zeros(img.size(),CV_32F); 
	Mat iDy = Mat::zeros(img.size(),CV_32F);
	
	Mat iDx2, iDy2, iDxDy;
		
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
	Size s(3,3);
	double sigma = 1.5f;
	
	//Kernel Gaussiano de Integracion (Explicacion)
	/**/
	GaussianBlur(iDx2,iDx2,s,sigma,sigma);
	GaussianBlur(iDy2,iDy2,s,sigma,sigma);
	GaussianBlur(iDxDy,iDxDy,s,sigma,sigma);

	///-------------------------------------------------------------------------
	/// Calculo el puntaje para cada pixel de la imagen, mayor puntaje -> mejor feature
	Size size_img = img.size();

	/// Computing corner Score		|| Formula 1: det - k*(trace)^2		|| Formula 2: det / trace	|| Shi-Tomasi: min(Dx,Dy)
	Mat corner_score = Mat::zeros(size_img,CV_32FC1);
	Mat det, trace, iDxDy2;
	
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
			
//			for(int i=0;i<640;i++)
//			{
//				for(int j=0;j<640;j++) 
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
	
	Mat output;
	double minVal, maxVal;
	
	minMaxLoc(corner_score, &minVal, &maxVal);
	
	maxVal = (maxVal+abs(minVal));
	
	corner_score = corner_score+abs(minVal);
	corner_score = corner_score/maxVal;
	
	corner_score.copyTo(output,mask);

	/// Non-Maximal Supression -> con vecindades de 3x3... revisar luego...
	Mat NMS;
	Size corner_size = corner_score.size();
	int ult_x = corner_size.width-1;
	int ult_y = corner_size.height-1;
	
	int nms_height, nms_width, pos_x, pos_y;
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

	/// Visualizar
	//	Mat harris_matrix = Mat::zeros(img.rows*2, img.cols*2,CV_32F);
	//	
	//	Rect roi_dx_2 = Rect(0,0,size_img.width,size_img.height);
	//	Rect roi_dy_2 = Rect(size_img.width,size_img.height,size_img.width,size_img.height);
	//	Rect roi_dy_dx = Rect(0,size_img.height,size_img.width,size_img.height);
	//	Rect roi_dx_dy = Rect(size_img.width,0,size_img.width,size_img.height);
	//	
	//	
	//	iDx2.copyTo(harris_matrix(roi_dx_2));
	//	iDy2.copyTo(harris_matrix(roi_dy_2));
	//	iDxDy.copyTo(harris_matrix(roi_dy_dx));
	//	iDxDy.copyTo(harris_matrix(roi_dx_dy));
	//	imshow("Harris", harris_matrix);		
	//	waitKey(0);
	
	return output;
}

///----------------------------------------------------------------------------
vector<Point2i> filter_features(Mat corner_score, int cantidad_features = 500){
	///Ordering
	
	Mat bin = Mat::zeros(corner_score.size(),CV_8UC1);
	
	vector<Point2i> features;
	vector<float> score;
	
	int i, j, k, l, c;
	int num_f = 1;
	int thresh = 10;
	for( i=0;i<corner_score.size().width;i++) 
	{
		for( j=0;j<corner_score.size().height;j++) 
		{
			float corner = corner_score.at<float>(j,i);
			Point2f position(i,j);
//			for( k=0;k<num_f;k++) 
//			{		
//				if(corner > score[k])
//				{
//					
//					for(l=num_f-1;l>k;l--) 
//					{
//						features[l] = features[l-1];
//						score[l] = score[l-1];
//					}
//					
//					score[k] = corner;
//					features[k] = position;
//					break;	
//				}
//			}
			
			if(features.empty())
			{
				features.push_back(position);
				score.push_back(corner);
			}
			else{
				num_f = features.size();
				for( k=0;k<num_f;k++) 
				{
					if(corner > score[k])
					{
						// Si todavia no tengo la cantidad deseada, agrego uno al arreglo (repito el ultimo)
						if(num_f<cantidad_features)
						{
							features.push_back(features[num_f-1]);
							score.push_back(score[num_f-1]);
						}
						
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
	
//		Eliminar similares
	for( k=0;k<cantidad_features;k++) 
	{
		for( int l=0;l<cantidad_features;l++) 
		{
			if(norm(features[k]-features[l])<thresh && k!=l)
			{
				if (score[k]<score[l])
				{
					for(int c=k;c<cantidad_features-1;c++) 
					{
						features[c] = features[c+1];
						score[c] = score[c+1];
					}
					k--;
				}
				else
				{	
					for(int c=l;c<cantidad_features-1;c++) 
					{
						features[c] = features[c+1];
						score[c] = score[c+1];
					}
					l--;
				}
				
				features[cantidad_features-1] = Point2f(0,0);
				score[cantidad_features-1] = 0;
				
				cantidad_features--;
			}
		}
	}	

	cout<<cantidad_features<<endl;
	
	return features;
}

///----------------------------------------------------------------------------


Mat checkb_mask = (Mat_<float>(11,11) <<  
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

Mat checkb_mask_ops = (Mat_<float>(11,11) <<  
					
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

///Radianes o Angulos?
Mat rotate_mask(Mat mask, double angle)
{
	Size s = mask.size();
	
	Point2f center( s.width/2, s.height/2);
	
	Mat R(2,3,CV_32F);
	
	R.at<float>(0,0) = cos(angle*180.0f/PI);
	R.at<float>(1,0) = -sin(angle*180.0f/PI);

	R.at<float>(0,1) = sin(angle*180.0f/PI);
	R.at<float>(1,1) = cos(angle*180.0f/PI);

	R.at<float>(0,2) = (1-cos(angle*180.0f/PI))*center.x - sin(angle*180.0f/PI)* center.y;
	R.at<float>(1,2) = sin(angle*180.0f/PI)*center.x + (1-cos(angle*180.0f/PI))* center.y;
	
	Mat output;
	warpAffine(mask,output,R,s);
	
	return output;
}

///UNA CAGADA, DEJA DE BOLUDEAR CON PUNTEROS ASI CAGAS MEMORIA Y ES MAS DIFICIL
//img en GRAYSCALE
// Cambiar b_tree por quadtree, arreglarselas despues con los Score, los duplicados joden mas  y son mas complicados.
void checkboard_features(Mat img,b_tree features_tree, Point2f* features, int maxcant)
{
	
	Point2i center;
	Mat region, reg_result;
	int angle;
	Scalar measure;
	for(int i=0;i<maxcant;i++) 
	{
		center = features[i];
		region = Mat(img, Rect(center.x-4,center.y-4,9,9));
		
		angle=0.0f;
		while(angle<360.0f)
		{
			rotate_mask(checkb_mask,angle);
			
			bitwise_xor(checkb_mask, region,reg_result);
			
			measure = mean(reg_result);
			
//			if(measure < /*some number a determinar*/)
//			{
				features_tree.erase(features[i]);
//			}
			
			angle+=25.0f;
		}
		
	}
	
	
	
	
}
#endif
