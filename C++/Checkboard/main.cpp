#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "harris_corner.h"

#include <vector>
using namespace std;
using namespace cv;

void prueba_1_mask_chessboard(Mat img)
{
	double angle = 0.0f;
	Mat show, show_ops;
	int key = 0;
	
	imshow("Img", img);
	
	
	Scalar media_global = mean(img);
	threshold(img,img,media_global.val[0],255,CV_THRESH_BINARY);
	
	
	namedWindow("Correlation",1);
	
	double minVal = 0.0f, maxVal = 1.0f;
	int bot=0, top=0;
	createTrackbar("top","Correlation",&top, 255, NULL, NULL);
	createTrackbar("bot","Correlation",&bot, 255, NULL, NULL);
	
	while(key!= 27){
		
		show = rotate_mask(checkb_mask, angle);
		show_ops = rotate_mask(checkb_mask_ops, angle);
		imshow("mask",show);
		
		Mat corr,corr_ops;
		filter2D(img,corr,CV_32FC1,show_ops);
		filter2D(img,corr_ops,CV_32FC1,show);
		
		minMaxLoc(corr, &minVal, &maxVal);
		
		corr = corr + abs(minVal);
		corr = corr / (abs(minVal)+maxVal);
		
		top = getTrackbarPos("top","Correlation");
		bot = getTrackbarPos("bot","Correlation");
		
		double up, down;
		up = top/255.0f;
		down = bot/255.0f;
		
		Mat corr2, corr3;
//		threshold(corr,corr2,down,1.0f,CV_THRESH_BINARY);
//		
//		threshold(corr,corr3,up,1.0f,CV_THRESH_BINARY_INV);
//		
//		bitwise_and(corr2,corr3,corr);
		
		minMaxLoc(corr_ops, &minVal, &maxVal);
		
		corr_ops = corr_ops + abs(minVal);
		corr_ops = corr_ops / (abs(minVal)+maxVal);

//		threshold(corr_ops,corr2,down,1.0f,CV_THRESH_BINARY);
//		
//		threshold(corr_ops,corr3,up,1.0f,CV_THRESH_BINARY_INV);
//		
//		bitwise_and(corr2,corr3,corr_ops);
		
		
//		bitwise_xor(corr,corr_ops,corr);
		
		//		threshold(corr,corr,3000.0f,1.0f,CV_THRESH_BINARY);
		
		imshow("Corr", corr);
		imshow("Corr_Ops", corr_ops);
		
		Mat diff = corr-corr_ops;
		
		threshold(diff,corr2,down,1.0f,CV_THRESH_BINARY);
		
		threshold(diff,corr3,up,1.0f,CV_THRESH_BINARY_INV);
		
		bitwise_and(corr2,corr3,diff);
		
		
//		bitwise_xor(corr,corr_ops,diff);
		imshow("Correlation",diff);
		
		if(key == 13){
			cout<< "Rotacion 25 grados: "<<angle<<endl;
			cout<< minVal << "	"<< maxVal<< endl;
			angle += 25.0f;
		}
		
		key = waitKey(5);
		//		cout<<"Key: "<<key<<endl;
	}
}

void prueba_2_mask_chessboard(Mat img)
{
	
	double angle = 0.0f;
	Mat show, show_ops, corr;
	Mat output, output2; 
	Mat region;
	Point2i center;
	int key = 0;
	
	Scalar media, media_mask, media_mask_ops;
	
	Scalar media_global = mean(img);
	threshold(img,img,media_global.val[0],255,CV_THRESH_BINARY);
	
	imshow("Img", img);
	
	while(key!= 27){
		
		show = rotate_mask(checkb_mask, angle);
		show_ops = rotate_mask(checkb_mask_ops, angle);
		//		show.convertTo(show,CV_8UC1);
		imshow("mask",show);
		
		output = Mat::zeros(img.size(),CV_8UC1);
		output2 = Mat::zeros(img.size(),CV_8UC1);
		for(int i=5;i<img.size().height-6;i++) 
		{
			for(int j=5;j<img.size().width-6;j++) 
			{
				center = Point2i(j,i);
				region = Mat(img,Rect(center.x-5,center.y-5,11,11));
				
				media = mean(region);
				show.convertTo(show,CV_8U);
				media_mask = mean(region,show);
				
				show_ops.convertTo(show_ops,CV_8U);
				media_mask_ops = mean(region,show_ops);
				
				
				if( media_mask.val[0] >= media.val[0])
				{
					output.at<unsigned char>(i,j) = 255;
				}
				
				if( media_mask_ops.val[0] >= media.val[0])
				{
					output2.at<unsigned char>(i,j) = 255;
				}
				//				cout<<media<<endl;
				
			}
		}
		
		bitwise_xor(output,output2,output);
		
		imshow("Correlation", output);
		
		if(key == 13){
			cout<< "Rotacion 25 grados"<<endl;
			angle += 25.0f;
		}
		
		key = waitKey(5);
	}
	
}


void prueba_3_mask_chessboard(Mat img)
{
	
	double angle = 0.0f;
	Mat show, show_ops, corr;
	Mat output, output2; 
	Mat region;
	Point2i center;
	int key = 0;
	
	Scalar media, media_mask, media_mask_ops;
	
	imshow("Img", img);
	
	Scalar media_global = mean(img);
	
	threshold(img,img,media_global.val[0],255,CV_THRESH_BINARY);
	
	while(key!= 27){
		
		show = rotate_mask(checkb_mask, angle);
		show_ops = rotate_mask(checkb_mask_ops, angle);
		//		show.convertTo(show,CV_8UC1);
		imshow("mask",show);
		
		output = Mat::zeros(img.size(),CV_8UC1);
		output2 = Mat::zeros(img.size(),CV_8UC1);
		for(int i=5;i<img.size().height-6;i++) 
		{
			for(int j=5;j<img.size().width-6;j++) 
			{
				center = Point2i(j,i);
				region = Mat(img,Rect(center.x-5,center.y-5,11,11));
				
				media = mean(region);
				show.convertTo(show,CV_8UC1);
				media_mask = mean(region,show);
				
				show_ops.convertTo(show_ops,CV_8UC1);
				media_mask_ops = mean(region,show_ops);
				
				
				if( media_mask.val[0] >= media.val[0])
				{
					output.at<unsigned char>(i,j) = 255;
				}
				
				if( media_mask_ops.val[0] >= media.val[0])
				{
					output2.at<unsigned char>(i,j) = 255;
				}
				//				cout<<media<<endl;
				
			}
		}
		
		bitwise_xor(output,output2,output);
		
		imshow("Correlation", output);
		
		if(key == 13){
			cout<< "Rotacion 25 grados"<<endl;
			angle += 25.0f;
		}
		
		key = waitKey(5);
	}
	
}

void prueba_4_mask_chessboard(Mat img)
{
	
	double angle = 0.0f;
	Mat show, show_ops, corr;
	Mat output;
	Mat output2;
	Mat region;
	Point2i center;
	int key = 0;
	
	Mat mask = Mat::zeros(11,11,CV_8UC3), mask_ops = Mat::zeros(11,11,CV_8UC3);
	
	for(int i=0;i<11;i++) 
	{
		for(int j=0;j<11;j++) 
		{
			if(i<4 && j<4){
				mask.at<Vec3b>(i,j) = Vec3b(255,255,255);
			}
			
			if(i>6 && j>6){
				mask.at<Vec3b>(i,j) = Vec3b(255,255,255);
			}
			
			if(i>6 && j<4){
				mask_ops.at<Vec3b>(i,j) = Vec3b(255,255,255);
			}
			
			if(i<4 && j<6){
				mask_ops.at<Vec3b>(i,j) = Vec3b(255,255,255);
			}
		}
	}
	
	
	int pressed_key = 0;
	bool break_row;

	imshow("Img", img);
	
	while(pressed_key!=27)
	{
		show = rotate_mask(mask, angle);
//		cvtColor(show,show,CV_GRAY2BGR);
		show_ops = rotate_mask(mask_ops, angle);
//		cvtColor(show_ops,show_ops,CV_GRAY2BGR);
		
		output= Mat::zeros(img.size(),CV_8UC3); 
		output2 =  Mat::zeros(img.size(),CV_8UC3); 
		
		imshow("mask",show);
		int i,j;
		int sx = img.size().width-6, sy = img.size().height-6;
//		for(i=5;i<sy;i++) 
//		{
//			for(j=5;j<sx;j++) 
//			{
//				region = Mat(img,Rect(j-5,i-5,11,11));
//				
//				break_row=false;
//				for(int k=0;k<11;k++) 
//				{
//					for(int l=0;l<11;l++) 
//					{
//						Vec3b v = region.at<Vec3b>(k,l);
//						
////						cout<<k<<" "<<l<<endl;
//						
//						// es algun tono de gris o blanco/negro
//						if(abs(v[0]-v[1])<10 && abs(v[0]-v[2])<10 && abs(v[1]-v[2])<10)
//						{
//							output.at<float>(i,j) += (abs(v[0] - show.at<Vec3b>(k,l)[0])
//												   + abs(v[1] - show.at<Vec3b>(k,l)[1]) 
//												   + abs(v[2] - show.at<Vec3b>(k,l)[2]))/3;
//							
//							output2.at<float>(i,j) += (abs(v[0] - show_ops.at<Vec3b>(k,l)[0])
//													+ abs(v[1] - show_ops.at<Vec3b>(k,l)[1]) 
//													+ abs(v[2] - show_ops.at<Vec3b>(k,l)[2]))/3;
//						}
//						else
//						{
//							output.at<float>(i,j) = 1.0f;
//							output2.at<float>(i,j) = 1.0f;
//							break_row = true;
//							break;
//						}
//					}
//					if(break_row)
//					{
//						break_row = false;
//						break;
//					}
//				}
//				
//				output.at<float>(i,j) = output.at<float>(i,j)/ (11*11);
//				output2.at<float>(i,j) = output2.at<float>(i,j)/ (11*11);
//				
//			}
//			
//		}
////		
//		bitwise_xor(output,output2,output);
		
//		double minVal, maxVal;
//		minMaxLoc(output, &minVal, &maxVal);
//		
////		output = maxVal - output;
//		output = output/maxVal;
		
//		cout<< minVal<<" "<<maxVal<<endl;
		
		pressed_key = waitKey(15);
		
		if(pressed_key == 13)
		{
			angle+=25.0f;
		}
		
		imshow("output", output);
	}
	//		show.convertTo(show,CV_8UC1);
	
	waitKey(0);
	
}

void hough_lines_corners(Mat img, Mat c1)
{
	Mat dst;
	Canny(img, dst, 50, 200, 3);
	
//	vector<Vec2f> lines;
//	HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );
	
//	for( size_t i = 0; i < lines.size(); i++ )
//	{
//		float rho = lines[i][0], theta = lines[i][1];
//		Point pt1, pt2;
//		double a = cos(theta), b = sin(theta);
//		double x0 = a*rho, y0 = b*rho;
//		pt1.x = cvRound(x0 + 1000*(-b));
//		pt1.y = cvRound(y0 + 1000*(a));
//		pt2.x = cvRound(x0 - 1000*(-b));
//		pt2.y = cvRound(y0 - 1000*(a));
//		line( cdst, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
//	}

	vector<Vec4i> lines;
	HoughLinesP(dst, lines, 1, CV_PI/180, 50, 50, 10 );
	for( size_t i = 0; i < lines.size(); i++ )
	{
		Vec4i l = lines[i];
		line( c1, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
	}

	imshow("source", img);
	imshow("detected lines", c1);
}
int main(int argc, char** argv) {
	Mat img, hsv, mask;
	Mat out;
	int v=80, vmax=255;
	
	//create a gui window:
//	VideoCapture c("http://192.168.1.113:4747/mjpegfeed?640x480");
//	
//	while(waitKey(5)!=27)
//	{
//		c >> img;
//		
//		imshow("Img", img);
//	}
////	
	Scalar lower_bound, upper_bound;
	
//	img = imread("D:\\Facultad\\Proyecto\\Implementaciones\\C++\\Imagenes_Prueba\\Planillas_Calibrar\\2Bfo4.png",CV_LOAD_IMAGE_ANYCOLOR);
	img = imread("D:\\Facultad\\Proyecto\\Implementaciones\\C++\\Imagenes_Prueba\\Prueba_Completo\\Calib\\cam_2\\cap_0.png",CV_LOAD_IMAGE_ANYCOLOR);
	
//	img = imread("D:\\Facultad\\Proyecto\\Implementaciones\\Matlab\\Caja_Cubo\\c2_2.jpeg",CV_LOAD_IMAGE_ANYCOLOR);
	
	mask = Mat::ones(480,640,CV_8UC1)*255;
	
	for(int i=0;i<15;i++) 
	{
		for(int j=0;j<640;j++) 
		{
			mask.at<unsigned char>(i,j) = 0;
		}
	}

	Mat c1;
	img.copyTo(c1);
	int id_cam = 3;
	cvtColor(c1,img,CV_BGR2GRAY);
	
//////	Mat corner_score = harris_corner_score(img,mask);
//////	
//////	ostringstream os;
//////	os<<id_cam;
//////	namedWindow("camara "+os.str(),1);
////////	
//////	int maxcant=1000, value1 = 10, value2 = 10;
//////	createTrackbar("Features","camara "+os.str(),&value1,maxcant);
////////	
//////////	vector<Point2i> f = filter_features(corner_score,maxcant);
////////	///ES UNA CAGADA, ARREGLAR
//////	Point2i* f = filter_features_vector(corner_score,maxcant);
//////
//////	
//////	Mat show;
//////
//////	while(waitKey(5)!= 27){
//////		c1.copyTo(show);
//////		
//////		value1 = getTrackbarPos("Features","camara "+os.str());
//////		
//////		for(int i=0;i<value1;i++) 
//////		{
//////			circle(show,f[i],5,Scalar(0,255,0));
//////		}
//////		
//////		imshow("camara "+os.str(),show);
//////	}

	
	/// La mejor solucion hasta ahora... discriminar con colores, agregar features...
	prueba_1_mask_chessboard(img);
	
//	prueba_2_mask_chessboard(img);
	
//	prueba_3_mask_chessboard(img);
	
//	prueba_4_mask_chessboard(c1);
	
	
	/// hough LINES
//	hough_lines_corners(img, c1);
	
	waitKey(0);
	return 0;
} 
