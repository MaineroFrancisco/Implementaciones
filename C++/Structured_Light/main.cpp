#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

//#include "auxiliares.h"
#include "test.hpp"
#include <ctime>

int main(int argc, char** argv) 
{
///-----------------------------------------------------------------------------
///		PATH POR ARGUMENTO
///-----------------------------------------------------------------------------	
//	string path = argv[1];	
//	sistema_completo(path,true);
	
///-----------------------------------------------------------------------------
///		CARGA CONTINUA IMAGENES, PATH
///-----------------------------------------------------------------------------
//	load_images(path_calib, path_img, mask_path);
	
///-----------------------------------------------------------------------------
///		CAPTURA CONTINUA, GUARDAR IMAGENES
///-----------------------------------------------------------------------------	
//	VideoCapture c1("http://192.168.1.103:4747/mjpegfeed?640x480");
//	string path = "D:\\Facultad\\Proyecto\\Fotos\\11012018\\";
//	save_images(path, c1, 5);
	
///-----------------------------------------------------------------------------
///		TEST: TRIANGULACION E INTERSECCION
///-----------------------------------------------------------------------------	
//	interseccion_prueba();

///-----------------------------------------------------------------------------
///		TEST CHESSBOARD COMPLETO
///-----------------------------------------------------------------------------
//	prueba_chessboard("D:\\Facultad\\Proyecto\\Implementaciones\\C++\\Imagenes_Prueba\\Prueba_Completo\\Calib\\cam_2\\");
//	prueba_chessboard("D:\\Facultad\\Proyecto\\Fotos\\11012018\\");
	
///-----------------------------------------------------------------------------
/// 	TEST FEATURES COMPLETO
///-----------------------------------------------------------------------------
//	Mat org = imread("D:\\Facultad\\Proyecto\\Fotos\\11012018\\cap_6.png",CV_LOAD_IMAGE_ANYCOLOR );
//	Mat org2 = imread("D:\\Facultad\\Proyecto\\Fotos\\11012018\\cap_5.png",CV_LOAD_IMAGE_ANYCOLOR );
//	
//	test_features_completo(org, org2);
	
///-----------------------------------------------------------------------------
//	projector();
//	fourier(img);
	
///-----------------------------------------------------------------------------
/// 	TEST COMPLETO
///-----------------------------------------------------------------------------
	
//	prueba_calib_auto_chessboard("D:\\Facultad\\Proyecto\\Implementaciones\\C++\\Imagenes_Prueba\\Prueba_Completo\\Calib\\cam_2\\", 
//								 "D:\\Facultad\\Proyecto\\Implementaciones\\C++\\Imagenes_Prueba\\Prueba_Completo\\Calib\\cam_1\\");
////	prueba_calib_auto_chessboard("D:\\Facultad\\Proyecto\\Fotos\\11012018\\", 
////								 "D:\\Facultad\\Proyecto\\Implementaciones\\C++\\Imagenes_Prueba\\Prueba_Completo\\Calib\\cam_2\\");

///-----------------------------------------------------------------------------
///Capturar
///-----------------------------------------------------------------------------
	
//	dos_camaras(19, 26, "D:\\Facultad\\Proyecto\\Fotos\\12022018");
//	
//	return 0;
	
///-----------------------------------------------------------------------------
///
///-----------------------------------------------------------------------------
//////////	vector<Mat> c1_calib, c2_calib;
//////////	
//////////	for(int i=5;i<11;i++) {
//////////		ostringstream os;
//////////		os<<i;
//////////		c2_calib.push_back(imread("D:\\Facultad\\Proyecto\\Fotos\\02022018\\calib\\c1_"+os.str()+".png",CV_LOAD_IMAGE_ANYCOLOR));
//////////		c1_calib.push_back(imread("D:\\Facultad\\Proyecto\\Fotos\\02022018\\calib\\c2_"+os.str()+".png",CV_LOAD_IMAGE_ANYCOLOR));
//////////	}
//////////	
////////////	Mat aff = (Mat_<float>(2,3)<<	// la camara 1 estaba dada vuelta
////////////			   -1.0f,0.0f,640.0f,
////////////			   0.0f,1.0f,0.0f
////////////			   );
////////////	for(int i=0;i<4;i++) {
////////////		// c1 izquierda		|	c2 derecha
////////////		ostringstream os;
////////////		os<<i;
////////////		
////////////		Mat c1 = imread("D:\\Facultad\\Proyecto\\Fotos\\12022018\\calib\\c1_"+os.str()+".png",CV_LOAD_IMAGE_ANYCOLOR);
////////////
//////////////		warpAffine(c1,c1,aff,c1.size());
////////////		
////////////		c1_calib.push_back(c1);
////////////		c2_calib.push_back(imread("D:\\Facultad\\Proyecto\\Fotos\\12022018\\calib\\c2_"+os.str()+".png",CV_LOAD_IMAGE_ANYCOLOR));
////////////	}
////////////	
	Mat color_c1,color_c2;
//////////	int img_cant = c1_calib.size();
//////////	Size chess_size(7,7);	//cantidad de puntos a encontrar en la tabla:		Ancho/Alto
//////////	Size gauss_size(11,11);	//paramaetro para la deteccion de los puntos claves y posterior filtrado, establece vecindades y espacio entre features
//////////	
//////////	Mat mask = Mat::ones(480,640,CV_8UC1)*255;
//////////	for(int i=0;i<15;i++) 
//////////	{
//////////		for(int j=0;j<640;j++) 
//////////		{
//////////			mask.at<unsigned char>(i,j) = 0;
//////////		}
//////////	}
//////////
////////////	c1_calib[0].copyTo(color_c1);
////////////	c2_calib[0].copyTo(color_c2);
//////////	
////////////	namedWindow("imagen",1);
////////////	namedWindow("imagen2",1);
//////////	int val = 50, val2 = 50, maximo = 10000;
////////////	createTrackbar("Threshold","imagen",&val,maximo);
////////////	createTrackbar("Threshold","imagen2",&val2,maximo);
//////////	
//////////	vector<Point2f> f_cam1, f_cam2;
//////////	vector<vector<Point2f>>f1,f2;
//////////	int pressed_key = 0, k=0, val_change = 0, val_change2 = 0;
//////////	while(pressed_key != 27 && k<img_cant)
//////////	{
//////////		c1_calib[(k%img_cant)].copyTo(color_c1);
//////////		c2_calib[(k%img_cant)].copyTo(color_c2);
//////////		
////////////		val = getTrackbarPos("Threshold","imagen");
////////////		val2 = getTrackbarPos("Threshold","imagen2");
//////////		
////////////		if(val_change!=val){
////////////			f_cam1.clear();
////////////////			Mat inv_mask;
////////////////			Mat inv_mask = mask;
////////////////			warpAffine(mask,inv_mask,aff,mask.size());
//////////////			f_cam1 = chessboard_features_fix(color_c1, chess_size,gauss_size,(float)val, inv_mask);
//////////			f_cam1 = chessboard_features_fix(color_c1, chess_size,gauss_size,(float)val, mask);
//////////			
////////////			val_change = val;
////////////			cout<< "Features Cam1: "<< f_cam1.size() << endl;
////////////		}
//////////
////////////		if(val_change2!=val2){
////////////			f_cam2.clear();
//////////			f_cam2 = chessboard_features_fix(color_c2, chess_size,gauss_size,(float)val2, mask);
//////////			
////////////			val_change2 = val2;
////////////			cout<< "Features Cam2: "<< f_cam2.size() << endl;
////////////		}
//////////		
////////////		for(int i =0; i< f_cam1.size(); i++)
////////////		{
////////////			circle(color_c1,f_cam1[i],5,Scalar(0,255,0));
////////////		}
////////////		for(int i =0; i< f_cam2.size(); i++)
////////////		{
////////////			circle(color_c2,f_cam2[i],5,Scalar(0,255,0));
////////////		}
//////////		
////////////		imshow("imagen", color_c1);
////////////		imshow("imagen2", color_c2);
//////////		
////////////		pressed_key = waitKey(5);
////////////		if(pressed_key == 13)
////////////		{
//////////			if(!f_cam1.empty())
//////////			{
//////////				f1.push_back(f_cam1);
//////////			}
//////////			
//////////			f_cam1.clear();
//////////			
//////////			if(!f_cam2.empty())
//////////			{
//////////				f2.push_back(f_cam2);
//////////			}
//////////			f_cam2.clear();
//////////			
//////////			k++;
////////////			val_change=0;
////////////			val_change2=0;
////////////		}
//////////		
//////////	}
////////////	
////////////	destroyWindow("imagen");
////////////	destroyWindow("imagen2");
//////////	
////////////	cout<<f1.size()<<endl;
////////////	cout<<f2.size()<<endl;
//////////	/// La chessboard es de 7x7, entonces tengo 49 puntos para asignar
//////////	vector<Point2f> chessboard;
//////////	vector<Point3f> chess_cloud;
//////////	for(int j=0;j<chess_size.height;j++)
//////////	{
//////////		for(int i=0;i<chess_size.width;i++) 
//////////		{
//////////			chessboard.push_back( Point2f(i,((chess_size.height-1)-j)) );			
////////////			chess_cloud.push_back( Point3f(i,((chess_size.height-1)-j),0) );			
//////////			
////////////			cout<< i << " "<< chess_size.height-1-j<< endl;
//////////		}
//////////	}
//////////	
//////////	SL sl(1024,768);
//////////	vector<Mat> cam1, cam2;
//////////	//	for(int i=0;i<f.size();i++) 
//////////	//	{ 			
//////////	cam1 = sl.plane_base_calibration( f1 ,chessboard );
//////////	cam2 = sl.plane_base_calibration( f2 ,chessboard );
//////////	//	}
////////////	cout<<"CAM1: "<<cam1.size()<<endl;
////////////	cout<<"CAM2: "<<cam2.size()<<endl;
	///-----------------------------------------------------------------------------
	/// Vizualisacion 3D	-	Chessboard
	///-----------------------------------------------------------------------------
	
////	cout<<"Visualizacion 3D... "<<endl;	
////	viz::Viz3d window("Coordinate Frame");
////	window.setWindowSize(Size(500,500));
////	window.setWindowPosition(Point(150,150));
////	window.setBackgroundColor(); // black by default
////	
////	/// Reconstruccion
////	vector<Point3f> pc;
////	int c1 = 1, c2 = 1;
////	
////	for(int i=0;i<chess_size.height*chess_size.width;i++) 
////	{
////		
////		Mat p1 = ( Mat_<float>(1,3)<<
////				  f1[c1][i].x,
////					  f1[c1][i].y,
////						  1.0f			);
////		
////		Mat p2 = ( Mat_<float>(1,3)<<
////				  f2[c2][i].x,
////					  f2[c2][i].y,
////						  1.0f			);
////		Mat l1 = sl.get_line(cam1[0],cam1[c1+1], p1);
////		Mat l2 = sl.get_line(cam2[0],cam2[c2+1], p2);
////		
////		pc.push_back(sl.calc_intersection(l1,l2));
////		
////	}
////	
////	/// Systema de coordenadas del mundo
////	viz::WLine axisX(Point3f(0.0f,0.0f,0.0f), Point3f(1.0f,0.0f,0.0f), Scalar(255,0,0));	//AZUL
////	axisX.setRenderingProperty(viz::LINE_WIDTH, 1.0);
////	window.showWidget("Orig X", axisX);
////	
////	viz::WLine axisY(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,1.0f,0.0f), Scalar(0,0,255));	//ROJO
////	axisY.setRenderingProperty(viz::LINE_WIDTH, 1.0);
////	window.showWidget("Orig Y", axisY);
////	
////	viz::WLine axisZ(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,0.0f,1.0f), Scalar(0,255,0));	//VERDE
////	axisZ.setRenderingProperty(viz::LINE_WIDTH, 1.0);
////	window.showWidget("Orig Z", axisZ);
////	
////	/// Add coordinate axes
////	draw_sys_coord(cam1[1], window);
////	draw_sys_coord(cam2[1], window);
////	
////	
////	Mat cloud = Mat(pc);
////	Mat real = Mat(chess_cloud);
////	viz::WCloud nube(cloud);
////	window.showWidget("cloud",nube);
////	viz::WCloud nube_real(real,viz::Color(0,255,0));
////	window.showWidget("Puntos reales",nube_real);
////	
////	
////	Mat error;
////	pow(cloud - real,2, error);
////	double err=0;
////	
////	for(int i=0;i<error.rows;i++) 
////	{
////		for(int j=0;j<error.cols;j++) 
////		{
////			err+=error.at<float>(i,j);
////		}
////	}
////	err = err/(error.rows*error.cols);
////	
////	cout<<endl;
////	cout<< "ERROR CUADRATICO: "<< err<<endl;
////	//	sl.get_line(camera[0],camera[1],f[0])
////	
////	window.spin();
	
	///-------------------------------------------------------------------------
	/// imagenes FEATURES
	vector<Mat> c1_feat, c2_feat;
	
	for(int i=0;i<5;i++) {
		ostringstream os;
		os<<i;
		c2_feat.push_back(imread("D:\\Facultad\\Proyecto\\Fotos\\02022018\\cam\\c1_"+os.str()+".png",CV_LOAD_IMAGE_ANYCOLOR));
		c1_feat.push_back(imread("D:\\Facultad\\Proyecto\\Fotos\\02022018\\cam\\c2_"+os.str()+".png",CV_LOAD_IMAGE_ANYCOLOR));
	}
	
	
////	for(int i=0;i<3;i++) {
////		ostringstream os;
////		os<<i;
////		Mat cap1 = imread("D:\\Facultad\\Proyecto\\Fotos\\12022018\\cam\\c1_"+os.str()+".png",CV_LOAD_IMAGE_ANYCOLOR);
//////		warpAffine(cap1,cap1,aff,cap1.size());
////		c1_feat.push_back(cap1);
////		c2_feat.push_back(imread("D:\\Facultad\\Proyecto\\Fotos\\12022018\\cam\\c2_"+os.str()+".png",CV_LOAD_IMAGE_ANYCOLOR));
////	}
	
	int imagen_elegida = 3;
	
	Mat img, img2, org, org2;
//	org = c1_feat[imagen_elegida].clone();
//	org2 = c2_feat[imagen_elegida].clone();

//	org = imread("C:\\Users\\Fran\\Desktop\\view0.png",CV_LOAD_IMAGE_ANYCOLOR);
////	cout<<org.size()<<endl;
//	org2 = imread("C:\\Users\\Fran\\Desktop\\view1.png",CV_LOAD_IMAGE_ANYCOLOR);
	
//////////	org = imread("D:\\Facultad\\Proyecto\\Fotos\\11012018\\cap_5.png", CV_LOAD_IMAGE_ANYCOLOR);
//////////	org2 = imread("D:\\Facultad\\Proyecto\\Fotos\\11012018\\cap_6.png", CV_LOAD_IMAGE_ANYCOLOR);
////////	
////////	cvtColor(org, img, CV_BGR2GRAY);
////////	cvtColor(org2, img2, CV_BGR2GRAY);
////////	
//////////	cout<< "pre_score"<<endl;
////////	Mat mask = Mat::ones(img.size(),CV_8UC1)*255;
////////	Mat harris = harris_score_image(img,Size(7,7),mask,SHI_TOMASI);
//////////	cout<< "harris"<<endl;
////////	Mat harris2 = harris_score_image(img2,Size(7,7),mask,SHI_TOMASI);
//////////	cout<< "post_score"<<endl;
////////	
////////	cout<< "pre_filter"<<endl;
////////	namedWindow("ImagenF1",1);
////////	namedWindow("ImagenF2",1);
////////
//////////	val = 100; val2 = 100; maximo = 1000; val_change = 0; val_change2 = 0;
////////	int val = 100, val2 = 100, maximo = 1000, val_change = 0, val_change2 = 0;
////////	createTrackbar("Threshold","ImagenF1",&val,maximo);
////////	createTrackbar("Threshold","ImagenF2",&val2,maximo);
////////	vector<Point2f> v, v2;
//////////	pressed_key=0;
////////	int pressed_key=0;
////////	while(pressed_key != 27)
////////	{
////////		
////////		org.copyTo(color_c1);
////////		org2.copyTo(color_c2);
////////		
////////		val = getTrackbarPos("Threshold","ImagenF1");
////////		val2 = getTrackbarPos("Threshold","ImagenF2");
////////		
////////		if(val_change!=val){
////////			v = harris_threshold(harris,val);	/// recibe un float entre 0 y 10000
////////			
////////			val_change = val;
////////			cout<< "Features Cam1: "<< v.size() << endl;
////////		}
////////		
////////		if(val_change2!=val2){
////////			v2 = harris_threshold(harris2,val2);	/// recibe un float entre 0 y 10000
////////			
////////			val_change2 = val2;
////////			cout<< "Features Cam2: "<< v2.size() << endl;
////////		}
////////		
////////		for(int i =0; i< v.size(); i++)
////////		{
////////			circle(color_c1,v[i],5,Scalar(0,255,0));
////////		}
////////		for(int i =0; i< v2.size(); i++)
////////		{
////////			circle(color_c2,v2[i],5,Scalar(0,255,0));
////////		}
////////		
////////		imshow("ImagenF1",color_c1);
////////		imshow("ImagenF2",color_c2);
////////		
////////		pressed_key = waitKey(5);
////////	}
////////	
////////	destroyWindow("ImagenF1");
////////	destroyWindow("ImagenF2");
////////	
////////	cout<< "post_filter"<<endl;
////////	cout<< "cant features: "<<v.size()<<" "<<v2.size()<<endl;
////////	
////////	cout<<endl;
////////	cout<< "pre_descp"<<endl;
////////	vector<descriptor> d = generate_descriptor(img, v);
////////	vector<descriptor> d2 = generate_descriptor(img2, v2);
////////	cout<< "post_descp"<<endl;
////////	
////////	cout<<endl;
////////	cout<< "pre_match"<<endl;
////////	vector<Mat> vm;
////////	
////////	Point2f p1_e, p2_e;
////////	Mat final_img = Mat::zeros(org.rows,org2.cols*2, CV_8UC3);
////////	org.copyTo(final_img(Rect(0,0,org.cols,org.rows)));
////////	org2.copyTo(final_img(Rect(org.cols,0,org2.cols,img.rows)));
////////	
////////	namedWindow("match",1);
////////	val=60; maximo=100; val2 = 100; val_change =0; val_change2=0;
////////	int maximo2 = 300;
////////	createTrackbar("tresh_relativo","match",&val,maximo);
////////	createTrackbar("RANSAC","match",&val2,maximo2);
////////	pressed_key=0;
////////	while(pressed_key!=27)
////////	{
////////		
////////		
////////		val = getTrackbarPos("tresh_relativo","match");
////////		val2 = getTrackbarPos("RANSAC","match");
////////		
////////		if(val_change!= val || val_change2!= val2)
////////		{
////////			org.copyTo(final_img(Rect(0,0,org.cols,org.rows)));
////////			org2.copyTo(final_img(Rect(org.cols,0,org2.cols,img.rows)));
////////			
////////			
////////			float rt = val / 100.0f;
////////			vm = feature_matching(d, d2,rt,(float)val2);
////////			
////////			for(int i=0;i<vm.size();i++) 
////////			{
////////				
////////				p1_e = Point2f(vm[i].at<float>(0),vm[i].at<float>(1));
////////				p2_e = Point2f(vm[i].at<float>(2),vm[i].at<float>(3));
////////				
////////				circle(final_img ,p1_e,5, Scalar(0,255,0));
////////				circle(final_img ,Point2f(org.cols,0) + p2_e,5, Scalar(0,255,0));
////////				line(final_img ,p1_e, Point2f(org.cols,0 )+ p2_e,Scalar(0,255,0));
////////				
////////			}
////////		
////////			val_change = val;
////////			val_change2 = val2;
////////		}
////////		
////////		imshow("match", final_img);
////////		
////////		pressed_key = waitKey(5);
////////	}
////////	cout<< "post_match"<<endl;
////////	destroyWindow("match");
//	
////////	
////////	/// Reconstruccion
////////	vector<Point3f> pc_f;
////////	
////////	for(int i=0;i<vm.size();i++) 
////////	{
////////		
////////		Mat p1 = ( Mat_<float>(1,3)<<
////////				  vm[i].at<float>(0),
////////				  vm[i].at<float>(1),
////////						  1.0f			);
////////		
////////		Mat p2 = ( Mat_<float>(1,3)<<
////////				  vm[i].at<float>(2),
////////				  vm[i].at<float>(3),
////////						  1.0f			);
////////		Mat l1 = sl.get_line(cam1[0],cam1[c1+1], p1);
////////		Mat l2 = sl.get_line(cam2[0],cam2[c2+1], p2);
////////		
////////		pc_f.push_back(sl.calc_intersection(l1,l2));
////////		
////////	}
////////	
////////	
////////	window.setWindowSize(Size(500,500));
////////	window.setWindowPosition(Point(150,150));
////////	window.setBackgroundColor(); // black by default
////////	cloud = Mat(pc_f);
////////	viz::WCloud nube2(cloud);
////////	window.showWidget("cloud",nube2);
//////////	window.showWidget("Puntos reales",nube_real);
////////	
////////	
//////////	cout<<"VM: "<<vm.size()<<endl;
//////////	cout<< "descrp: "<< d.size() << " "<< d2.size()<<endl;
//////////	cout<< "match: "<<vm.size()<<endl;
////////	
////////	window.spin();
	
	///-----------------------------------------------------------------------------
	/// RECTIFICACION
	///-----------------------------------------------------------------------------
//////////////	vector<Mat> vcam1, vcam2;
//////////////	vcam1.push_back(cam1[0]);
//////////////	vcam1.push_back(cam1[1]);
//////////////	vcam2.push_back(cam2[0]);
//////////////	vcam2.push_back(cam2[1]);
//////////////	
//////////////	cout<< "PRE RECT"<<endl;
//////////////	vector<Mat> rect = sl.rectification(vcam1, vcam2);	// 0 - Im | 1 - Em
//////////////////	
//////////////////	/// PROBLEMA TRASLACION... REVISAR... PROBLEMA MESCLANDO MATRICES... BUSCAR COMO CENTRARLAS... PORQUE INVERTIDAS?
//////////////	Mat org_fix, org2_fix;
//////////////	
//////////////	org_fix = fix_rectify(org, rect[0]);
//////////////	org2_fix = fix_rectify(org2, rect[1]);
////////////////////	org_fix = fix_rectify(org, org2, rect[0], rect[1]);
//////////////////	
//////////////	resize(org_fix,org_fix,Size(640,480));
//////////////	resize(org2_fix,org2_fix,Size(640,480));
//////////////
//////////////	show_mat(org_fix, IMAGEN, 0);
//////////////	show_mat(org2_fix, IMAGEN, 1);
//////////////	
//////////////	waitKey(0);	
//////////////	
//////////////	cout<< "POST RECT"<<endl;
	
//	Mat torg = org.clone(), torg2 = org2.clone();
//	draw_epiline(torg, cam1[0], cam1[1], torg2, cam2[0], cam2[1], Point2f(320.0f,200.0f));
//	draw_epiline(torg, cam1[0], cam1[1], torg2, cam2[0], cam2[1], Point2f(320.0f,220.0f));
//	draw_epiline(torg, cam1[0], cam1[1], torg2, cam2[0], cam2[1], Point2f(320.0f,240.0f));
//	draw_epiline(torg, cam1[0], cam1[1], torg2, cam2[0], cam2[1], Point2f(320.0f,260.0f));
//	draw_epiline(torg, cam1[0], cam1[1], torg2, cam2[0], cam2[1], Point2f(320.0f,280.0f));
//	
//	show_mat(torg,IMAGEN,0);
//	show_mat(torg2,IMAGEN,1);
//	waitKey(0);

	///
	///
	/// 
	
	// Mido el tiempo
//	clock_t begin,end;
//	double tiempo;			
//	
//	cout<< "PRE DISPARITY"<<endl;
//	Mat disparity = Mat::zeros(org.size(),CV_32F);
//	
//	cout<<endl;
//	cout<< "Disparidad por Bloques...";
//	
//	begin = clock();
//	disparity_map(org, org2);
//	end = clock();
//	
//	tiempo = double(end - begin) / CLOCKS_PER_SEC;
//	
//	cout<< "Disparidad por Bloques... FINALIZADO. Tiempo: "<<tiempo<<endl;
//	cout<<endl;
	
	
///-----------------------------------------------------------------------------
/// DISPARITY
///-----------------------------------------------------------------------------
	
	cout<< "PRE DISPARITY"<<endl;
//
//	org = imread("D:\\Facultad\\ohta\\scene1.row1.col1.ppm",CV_LOAD_IMAGE_ANYCOLOR);
//	org2 = imread("D:\\Facultad\\ohta\\scene1.row1.col2.ppm",CV_LOAD_IMAGE_ANYCOLOR);
	org = imread("D:\\Facultad\\ALOI\\png\\76\\76_r110.png",CV_LOAD_IMAGE_ANYCOLOR);
	org2 = imread("D:\\Facultad\\ALOI\\png\\76\\76_r115.png",CV_LOAD_IMAGE_ANYCOLOR);
	
//	Mat gorg, gorg2;
//	cvtColor(org,gorg,CV_BGR2GRAY);
//	cvtColor(org2,gorg2,CV_BGR2GRAY);
//	Mat mask = (gorg - gorg2)>10;
//	dilate(mask,mask,getStructuringElement( 0, Size( 7,7)));
////	morphologyEx( mask, mask, MORPH_CLOSE,  getStructuringElement( 0, Size( 7,7)));
//	morphologyEx( mask, mask, MORPH_CLOSE,  getStructuringElement( 0, Size( 15,15)));
//	
//	show_mat(mask,IMAGEN,0);
//	waitKey(0);
	
	/// RECURSIVO
	Mat disparity_le,disparity_ri;
	disparity_le = disparity_r(org, org2, 3, 30,1);
//	disparity_ri = disparity_r(org2, org, 3, 6,9);
	
	double min, max;
	disparity_le = abs(disparity_le);
	disparity_le.convertTo(disparity_le, CV_8UC1);
	
//	disparity_le = disparity_le(Rect(36,36,org.cols-36, org.rows-36));
	
//	disparity_ri = abs(disparity_ri);
//	disparity_ri.convertTo(disparity_ri, CV_8UC1);
//	
//	disparity_ri = disparity_ri(Rect(36,36,org.cols-36, org.rows-36));
//	

	///---------------------------------------------------------------------
	/// SMOOTHING
	///---------------------------------------------------------------------
	
//	Mat disp_d = abs(disparity_le - disparity_ri)>1;
//	
//	Mat new_disp;
//	disparity_le.copyTo(new_disp,1.0f-disp_d);
//	
//	minMaxLoc(new_disp,&min,&max);
//	new_disp = (new_disp/max)*255.0f;
//	
//	show_mat(new_disp,IMAGEN,0);
//	waitKey(0);
	
	
//	medianBlur(disparity_le,disparity_le,11);
//	medianBlur(disparity_ri,disparity_ri,11);
	boxFilter(disparity_le,disparity_le,-1,	Size(15,15));
//	GaussianBlur(disparity_le,disparity_le,Size(11,11),1.5f);
//	GaussianBlur(disparity_ri,disparity_ri,Size(11,11),1.5f);
	
	///---------------------------------------------------------------------
	
	
	/// MIN MAX	
	minMaxLoc(disparity_le,&min,&max);
	disparity_le = (disparity_le/max)*255.0f;
//	disparity_le = (disparity_le/max);
	cout<<"Disp L Rec: "<< min<<" "<<max<<endl;
	
//	minMaxLoc(disparity_ri,&min,&max);
//	disparity_ri = (disparity_ri/max)*255.0f;
//	cout<<"Disp R Rec: "<< min<<" "<<max<<endl;
	
	/// SHOW
	show_mat(disparity_le,IMAGEN,0);
//	show_mat(disparity_ri,IMAGEN,1);
	waitKey(0);
	
	
	/// NO RECURSIVO
	Mat disparity2,disparity3;
	disparity2 = disparity_nr(org, org2, 11, 25);
//	disparity3 = disparity_nr(org2, org, 7, 30);
	
	disparity2 = abs(disparity2);
	disparity2.convertTo(disparity2, CV_8UC1);
	
//	disparity3 = abs(disparity3);
//	disparity3.convertTo(disparity3, CV_8UC1);
	
	disparity2 = disparity2(Rect(36,36,org.cols-36, org.rows-36));
//	disparity3 = disparity3(Rect(36,36,org.cols-36, org.rows-36));
	
	minMaxLoc(disparity2,&min,&max);
	cout<<"Disp NR: "<< min<<" "<<max<<endl;
//	minMaxLoc(disparity3,&min,&max);
//	cout<<"Disp NR: "<< min<<" "<<max<<endl;
	
//	medianBlur(disparity2,disparity2,11);
//	medianBlur(disparity3,disparity3,11);
	
	disparity2 = (disparity2/max)*255;
//	disparity3 = disparity3/max;
	show_mat(disparity2,IMAGEN,2);
//	show_mat(disparity3,IMAGEN,3);
	waitKey(0);
	
	
//	Mat real_disp = imread("D:\\Facultad\\ohta\\scene1.truedisp.pgm",CV_LOAD_IMAGE_ANYCOLOR);
//	minMaxLoc(real_disp,&min,&max);
//	cout<<"Disp Real: "<< min<<" "<<max<<endl;
//	
//	show_mat(real_disp,IMAGEN,3);
//	
	cout<< "POST DISPARITY"<<endl;
	
	waitKey(0);
	return 0;
} 
	
