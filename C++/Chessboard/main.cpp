#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "chessboard.h"

#include <vector>

using namespace std;
using namespace cv;

int main(int argc, char** argv) {

	Mat color, mask;
	string path;
	int img_cant = 5;	//La seteo yo nomas
	
	if(argc)
	{
		path = argv[1];
	}
	cout<< path<<endl;
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
	
	int pressed_key = 0, k=0;
	while(pressed_key != 27)
	{
		
		imshow("imagen", color);
		
		pressed_key = waitKey(5);
		if(pressed_key == 13)
		{
			imagenes[(k%img_cant)].copyTo(color);
			
			vector<Point2i>features = chessboard_features(color, Size(7,7), mask);
			
			cout<< "Cantidad de features: "<< features.size() << endl;
			
			for(int i =0; i< features.size(); i++)
			{
				circle(color,features[i],5,Scalar(0,255,0));
			}
			
			k++;
			features.clear();
		}
	}
	
	waitKey(0);
	return 0;
} 
