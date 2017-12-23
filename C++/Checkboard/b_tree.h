#ifndef B_TREE_H
#define B_TREE_H

#include "opencv2/opencv.hpp"
#include <vector>
using namespace std;
using namespace cv;

struct feature
{
	Point2i p;
	float score;
	feature *left;
	feature *right;
};

class b_tree {
public:
	
	feature* base;
	feature* act;
	int size_max;
	int tam;
	
	vector<Point2i> pasaje;
	
	b_tree(){
		this->base = NULL;
		tam = 0;
		size_max = 100;
	};

	b_tree(int max){
		this->base = NULL;
		tam = 0;
		size_max = max;
	};
	
	
	void insert(Point2i p, float score);
	void erase(Point2i p);
	
	int get_size();
	
	vector<Point2i> get_tree ();
private:
	feature* insert (feature* nodo, Point2i p, float score);
	feature* erase(feature* nodo, Point2i p);
	
	void get_tree(feature* nodo);
	Point2i get(feature* nodo);
	
	int get_size(feature* nodo);
};



#endif

