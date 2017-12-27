#ifndef LABEL_SEGMENTATION_H
#define LABEL_SEGMENTATION_H

#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <vector>

using namespace cv;
using namespace std;

typedef unsigned char label;

vector<label> etiquetas_usadas;

label check_neightbor(Mat dest, int i, int j, label &lb){
	
	label up,down,left,right, tag=0;
	down 	= 	(j+1<dest.cols)? dest.at<label>(i,j+1): 0;
	up 		= 	(j-1>=0)? dest.at<label>(i,j-1): 0;
	left 	= 	(i-1>=0)? dest.at<label>(i-1,j): 0;
	right 	= 	(i+1<dest.rows)? dest.at<label>(i+1,j): 0;
	
	if(!(up || down || left || right)){
		tag = lb;
		lb++;
	}
	else{
		if(up){
			tag = up;
		}
		if(down){
			tag = down;
		}
		if(left){
			tag = left;
		}
		if(right){
			tag = right;
		}
	}
	
	return tag;
}

void second_pass(Mat &img, int i, int j){
	
	label current	= img.at<label>(i,j);
	
	if(current){
		
		label down 	= 	(j+1<img.cols)? img.at<label>(i,j+1): 0;
		label up 		= 	(j-1>=0)? img.at<label>(i,j-1): 0;
		label left 	= 	(i-1>=0)? img.at<label>(i-1,j): 0;
		label right 	= 	(i+1<img.rows)? img.at<label>(i+1,j): 0;
		
		if(up && up!=current){
			img.at<label>(i,j-1) = current;
			second_pass(img, i, j-1);
		}
		if(down && down!=current){
			img.at<label>(i,j+1) = current;
			second_pass(img, i, j+1);
		}
		if(left && left!=current){
			img.at<label>(i-1,j) = current;
			second_pass(img, i-1, j);
		}
		if(right && right!=current){
			img.at<label>(i+1,j) = current;
			second_pass(img, i+1, j);
		}
		
	}
}

vector<label> label_segmentation(Mat img, Mat& dest){
	
	etiquetas_usadas.clear();
	
/// Asumo que dest ya viene con la imagen en negro...
	if(dest.empty()){
		dest = Mat(img.size(),CV_8UC1,Scalar(0,0,0));
	}
	label current_img, current_lbl;
	label lb=1;
	
	/// Primer Pasada
	for(int i =0;i<img.rows;i++)
		for(int j=0; j<img.cols; j++)
	{
		current_lbl = dest.at<label>(i,j);
		current_img = img.at<label>(i,j);
		
		if(current_img && !current_lbl){
			dest.at<label>(i,j) = check_neightbor(dest, i , j, lb);
		}
	}
		
	/// Segunda Pasada
	label up,down,left,right, current;
	vector<label> connected;
		
	for(int i =0;i<img.rows;i++)
		for(int j=0; j<img.cols; j++)
	{
		second_pass(dest, i, j);
	}
	
	vector<label>::iterator it;
	for(int i =0;i<img.rows;i++)
		for(int j=0; j<img.cols; j++)
	{
		current = dest.at<label>(i,j);
		if(current){
			it = find(etiquetas_usadas.begin(),etiquetas_usadas.end(), current);
			
			if(it == etiquetas_usadas.end())
				etiquetas_usadas.push_back(current);
		}
		
	}
	
	return etiquetas_usadas;
	
}

#endif
