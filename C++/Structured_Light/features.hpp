
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
using namespace std;
using namespace cv;
///-------------------------------------------------------------------------
///Mascaras gaussianas para derivadas (Prewitt)

/// el tamanio necesita variar si voy a jugar Con multiples resoluciones de una misma foto, completar todo primero luego probar
/// Probar otras mascaras (Ej.: Sobel) 
//// Dx
//const Mat dx = (Mat_<float>(3, 3) << -1.0f, 0.0f, 1.0f,
//				-1.0f,  0.0f,  1.0f,
//				-1.0f,  0.0f,  1.0f);
//
////Dy
//const Mat dy = (Mat_<float>(3, 3) << -1.0f, -1.0f, -1.0f,
//				0.0f,  0.0f,  0.0f,
//				1.0f,  1.0f,  1.0f);

// Dx
const Mat dx = (Mat_<float>(1, 3) << -1.0f, 0.0f, 1.0f);
//Dy
const Mat dy = (Mat_<float>(3, 1) << -1.0f, 0.0f, 1.0f);

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
		
		// Calculate Corner Score by "HARRIS_STEPHENS formula"
		Scalar k(0.04);
		pow(trace,2,trace);
		multiply(trace,k,trace);
		subtract(det,trace,corner_score);	
		
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
	
//	minMaxLoc(output, &minVal, &maxVal);	
//	output = output/maxVal;
	
	normalize(output,output,1,0,cv::NORM_MINMAX);
	
	return output;
	
}

///-----------------------------------------------------------------------------
/// DEFINIR PROFUNDIDAD DE BITS PARA FILTRAR, TRABAJAR TODO EN FLOTANTES? 
vector<Point2f> harris_threshold(Mat corner_score, int thresh = 100)
{
	Mat filtrada;
	Size corner_size = corner_score.size();
	
	vector<Point2f> features;
	
	corner_score.convertTo(corner_score, CV_16U,65535);
	filtrada = corner_score > thresh;
	
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
	
	return features;
}

///-----------------------------------------------------------------------------

//gris -> imagen grayscale;
void generate_descriptor(Mat gris, vector<Point2f> features)
{
	Mat iDx, iDy;
	
	gris.convertTo(gris, CV_32F);
	
	/// Calculo las derivadas
	
	//Calculate Dx
	filter2D(gris, iDx,-1,dx,cv::Point(-1,-1), 0, cv::BORDER_REPLICATE);
	
	//Calculate Dy
	filter2D(gris, iDy,-1,dy,cv::Point(-1,-1), 0, cv::BORDER_REPLICATE);
	
	iDx = abs(iDx);
	iDy = abs(iDy);
	
	double minVal,maxVal;
	minMaxLoc(iDx, &minVal, &maxVal);	
	iDx = iDx/maxVal;
	minMaxLoc(iDy, &minVal, &maxVal);	
	iDy = iDy/maxVal;
	
//	imshow("Dx",iDx);
//	imshow("Dy",iDy);
//	waitKey(0);
	
//	double desvio = 1.5f;
//	
//	GaussianBlur(iDx,iDx,Size(),desvio,desvio);
//	GaussianBlur(iDy,iDy,Size(),desvio,desvio);
	
	Mat m, phi;

	// Calculate gradient magnitude and direction (in degrees)
	cartToPolar(iDx, iDy, m, phi, 1); 
	
	minMaxLoc(phi, &minVal, &maxVal);	
	phi = phi/maxVal;
	
	imshow("magnitud",m);
	imshow("fase",phi);
	waitKey(0);
	
	///
	
}

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