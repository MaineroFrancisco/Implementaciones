#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "aux_func.cpp"

#include <string>
using namespace std;
using namespace cv;

vector<int> mouse_click_x,mouse_click_y;
int cap_ip = 1;
bool next_p = false;

int main(int argc, char** argv) {
	
	///
	string path_capturas = argv[1];

	unsigned char pressed_key = 0;
	namedWindow("Capturas",1);
	setMouseCallback("Capturas",mouseRecorder);
	while (pressed_key != 27 && cap_ip<5) 
	{
		ostringstream os;
		os << cap_ip;
		
		string path = path_capturas + "\\c2_"+os.str()+".jpeg";
		
		Mat img = imread(path,CV_LOAD_IMAGE_ANYCOLOR);
		
		imshow("Capturas", img);
		
		os.clear();
		os<<"";
		
		pressed_key = waitKey(5);

		if(next_p)
		{
			cap_ip++;
			next_p = false;
		}
		
	}
	
	
	return 0;
} 
