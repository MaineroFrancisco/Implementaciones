
#include <vector>

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "chessboard.hpp"
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
	Size chess_size(7,7);	//cantiadd de puntos a encontrar en la tabla
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
	int val = 50, maximo = 10000;
	createTrackbar("Threshold","imagen",&val,maximo);
	
	vector<Point2f>features;
	int pressed_key = 0, k=0, val2 = 0;
	while(pressed_key != 27)
	{
		
		imagenes[(k%img_cant)].copyTo(color);
		
		val = getTrackbarPos("Threshold","imagen");
		
		if(val2!=val){
			features.clear();
			features = chessboard_features(color, chess_size,gauss_size,(float)val, mask);
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
	
	//	Mat img = imread("D:\\Facultad\\Proyecto\\Fotos\\11012018\\cap_6.png",CV_LOAD_IMAGE_GRAYSCALE );
	//	Mat img2 = imread("D:\\Facultad\\Proyecto\\Fotos\\11012018\\cap_5.png",CV_LOAD_IMAGE_GRAYSCALE );
	//	Mat img = imread("C:\\Users\\Fran\\Desktop\\test_1.png",CV_LOAD_IMAGE_GRAYSCALE );
	//	Mat img2 = imread("C:\\Users\\Fran\\Desktop\\test_2.png",CV_LOAD_IMAGE_GRAYSCALE );
	
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

