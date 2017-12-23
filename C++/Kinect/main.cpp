#include <opencv2/opencv.hpp>
#include <iostream>
#include "NiTE.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv) {
	nite::Status niteRc;
	
	VideoCapture cap(CAP_OPENNI2);
	
	unsigned char pressed_key = 0;
	Mat frame;
	
	cout<<"Visualizacion 3D... "<<endl;	
	viz::Viz3d window("Coordinate Frame");
	window.setWindowSize(Size(500,500));
	window.setWindowPosition(Point(150,150));
	window.setBackgroundColor(); // black by default
	
	/// Systema de coordenadas del mundo
	viz::WLine axisX(Point3f(0.0f,0.0f,0.0f), Point3f(1.0f,0.0f,0.0f), Scalar(255,0,0));
	axisX.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig X", axisX);
	
	viz::WLine axisY(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,1.0f,0.0f), Scalar(0,0,255));
	axisY.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig Y", axisY);
	
	viz::WLine axisZ(Point3f(0.0f,0.0f,0.0f), Point3f(0.0f,0.0f,1.0f), Scalar(0,255,0));
	axisZ.setRenderingProperty(viz::LINE_WIDTH, 1.0);
	window.showWidget("Orig Z", axisZ);
	
	///
	niteRc = nite::NiTE::initialize();

	if(niteRc != nite::STATUS_OK)\
	{
		cout<< "Error de inicializacion" <<endl;
		return -1;
	}
	
	///
	nite::HandTracker hand;
	
	niteRc = hand.create();
	
	nite::HandTrackerFrameRef handFrame;

	if(niteRc != nite::STATUS_OK)\
	{
		cout<< "Error de handtracker" <<endl;
		return -2;
	}
	
	//	viz::WCloud cloud();
	hand.startGestureDetection(nite::GESTURE_WAVE);
	hand.startGestureDetection(nite::GESTURE_CLICK);
	for(;;)
	{
		Mat depthMap;
		Mat bgrImage;
		Mat cloudMap;
		cap.grab();
		cap.retrieve( depthMap, CAP_OPENNI_DEPTH_MAP );
		cap.retrieve( bgrImage, CAP_OPENNI_BGR_IMAGE );
		cap.retrieve( cloudMap, CAP_OPENNI_POINT_CLOUD_MAP);
		
		imshow("test",cloudMap);
		
		Size s = cloudMap.size();

		viz::WCloud cloud(cloudMap);
		window.showWidget("cloud", cloud);
		
		window.spinOnce();
		
		/// nite
		hand.readFrame(&handFrame);
	
		/// NiTE Gesture
		const nite::Array<nite::GestureData>& gesture = handFrame.getGestures();
		
		for(int i=0;i<gesture.getSize();i++) 
		{
			if(gesture[i].isComplete())
			{
				nite::HandId Id;
				hand.startHandTracking(gesture[i].getCurrentPosition(),&Id);
			}
		}
		
		/// NiTE Hands		
		const nite::Array<nite::HandData>& hands = handFrame.getHands();
		
		for(int i=0;i<hands.getSize();i++) 
		{
			const nite::HandData mano = hands[i];
			if(mano.isTracking())
			{
				cout<< mano.getId() << ", " << mano.getPosition().x << ", " << mano.getPosition().y << ", " << mano.getPosition().z <<endl;
			}
		}
		
		if( waitKey( 10 ) >= 0 )
			break;
	}
	
///-----------------------------------------------------------------------------
/// Vizualisacion 3D
///-----------------------------------------------------------------------------
	
	waitKey(0);
	
	return 0;
} 
