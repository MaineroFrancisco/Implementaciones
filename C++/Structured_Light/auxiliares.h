#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include "SL.hpp"

#include "opencv2/viz.hpp"
#include "opencv2/viz/widgets.hpp"

//#include "test.hpp"

#include <iostream>
using namespace std;
using namespace cv;

vector<Mat> cam1;
vector<Mat> cam2;
static int id = 0;
int save = 0;
Mat c1(4,4,CV_32FC1);
Mat c2(4,4,CV_32FC1);
int ind1=0, ind2=0;

enum tipo{ TEXTO, IMAGEN};
void show_mat(Mat img, tipo t = TEXTO,  int cam = 0)
{
	cv::Size s;
	switch(t)
	{
		case TEXTO:
			s = img.size();
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
			break;
			
		case IMAGEN:
			
			ostringstream os;
			os<<cam;
//			os<<id;
//			id++;
			
			imshow("Imagen_"+os.str(), img);
//			waitKey(0);
			break;
	}
}

/// CALLBACKS

///
void save_capture(Mat img,string path, int camera)
{
	ostringstream capture_id;
	capture_id << camera;
	imwrite(path + "cap_"+ capture_id.str()+".png", img);
}

///
void callback_c1(int event, int x, int y, int flags, void* userdata)
{
	if(cam1.size() < 3)
	{
		if(ind1>=4)
		{
			cam1.push_back(c1.clone());
			c1 = Mat::zeros(4,4,CV_32FC1);
			ind1=0;
		}
		
		// p_reales = 0,0 | 0,1 | 1,0 | 1,1 
		if  ( event == EVENT_LBUTTONDOWN )
		{
			c1.at<float>(ind1, 0) = (float)x;
			c1.at<float>(ind1, 1) = (float)y;
			c1.at<float>(ind1, 2) = (ind1 & 2)/2;
			c1.at<float>(ind1, 3) = ind1 & 1;
			ind1++;
		}
	}
}

void callback_c2(int event, int x, int y, int flags, void* userdata)
{
	
	if(cam2.size() < 3)
	{
		if(ind2 >= 4)
		{
			cam2.push_back(c2.clone());
			c2 = Mat::zeros(4,4,CV_32FC1);
			ind2=0;
		}
		
		// p_reales = 0,0 | 0,1 | 1,0 | 1,1 
		if  ( event == EVENT_LBUTTONDOWN )
		{
			c2.at<float>(ind2, 0) = (float)x;
			c2.at<float>(ind2, 1) = (float)y;
			c2.at<float>(ind2, 2) = (ind2 & 2)/2;
			c2.at<float>(ind2, 3) = ind2 & 1;
			ind2++;
		}
	}
}

///
void draw_sys_coord(Mat M, viz::Viz3d windows)
{
	Mat Em = Mat::zeros(4,4,CV_32FC1);
	
	//	show_mat(M);
	
	M.row(0).copyTo(Em.row(0));
	M.row(1).copyTo(Em.row(1));
	M.row(2).copyTo(Em.row(2));
	
	Em.at<float>(3,3) = 1.0f;
	
	Mat dimtrim = (Mat_<float> (3,4) <<
				   1.0f,0.0f,0.0f,0.0f,
				   0.0f,1.0f,0.0f,0.0f,
				   0.0f,0.0f,1.0f,0.0f
				   );
	
	Mat invEm = dimtrim*Em.inv();
	
	Mat sc = (
			  Mat_<float>(4,3) <<
			  1.0f, 0.0f, 0.0f,
			  0.0f, 1.0f, 0.0f,
			  0.0f, 0.0f, 1.0f,
			  1.0f, 1.0f, 1.0f
			  );
	
	Mat orig = (
				Mat_<float>(4,1) <<
				0.0f, 0.0f, 0.0f, 1.0f
				);
	
	sc = invEm*sc;
	
	orig = invEm*orig;
	
	//	Affine3f cam(sc);
	
	ostringstream os;
	os << id;
	
	viz::WLine axisX(Point3f(orig), Point3f(sc.col(0)), Scalar(255,0,0));
	axisX.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	windows.showWidget("X_"+os.str(), axisX);
	
	viz::WLine axisY(Point3f(orig), Point3f(sc.col(1)), Scalar(0,0,255));
	axisY.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	windows.showWidget("Y_"+os.str(), axisY);
	
	viz::WLine axisZ(Point3f(orig), Point3f(sc.col(2)), Scalar(0,255,0));
	axisZ.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	windows.showWidget("Z_"+os.str(), axisZ);
	
	id++;
}

///

vector<Mat> pc1, pc2;

void callback_pc1(int event, int x, int y, int flags, void* userdata)
{
	Mat p(1,3,CV_32FC1);
	// p_reales = 0,0 | 0,1 | 1,0 | 1,1 
	if  ( event == EVENT_LBUTTONDOWN )
	{
		p.at<float>(0, 0) = (float)x;
		p.at<float>(0, 1) = (float)y;
		p.at<float>(0, 2) = 1.0f;
		
		pc1.push_back(p.clone());
	}
	
	
}

void callback_pc2(int event, int x, int y, int flags, void* userdata)
{
	Mat p(1,3,CV_32FC1);
	// p_reales = 0,0 | 0,1 | 1,0 | 1,1 
	if  ( event == EVENT_LBUTTONDOWN )
	{
		p.at<float>(0, 0) = (float)x;
		p.at<float>(0, 1) = (float)y;
		p.at<float>(0, 2) = 1.0f;
		
		pc2.push_back(p.clone());
	}
	
}




/// FUNCIONES
void save_images(string path, VideoCapture c1, int start = 0)
{
	unsigned char pressed_key =0;
	int i = start;
	
	Mat f1;
	
	while(pressed_key != 27 )
	{
		c1>>f1;
		imshow("Camara 1", f1);
		
		if(pressed_key == 13) //Enter
		{
			save_capture(f1,path,i);
			i++;
		}
		
		pressed_key = waitKey(5);
	}
	
}

void histograma(Mat f_hist, int histSize)
{
	///Mostrar HISTOGRAMA / HOG
	
	// Draw the histograms for B, G and R
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound( (double) hist_w/histSize );
	
	Mat histImage( hist_h, hist_w, CV_8UC1, Scalar( 0) );
	
	/// Normalize the result to [ 0, histImage.rows ]
	Mat result = f_hist.clone();
	normalize(result, result, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
	
	/// Draw for each channel
	for( int l = 1; l < histSize; l++ )
	{
		line( histImage, Point( bin_w*(l-1), hist_h - cvRound(result.at<float>(l-1)) ) ,
			 Point( bin_w*(l), hist_h - cvRound(result.at<float>(l)) ),
			 Scalar(255), 2, 8, 0  );
	}
	show_mat(histImage,IMAGEN,0);
	
}

void show_hog(Mat gris, Point2f pos_feature, float orientation, Mat HOG)
//void show_hog(Mat parche, Mat hist )
{	
	/// ESTA FUNCION RESIVE UN PARCHE DE LA IMAGEN SOBRE LA QUE SE VA A PLOTEAR, EL HISTOGRAMA DE ESE PARCHE (SUBPARCHE DE LA VNETANA GENERAL EN REALIDAD)
	/// Y CONSTRUYE LA SUBESTRUCTURA DE HOG PARA PLOTEAR, ESCALADA SEGUN EL HISTOGRAMA NORMALIZADO
	
	Mat copy_g = gris.clone();
	
//	normalize(copy_g,copy_g,1,0,cv::NORM_MINMAX);
	
	// ORIENTAR LA IMAGEN SEGUN LA ORIENTACION GENERAL DE LA FEATURE, ASI OBTENER LA ROI CORRECTAMENTE
	Mat rot_g, m_rot;
	
	m_rot = getRotationMatrix2D(pos_feature, orientation, 1);
	
	warpAffine(copy_g, rot_g, m_rot,copy_g.size());
	
	// extraer parche de la feature
	Point2f pos = pos_feature;
	pos.x -=8;
	pos.y -=8;
	
	Mat roi_g = rot_g(Rect(pos.x,pos.y,16,16)).clone();
	Mat sub_roi, sub_hist;
	
	pyrUp( roi_g, roi_g, Size( roi_g.cols*2, roi_g.rows*2 ));
	pyrUp( roi_g, roi_g, Size( roi_g.cols*2, roi_g.rows*2 ));
	pyrUp( roi_g, roi_g, Size( roi_g.cols*2, roi_g.rows*2 ));
	
	Point2f center, pos_fin;
	float angle,x,y;
	
	for(int i=0;i<16;i++) 
	{
		
		sub_roi = roi_g(Rect(32*(i%4),32*(i/4),32,32));
		
		center = Point2f(16+(32*(i%4)),16+(32*(i/4)));
		
		sub_hist = HOG(Rect(0,i*8,1,8));
		
		for(int j=0;j<8;j++) 
		{
			angle = j*45;	// 45 = 360/n_bins
//			x = 20*sub_hist.at<float>(j)*cos(angle*CV_PI/180);
//			y = 20*sub_hist.at<float>(j)*sin(angle*CV_PI/180);
			x = 20*sub_hist.at<unsigned char>(j)*cos(angle*CV_PI/180);
			y = 20*sub_hist.at<unsigned char>(j)*sin(angle*CV_PI/180);
			
			pos_fin = center + Point2f(x,y);
			
			arrowedLine(roi_g,center, pos_fin, Scalar(125),1,8,0,0.1);
		}
	}
	
	show_mat(roi_g,IMAGEN,1);
}

#endif
