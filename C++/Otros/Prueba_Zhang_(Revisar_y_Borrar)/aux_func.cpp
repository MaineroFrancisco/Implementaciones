#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <string>
using namespace std;

extern vector<int> mouse_click_x,mouse_click_y;
extern int cap_ip;
extern bool next_p;

static void mouseRecorder(int event,int x,int y, int flags,void* param){
	if(event == CV_EVENT_LBUTTONDOWN)
	{
		mouse_click_x.push_back(x);
		mouse_click_y.push_back(y);
	}
	
	if(event == CV_EVENT_RBUTTONDOWN)
	{
		ofstream output;
		output.open ("c_2_"+to_string(cap_ip)+".txt",ios::out);
		for( int i=0; i<mouse_click_x.size(); i++)
		{
			output<< mouse_click_x[i] <<" "<< mouse_click_y[i]<<endl; 
		}
		output.close();
		
		next_p = true;
	}
}

