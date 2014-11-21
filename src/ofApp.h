#pragma once

#include "ofMain.h"
#include "MyTestObject.h"
#include "ofxPS3EyeGrabber.h"
#include "ofxOsc.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);


        ofVideoGrabber 		vidGrabber;
        unsigned char * 	videoInverted;
        ofTexture			videoTexture;
        int 				camWidth;
        int 				camHeight;

        ofImage             videoSource;

        vector <jellySequence*> jellySequencer;

        ofxOscSender sender;

        float timer_interval;
        unsigned long long timer_current;

        int jelly_cnt;

        #define HOST "localhost"
        #define PORT 12345

private:

};
