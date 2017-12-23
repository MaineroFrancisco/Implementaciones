#include "feature.h"

feature::feature() {
	
}

int main(int argc, char** argv) {
	
	//write text on the matrix:
	Mat img = imread("iglesia2.JPG",CV_LOAD_IMAGE_GRAYSCALE);
	
	imshow("Original", img);
	
	///-------------------------------------------------------------------------
	///Mascaras gaussianas para derivadas
	
	// Dx
	Mat dx = (Mat_<float>(3, 3) << -1.0f, 0.0f, 1.0f,
			  -1.0f,  0.0f,  1.0f,
			  -1.0f,  0.0f,  1.0f);
	
	//Dy
	Mat dy;
	transpose(dx,dy);
	
	//Calculate Dx
	Mat iDx = Mat::zeros(img.size(),CV_32FC1);
	filter2D(img, iDx,-1,dx,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	
	
	//Calculate Dx^2
	Mat iDx2;
	multiply(iDx, iDx,iDx2);
	
	//Calculate Dy
	Mat iDy = Mat::zeros(img.size(),CV_32FC1);
	filter2D(img, iDy,-1,dy,cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	
	//Calculate Dy^2
	Mat iDy2;
	multiply(iDy, iDy,iDy2);
	
	//Calculate DxDy
	Mat iDxDy;
	multiply(iDx, iDy,iDxDy);
	
	///-------------------------------------------------------------------------
	///Applying gaussian filter
	int size = 3;
	double sigma = 1.5f;
	
	//	Mat kernel ={Mat<float>(3,3) << 1.0f, 1.0f, 1.0f,
	//									1.0f, 1.0f, 1.0f,
	//									1.0f, 1.0f, 1.0f
	//				}
	
	Mat kernel = getGaussianKernel(size,sigma,CV_32F);
	//Kernel Gaussiano de Integracion (Explicacion)
	/**/
	filter2D(iDx2,iDx2, -1, kernel, cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	filter2D(iDy2,iDy2, -1, kernel, cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	filter2D(iDxDy,iDxDy, -1, kernel, cv::Point(-1,-1), 0, cv::BORDER_CONSTANT);
	
	///-------------------------------------------------------------------------
	/// Creating harris Matrix
	Mat harris_matrix = Mat::zeros(img.rows*2, img.cols*2,CV_32FC1);
	Size size_img = img.size();
	
	Rect roi_dx_2 = Rect(0,0,size_img.width,size_img.height);
	Rect roi_dy_2 = Rect(size_img.width,size_img.height,size_img.width,size_img.height);
	Rect roi_dy_dx = Rect(0,size_img.height,size_img.width,size_img.height);
	Rect roi_dx_dy = Rect(size_img.width,0,size_img.width,size_img.height);
	
	
	iDx2.copyTo(harris_matrix(roi_dx_2));
	iDy2.copyTo(harris_matrix(roi_dy_2));
	iDxDy.copyTo(harris_matrix(roi_dy_dx));
	iDxDy.copyTo(harris_matrix(roi_dx_dy));
	//	imshow("Harris", harris_matrix);		
	
	/// Computing corner Score		|| Formula 1: det - k*(trace)^2		|| Formula 2: det / trace
	Mat corner_score = Mat::zeros(size_img,CV_32FC1);
	Mat det;
	Mat trace;
	
	// Calculate the Determinant
	Mat iDxDy2;
	multiply(iDxDy,iDxDy,iDxDy2);
	multiply(iDx2,iDy2,det);	
	subtract(det,iDxDy2,det);
	
	//Calculate the trace
	Scalar k(0.04);
	add(iDx2,iDy2,trace);
	
	// Calculate Corner Score by "Formula 1"
	multiply(trace,trace, trace);
	multiply(trace,k,trace);
	subtract(det,trace,corner_score);
	
	// Show in screen
	imshow("Corner_Score", corner_score);
	
	
	///Ordering
	
	double minVal, maxVal;
	minMaxLoc(corner_score, &minVal, &maxVal);
	
	cout<<minVal<<" "<<maxVal<<endl;
	
	//	Mat se = getStructuringElement(MORPH_RECT,Size(3,3));
	//	dilate(corner_score,corner_score,se);
	//	erode(corner_score,corner_score,se);
	//	
	threshold(corner_score,corner_score,240,255,CV_THRESH_TOZERO);
	// Show in screen
	imshow("Filtrada", corner_score);
	
	//wait for the user to press any key:
	waitKey(0);
	return 0;
} 
