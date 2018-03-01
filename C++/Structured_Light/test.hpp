#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "auxiliares.h"
#include "SL.hpp"
#include "chessboard.hpp"

#include <vector>

using namespace std;
using namespace cv;


vector<Mat> load_p1()
{
	
	// 		x_img | y_img | x_pln | y_pln
	
	Mat img_1 = (Mat_<float>(4,4) << 
				337.00f , 394.00f , 0.0f, 0.0f,
				310.00f , 266.00f , 0.0f, 1.0f,
				463.00f , 384.00f , 1.0f, 0.0f,
				425.00f , 268.00f , 1.0f, 1.0f
	);

	Mat img_2 = (Mat_<float>(4,4) << 
				424.00f , 370.00f , 0.0f, 0.0f,
				424.00f , 238.00f , 0.0f, 1.0f,
				564.00f , 378.00f , 1.0f, 0.0f,
				563.00f , 237.00f , 1.0f, 1.0f
	);
	
	Mat img_3 = (Mat_<float>(4,4) << 
				255.00f , 393.00f , 0.0f, 0.0f,
				254.00f , 231.00f , 0.0f, 1.0f,
				352.00f , 373.00f , 1.0f, 0.0f,
				349.00f , 239.00f , 1.0f, 1.0f
	);
	
	
	vector<Mat> temp;
	
	temp.push_back(img_1);
	temp.push_back(img_2);
	temp.push_back(img_3);

	return temp;
}

vector<Mat> load_p2()
{
	
	// 		x_img | y_img | x_pln | y_pln
	
	Mat img_1 = (Mat_<float>(4,4) << 
				116.00f,   376.00f,     0.0f,	0.0f,
				142.00f,   266.00f,     0.0f,	1.0f,
				236.00f,   377.00f,     1.0f,	0.0f,
				252.00f,   265.00f,     1.0f,	1.0f
				);
	
	Mat img_2 = (Mat_<float>(4,4) << 
				 221.00f,   362.00f,     0.0f,	0.0f,
				 226.00f,   241.00f,     0.0f,	1.0f,
				 300.00f,   378.00f,     1.0f,	0.0f,
				 302.00f,   238.00f,     1.0f,	1.0f
				 );
	
	Mat img_3 = (Mat_<float>(4,4) << 
				 40.00f,   368.00f,     0.0f,	0.0f,
				 39.00f,   243.00f,     0.0f,	1.0f,
				 167.00f,   360.00f,     1.0f,	0.0f,
				 165.00f,   242.00f,     1.0f,	1.0f
				 );
	
	
	vector<Mat> temp;
	
	temp.push_back(img_1);
	temp.push_back(img_2);
	temp.push_back(img_3);
	
	return temp;
}

Mat load_c1_obj()
{
	Mat p = (
			Mat_<float>(16,3) <<
				491.0000,   474.0000,     1.0000,
				491.0000,   449.0000,     1.0000,
				506.0000,   438.0000,     1.0000,
				507.0000,   362.0000,     1.0000,
				468.0000,   351.0000,     1.0000,
				608.0000,   459.0000,     1.0000,
				606.0000,   436.0000,     1.0000,
				570.0000,   430.0000,     1.0000,
				569.0000,   358.0000,     1.0000,
				525.0000,   348.0000,     1.0000,
				531.0000,   410.0000,     1.0000,
				529.0000,   385.0000,     1.0000,
				528.0000,   362.0000,     1.0000,
				548.0000,   406.0000,     1.0000,
				548.0000,   385.0000,     1.0000,
				547.0000,   359.0000,     1.0000
			);
	
	return p;
}

Mat load_c2_obj()
{
	Mat p = (
			Mat_<float>(16,3) <<
				122.0000,   450.0000,     1.0000,
				121.0000,   426.0000,     1.0000,
				154.0000,   421.0000,     1.0000,
				154.0000,   353.0000,     1.0000,
				177.0000,   341.0000,     1.0000,
				243.0000,   456.0000,     1.0000,
				241.0000,   431.0000,     1.0000,
				216.0000,   422.0000,     1.0000,
				216.0000,   356.0000,     1.0000,
				236.0000,   344.0000,     1.0000,
				175.0000,   398.0000,     1.0000,
				175.0000,   376.0000,     1.0000,
				175.0000,   354.0000,     1.0000,
				196.0000,   398.0000,     1.0000,
				196.0000,   377.0000,     1.0000,
				196.0000,   355.0000,     1.0000
			);
	
	return p;
}

Mat load_im1()
{
	Mat p = (
			Mat_<float>(3,3) <<
				634.29728,     4.70994,   358.56174,
				0.00000,   628.52967,   224.49296,
				0.00000,     0.00000,     1.00000
			);
	
	return p;
}

Mat load_im2()
{
	Mat p = (
			 Mat_<float>(3,3) <<
			 610.47494,   -36.28043,   466.19670,
			 0.00000,   550.53742,   162.40289,
			 0.00000,     0.00000,     1.00000
			 );
	
	return p;
}

Mat load_em1()
{
	Mat p = (
			 Mat_<float>(3,4) <<
			 0.897271,  -0.212368,   0.380426,  -0.149550,
			 0.045344,  -0.810268,  -0.580040,   1.120461,
			 0.439145,   0.542511,  -0.717401,   4.154655
			 );
	
	return p;
}

Mat load_em2()
{
	Mat p = (
			 Mat_<float>(3,4) <<
			 0.995442,  -0.087940,  -0.093936,  -2.696020,
			 -0.026785,  -0.892096,  -0.448321,   1.899784,
			 -0.091533,   0.458460,  -0.890385,   4.896612
			 );
	
	return p;	
}

///
vector<Mat> load_pln()
{
	vector<Mat> load;
	Mat temp;
		
	for(int i=0;i<24;i++) 
	{
		ostringstream os;
		os<<i;
		Mat test2;
		temp = imread("Calibration/Pruebas/"+os.str()+"_calib_home.png",CV_LOAD_IMAGE_GRAYSCALE);
		load.push_back(temp);
	}
	
	temp = imread("Calibration/Pruebas/mascara_prueba.png",CV_LOAD_IMAGE_GRAYSCALE);
	load.push_back(temp);
	
	return load;
	
}

///-----------------------------------------------------------------------------
///		TEST CHESSBOARD COMPLETO: OBTENER EN MULTIPLES CAPTURAS DE LA MISMA 
///				CHESSBOARD LOS PUNTOS CORRESPONDIENTES, RELACIONADOS A LA 
///				REFERENCIA EN EL MUNDO REAL
///-----------------------------------------------------------------------------
/// HACER PRUEBAS CON LAS DEMAS COSAS, TODO JUNTO...
void prueba_chessboard(String path)
{
	Mat color, mask;
	int img_cant = 5;	//CANTIDAD DE IMAGENES, La seteo yo nomas
	Size chess_size(7,6);	//cantiadd de puntos a encontrar en la tabla:		Ancho/Alto
	Size gauss_size(11,11);	//paramaetro para la deteccion de los puntos claves y posterior filtrado, establece vecindades y espacio entre features
	
	
	//////////////////////////////////////////////////////////////////
	/// Cargar Imagenes desde archivo
	vector<Mat> imagenes;
	for(int i=0;i<img_cant;i++) 
	{
		ostringstream os;
		os<< i;
		Mat aux  =  imread(path+"cap_"+os.str()+".png",CV_LOAD_IMAGE_ANYCOLOR);
		imagenes.push_back(aux);
	}
	
	/// Mascara - Para quitar la propaganda del droidcam de las capturas
	//	mask = Mat::ones(1944,2592,CV_8UC1)*255;
	
	mask = Mat::ones(480,640,CV_8UC1)*255;
	for(int i=0;i<15;i++) 
	{
		for(int j=0;j<640;j++) 
		{
			mask.at<unsigned char>(i,j) = 0;
		}
	}
	
	///
	imagenes[0].copyTo(color);
	
	namedWindow("imagen",1);
	int val = 2050, maximo = 10000;
	createTrackbar("Threshold","imagen",&val,maximo);
	
	vector<Point2f>features;
	int pressed_key = 0, k=0, val2 = 0;
	while(pressed_key != 27)
	{
		
		imagenes[(k%img_cant)].copyTo(color);
		
		val = getTrackbarPos("Threshold","imagen");
		
		if(val2!=val){
			features.clear();
			features = chessboard_features_fix(color, chess_size,gauss_size,(float)val, mask);
			val2 = val;
			cout<< "Cantidad de features: "<< features.size() << endl;
		}
		
		for(int i =0; i< features.size(); i++)
		{
			circle(color,features[i],5,Scalar(0,255,0));
		}
		
		imshow("imagen", color);
		
		pressed_key = waitKey(5);
		if(pressed_key == 13)
		{
			features.clear();
			val2=0;
			k++;
		}
		
	}
	
	waitKey(0);
	
}

///-----------------------------------------------------------------------------
/// 	TEST FEATURES COMPLETO: 	DETECCION -> DESCRIPCION -> MATCHING
///-----------------------------------------------------------------------------
void test_features_completo(Mat org, Mat org2)
{
	
	Mat img, img2;
	cvtColor(org, img, CV_BGR2GRAY);
	cvtColor(org2, img2, CV_BGR2GRAY);
	
	Mat mask = Mat::ones(480,640,CV_8UC1)*255;
	for(int i=0;i<15;i++) 
	{
		for(int j=0;j<640;j++) 
		{
			mask.at<unsigned char>(i,j) = 0;
		}
	}
	
	cout<< "pre_score"<<endl;
	Mat harris = harris_score_image(img,Size(11,11),mask,HARRIS_NOBEL);
	Mat harris2 = harris_score_image(img2,Size(11,11),mask,HARRIS_NOBEL);
	cout<< "post_score"<<endl;
	
	cout<< "pre_filter"<<endl;
	//	vector<Point2f> v = harris_threshold(harris,20000);
	//	vector<Point2f> v2 = harris_threshold(harris2,20000);
	vector<Point2f> v = harris_threshold(harris,100);	/// recibe un float entre 0 y 10000
	vector<Point2f> v2 = harris_threshold(harris2,100);
	cout<< "post_filter"<<endl;
	cout<< "cant features: "<<v.size()<<" "<<v2.size()<<endl;
	
	cout<<endl;
	cout<< "pre_descp"<<endl;
	vector<descriptor> d = generate_descriptor(img, v);
	vector<descriptor> d2 = generate_descriptor(img2, v2);
	cout<< "post_descp"<<endl;
	
	cout<<endl;
	cout<< "pre_match"<<endl;
	vector<Mat> vm = feature_matching(d, d2);
	cout<< "post_match"<<endl;
	
	
	cout<<"VM: "<<vm.size()<<endl;
	
	Point2f p1, p2;
	Mat final_img = Mat::zeros(org.rows,org.cols*2, CV_8UC3);
	
	cout<< "PLOT FINAL MATCHING"<<endl;
	org.copyTo(final_img(Rect(0,0,org.cols,org.rows)));
	org2.copyTo(final_img(Rect(org.cols,0,org2.cols,img.rows)));
	
	//	int pressed_key=0, i = 0;
	//	Mat aux = final_img.clone();
	//	while(pressed_key!=27)
	//	{
	//		
	//		if(pressed_key == 13)
	//		{
	//			if(i> vm.size()-1){ i = 0;}
	//			
	//			aux = final_img.clone();
	//			p1 = Point2f(vm[i].at<float>(0),vm[i].at<float>(1));
	//			p2 = Point2f(vm[i].at<float>(2),vm[i].at<float>(3));
	//			
	////			circle(final_img ,p1,5, Scalar(0,255,0));
	////			circle(final_img ,Point2f(org.cols,0) + p2,5, Scalar(0,255,0));
	////			line(final_img ,p1, Point2f(org.cols,0 )+ p2,Scalar(0,255,0));
	//			circle(aux ,p1,5, Scalar(0,255,0));
	//			circle(aux ,Point2f(org.cols,0) + p2,5, Scalar(0,255,0));
	//			line(aux ,p1, Point2f(org.cols,0 )+ p2,Scalar(0,255,0));
	//			i++;
	//		}
	//		
	////		imshow("test", final_img);
	//		imshow("test", aux);
	//		pressed_key = waitKey(5);
	//	}
	
	Mat aux = final_img.clone();
	for(int i=0;i<vm.size();i++) 
	{
		
		p1 = Point2f(vm[i].at<float>(0),vm[i].at<float>(1));
		p2 = Point2f(vm[i].at<float>(2),vm[i].at<float>(3));
		
		circle(final_img ,p1,5, Scalar(0,255,0));
		circle(final_img ,Point2f(org.cols,0) + p2,5, Scalar(0,255,0));
		line(final_img ,p1, Point2f(org.cols,0 )+ p2,Scalar(0,255,0));
		
	}
	
	imshow("test", final_img);
	
	cout<< "descrp: "<< d.size() << " "<< d2.size()<<endl;
	cout<< "match: "<<vm.size()<<endl;
	
}

///
///
///
//void sistema_completo(string path, bool cm2)
//{
//
//	///-----------------------------------------------------------------------------	
//	/// Camera Setting
//	///-----------------------------------------------------------------------------	
//	
//	VideoCapture cap1("http://192.168.1.105:4747/mjpegfeed?640x480"); 
////	VideoCapture cap2("http://192.168.1.103:4747/mjpegfeed?640x480");
//	
//	VideoCapture cap2(0);
//	cap2.set(CV_CAP_PROP_FRAME_WIDTH,640);
//	cap2.set(CV_CAP_PROP_FRAME_HEIGHT,480);
//	
//	// Return si hubo error al abrir la camara.
//	if(!cap1.isOpened())
//	{
//		cout<<"Error al abrir la camara 1"<<endl;
//		return;
//	}
//	
//	//	 Return si hubo error al abrir la camara.
//	if(!cap2.isOpened())
//	{
//		cout<<"Error al abrir la camara 2"<<endl;
//		//return -1;
//		cm2 = false;
//	}
//	
//	unsigned char pressed_key;
//	int cam_id = 1, i;
//	
//	Mat frame1, frame2;
//	
//	cout<<"Comienza Proceso ... "<<endl;
//	///-----------------------------------------------------------------------------
//	/// Camera Captures
//	///-----------------------------------------------------------------------------
//	
//	namedWindow("Camara 1",1);
//	setMouseCallback("Camara 1", callback_c1, NULL);
//	
//	if (cm2)
//	{
//		namedWindow("Camara 2",1);
//		setMouseCallback("Camara 2", callback_c2, NULL);
//	}
//	
//	cout<<"Capturar Planilla ... "<<endl;
//	pressed_key = 0; 
//	while(pressed_key != 27)
//	{
//		cap1 >> frame1;  // Capturar el frame actual de la camara.
//		
//		for(int j=0;j<ind1;j++) 
//		{
//			Point2f pc1;
//			pc1.x = c1.at<float>(j,0);
//			pc1.y = c1.at<float>(j,1);
//			
//			circle(frame1,pc1,5,Scalar(255));
//		}
//		
//		imshow("Camara 1", frame1);
//		
//		
//		if(cm2)
//		{
//			cap2 >> frame2;  // Capturar el frame actual de la camara.
//			
//			for(int j=0;j<ind2;j++) 
//			{
//				Point2f pc2;
//				pc2.x = c2.at<float>(j,0);
//				pc2.y = c2.at<float>(j,1);
//				
//				circle(frame2,pc2,5,Scalar(255));
//			}
//			
//			imshow("Camara 2", frame2);
//		}
//		
////		if (pressed_key == 10)
//		if (pressed_key == 13)
//		{
//			save_capture(frame1, path, 1);
//			
//			if(cm2)
//			{
//				save_capture(frame2, path, 2);
//			}
//		}
//		
//		pressed_key  = waitKey(5);
//	}
//	
//	setMouseCallback("Camara 1", NULL, NULL);
//	
//	if(cm2)
//		setMouseCallback("Camara 2", NULL, NULL);
//	
//	cout<<"Capturar Planilla ... Terminado "<<endl;
//	
//	///-----------------------------------------------------------------------------
//	/// Calibracion y Construccion de la Escena General (Determinar Propiedades 
//	///		Extrinsecas de la camara para la posicionar todo en escena, 
//	///		poseteriormente triangular para reconstruir)
//	///-----------------------------------------------------------------------------
//	//		 Ancho  |	Alto	
//	int proj_res_w = 128, proj_res_h = 128;
//	
//	SL sl(proj_res_w,proj_res_h);
//	
//	cout<< "Calibrando Camaras... "<<endl;
//	vector<Mat> vc1, vc2;
//	
//	vc1 = sl.plane_base_calibration(cam1);
//	
//	if(cm2)
//		vc2 = sl.plane_base_calibration(cam2);
//	
//	cout<< "Calibrando Camaras... Terminado"<<endl<<endl;
/////-----------------------------------------------------------------------------
///// patrones codificados
/////-----------------------------------------------------------------------------
//	
/////-----------------------------------------------------------------------------
///// 
///// Construir mascara para filtrar sombra y fondo.
/////		Requiere capturas extra:
/////			Para Background:
/////				Capturas antes y despues de colocar el objeto (de por si al usar luz estructurada la escena se supone estatica asi que no deberia haber problema)
/////			Para sombra:
/////				Capturas full iluminada y oscura.
/////	
/////-----------------------------------------------------------------------------
//	
//	namedWindow("Pattern Windows",CV_WINDOW_NORMAL);
//	setWindowProperty("Pattern Windows", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
//	
//	/// Mascara de segmentado
//	
//	cout<< "Capturar p/ Mascara - Segmentacion... "<<endl;
//	
//	pressed_key = 0;
//	vector<Mat> obj_c1, obj_c2;
//	while(pressed_key != 27 && obj_c1.size()<2)
//	{
//		
//		cap1 >> frame1;
//		imshow("Camara 1", frame1);
//		
//		if(cm2)
//		{
//			cap2 >> frame2;
//			imshow("Camara 2", frame2);
//		}
//		
////		if (pressed_key == 10)	//enter
//		if (pressed_key == 13) 	//espacio
//		{
//				cvtColor(frame1,frame1,cv::COLOR_BGR2GRAY);
//				obj_c1.push_back(frame1.clone());
//				
//				save_capture(frame1, path, 1);
//				
//				if(cm2)
//				{
//					cvtColor(frame2,frame2,cv::COLOR_BGR2GRAY);
//					obj_c2.push_back(frame2.clone());
//					
//					save_capture(frame2, path, 2);
//				}
//		}
//			
//			pressed_key  = waitKey(5);
//			
//	}
//	
//	Mat m_segm_c1, m_segm_c2;
//	
//	m_segm_c1 = obj_c1[1] - obj_c1[0];
//	
//	if(cm2)
//		m_segm_c2 = obj_c2[1] - obj_c2[0];
//			
//	cout<< "Capturar p/ Mascara - Segmentacion... Terminado"<<endl;
//	
//	///	Mascara para la sombra
//	
//	cout<< "Capturar p/ Mascara - Sombra... "<<endl;
//	
//	//oscuro
//	Mat osc_c1, osc_c2;
//	Mat oscuro = Mat::zeros(proj_res_h,proj_res_w,CV_32FC1);
//	imshow("Pattern Windows", oscuro);
//	waitKey(0);
//	
//	pressed_key =0;
//	while(pressed_key != 27)
//	{
//		
//		cap1 >> frame1;
//		imshow("Camara 1", frame1);
//		
//		if(cm2)
//		{
//			cap2 >> frame2;
//			imshow("Camara 2", frame2);
//		}
//		
////		if (pressed_key == 10)
//		if (pressed_key == 13)
//		{
//				cvtColor(frame1,frame1,cv::COLOR_BGR2GRAY);
//				osc_c1 = frame1;
//				
//				save_capture(frame1, path, 1);
//				
//				if(cm2)
//				{
//					cvtColor(frame2,frame2,cv::COLOR_BGR2GRAY);
//					osc_c2 = frame2;
//					
//					save_capture(frame2, path, 2);
//				}
//				
//				break;
//		}
//			
//			pressed_key  = waitKey(5);
//			
//	}
//	
//	//	brillante
//	Mat bri_c1, bri_c2;
//	Mat brillante = Mat::ones(proj_res_h,proj_res_w,CV_32FC1);
//	imshow("Pattern Windows", brillante);
//	waitKey(0);
//	
//	pressed_key =0;
//	while(pressed_key != 27)
//	{
//		
//		cap1 >> frame1;
//		imshow("Camara 1", frame1);
//		
//		if(cm2)
//		{
//			cap2 >> frame2;
//			imshow("Camara 2", frame2);
//		}
//		
//		//		if (pressed_key == 10)
//		if (pressed_key == 13)
//		{
//			cvtColor(frame1,frame1,cv::COLOR_BGR2GRAY);
//			bri_c1 = frame1;
//			
//			save_capture(frame1, path, 1);
//			
//			if(cm2)
//			{
//				cvtColor(frame2,frame2,cv::COLOR_BGR2GRAY);
//				bri_c2 = frame2;
//				
//				save_capture(frame2, path, 2);
//			}
//			break;
//		}
//		
//		pressed_key  = waitKey(5);
//		
//	}
//	
//	// Mascara
//	Mat m_sombra_c1, m_sombra_c2;
//	
//	m_sombra_c1 = bri_c1 - osc_c1;
//	
//	if(cm2)
//		m_sombra_c2 = bri_c2 - osc_c2;
//	
//	cout<< "Capturar p/ Mascara - Sombra... Terminado"<<endl;
//	
//	// Binarizacion de la mascara
//	cout<< "Binarizacion Mascara... "<<endl;
//	int sl_c1 = 0, sh_c1 = 255, bl_c1 = 0, bh_c1 = 255;
//	int sl_c2 = 0, sh_c2 = 255, bl_c2 = 0, bh_c2 = 255;
//	
//	// LOW | HIGH
//	createTrackbar("Back_l","Camara 1",&bl_c1,255,NULL);
//	createTrackbar("Back_h","Camara 1",&bh_c1,255,NULL);
//	createTrackbar("Sombra_l","Camara 1",&sl_c1,255,NULL);
//	createTrackbar("Sombra_h","Camara 1",&sh_c1,255,NULL);
//	
//	if(cm2)
//	{
//		createTrackbar("Back_l","Camara 2",&bl_c2,255,NULL);
//		createTrackbar("Back_h","Camara 2",&bh_c2,255,NULL);
//		createTrackbar("Sombra_l","Camara 2",&sl_c2,255,NULL);
//		createTrackbar("Sombra_h","Camara 2",&sh_c2,255,NULL);
//	}
//	
//	Mat sl_1, sh_1, bgl_1, bgh_1, sl_2, sh_2, bgl_2, bgh_2;
//	Mat sh1, bg1, sh2, bg2;
//	Mat mask_c1, mask_c2;
//	
//	pressed_key = 0;
//	while(pressed_key != 27)
//	{
//		
//		/// Threshold
//		// Segmentacion
//		threshold(m_segm_c1,bgl_1,bl_c1,255, THRESH_BINARY);
//		threshold(m_segm_c1,bgh_1,bh_c1,255, THRESH_BINARY_INV);
//		
//		// Sombra
//		threshold(m_sombra_c1,sl_1,sl_c1,255, THRESH_BINARY);
//		threshold(m_sombra_c1,sh_1,sh_c1,255, THRESH_BINARY_INV);
//		
//		/// Mascara
//		bitwise_and(sl_1,sh_1,sh1);
//		bitwise_and(bgl_1,bgh_1,bg1);
//		bitwise_and(sh1,bg1,mask_c1);
//		
//		/// Trackbar Posicion
//		bl_c1 = getTrackbarPos("Back_l", "Camara 1");
//		bh_c1 = getTrackbarPos("Back_h", "Camara 1");
//		sl_c1 = getTrackbarPos("Sombra_l", "Camara 1");
//		sh_c1 = getTrackbarPos("Sombra_h", "Camara 1");
//		
//		/// Mostrar Mascaras Finales
//		imshow("Camara 1", mask_c1);
//		
//		if(cm2){
//			/// Threshold
//			// Segmentacion
//			threshold(m_segm_c2,bgl_2,bl_c2,255, THRESH_BINARY);
//			threshold(m_segm_c2,bgh_2,bh_c2,255, THRESH_BINARY_INV);
//			
//			// Sombra
//			threshold(m_sombra_c2,sl_2,sl_c2,255, THRESH_BINARY);
//			threshold(m_sombra_c2,sh_2,sh_c2,255, THRESH_BINARY_INV);
//			
//			/// Mascara
//			bitwise_and(sl_2,sh_2,sh2);
//			bitwise_and(bgl_2,bgh_2,bg2);
//			bitwise_and(sh2,bg2,mask_c2);
//			
//			/// Trackbar Posicion
//			bl_c2 = getTrackbarPos("Back_l", "Camara 2");
//			bh_c2 = getTrackbarPos("Back_h", "Camara 2");
//			sl_c2 = getTrackbarPos("Sombra_l", "Camara 2");
//			sh_c2 = getTrackbarPos("Sombra_h", "Camara 2");
//			
//			imshow("Camara 2", mask_c2);
//		}
//		
//		///
//		pressed_key = waitKey(5);
//		
//		cap1 >> frame1; //no necesario...lo deje porque ocurria un error con el enlace al telefono sino... quitar despues...
//		cap2 >> frame2; 
//	}
//	
//	cout<< "Binarizacion Mascara... Terminado"<<endl<<endl;
//	
//	///-----------------------------------------------------------------------------
//	/// Capturar y salvar imagenes de los patrones producidos (trabajo efectivo sobre la escena)
//	///-----------------------------------------------------------------------------
//	/// Continua lo anterior
//	pressed_key = 0; 
//	i=0;
//	
//	vector<Mat> test_g = sl.generate_code_patterns(GRAY);
//	vector<Mat> test_b = sl.generate_code_patterns();
////	vector<Mat> test_g = sl.generate_gray_code_patterns();
////	vector<Mat> test_b = sl.generate_binary_code_patterns();
//	int cd=0;
//	
//	vector<Mat> cap_c1, cap_c2;
//	
//	cout<< "Capturar Patrones Codificados... "<<endl;
//	pressed_key = 0;
//	while(pressed_key != 27 && cd<test_g.size())
//	{
//		imshow("Pattern Windows", test_b[cd]);
//		
//		cap1 >> frame1;
//		imshow("Camara 1", frame1);
//		
//		if(cm2)
//		{
//			cap2 >> frame2;
//			imshow("Camara 2", frame2);
//		}
//		
//		//		if (pressed_key == 10)
//		if (pressed_key == 13)
//		{
//			cout<< "	Saving Capture..."<<endl;
//			
//			cap_c1.push_back(frame1);
//			save_capture(frame1, path, 1);
//			
//			if(cm2)
//			{
//				cap_c2.push_back(frame2);
//				save_capture(frame2, path, 2);
//			}
//			
//			i++;
//			cd++;
//		}
//		
//		pressed_key  = waitKey(5);
//		
//	}
//	
//	cout<< "Capturar Patrones Codificados... Terminado"<<endl;
//	
//	destroyWindow("Pattern Windows");
//	
//	
//	/// Decodificacion
//	Mat t1, t2;
//	cout<< "Decodificar Patrones... "<<endl;
//	
//	destroyWindow("Camara 1");
//	save_capture(mask_c1, path, 1);
//	t1 = sl.decode_captured_patterns(cap_c1,mask_c1);
//	
//	if(cm2)
//	{
//		destroyWindow("Camara 2");
//		save_capture(mask_c2, path, 2);
//		t2 = sl.decode_captured_patterns(cap_c2,mask_c2);
//	}
//	
//	cout<< "Decodificar Patrones... Terminado"<<endl<<endl;
//	///--------------------------------------------------------------------------------------------------------
//	
//	int N = t1.size().height;
//	Mat inters;
//	vector<Point3f> pc;
//	
//	cout<<"Reconstruccion... "<<endl;
//	
//	if (cm2){
//		
//		for(int i=0;i<N;i++) 
//		{
//			int row_1 = t1.at<int>(i,0);
//			int col_1 = t1.at<int>(i,1);
//			int cant_1 = t1.at<int>(i,2);
//			
//			int row_2 = t2.at<int>(i,0);
//			int col_2 = t2.at<int>(i,1);
//			int cant_2 = t2.at<int>(i,2);
//			
//			if (cant_1 && cant_2){					
//				row_1 /= cant_1;
//				col_1 /= cant_1;
//				
//				row_2 /= cant_2;
//				col_2 /= cant_2;
//				
//				Mat p1 = (
//						  Mat_<float>(1,3) << 
//						  (float) row_1, (float) col_1, 1.0f
//						  );
//				
//				Mat p2 = (
//						  Mat_<float>(1,3) << 
//						  (float) row_2, (float) col_2, 1.0f
//						  );
//				
//				// Orden de elementos: Pendiente | Offset
//				Mat line1 = sl.get_line(vc1[0],vc1[1],p1);
//				Mat line2 = sl.get_line(vc2[0],vc2[1],p2);
//				
//				pc.push_back( sl.calc_intersection(line1,line2) );
//				
//			}
//			
//		}
//	}
//	
//	
//	cout<<"Reconstruccion... Terminado"<<endl<<endl;
//	///-----------------------------------------------------------------------------
//	/// Vizualisacion 3D
//	///-----------------------------------------------------------------------------
//	
//	cout<<"Visualizacion 3D... "<<endl;	
//	viz::Viz3d window("Coordinate Frame");
//	window.setWindowSize(Size(500,500));
//	window.setWindowPosition(Point(150,150));
//	window.setBackgroundColor(); // black by default
//	
//	
//	/// Systema de coordenadas del mundo
//	viz::WLine axisX(Point3f(0.0f,0.0f,0.0f), Point3f(1.0f,0.0f,0.0f), Scalar(255,0,0));
//	axisX.setRenderingProperty(viz::LINE_WIDTH, 1.0);
//	window.showWidget("Orig X", axisX);
//	
//	viz::WLine axisY(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,1.0f,0.0f), Scalar(0,0,255));
//	axisY.setRenderingProperty(viz::LINE_WIDTH, 1.0);
//	window.showWidget("Orig Y", axisY);
//	
//	viz::WLine axisZ(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,0.0f,1.0f), Scalar(0,255,0));
//	axisZ.setRenderingProperty(viz::LINE_WIDTH, 1.0);
//	window.showWidget("Orig Z", axisZ);
//	
//	/// Add coordinate axes
//	draw_sys_coord(vc1[1], window);
//	
//	if (cm2)
//		draw_sys_coord(vc2[1], window);
//	
//	/// Draw Point cloud
//	
//	for(int i=0;i<pc.size();i++) 
//	{
//		ostringstream os;
//		os<<i;
//		viz::WSphere p( pc[i], 0.05f );	
//		window.showWidget("P_"+os.str(), p);
//	}	
//	
//	window.spin();
//	
//	cout<<"Visualizacion 3D... Terminado"<<endl<<endl;
//	
//	///-----------------------------------------------------------------------------
//	cout<<"Proceso Completo."<<endl;
//}



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
	
	
//	vector<Mat> bin = sl.generate_binary_code_patterns();
	vector<Mat> bin = sl.generate_code_patterns();
	
	unsigned char pressed_key =0;
	int i =0;
	while(pressed_key != 27 && i< bin.size())
	{
		imshow("Show",bin[i]);
		
//		if(pressed_key == 10){
		if(pressed_key == 13){
			i++;
		}
		
		pressed_key = waitKey(5);
	}
	
//	vector<Mat> gry = sl.generate_gray_code_patterns();
	vector<Mat> gry = sl.generate_code_patterns(GRAY);
	
	pressed_key =0;
	i =0;
	while(pressed_key != 27 && i< bin.size())
	{
		imshow("Show",gry[i]);
		
//		if(pressed_key == 10){
		if(pressed_key == 13){
			i++;
		}
		
		pressed_key = waitKey(5);
	}
	
}

///
//void calibrar_reconstruir_mouse(bool cm2)
//{
//	namedWindow("Camara 1", 1);
//	namedWindow("Camara 2", 1);
//	setMouseCallback("Camara 1", callback_pc1,NULL);
//	setMouseCallback("Camara 2", callback_pc2,NULL);
//	
//	VideoCapture cap1("http://192.168.1.103:4747/mjpegfeed?640x480");
//	VideoCapture cap2("http://192.168.1.103:4747/mjpegfeed?640x480");
//	
//	SL sl(1024,768);
//	Mat frame1,frame2;
//	
//	cout<<"Capturar Planilla ... "<<endl;
//	int pressed_key = 0; 
//	while(pressed_key != 27)
//	{
//		cap1 >> frame1;  // Capturar el frame actual de la camara.
//		
//		for(int j=0;j<ind1;j++) 
//		{
//			Point2f pc1;
//			pc1.x = c1.at<float>(j,0);
//			pc1.y = c1.at<float>(j,1);
//			
//			circle(frame1,pc1,5,Scalar(255));
//		}
//		
//		imshow("Camara 1", frame1);
//		
//		
//		if(cm2)
//		{
//			cap2 >> frame2;  // Capturar el frame actual de la camara.
//			
//			for(int j=0;j<ind2;j++) 
//			{
//				Point2f pc2;
//				pc2.x = c2.at<float>(j,0);
//				pc2.y = c2.at<float>(j,1);
//				
//				circle(frame2,pc2,5,Scalar(255));
//			}
//			
//			imshow("Camara 2", frame2);
//		}
//		
//		pressed_key  = waitKey(5);
//	}
//	
//	setMouseCallback("Camara 1", NULL, NULL);
//	
//	if(cm2)
//		setMouseCallback("Camara 2", NULL, NULL);
//	
//	cout<<"Capturar Planilla ... Terminado "<<endl;
//	cout<< "Calibrando Camaras... "<<endl;
//	vector<Mat> vc1, vc2;
//	
//	vc1 = sl.plane_base_calibration(cam1);
//	
//	if(cm2)
//		vc2 = sl.plane_base_calibration(cam2);
//	
//	cout<< "Calibrando Camaras... Terminado"<<endl<<endl;
//	
//	cout<<"Visualizacion 3D... "<<endl;	
//	viz::Viz3d window("Coordinate Frame");
//	window.setWindowSize(Size(500,500));
//	window.setWindowPosition(Point(150,150));
//	window.setBackgroundColor(); // black by default
//	
//	
//	/// Systema de coordenadas del mundo
//	viz::WLine axisX(Point3f(0.0f,0.0f,0.0f), Point3f(1.0f,0.0f,0.0f), Scalar(255,0,0));
//	axisX.setRenderingProperty(viz::LINE_WIDTH, 1.0);
//	window.showWidget("Orig X", axisX);
//	
//	viz::WLine axisY(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,1.0f,0.0f), Scalar(0,0,255));
//	axisY.setRenderingProperty(viz::LINE_WIDTH, 1.0);
//	window.showWidget("Orig Y", axisY);
//	
//	viz::WLine axisZ(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,0.0f,1.0f), Scalar(0,255,0));
//	axisZ.setRenderingProperty(viz::LINE_WIDTH, 1.0);
//	window.showWidget("Orig Z", axisZ);
//	
//	if(cm2){
//		
//		int pressed_key=0;
//		while(pressed_key!=27)
//		{
//			cap1 >> frame1;
//			cap2 >> frame2;
//			
//			cout<<pc1.size() << " | " << pc2.size()<<endl;
//			if(pc1.size() == pc2.size()  && pc1.size() > 0 && pc2.size() > 0)
//			{
//				for(int i=0;i<pc1.size();i++) 
//				{
//					
//					Point2f p1, p2;
//					
//					p1.x = pc1[i].at<float>(0,0);
//					p1.y = pc1[i].at<float>(0,1);
//					
//					p2.x = pc2[i].at<float>(0,0);
//					p2.y = pc2[i].at<float>(0,1);
//					
//					circle(frame1,p1,5,Scalar(0,255,0));
//					circle(frame2,p2,5,Scalar(0,255,0));
//					
//					Mat line1 = sl.get_line(vc1[0],vc1[1],pc1[i]);
//					Mat line2 = sl.get_line(vc2[0],vc2[1],pc2[i]);
//					
//					viz::WSphere p( sl.calc_intersection(line1,line2), 0.05f );	
//					
//					ostringstream os;
//					os << i;
//					window.showWidget("P_"+os.str(), p);
//					
//				}			
//			}
//
//			imshow("Camara 1", frame1);
//			imshow("Camara 2", frame2);
//			
//			window.spinOnce();
//			
//			pressed_key = waitKey(5);
//			
//		}
//	}
//	
//	window.spin();
//	
//	setMouseCallback("Camara 1",NULL,NULL);
//	setMouseCallback("Camara 2",NULL,NULL);
//}

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
//	draw_sys_coord(Em1,window);
//	draw_sys_coord(Em2,window);
	
	/// Draw Point cloud
	Mat cloud = Mat(pc);
	
	viz::WCloud nube(cloud);
	window.showWidget("cloud",nube);
	
//	for(int i=0;i<pc.size();i++) 
//	{
//		ostringstream os;
//		os<<i;
//		viz::WSphere p( pc[i], 0.05f );	
//		window.showWidget("P_"+os.str(), p);
//	}	
//	
	window.spin();
	
	cout<<"Visualizacion 3D... Terminado"<<endl<<endl;	
}

///
//////void saving_images(string path_calib, string path_img, string mask_path, VideoCapture c1, VideoCapture c2)
//////{
//////	SL sl(128,128);
//////	unsigned char pressed_key =0;
//////	int i =0;
//////	
//////	Mat f1,f2;
//////	
//////	while(pressed_key !=27 )
//////	{
//////		c1>>f1;
//////		c2>>f2;
//////		imshow("Camara 1", f1);
//////		imshow("Camara 2", f2);
//////		
//////		if(pressed_key == 13) //Enter
//////		{
////////			save_capture(f1,path_calib+"cam_1\\",i);
////////			save_capture(f2,path_calib+"cam_2\\",i);
//////			
//////			i++;
//////		}
//////		
//////		pressed_key = waitKey(5);
//////	}
//////	
//////	namedWindow("Show",CV_WINDOW_NORMAL);
//////	setWindowProperty("Show",CV_WND_PROP_FULLSCREEN,CV_WINDOW_FULLSCREEN);
//////	
//////	Mat dark = Mat::zeros(1024,768,CV_8UC1);
//////	
//////	imshow("Show",dark);
//////	pressed_key = 0; i = 0;
//////	while(pressed_key !=27 )
//////	{
//////		c1>>f1;
//////		c2>>f2;
//////		imshow("Camara 1", f1);
//////		imshow("Camara 2", f2);
//////		
//////		if(pressed_key == 13) //Spacebar
//////		{
////////			save_capture(f1,mask_path+"cam_1\\",i);
////////			save_capture(f2,mask_path+"cam_2\\",i);
//////			
//////			i++;
//////			break;
//////		}
//////		
//////		pressed_key = waitKey(5);
//////	}
//////	
//////	Mat light = Mat::ones(1024,768,CV_8UC1)*255;
//////	
//////	imshow("Show",light);
//////	pressed_key = 0;
//////	while(pressed_key !=27 )
//////	{
//////		c1>>f1;
//////		c2>>f2;
//////		imshow("Camara 1", f1);
//////		imshow("Camara 2", f2);
//////		
//////		if(pressed_key == 13) //Spacebar
//////		{
////////			save_capture(f1,mask_path+"cam_1\\",i);
////////			save_capture(f2,mask_path+"cam_2\\",i);
//////			
//////			i++;
//////			break;
//////		}
//////		
//////		pressed_key = waitKey(5);
//////	}
//////	
////////	vector<Mat> bin = sl.generate_binary_code_patterns();
//////	vector<Mat> bin = sl.generate_code_patterns();
//////	
//////	pressed_key = 0; i = 0;
//////	while(pressed_key != 27 && i< bin.size())
//////	{
//////		imshow("Show",bin[i]);
//////		
//////		c1>>f1;
//////		c2>>f2;
//////		
//////		imshow("Camara 1", f1);
//////		imshow("Camara 2", f2);
//////
//////		if(pressed_key == 13){
//////			
////////			save_capture(f1,path_img+"cam_bin_1\\",i);
////////			save_capture(f2,path_img+"cam_bin_2\\",i);
//////			
//////			i++;
//////		}
//////		
//////		pressed_key = waitKey(5);
//////	}
//////	
////////	vector<Mat> gry = sl.generate_gray_code_patterns();
//////	vector<Mat> gry = sl.generate_code_patterns(GRAY);
//////	
//////	pressed_key =0; i = 0;
//////	while(pressed_key != 27 && i< bin.size())
//////	{
//////		imshow("Show",gry[i]);
//////		c1>>f1;
//////		c2>>f2;
//////		
//////		imshow("Camara 1", f1);
//////		imshow("Camara 2", f2);
//////
//////		if(pressed_key == 13){
//////			
////////			save_capture(f1,path_img+"cam_gray_1\\",i);
////////			save_capture(f2,path_img+"cam_gray_2\\",i);
//////			
//////			i++;
//////		}
//////		
//////		pressed_key = waitKey(5);
//////	}
//////	
//////}

//void load_images(string path_calib, string path_img, string mask_path)
//{
//	SL sl(128,128);
//	unsigned char pressed_key =0;
//	int i;
//	
//	vector<Mat> calib_c1,calib_c2;
//	for (i=0;i<5;i++)
//	{
//		ostringstream os;
//		os<<i;
//		calib_c1.push_back(imread(path_calib+"cam_1\\cap_"+os.str()+".png",CV_LOAD_IMAGE_GRAYSCALE));
//		calib_c2.push_back(imread(path_calib+"cam_2\\cap_"+os.str()+".png",CV_LOAD_IMAGE_GRAYSCALE));
//	}
//	
//	namedWindow("Camara 1",1);
//	setMouseCallback("Camara 1", callback_c1, NULL);
//	
//	namedWindow("Camara 2",1);
//	setMouseCallback("Camara 2", callback_c2, NULL);
//	
//	cout<<"Capturar Planilla ... "<<endl;
//	pressed_key = 0; i =0;
//	while(pressed_key != 27 && i<5)
//	{
//		
//		for(int j=0;j<ind1;j++) 
//		{
//			Point2f pc1;
//			pc1.x = c1.at<float>(j,0);
//			pc1.y = c1.at<float>(j,1);
//			
//			circle(calib_c1[i],pc1,5,Scalar(255));
//		}
//		
//		for(int j=0;j<ind2;j++) 
//		{
//			Point2f pc2;
//			pc2.x = c2.at<float>(j,0);
//			pc2.y = c2.at<float>(j,1);
//			
//			circle(calib_c2[i],pc2,5,Scalar(255));
//		}
//		
//		imshow("Camara 1", calib_c1[i]);		
//		imshow("Camara 2", calib_c2[i]);		
//		//		if (pressed_key == 10)
//		if (pressed_key == 13)
//		{
//			i++;
//		}
//		
//		pressed_key  = waitKey(5);
//	}
//	
//	setMouseCallback("Camara 1", NULL, NULL);
//	
//	setMouseCallback("Camara 2", NULL, NULL);
//	
//	cout<<"Capturar Planilla ... Terminado "<<endl;
//	///
//	///
//	cout<< "Calibrando Camaras... "<<endl;
//	vector<Mat> vc1, vc2;
//	
//	vc1 = sl.plane_base_calibration(cam1);
//	vc2 = sl.plane_base_calibration(cam2);
//	
//	cout<< "Calibrando Camaras... Terminado"<<endl<<endl;
//	
//	///
//	///
//	Mat m_sombra_c1, m_sombra_c2;
//	m_sombra_c1 = imread(mask_path+"cam_1\\cap_02.png",CV_LOAD_IMAGE_GRAYSCALE);
//	m_sombra_c1 = imread(mask_path+"cam_1\\cap_12.png",CV_LOAD_IMAGE_GRAYSCALE) - m_sombra_c1;
//	
//	m_sombra_c2 = imread(mask_path+"cam_2\\cap_02.png",CV_LOAD_IMAGE_GRAYSCALE);
//	m_sombra_c2 = imread(mask_path+"cam_2\\cap_12.png",CV_LOAD_IMAGE_GRAYSCALE) - m_sombra_c2;
//	
//	///
//	cout<< "Binarizacion Mascara... "<<endl;
//	int sl_c1 = 0, sh_c1 = 255;
//	int sl_c2 = 0, sh_c2 = 255;
//	
//	// LOW | HIGH
//	createTrackbar("Sombra_l","Camara 1",&sl_c1,255,NULL);
//	createTrackbar("Sombra_h","Camara 1",&sh_c1,255,NULL);
//	
//	createTrackbar("Sombra_l","Camara 2",&sl_c2,255,NULL);
//	createTrackbar("Sombra_h","Camara 2",&sh_c2,255,NULL);
//	
//	Mat sl_1, sh_1, sl_2, sh_2;
//	Mat sh1, sh2;
//	Mat mask_c1, mask_c2;
//	
//	pressed_key = 0;
//	while(pressed_key != 27)
//	{
//		
//		/// Threshold
//		
//		// Sombra
//		threshold(m_sombra_c1,sl_1,sl_c1,255, THRESH_BINARY);
//		threshold(m_sombra_c1,sh_1,sh_c1,255, THRESH_BINARY_INV);
//		
//		/// Mascara
//		bitwise_and(sl_1,sh_1,mask_c1);
//		
//		/// Trackbar Posicion
//		sl_c1 = getTrackbarPos("Sombra_l", "Camara 1");
//		sh_c1 = getTrackbarPos("Sombra_h", "Camara 1");
//		
//		/// Mostrar Mascaras Finales
//		imshow("Camara 1", mask_c1);
//		
//		/// Threshold
//		// Sombra
//		threshold(m_sombra_c2,sl_2,sl_c2,255, THRESH_BINARY);
//		threshold(m_sombra_c2,sh_2,sh_c2,255, THRESH_BINARY_INV);
//		
//		/// Mascara
//		bitwise_and(sl_2,sh_2,mask_c2);
//		
//		/// Trackbar Posicion
//		sl_c2 = getTrackbarPos("Sombra_l", "Camara 2");
//		sh_c2 = getTrackbarPos("Sombra_h", "Camara 2");
//		
//		imshow("Camara 2", mask_c2);
//		
//		pressed_key = waitKey(5);
//	
//	}
//	///
//	///
//	vector<Mat> cap_c1, cap_c2;
//	
//	for(int i=0;i<28;i++) 
//	{ 
//		ostringstream os;
//		os<<i;
//		cap_c1.push_back(imread(path_img+"cam_bin_1\\cap_"+os.str()+".png",CV_LOAD_IMAGE_GRAYSCALE));
//		cap_c2.push_back(imread(path_img+"cam_bin_2\\cap_"+os.str()+".png",CV_LOAD_IMAGE_GRAYSCALE));
//	}
//	
//	/// Decodificacion
//	Mat t1, t2;
//	cout<< "Decodificar Patrones... "<<endl;
//
//	t1 = sl.decode_captured_patterns(cap_c1,mask_c1);
//	t2 = sl.decode_captured_patterns(cap_c2,mask_c2);
//	
//	cout<< "Decodificar Patrones... Terminado"<<endl<<endl;
//	///--------------------------------------------------------------------------------------------------------
//	
//	int N = t1.size().height;
//	Mat inters;
//	vector<Point3f> pc;
//	
//	cout<<"Reconstruccion... "<<endl;
//	
////	Mat cloud = Mat::zeros(t1.size().height,1,CV_32FC3);
//	for(int i=0;i<N;i++) 
//	{
//		int row_1 = t1.at<int>(i,0);
//		int col_1 = t1.at<int>(i,1);
//		int cant_1 = t1.at<int>(i,2);
//		
//		int row_2 = t2.at<int>(i,0);
//		int col_2 = t2.at<int>(i,1);
//		int cant_2 = t2.at<int>(i,2);
//		
//		if (cant_1 && cant_2){					
//			row_1 /= cant_1;
//			col_1 /= cant_1;
//			
//			row_2 /= cant_2;
//			col_2 /= cant_2;
//			
//			Mat p1 = (
//					  Mat_<float>(1,3) << 
//					  (float) row_1, (float) col_1, 1.0f
//					  );
//			
//			Mat p2 = (
//					  Mat_<float>(1,3) << 
//					  (float) row_2, (float) col_2, 1.0f
//					  );
//			
//			// Orden de elementos: Pendiente | Offset
//			Mat line1 = sl.get_line(vc1[0],vc1[1],p1);
//			Mat line2 = sl.get_line(vc2[0],vc2[1],p2);
//			
//			
////			cloud.at<float>(i,0) = sl.calc_intersection(line1,line2);
//			pc.push_back( sl.calc_intersection(line1,line2) );
//			
//		}
//		
//	}
//	Mat cloud = Mat(pc);
//	
//	cout<<"Reconstruccion... Terminado"<<endl<<endl;
//	
//	///-----------------------------------------------------------------------------
//	/// Vizualisacion 3D
//	///-----------------------------------------------------------------------------
//	
//	cout<<"Visualizacion 3D... "<<endl;	
//	viz::Viz3d window("Coordinate Frame");
//	window.setWindowSize(Size(500,500));
//	window.setWindowPosition(Point(150,150));
//	window.setBackgroundColor(); // black by default
//	
//	
//	/// Systema de coordenadas del mundo
//	viz::WLine axisX(Point3f(0.0f,0.0f,0.0f), Point3f(1.0f,0.0f,0.0f), Scalar(255,0,0));
//	axisX.setRenderingProperty(viz::LINE_WIDTH, 1.0);
//	window.showWidget("Orig X", axisX);
//	
//	viz::WLine axisY(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,1.0f,0.0f), Scalar(0,0,255));
//	axisY.setRenderingProperty(viz::LINE_WIDTH, 1.0);
//	window.showWidget("Orig Y", axisY);
//	
//	viz::WLine axisZ(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,0.0f,1.0f), Scalar(0,255,0));
//	axisZ.setRenderingProperty(viz::LINE_WIDTH, 1.0);
//	window.showWidget("Orig Z", axisZ);
//	
//	/// Add coordinate axes
//	draw_sys_coord(vc1[1], window);
//	
//	draw_sys_coord(vc2[1], window);
//	
//	/// Draw Point cloud
//	
////	for(int i=0;i<pc.size();i++) 
////	{
////		ostringstream os;
////		os<<i;
////		
////		
////		viz::WSphere p( pc[i], 0.05f );	
////		window.showWidget("P_"+os.str(), p);
////	}	
////	
//	viz::WCloud nube(cloud);
//	window.showWidget("cloud",nube);
//	
//	imshow("Camara 1", calib_c1[0]);		
//	imshow("Camara 2", calib_c2[0]);
//	
//	window.spin();
//	
//	cout<<"Visualizacion 3D... Terminado"<<endl<<endl;
//	
//}

///
void prueba_calib_auto_chessboard(string path_c1, string path_c2)
{
	/// Cargar Imagenes desde archivo
	vector<Mat> imagenes;
	Mat color;
	int img_cant = 5;
	Size chess_size(7,6);	//cantidad de puntos a encontrar en la tabla:		Ancho/Alto
	Size gauss_size(11,11);	//paramaetro para la deteccion de los puntos claves y posterior filtrado, establece vecindades y espacio entre features
	
	for(int i=0;i<img_cant;i++) 
	{
		ostringstream os;
		os<< i;
		Mat aux  =  imread(path_c1+"cap_"+os.str()+".png",CV_LOAD_IMAGE_ANYCOLOR);
//		Mat aux  =  imread(path_c1+"cap_"+os.str()+".png",CV_LOAD_IMAGE_ANYCOLOR);
		imagenes.push_back(aux);
	}
	
	/// Mascara - Para quitar la propaganda del droidcam de las capturas
//	Mat	mask = Mat::ones(1944,2592,CV_8UC1)*255;
	
	Mat mask = Mat::ones(480,640,CV_8UC1)*255;
	for(int i=0;i<15;i++) 
	{
		for(int j=0;j<640;j++) 
		{
			mask.at<unsigned char>(i,j) = 0;
		}
	}
	
	///
	imagenes[0].copyTo(color);
	
	namedWindow("imagen",1);
	int val = 2050, maximo = 10000;
	createTrackbar("Threshold","imagen",&val,maximo);
	
	vector<Point2f> features;
	vector<vector<Point2f>>f;
	int pressed_key = 0, k=0, val2 = 0;
	while(pressed_key != 27)
	{
		
		imagenes[(k%img_cant)].copyTo(color);
		
		val = getTrackbarPos("Threshold","imagen");
		
		if(val2!=val){
			features.clear();
			features = chessboard_features_fix(color, chess_size,gauss_size,(float)val, mask);
			
//			Mat copy;
//			for(int i=25;i<28;i++) 
//			{
//				copy = color.clone();
//				
//				cout<< features[i]<<endl;
//				circle(copy,features[i],5,Scalar(0,255,0));
//				
//				show_mat(copy,IMAGEN,0);
//				waitKey(0);
//			}
			
			val2 = val;
			cout<< "Cantidad de features: "<< features.size() << endl;
		}
		
		for(int i =0; i< features.size(); i++)
		{
			circle(color,features[i],5,Scalar(0,255,0));
		}
		
		imshow("imagen", color);
		
		pressed_key = waitKey(5);
		if(pressed_key == 13)
		{
			if(!features.empty())
			{
				f.push_back(features);
			}
			
			features.clear();
			val2=0;
			k++;
		}
		
	}
	
	cout<<f.size()<<endl;
	/// La chessboard es de 7x7, entonces tengo 49 puntos para asignar
	vector<Point2f> chessboard;
	vector<Point3f> chess_cloud;
	for(int j=0;j<chess_size.height;j++)
	{
		for(int i=0;i<chess_size.width;i++) 
		{
			chessboard.push_back( Point2f(i,((chess_size.height-1)-j)) );			
			chess_cloud.push_back( Point3f(i,((chess_size.height-1)-j),0) );			
			
			cout<< i << " "<< 5-j<< endl;
		}
	}
	
	SL sl(1024,768);
	vector<Mat> camera;
//	for(int i=0;i<f.size();i++) 
//	{ 			
		camera = sl.plane_base_calibration( f ,chessboard );
//	}
	
	///-----------------------------------------------------------------------------
	/// Vizualisacion 3D
	///-----------------------------------------------------------------------------
	
	cout<<"Visualizacion 3D... "<<endl;	
	viz::Viz3d window("Coordinate Frame");
	window.setWindowSize(Size(500,500));
	window.setWindowPosition(Point(150,150));
	window.setBackgroundColor(); // black by default
	
	
	/// Systema de coordenadas del mundo
	viz::WLine axisX(Point3f(0.0f,0.0f,0.0f), Point3f(1.0f,0.0f,0.0f), Scalar(255,0,0));	//AZUL
	axisX.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig X", axisX);
	
	viz::WLine axisY(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,1.0f,0.0f), Scalar(0,0,255));	//ROJO
	axisY.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig Y", axisY);
	
	viz::WLine axisZ(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,0.0f,1.0f), Scalar(0,255,0));	//VERDE
	axisZ.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig Z", axisZ);
	
	/// Add coordinate axes
//	cout<<endl;
//	show_mat(camera[1]);
//	waitKey(0);
//	
	for(int i=1;i<camera.size();i++)
	{
		draw_sys_coord(camera[i], window);
	}
//	draw_sys_coord(camera[1], window);
//	draw_sys_coord(camera[2], window);
//	draw_sys_coord(camera[3], window);
//	draw_sys_coord(camera[4], window);
	
	/// Reconstruccion
	vector<Point3f> pc;
	int c1 = 1, c2 = 2;
	
	for(int i=0;i<chess_size.height*chess_size.width;i++) 
	{
		
		Mat p1 = ( Mat_<float>(1,3)<<
						f[c1][i].x,
						f[c1][i].y,
						1.0f			);
		
		Mat p2 = ( Mat_<float>(1,3)<<
						f[c2][i].x,
						f[c2][i].y,
						1.0f			);
		Mat l1 = sl.get_line(camera[0],camera[c1+1], p1);
		Mat l2 = sl.get_line(camera[0],camera[c2+1], p2);
		
		pc.push_back(sl.calc_intersection(l1,l2));
		
	}
	
	Mat cloud = Mat(pc);
	Mat real = Mat(chess_cloud);
	viz::WCloud nube(cloud);
	viz::WCloud nube_real(real,viz::Color(0,255,0));
	window.showWidget("cloud",nube);
	window.showWidget("Puntos reales",nube_real);
	
	
	Mat error;
	pow(cloud - real,2, error);
	double err=0;
	
	for(int i=0;i<error.rows;i++) 
	{
		for(int j=0;j<error.cols;j++) 
		{
			err+=error.at<float>(i,j);
		}
	}
	err = err/(error.rows*error.cols);
	
	cout<<endl;
	cout<< "ERROR CUADRATICO: "<< err<<endl;
//	sl.get_line(camera[0],camera[1],f[0])
	
	window.spin();
	waitKey(0);
	
}


///

//static int pct_id = 0;
void guardar_foto(string path, Mat img, int cam=0, int pct_id=0)
{
	
	ostringstream capture_id;
	capture_id << cam;
	capture_id << "_";
	capture_id << pct_id;
//	pct_id++;
	
	imwrite(path + "\\c"+ capture_id.str()+".png", img);
}

void dos_camaras(int ip1, int ip2, string path)
{
	ostringstream o1, o2;
	o1<<ip1;
	o2<<ip2;
	VideoCapture c1("http://192.168.1."+o1.str()+":4747/mjpegfeed?640x480");
	VideoCapture c2("http://192.168.1."+o2.str()+":4747/mjpegfeed?640x480");
	
	int key=0, pct_1 = 0, pct_2 = 0;
	Mat im1, im2;
	while(key!=27)
	{
		c1>>im1;
		
//		Mat inv_y = (Mat_<float>(2,3)<<	// la camara estaba dada vuelta
//					 1.0f,0.0f,0.0f,
//					 0.0f,-1.0f,im1.rows
//					 );
//		warpAffine( im1, im1, inv_y, im1.size() );
		
		
		c2>>im2;
		
		imshow("Cam1", im1);
		imshow("Cam2", im2);
//		// ENTER, CAMARA 1
//		if(key == 13)
//		{
//			guardar_foto(path,im1,1,pct_1);
//			pct_1++;
//		}
//		
//		//BARRA ESPACIADORA, CAMARA 2
//		if(key == 32)
//		{
//			guardar_foto(path,im2,2, pct_2);
//			pct_2++;
//		}
		// ENTER, CAMARA 1
		if(key == 13)
		{
			guardar_foto(path,im1,1,pct_1);
			pct_1++;
			
			guardar_foto(path,im2,2, pct_2);
			pct_2++;
		}
		
		key=waitKey(15);
	}
}

///
/// TODO JUNTO
///
void prueba_todo_junto(string path_c1, string path_c2)
{
	/// Cargar Imagenes desde archivo
	vector<Mat> imagenes;
	Mat color;
	int img_cant = 5;
	Size chess_size(7,6);	//cantidad de puntos a encontrar en la tabla:		Ancho/Alto
	Size gauss_size(11,11);	//paramaetro para la deteccion de los puntos claves y posterior filtrado, establece vecindades y espacio entre features
	
	for(int i=0;i<img_cant;i++) 
	{
		ostringstream os;
		os<< i;
		Mat aux  =  imread(path_c1+"cap_"+os.str()+".png",CV_LOAD_IMAGE_ANYCOLOR);
		//		Mat aux  =  imread(path_c1+"cap_"+os.str()+".png",CV_LOAD_IMAGE_ANYCOLOR);
		imagenes.push_back(aux);
	}
	
	/// Mascara - Para quitar la propaganda del droidcam de las capturas
	//	Mat	mask = Mat::ones(1944,2592,CV_8UC1)*255;
	
	Mat mask = Mat::ones(480,640,CV_8UC1)*255;
	for(int i=0;i<15;i++) 
	{
		for(int j=0;j<640;j++) 
		{
			mask.at<unsigned char>(i,j) = 0;
		}
	}
	
	///
	imagenes[0].copyTo(color);
	
	namedWindow("imagen",1);
	int val = 2050, maximo = 10000;
	createTrackbar("Threshold","imagen",&val,maximo);
	
	vector<Point2f> features;
	vector<vector<Point2f>>f;
	int pressed_key = 0, k=0, val2 = 0;
	while(pressed_key != 27)
	{
		
		imagenes[(k%img_cant)].copyTo(color);
		
		val = getTrackbarPos("Threshold","imagen");
		
		if(val2!=val){
			features.clear();
			features = chessboard_features_fix(color, chess_size,gauss_size,(float)val, mask);
			
			//			Mat copy;
			//			for(int i=25;i<28;i++) 
			//			{
			//				copy = color.clone();
			//				
			//				cout<< features[i]<<endl;
			//				circle(copy,features[i],5,Scalar(0,255,0));
			//				
			//				show_mat(copy,IMAGEN,0);
			//				waitKey(0);
			//			}
			
			val2 = val;
			cout<< "Cantidad de features: "<< features.size() << endl;
		}
		
		for(int i =0; i< features.size(); i++)
		{
			circle(color,features[i],5,Scalar(0,255,0));
		}
		
		imshow("imagen", color);
		
		pressed_key = waitKey(5);
		if(pressed_key == 13)
		{
			if(!features.empty())
			{
				f.push_back(features);
			}
			
			features.clear();
			val2=0;
			k++;
		}
		
	}
	
	cout<<f.size()<<endl;
	/// La chessboard es de 7x7, entonces tengo 49 puntos para asignar
	vector<Point2f> chessboard;
	vector<Point3f> chess_cloud;
	for(int j=0;j<chess_size.height;j++)
	{
		for(int i=0;i<chess_size.width;i++) 
		{
			chessboard.push_back( Point2f(i,((chess_size.height-1)-j)) );			
			chess_cloud.push_back( Point3f(i,((chess_size.height-1)-j),0) );			
			
			cout<< i << " "<< 5-j<< endl;
		}
	}
	
	SL sl(1024,768);
	vector<Mat> camera;
	//	for(int i=0;i<f.size();i++) 
	//	{ 			
	camera = sl.plane_base_calibration( f ,chessboard );
	//	}
	
	///-----------------------------------------------------------------------------
	/// Vizualisacion 3D
	///-----------------------------------------------------------------------------
	
	cout<<"Visualizacion 3D... "<<endl;	
	viz::Viz3d window("Coordinate Frame");
	window.setWindowSize(Size(500,500));
	window.setWindowPosition(Point(150,150));
	window.setBackgroundColor(); // black by default
	
	
	/// Systema de coordenadas del mundo
	viz::WLine axisX(Point3f(0.0f,0.0f,0.0f), Point3f(1.0f,0.0f,0.0f), Scalar(255,0,0));	//AZUL
	axisX.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig X", axisX);
	
	viz::WLine axisY(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,1.0f,0.0f), Scalar(0,0,255));	//ROJO
	axisY.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig Y", axisY);
	
	viz::WLine axisZ(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,0.0f,1.0f), Scalar(0,255,0));	//VERDE
	axisZ.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig Z", axisZ);
	
	/// Add coordinate axes
	//	cout<<endl;
	//	show_mat(camera[1]);
	//	waitKey(0);
	//	
	for(int i=1;i<camera.size();i++)
	{
		draw_sys_coord(camera[i], window);
	}
	//	draw_sys_coord(camera[1], window);
	//	draw_sys_coord(camera[2], window);
	//	draw_sys_coord(camera[3], window);
	//	draw_sys_coord(camera[4], window);
	
	/// Reconstruccion
	vector<Point3f> pc;
	int c1 = 1, c2 = 2;
	
	for(int i=0;i<chess_size.height*chess_size.width;i++) 
	{
		
		Mat p1 = ( Mat_<float>(1,3)<<
				  f[c1][i].x,
					  f[c1][i].y,
						  1.0f			);
		
		Mat p2 = ( Mat_<float>(1,3)<<
				  f[c2][i].x,
					  f[c2][i].y,
						  1.0f			);
		Mat l1 = sl.get_line(camera[0],camera[c1+1], p1);
		Mat l2 = sl.get_line(camera[0],camera[c2+1], p2);
		
		pc.push_back(sl.calc_intersection(l1,l2));
		
	}
	
	Mat cloud = Mat(pc);
	Mat real = Mat(chess_cloud);
	viz::WCloud nube(cloud);
	viz::WCloud nube_real(real,viz::Color(0,255,0));
	window.showWidget("cloud",nube);
	window.showWidget("Puntos reales",nube_real);
	
	
	Mat error;
	pow(cloud - real,2, error);
	double err=0;
	
	for(int i=0;i<error.rows;i++) 
	{
		for(int j=0;j<error.cols;j++) 
		{
			err+=error.at<float>(i,j);
		}
	}
	err = err/(error.rows*error.cols);
	
	cout<<endl;
	cout<< "ERROR CUADRATICO: "<< err<<endl;
	//	sl.get_line(camera[0],camera[1],f[0])
	
	window.spin();
	waitKey(0);
	
}
