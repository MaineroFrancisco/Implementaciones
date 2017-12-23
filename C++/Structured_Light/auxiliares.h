#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "SL.hpp"

#include "opencv2/viz.hpp"
#include "opencv2/viz/widgets.hpp"

#include "test.hpp"

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

void sistema_completo(string path, bool cm2)
{

	///-----------------------------------------------------------------------------	
	/// Camera Setting
	///-----------------------------------------------------------------------------	
	
	VideoCapture cap1("http://192.168.1.105:4747/mjpegfeed?640x480"); 
//	VideoCapture cap2("http://192.168.1.103:4747/mjpegfeed?640x480");
	
	VideoCapture cap2(0);
	cap2.set(CV_CAP_PROP_FRAME_WIDTH,640);
	cap2.set(CV_CAP_PROP_FRAME_HEIGHT,480);
	
	// Return si hubo error al abrir la camara.
	if(!cap1.isOpened())
	{
		cout<<"Error al abrir la camara 1"<<endl;
		return;
	}
	
	//	 Return si hubo error al abrir la camara.
	if(!cap2.isOpened())
	{
		cout<<"Error al abrir la camara 2"<<endl;
		//return -1;
		cm2 = false;
	}
	
	unsigned char pressed_key;
	int cam_id = 1, i;
	
	Mat frame1, frame2;
	
	cout<<"Comienza Proceso ... "<<endl;
	///-----------------------------------------------------------------------------
	/// Camera Captures
	///-----------------------------------------------------------------------------
	
	namedWindow("Camara 1",1);
	setMouseCallback("Camara 1", callback_c1, NULL);
	
	if (cm2)
	{
		namedWindow("Camara 2",1);
		setMouseCallback("Camara 2", callback_c2, NULL);
	}
	
	cout<<"Capturar Planilla ... "<<endl;
	pressed_key = 0; 
	while(pressed_key != 27)
	{
		cap1 >> frame1;  // Capturar el frame actual de la camara.
		
		for(int j=0;j<ind1;j++) 
		{
			Point2f pc1;
			pc1.x = c1.at<float>(j,0);
			pc1.y = c1.at<float>(j,1);
			
			circle(frame1,pc1,5,Scalar(255));
		}
		
		imshow("Camara 1", frame1);
		
		
		if(cm2)
		{
			cap2 >> frame2;  // Capturar el frame actual de la camara.
			
			for(int j=0;j<ind2;j++) 
			{
				Point2f pc2;
				pc2.x = c2.at<float>(j,0);
				pc2.y = c2.at<float>(j,1);
				
				circle(frame2,pc2,5,Scalar(255));
			}
			
			imshow("Camara 2", frame2);
		}
		
//		if (pressed_key == 10)
		if (pressed_key == 13)
		{
			save_capture(frame1, path, 1);
			
			if(cm2)
			{
				save_capture(frame2, path, 2);
			}
		}
		
		pressed_key  = waitKey(5);
	}
	
	setMouseCallback("Camara 1", NULL, NULL);
	
	if(cm2)
		setMouseCallback("Camara 2", NULL, NULL);
	
	cout<<"Capturar Planilla ... Terminado "<<endl;
	
	///-----------------------------------------------------------------------------
	/// Calibracion y Construccion de la Escena General (Determinar Propiedades 
	///		Extrinsecas de la camara para la posicionar todo en escena, 
	///		poseteriormente triangular para reconstruir)
	///-----------------------------------------------------------------------------
	//		 Ancho  |	Alto	
	int proj_res_w = 128, proj_res_h = 128;
	
	SL sl(proj_res_w,proj_res_h);
	
	cout<< "Calibrando Camaras... "<<endl;
	vector<Mat> vc1, vc2;
	
	vc1 = sl.plane_base_calibration(cam1);
	
	if(cm2)
		vc2 = sl.plane_base_calibration(cam2);
	
	cout<< "Calibrando Camaras... Terminado"<<endl<<endl;
///-----------------------------------------------------------------------------
/// patrones codificados
///-----------------------------------------------------------------------------
	
///-----------------------------------------------------------------------------
/// 
/// Construir mascara para filtrar sombra y fondo.
///		Requiere capturas extra:
///			Para Background:
///				Capturas antes y despues de colocar el objeto (de por si al usar luz estructurada la escena se supone estatica asi que no deberia haber problema)
///			Para sombra:
///				Capturas full iluminada y oscura.
///	
///-----------------------------------------------------------------------------
	
	namedWindow("Pattern Windows",CV_WINDOW_NORMAL);
	setWindowProperty("Pattern Windows", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	
	/// Mascara de segmentado
	
	cout<< "Capturar p/ Mascara - Segmentacion... "<<endl;
	
	pressed_key = 0;
	vector<Mat> obj_c1, obj_c2;
	while(pressed_key != 27 && obj_c1.size()<2)
	{
		
		cap1 >> frame1;
		imshow("Camara 1", frame1);
		
		if(cm2)
		{
			cap2 >> frame2;
			imshow("Camara 2", frame2);
		}
		
//		if (pressed_key == 10)	//enter
		if (pressed_key == 13) 	//espacio
		{
				cvtColor(frame1,frame1,cv::COLOR_BGR2GRAY);
				obj_c1.push_back(frame1.clone());
				
				save_capture(frame1, path, 1);
				
				if(cm2)
				{
					cvtColor(frame2,frame2,cv::COLOR_BGR2GRAY);
					obj_c2.push_back(frame2.clone());
					
					save_capture(frame2, path, 2);
				}
		}
			
			pressed_key  = waitKey(5);
			
	}
	
	Mat m_segm_c1, m_segm_c2;
	
	m_segm_c1 = obj_c1[1] - obj_c1[0];
	
	if(cm2)
		m_segm_c2 = obj_c2[1] - obj_c2[0];
			
	cout<< "Capturar p/ Mascara - Segmentacion... Terminado"<<endl;
	
	///	Mascara para la sombra
	
	cout<< "Capturar p/ Mascara - Sombra... "<<endl;
	
	//oscuro
	Mat osc_c1, osc_c2;
	Mat oscuro = Mat::zeros(proj_res_h,proj_res_w,CV_32FC1);
	imshow("Pattern Windows", oscuro);
	waitKey(0);
	
	pressed_key =0;
	while(pressed_key != 27)
	{
		
		cap1 >> frame1;
		imshow("Camara 1", frame1);
		
		if(cm2)
		{
			cap2 >> frame2;
			imshow("Camara 2", frame2);
		}
		
//		if (pressed_key == 10)
		if (pressed_key == 13)
		{
				cvtColor(frame1,frame1,cv::COLOR_BGR2GRAY);
				osc_c1 = frame1;
				
				save_capture(frame1, path, 1);
				
				if(cm2)
				{
					cvtColor(frame2,frame2,cv::COLOR_BGR2GRAY);
					osc_c2 = frame2;
					
					save_capture(frame2, path, 2);
				}
				
				break;
		}
			
			pressed_key  = waitKey(5);
			
	}
	
	//	brillante
	Mat bri_c1, bri_c2;
	Mat brillante = Mat::ones(proj_res_h,proj_res_w,CV_32FC1);
	imshow("Pattern Windows", brillante);
	waitKey(0);
	
	pressed_key =0;
	while(pressed_key != 27)
	{
		
		cap1 >> frame1;
		imshow("Camara 1", frame1);
		
		if(cm2)
		{
			cap2 >> frame2;
			imshow("Camara 2", frame2);
		}
		
		//		if (pressed_key == 10)
		if (pressed_key == 13)
		{
			cvtColor(frame1,frame1,cv::COLOR_BGR2GRAY);
			bri_c1 = frame1;
			
			save_capture(frame1, path, 1);
			
			if(cm2)
			{
				cvtColor(frame2,frame2,cv::COLOR_BGR2GRAY);
				bri_c2 = frame2;
				
				save_capture(frame2, path, 2);
			}
			break;
		}
		
		pressed_key  = waitKey(5);
		
	}
	
	// Mascara
	Mat m_sombra_c1, m_sombra_c2;
	
	m_sombra_c1 = bri_c1 - osc_c1;
	
	if(cm2)
		m_sombra_c2 = bri_c2 - osc_c2;
	
	cout<< "Capturar p/ Mascara - Sombra... Terminado"<<endl;
	
	// Binarizacion de la mascara
	cout<< "Binarizacion Mascara... "<<endl;
	int sl_c1 = 0, sh_c1 = 255, bl_c1 = 0, bh_c1 = 255;
	int sl_c2 = 0, sh_c2 = 255, bl_c2 = 0, bh_c2 = 255;
	
	// LOW | HIGH
	createTrackbar("Back_l","Camara 1",&bl_c1,255,NULL);
	createTrackbar("Back_h","Camara 1",&bh_c1,255,NULL);
	createTrackbar("Sombra_l","Camara 1",&sl_c1,255,NULL);
	createTrackbar("Sombra_h","Camara 1",&sh_c1,255,NULL);
	
	if(cm2)
	{
		createTrackbar("Back_l","Camara 2",&bl_c2,255,NULL);
		createTrackbar("Back_h","Camara 2",&bh_c2,255,NULL);
		createTrackbar("Sombra_l","Camara 2",&sl_c2,255,NULL);
		createTrackbar("Sombra_h","Camara 2",&sh_c2,255,NULL);
	}
	
	Mat sl_1, sh_1, bgl_1, bgh_1, sl_2, sh_2, bgl_2, bgh_2;
	Mat sh1, bg1, sh2, bg2;
	Mat mask_c1, mask_c2;
	
	pressed_key = 0;
	while(pressed_key != 27)
	{
		
		/// Threshold
		// Segmentacion
		threshold(m_segm_c1,bgl_1,bl_c1,255, THRESH_BINARY);
		threshold(m_segm_c1,bgh_1,bh_c1,255, THRESH_BINARY_INV);
		
		// Sombra
		threshold(m_sombra_c1,sl_1,sl_c1,255, THRESH_BINARY);
		threshold(m_sombra_c1,sh_1,sh_c1,255, THRESH_BINARY_INV);
		
		/// Mascara
		bitwise_and(sl_1,sh_1,sh1);
		bitwise_and(bgl_1,bgh_1,bg1);
		bitwise_and(sh1,bg1,mask_c1);
		
		/// Trackbar Posicion
		bl_c1 = getTrackbarPos("Back_l", "Camara 1");
		bh_c1 = getTrackbarPos("Back_h", "Camara 1");
		sl_c1 = getTrackbarPos("Sombra_l", "Camara 1");
		sh_c1 = getTrackbarPos("Sombra_h", "Camara 1");
		
		/// Mostrar Mascaras Finales
		imshow("Camara 1", mask_c1);
		
		if(cm2){
			/// Threshold
			// Segmentacion
			threshold(m_segm_c2,bgl_2,bl_c2,255, THRESH_BINARY);
			threshold(m_segm_c2,bgh_2,bh_c2,255, THRESH_BINARY_INV);
			
			// Sombra
			threshold(m_sombra_c2,sl_2,sl_c2,255, THRESH_BINARY);
			threshold(m_sombra_c2,sh_2,sh_c2,255, THRESH_BINARY_INV);
			
			/// Mascara
			bitwise_and(sl_2,sh_2,sh2);
			bitwise_and(bgl_2,bgh_2,bg2);
			bitwise_and(sh2,bg2,mask_c2);
			
			/// Trackbar Posicion
			bl_c2 = getTrackbarPos("Back_l", "Camara 2");
			bh_c2 = getTrackbarPos("Back_h", "Camara 2");
			sl_c2 = getTrackbarPos("Sombra_l", "Camara 2");
			sh_c2 = getTrackbarPos("Sombra_h", "Camara 2");
			
			imshow("Camara 2", mask_c2);
		}
		
		///
		pressed_key = waitKey(5);
		
		cap1 >> frame1; //no necesario...lo deje porque ocurria un error con el enlace al telefono sino... quitar despues...
		cap2 >> frame2; 
	}
	
	cout<< "Binarizacion Mascara... Terminado"<<endl<<endl;
	
	///-----------------------------------------------------------------------------
	/// Capturar y salvar imagenes de los patrones producidos (trabajo efectivo sobre la escena)
	///-----------------------------------------------------------------------------
	/// Continua lo anterior
	pressed_key = 0; 
	i=0;
	
	vector<Mat> test_g = sl.generate_gray_code_patterns();
	vector<Mat> test_b = sl.generate_binary_code_patterns();
	int cd=0;
	
	vector<Mat> cap_c1, cap_c2;
	
	cout<< "Capturar Patrones Codificados... "<<endl;
	pressed_key = 0;
	while(pressed_key != 27 && cd<test_g.size())
	{
		imshow("Pattern Windows", test_b[cd]);
		
		cap1 >> frame1;
		imshow("Camara 1", frame1);
		
		if(cm2)
		{
			cap2 >> frame2;
			imshow("Camara 2", frame2);
		}
		
		//		if (pressed_key == 10)
		if (pressed_key == 13)
		{
			cout<< "	Saving Capture..."<<endl;
			
			cap_c1.push_back(frame1);
			save_capture(frame1, path, 1);
			
			if(cm2)
			{
				cap_c2.push_back(frame2);
				save_capture(frame2, path, 2);
			}
			
			i++;
			cd++;
		}
		
		pressed_key  = waitKey(5);
		
	}
	
	cout<< "Capturar Patrones Codificados... Terminado"<<endl;
	
	destroyWindow("Pattern Windows");
	
	
	/// Decodificacion
	Mat t1, t2;
	cout<< "Decodificar Patrones... "<<endl;
	
	destroyWindow("Camara 1");
	save_capture(mask_c1, path, 1);
	t1 = sl.decode_captured_patterns(cap_c1,mask_c1);
	
	if(cm2)
	{
		destroyWindow("Camara 2");
		save_capture(mask_c2, path, 2);
		t2 = sl.decode_captured_patterns(cap_c2,mask_c2);
	}
	
	cout<< "Decodificar Patrones... Terminado"<<endl<<endl;
	///--------------------------------------------------------------------------------------------------------
	
	int N = t1.size().height;
	Mat inters;
	vector<Point3f> pc;
	
	cout<<"Reconstruccion... "<<endl;
	
	if (cm2){
		
		for(int i=0;i<N;i++) 
		{
			int row_1 = t1.at<int>(i,0);
			int col_1 = t1.at<int>(i,1);
			int cant_1 = t1.at<int>(i,2);
			
			int row_2 = t2.at<int>(i,0);
			int col_2 = t2.at<int>(i,1);
			int cant_2 = t2.at<int>(i,2);
			
			if (cant_1 && cant_2){					
				row_1 /= cant_1;
				col_1 /= cant_1;
				
				row_2 /= cant_2;
				col_2 /= cant_2;
				
				Mat p1 = (
						  Mat_<float>(1,3) << 
						  (float) row_1, (float) col_1, 1.0f
						  );
				
				Mat p2 = (
						  Mat_<float>(1,3) << 
						  (float) row_2, (float) col_2, 1.0f
						  );
				
				// Orden de elementos: Pendiente | Offset
				Mat line1 = sl.get_line(vc1[0],vc1[1],p1);
				Mat line2 = sl.get_line(vc2[0],vc2[1],p2);
				
				pc.push_back( sl.calc_intersection(line1,line2) );
				
			}
			
		}
	}
	
	
	cout<<"Reconstruccion... Terminado"<<endl<<endl;
	///-----------------------------------------------------------------------------
	/// Vizualisacion 3D
	///-----------------------------------------------------------------------------
	
	cout<<"Visualizacion 3D... "<<endl;	
	viz::Viz3d window("Coordinate Frame");
	window.setWindowSize(Size(500,500));
	window.setWindowPosition(Point(150,150));
	window.setBackgroundColor(); // black by default
	
	
	/// Systema de coordenadas del mundo
	viz::WLine axisX(Point3f(0.0f,0.0f,0.0f), Point3f(1.0f,0.0f,0.0f), Scalar(255,0,0));
	axisX.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig X", axisX);
	
	viz::WLine axisY(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,1.0f,0.0f), Scalar(0,0,255));
	axisY.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig Y", axisY);
	
	viz::WLine axisZ(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,0.0f,1.0f), Scalar(0,255,0));
	axisZ.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig Z", axisZ);
	
	/// Add coordinate axes
	draw_sys_coord(vc1[1], window);
	
	if (cm2)
		draw_sys_coord(vc2[1], window);
	
	/// Draw Point cloud
	
	for(int i=0;i<pc.size();i++) 
	{
		ostringstream os;
		os<<i;
		viz::WSphere p( pc[i], 0.05f );	
		window.showWidget("P_"+os.str(), p);
	}	
	
	window.spin();
	
	cout<<"Visualizacion 3D... Terminado"<<endl<<endl;
	
	///-----------------------------------------------------------------------------
	cout<<"Proceso Completo."<<endl;
}



void projector()
{
	SL sl(128,128);
	
	namedWindow("Show",CV_WINDOW_NORMAL);
	setWindowProperty("Show",CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);
	
	Mat dark = Mat::zeros(1024,1024,CV_8UC1);
	
	imshow("Show",dark);
	waitKey(0);
	
	
	Mat light = Mat::ones(1024,1024,CV_8UC1)*255;
	
	imshow("Show",light);
	waitKey(0);
	
	
	vector<Mat> bin = sl.generate_binary_code_patterns();
	
	unsigned char pressed_key =0;
	int i =0;
	while(pressed_key != 27 && i< bin.size())
	{
		imshow("Show",bin[i]);
		
		if(pressed_key == 10){
			i++;
		}
		
		pressed_key = waitKey(5);
	}
	
	vector<Mat> gry = sl.generate_gray_code_patterns();
	
	pressed_key =0;
	i =0;
	while(pressed_key != 27 && i< bin.size())
	{
		imshow("Show",gry[i]);
		
		if(pressed_key == 10){
			i++;
		}
		
		pressed_key = waitKey(5);
	}
	
}

///
void calibrar_reconstruir_mouse(bool cm2)
{
	namedWindow("Camara 1", 1);
	namedWindow("Camara 2", 1);
	setMouseCallback("Camara 1", callback_pc1,NULL);
	setMouseCallback("Camara 2", callback_pc2,NULL);
	
	VideoCapture cap1("http://192.168.1.103:4747/mjpegfeed?640x480");
	VideoCapture cap2("http://192.168.1.103:4747/mjpegfeed?640x480");
	
	SL sl(1024,768);
	Mat frame1,frame2;
	
	cout<<"Capturar Planilla ... "<<endl;
	int pressed_key = 0; 
	while(pressed_key != 27)
	{
		cap1 >> frame1;  // Capturar el frame actual de la camara.
		
		for(int j=0;j<ind1;j++) 
		{
			Point2f pc1;
			pc1.x = c1.at<float>(j,0);
			pc1.y = c1.at<float>(j,1);
			
			circle(frame1,pc1,5,Scalar(255));
		}
		
		imshow("Camara 1", frame1);
		
		
		if(cm2)
		{
			cap2 >> frame2;  // Capturar el frame actual de la camara.
			
			for(int j=0;j<ind2;j++) 
			{
				Point2f pc2;
				pc2.x = c2.at<float>(j,0);
				pc2.y = c2.at<float>(j,1);
				
				circle(frame2,pc2,5,Scalar(255));
			}
			
			imshow("Camara 2", frame2);
		}
		
		pressed_key  = waitKey(5);
	}
	
	setMouseCallback("Camara 1", NULL, NULL);
	
	if(cm2)
		setMouseCallback("Camara 2", NULL, NULL);
	
	cout<<"Capturar Planilla ... Terminado "<<endl;
	cout<< "Calibrando Camaras... "<<endl;
	vector<Mat> vc1, vc2;
	
	vc1 = sl.plane_base_calibration(cam1);
	
	if(cm2)
		vc2 = sl.plane_base_calibration(cam2);
	
	cout<< "Calibrando Camaras... Terminado"<<endl<<endl;
	
	cout<<"Visualizacion 3D... "<<endl;	
	viz::Viz3d window("Coordinate Frame");
	window.setWindowSize(Size(500,500));
	window.setWindowPosition(Point(150,150));
	window.setBackgroundColor(); // black by default
	
	
	/// Systema de coordenadas del mundo
	viz::WLine axisX(Point3f(0.0f,0.0f,0.0f), Point3f(1.0f,0.0f,0.0f), Scalar(255,0,0));
	axisX.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig X", axisX);
	
	viz::WLine axisY(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,1.0f,0.0f), Scalar(0,0,255));
	axisY.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig Y", axisY);
	
	viz::WLine axisZ(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,0.0f,1.0f), Scalar(0,255,0));
	axisZ.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig Z", axisZ);
	
	if(cm2){
		
		int pressed_key=0;
		while(pressed_key!=27)
		{
			cap1 >> frame1;
			cap2 >> frame2;
			
			cout<<pc1.size() << " | " << pc2.size()<<endl;
			if(pc1.size() == pc2.size()  && pc1.size() > 0 && pc2.size() > 0)
			{
				for(int i=0;i<pc1.size();i++) 
				{
					
					Point2f p1, p2;
					
					p1.x = pc1[i].at<float>(0,0);
					p1.y = pc1[i].at<float>(0,1);
					
					p2.x = pc2[i].at<float>(0,0);
					p2.y = pc2[i].at<float>(0,1);
					
					circle(frame1,p1,5,Scalar(0,255,0));
					circle(frame2,p2,5,Scalar(0,255,0));
					
					Mat line1 = sl.get_line(vc1[0],vc1[1],pc1[i]);
					Mat line2 = sl.get_line(vc2[0],vc2[1],pc2[i]);
					
					viz::WSphere p( sl.calc_intersection(line1,line2), 0.05f );	
					
					ostringstream os;
					os << i;
					window.showWidget("P_"+os.str(), p);
					
				}			
			}

			imshow("Camara 1", frame1);
			imshow("Camara 2", frame2);
			
			window.spinOnce();
			
			pressed_key = waitKey(5);
			
		}
	}
	
	window.spin();
	
	setMouseCallback("Camara 1",NULL,NULL);
	setMouseCallback("Camara 2",NULL,NULL);
}

/// 
void interseccion_prueba()
{
	SL sl(1027,768);
	/// Prueba Intersecciones
	Mat Im1 = load_im1();
	Mat Im2 = load_im2();
	
	Mat Em1 = load_em1();
	Mat Em2 = load_em2();
	
	Mat c1_obj = load_c1_obj();
	Mat c2_obj = load_c2_obj();
	
	vector<Point3f> pc;
	for(int i=0;i<c1_obj.size().height;i++) 
	{
		
		// Orden de elementos: Pendiente | Offset*/
		Mat line1 = sl.get_line(Im1,Em1,c1_obj.row(i));
		Mat line2 = sl.get_line(Im2,Em2,c2_obj.row(i));
		
		pc.push_back( sl.calc_intersection(line1,line2) );
		
	}
	
	cout<<"Visualizacion 3D... "<<endl;	
	viz::Viz3d window("Coordinate Frame");
	window.setWindowSize(Size(500,500));
	window.setWindowPosition(Point(150,150));
	window.setBackgroundColor(); // black by default
	
	
	/// Systema de coordenadas del mundo
	viz::WLine axisX(Point3f(0.0f,0.0f,0.0f), Point3f(1.0f,0.0f,0.0f), Scalar(255,0,0));
	axisX.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig X", axisX);
	
	viz::WLine axisY(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,1.0f,0.0f), Scalar(0,0,255));
	axisY.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig Y", axisY);
	
	viz::WLine axisZ(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,0.0f,1.0f), Scalar(0,255,0));
	axisZ.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig Z", axisZ);
	
	/// draw_sys_coord
	draw_sys_coord(Em1,window);
	draw_sys_coord(Em2,window);
	
	/// Draw Point cloud
	
	for(int i=0;i<pc.size();i++) 
	{
		ostringstream os;
		os<<i;
		viz::WSphere p( pc[i], 0.05f );	
		window.showWidget("P_"+os.str(), p);
	}	
	
	window.spin();
	
	cout<<"Visualizacion 3D... Terminado"<<endl<<endl;	
}

///
void saving_images(string path_calib, string path_img, string mask_path, VideoCapture c1, VideoCapture c2)
{
	SL sl(128,128);
	unsigned char pressed_key =0;
	int i =0;
	
	Mat f1,f2;
	
	while(pressed_key !=27 )
	{
		c1>>f1;
		c2>>f2;
		imshow("Camara 1", f1);
		imshow("Camara 2", f2);
		
		if(pressed_key == 13) //Enter
		{
			save_capture(f1,path_calib+"cam_1\\",i);
			save_capture(f2,path_calib+"cam_2\\",i);
			
			i++;
		}
		
		pressed_key = waitKey(5);
	}
	
	namedWindow("Show",CV_WINDOW_NORMAL);
	setWindowProperty("Show",CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);
	
	Mat dark = Mat::zeros(1024,768,CV_8UC1);
	
	imshow("Show",dark);
	pressed_key = 0; i = 0;
	while(pressed_key !=27 )
	{
		c1>>f1;
		c2>>f2;
		imshow("Camara 1", f1);
		imshow("Camara 2", f2);
		
		if(pressed_key == 13) //Spacebar
		{
			save_capture(f1,mask_path+"cam_1\\",i);
			save_capture(f2,mask_path+"cam_2\\",i);
			
			i++;
			break;
		}
		
		pressed_key = waitKey(5);
	}
	
	Mat light = Mat::ones(1024,768,CV_8UC1)*255;
	
	imshow("Show",light);
	pressed_key = 0;
	while(pressed_key !=27 )
	{
		c1>>f1;
		c2>>f2;
		imshow("Camara 1", f1);
		imshow("Camara 2", f2);
		
		if(pressed_key == 13) //Spacebar
		{
			save_capture(f1,mask_path+"cam_1\\",i);
			save_capture(f2,mask_path+"cam_2\\",i);
			
			i++;
			break;
		}
		
		pressed_key = waitKey(5);
	}
	
	vector<Mat> bin = sl.generate_binary_code_patterns();
	
	pressed_key = 0; i = 0;
	while(pressed_key != 27 && i< bin.size())
	{
		imshow("Show",bin[i]);
		
		c1>>f1;
		c2>>f2;
		
		imshow("Camara 1", f1);
		imshow("Camara 2", f2);

		if(pressed_key == 13){
			
			save_capture(f1,path_img+"cam_bin_1\\",i);
			save_capture(f2,path_img+"cam_bin_2\\",i);
			
			i++;
		}
		
		pressed_key = waitKey(5);
	}
	
	vector<Mat> gry = sl.generate_gray_code_patterns();
	
	pressed_key =0; i = 0;
	while(pressed_key != 27 && i< bin.size())
	{
		imshow("Show",gry[i]);
		c1>>f1;
		c2>>f2;
		
		imshow("Camara 1", f1);
		imshow("Camara 2", f2);

		if(pressed_key == 13){
			
			save_capture(f1,path_img+"cam_gray_1\\",i);
			save_capture(f2,path_img+"cam_gray_2\\",i);
			
			i++;
		}
		
		pressed_key = waitKey(5);
	}
	
}

void load_images(string path_calib, string path_img, string mask_path)
{
	SL sl(128,128);
	unsigned char pressed_key =0;
	int i;
	
	vector<Mat> calib_c1,calib_c2;
	for (i=0;i<5;i++)
	{
		ostringstream os;
		os<<i;
		calib_c1.push_back(imread(path_calib+"cam_1\\cap_"+os.str()+".png",CV_LOAD_IMAGE_GRAYSCALE));
		calib_c2.push_back(imread(path_calib+"cam_2\\cap_"+os.str()+".png",CV_LOAD_IMAGE_GRAYSCALE));
	}
	
	namedWindow("Camara 1",1);
	setMouseCallback("Camara 1", callback_c1, NULL);
	
	namedWindow("Camara 2",1);
	setMouseCallback("Camara 2", callback_c2, NULL);
	
	cout<<"Capturar Planilla ... "<<endl;
	pressed_key = 0; i =0;
	while(pressed_key != 27 && i<5)
	{
		
		for(int j=0;j<ind1;j++) 
		{
			Point2f pc1;
			pc1.x = c1.at<float>(j,0);
			pc1.y = c1.at<float>(j,1);
			
			circle(calib_c1[i],pc1,5,Scalar(255));
		}
		
		for(int j=0;j<ind2;j++) 
		{
			Point2f pc2;
			pc2.x = c2.at<float>(j,0);
			pc2.y = c2.at<float>(j,1);
			
			circle(calib_c2[i],pc2,5,Scalar(255));
		}
		
		imshow("Camara 1", calib_c1[i]);		
		imshow("Camara 2", calib_c2[i]);		
		//		if (pressed_key == 10)
		if (pressed_key == 13)
		{
			i++;
		}
		
		pressed_key  = waitKey(5);
	}
	
	setMouseCallback("Camara 1", NULL, NULL);
	
	setMouseCallback("Camara 2", NULL, NULL);
	
	cout<<"Capturar Planilla ... Terminado "<<endl;
	///
	///
	cout<< "Calibrando Camaras... "<<endl;
	vector<Mat> vc1, vc2;
	
	vc1 = sl.plane_base_calibration(cam1);
	vc2 = sl.plane_base_calibration(cam2);
	
	cout<< "Calibrando Camaras... Terminado"<<endl<<endl;
	
	///
	///
	Mat m_sombra_c1, m_sombra_c2;
	m_sombra_c1 = imread(mask_path+"cam_1\\cap_02.png",CV_LOAD_IMAGE_GRAYSCALE);
	m_sombra_c1 = imread(mask_path+"cam_1\\cap_12.png",CV_LOAD_IMAGE_GRAYSCALE) - m_sombra_c1;
	
	m_sombra_c2 = imread(mask_path+"cam_2\\cap_02.png",CV_LOAD_IMAGE_GRAYSCALE);
	m_sombra_c2 = imread(mask_path+"cam_2\\cap_12.png",CV_LOAD_IMAGE_GRAYSCALE) - m_sombra_c2;
	
	///
	cout<< "Binarizacion Mascara... "<<endl;
	int sl_c1 = 0, sh_c1 = 255;
	int sl_c2 = 0, sh_c2 = 255;
	
	// LOW | HIGH
	createTrackbar("Sombra_l","Camara 1",&sl_c1,255,NULL);
	createTrackbar("Sombra_h","Camara 1",&sh_c1,255,NULL);
	
	createTrackbar("Sombra_l","Camara 2",&sl_c2,255,NULL);
	createTrackbar("Sombra_h","Camara 2",&sh_c2,255,NULL);
	
	Mat sl_1, sh_1, sl_2, sh_2;
	Mat sh1, sh2;
	Mat mask_c1, mask_c2;
	
	pressed_key = 0;
	while(pressed_key != 27)
	{
		
		/// Threshold
		
		// Sombra
		threshold(m_sombra_c1,sl_1,sl_c1,255, THRESH_BINARY);
		threshold(m_sombra_c1,sh_1,sh_c1,255, THRESH_BINARY_INV);
		
		/// Mascara
		bitwise_and(sl_1,sh_1,mask_c1);
		
		/// Trackbar Posicion
		sl_c1 = getTrackbarPos("Sombra_l", "Camara 1");
		sh_c1 = getTrackbarPos("Sombra_h", "Camara 1");
		
		/// Mostrar Mascaras Finales
		imshow("Camara 1", mask_c1);
		
		/// Threshold
		// Sombra
		threshold(m_sombra_c2,sl_2,sl_c2,255, THRESH_BINARY);
		threshold(m_sombra_c2,sh_2,sh_c2,255, THRESH_BINARY_INV);
		
		/// Mascara
		bitwise_and(sl_2,sh_2,mask_c2);
		
		/// Trackbar Posicion
		sl_c2 = getTrackbarPos("Sombra_l", "Camara 2");
		sh_c2 = getTrackbarPos("Sombra_h", "Camara 2");
		
		imshow("Camara 2", mask_c2);
		
		pressed_key = waitKey(5);
	
	}
	///
	///
	vector<Mat> cap_c1, cap_c2;
	
	for(int i=0;i<28;i++) 
	{ 
		ostringstream os;
		os<<i;
		cap_c1.push_back(imread(path_img+"cam_bin_1\\cap_"+os.str()+".png",CV_LOAD_IMAGE_GRAYSCALE));
		cap_c2.push_back(imread(path_img+"cam_bin_2\\cap_"+os.str()+".png",CV_LOAD_IMAGE_GRAYSCALE));
	}
	
	/// Decodificacion
	Mat t1, t2;
	cout<< "Decodificar Patrones... "<<endl;

	t1 = sl.decode_captured_patterns(cap_c1,mask_c1);
	t2 = sl.decode_captured_patterns(cap_c2,mask_c2);
	
	cout<< "Decodificar Patrones... Terminado"<<endl<<endl;
	///--------------------------------------------------------------------------------------------------------
	
	int N = t1.size().height;
	Mat inters;
	vector<Point3f> pc;
	
	cout<<"Reconstruccion... "<<endl;
	
//	Mat cloud = Mat::zeros(t1.size().height,1,CV_32FC3);
	for(int i=0;i<N;i++) 
	{
		int row_1 = t1.at<int>(i,0);
		int col_1 = t1.at<int>(i,1);
		int cant_1 = t1.at<int>(i,2);
		
		int row_2 = t2.at<int>(i,0);
		int col_2 = t2.at<int>(i,1);
		int cant_2 = t2.at<int>(i,2);
		
		if (cant_1 && cant_2){					
			row_1 /= cant_1;
			col_1 /= cant_1;
			
			row_2 /= cant_2;
			col_2 /= cant_2;
			
			Mat p1 = (
					  Mat_<float>(1,3) << 
					  (float) row_1, (float) col_1, 1.0f
					  );
			
			Mat p2 = (
					  Mat_<float>(1,3) << 
					  (float) row_2, (float) col_2, 1.0f
					  );
			
			// Orden de elementos: Pendiente | Offset
			Mat line1 = sl.get_line(vc1[0],vc1[1],p1);
			Mat line2 = sl.get_line(vc2[0],vc2[1],p2);
			
			
//			cloud.at<float>(i,0) = sl.calc_intersection(line1,line2);
			pc.push_back( sl.calc_intersection(line1,line2) );
			
		}
		
	}
	Mat cloud = Mat(pc);
	
	cout<<"Reconstruccion... Terminado"<<endl<<endl;
	
	///-----------------------------------------------------------------------------
	/// Vizualisacion 3D
	///-----------------------------------------------------------------------------
	
	cout<<"Visualizacion 3D... "<<endl;	
	viz::Viz3d window("Coordinate Frame");
	window.setWindowSize(Size(500,500));
	window.setWindowPosition(Point(150,150));
	window.setBackgroundColor(); // black by default
	
	
	/// Systema de coordenadas del mundo
	viz::WLine axisX(Point3f(0.0f,0.0f,0.0f), Point3f(1.0f,0.0f,0.0f), Scalar(255,0,0));
	axisX.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig X", axisX);
	
	viz::WLine axisY(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,1.0f,0.0f), Scalar(0,0,255));
	axisY.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig Y", axisY);
	
	viz::WLine axisZ(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,0.0f,1.0f), Scalar(0,255,0));
	axisZ.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig Z", axisZ);
	
	/// Add coordinate axes
	draw_sys_coord(vc1[1], window);
	
	draw_sys_coord(vc2[1], window);
	
	/// Draw Point cloud
	
//	for(int i=0;i<pc.size();i++) 
//	{
//		ostringstream os;
//		os<<i;
//		
//		
//		viz::WSphere p( pc[i], 0.05f );	
//		window.showWidget("P_"+os.str(), p);
//	}	
//	
	viz::WCloud nube(cloud);
	window.showWidget("cloud",nube);
	
	imshow("Camara 1", calib_c1[0]);		
	imshow("Camara 2", calib_c2[0]);
	
	window.spin();
	
	cout<<"Visualizacion 3D... Terminado"<<endl<<endl;
	
}



#endif
