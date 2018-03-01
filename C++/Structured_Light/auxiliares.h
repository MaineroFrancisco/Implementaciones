#ifndef AUXILIARES_H
#define AUXILIARES_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "opencv2/viz.hpp"
#include "opencv2/viz/widgets.hpp"

#include <iostream>

using namespace std;
using namespace cv;

enum tipo{ TEXTO, IMAGEN};

void show_mat(Mat img, tipo t = TEXTO,  int cam = 0);
void save_capture(Mat img,string path, int camera);
void callback_c1(int event, int x, int y, int flags, void* userdata);
void callback_c2(int event, int x, int y, int flags, void* userdata);
void draw_sys_coord(Mat M, viz::Viz3d windows);
void callback_pc1(int event, int x, int y, int flags, void* userdata);
void callback_pc2(int event, int x, int y, int flags, void* userdata);
void save_images(string path, VideoCapture c1, int start = 0);
void histograma(Mat f_hist, int histSize);
void show_hog(Mat gris, Point2f pos_feature, float orientation, Mat HOG);
Mat get_norm_matrix(Mat img);
Mat gauss_jordan(Mat input);
Mat estimate_homography(vector<Point2f> f, vector<Point2f> r);
Mat fix_rectify(Mat img, Mat r);
void draw_epiline(Mat img1, Mat I1, Mat E1, Mat img2, Mat I2, Mat E2, Point2f p);
#endif
