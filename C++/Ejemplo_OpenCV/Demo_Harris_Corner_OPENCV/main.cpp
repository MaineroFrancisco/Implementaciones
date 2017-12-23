#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <string>
using namespace std;
using namespace cv;

Mat src, src_gray;
int thresh = 200;
int max_thresh = 255;
char* source_window = "Source image";
char* corners_window = "Corners detected";

/* @function cornerHarris_demo */
void cornerHarris_demo( int, void* )
{
	Mat dst, dst_norm, dst_norm_scaled;
	dst = Mat::zeros( src.size(), CV_32FC1 );
	int blockSize = 5;
	int apertureSize = 5;
	double k = 0.04;
	cornerHarris( src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );
	normalize( dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
	convertScaleAbs( dst_norm, dst_norm_scaled );
	for( int j = 0; j < dst_norm.rows ; j++ )
	{ for( int i = 0; i < dst_norm.cols; i++ )
	{
		if( (int) dst_norm.at<float>(j,i) > thresh )
		{
			circle( dst_norm_scaled, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
		}
	}
	}
	namedWindow( corners_window, WINDOW_AUTOSIZE );
	imshow( corners_window, dst_norm_scaled );
	waitKey(10);
}
int main(int argc, char** argv) {
	
	string path = argv[1];
	
	src = imread( path+"\\cap_1.png", 1 );
	cvtColor( src, src_gray, COLOR_BGR2GRAY );
	namedWindow( source_window, WINDOW_AUTOSIZE );
	createTrackbar( "Threshold: ", source_window, &thresh, max_thresh, cornerHarris_demo );
	imshow( source_window, src );
	cornerHarris_demo( 0, 0 );
	
	///
	
////	Mat img_hsv;
////	Mat img = imread(path+"\\cap1.png",CV_LOAD_IMAGE_ANYCOLOR);

//	namedWindow("Original",CV_WINDOW_AUTOSIZE);
	
//	createTrackbar("H Low","Original",0,179);
//	createTrackbar("H High","Original",0,179);
//	
//	createTrackbar("S Low","Original",0,255);
//	createTrackbar("S High","Original",0,255);
//	
//	createTrackbar("V Low","Original",0,255);
//	createTrackbar("V High","Original",0,255);
	
////	cvtColor(img,img_hsv,CV_BGR2HSV);
////	
////	unsigned char rl,rh,bl,bh,gl,gh;
////	Mat mask;
//	unsigned char key_pressed = 0;
//	while(key_pressed != 27){
//	
//		rl = getTrackbarPos("H Low", "Original");
//		gl = getTrackbarPos("S Low", "Original");
//		bl = getTrackbarPos("V Low", "Original");
//		rh = getTrackbarPos("H High", "Original");
//		gh = getTrackbarPos("S High", "Original");
//		bh = getTrackbarPos("V High", "Original");
//		
//		if(!rh){
//			rh=179;
//		}
//		if(!gh){
//			gh=255;
//		}
//		if(!bh){
//			bh=255;
//		}
//		
//		if(rh<=rl){
//			rh=rl++;
//		}
//		if(gh<=gl){
//			gh=gl++;
//		}
//		if(bh<=bl){
//			bh=bl++;
//		}
//		
//		inRange(img_hsv,Scalar(rl,gl,bl),Scalar(rh,gh,bh),mask);
//		
//		Mat test;
//		bitwise_and(img,img,test,mask);
//		
//		imshow("Original",test);
////		imshow("Mask", mask);
//		
//		key_pressed = waitKey(5);
//	}
////	rl=0;
////	gl=0;
////	bl=118;
////	rh=179;
////	gh=36;
////	bh=255;
////	
////	inRange(img_hsv,Scalar(rl,gl,bl),Scalar(rh,gh,bh),mask);
////	Mat test;
////	bitwise_and(img,img,test,mask);
////	
////	Mat edges, gray;
////	cvtColor(test,test,CV_BGR2GRAY);
////	Canny(test,edges,50,150,3);
////	imshow("Test",edges);
////	
////	///Hough simple
////	vector<Vec2f> lines;
////	HoughLines(edges, lines, 1, CV_PI/180, 120, 0, 0 );
////	
////	for( size_t i = 0; i < lines.size(); i++ )
////	{
////		float rho = lines[i][0], theta = lines[i][1];
////		Point pt1, pt2;
////		double a = cos(theta), b = sin(theta);
////		double x0 = a*rho, y0 = b*rho;
////		pt1.x = cvRound(x0 + 1000*(-b));
////		pt1.y = cvRound(y0 + 1000*(a));
////		pt2.x = cvRound(x0 - 1000*(-b));
////		pt2.y = cvRound(y0 - 1000*(a));
////		line( img, pt1, pt2, Scalar(0,0,255), 3, CV_AA);
////	}
////	
////	imshow("Output", img);

	///
//	Mat image;
//	
//	VideoCapture cap(0);
//	if(!cap.isOpened()){
//		cerr << "No camera detected on this system" << endl;
//		return -1;
//	}
//	
//	while(true){
//		cap >> image;
//		if(image.empty()){
//			cerr << "Frame invalid and skipped!" << endl;
//			continue;
//		}
//		imshow("test", image);
//		waitKey(5);
//	}
//	
//	while(true){
//		cap >> image;
//		if(image.empty()){
//			cerr << "Frame invalid and skipped!" << endl;
//			continue;
//		}
//		imshow("test", image);
//		waitKey(5);
//	}
	/*
	//initialize a 120X350 matrix of black pixels:
	Mat img = imread(path+"\\cap1.png",CV_LOAD_IMAGE_ANYCOLOR);
	
	Mat edges;
	Mat gray;
	cvtColor(img,gray,CV_BGR2GRAY);
	Canny(gray,edges,50,150,3);
	
	
	///Hough simple
	//	vector<Vec2f> lines;
	//	HoughLines(dst, lines, 1, CV_PI/180, 50, 0, 0 );
	//	
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
	/// Hough Acumulado
	vector<Vec4i> lines;
	HoughLinesP(edges, lines, 1, CV_PI/180, 130, 350, 100 );
	for( size_t i = 0; i < lines.size(); i++ )
	{
		Vec4i l = lines[i];
		line( img, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(0,0,255), 3, CV_AA);
	}
	
	imshow("Edges", edges);
	imshow("Output", img);
	*/
	waitKey(0);
	return 0;
} 
