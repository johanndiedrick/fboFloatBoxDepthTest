#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void keyPressed(int key);
        void drawIntoFBO();

		
    ofFbo rgbaFboFloat; // with alpha
    ofVideoPlayer player;
    int fadeAmnt;
    ofEasyCam cam; // add mouse controls for camera movement
    
    bool enableDepthTest;


};
