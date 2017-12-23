#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <sstream>

using namespace cv;
using namespace std;

string int_to_string(int i){
	ostringstream ss;
	ss << i;
	return ss.str();
}

void create_pattern(unsigned int width, unsigned int height ){
	unsigned int n_row = log10(height)/log10(2);
	unsigned int n_col = log10(width)/log10(2);
	unsigned int mask = 1;
	
	unsigned char white = 255, black = 0;

	unsigned int bit;
	Mat img;
	
	
	for(unsigned int i=0; i<=n_row; i++){
		
		img = Mat::zeros( height, width, CV_8UC1);
		
		for(unsigned int j=0; j<height; j++){
			
			bit = (j >> i);
			
			for(unsigned int k=0; k<width; k++){
				
				if( bit & mask){
					img.at<unsigned char>(j,k) = white; 
				}
				
			}
			
		}
		
		imshow("Output",img);
		waitKey(0);
	}
	
	for(int i=0; i<=n_col; i++){
		
		img = Mat::zeros(height, width, CV_8UC1);
		
		for(int k=0; k<width; k++){	
			bit = (k >> i);
			
			for(int j=0; j<height; j++){
				
				if( bit & mask){
					img.at<unsigned char>(j,k) = white; 
				}
				
			}
		}
		
		imshow("Output",img);
		waitKey(0);
	}
	
	
}


int main(int argc, char** argv) {
	//create a gui window:
	namedWindow("Output",1);
	//initialize a 120X350 matrix of black pixels:
	//write text on the matrix:
	
	create_pattern(1024, 768);

	return 0;
} 
