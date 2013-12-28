#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofBackground(0,0,0);
	ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    player.loadMovie("fingers.mov");
    player.play();
    player.setVolume(0.0);
    
    rgbaFboFloat.allocate(ofGetWindowWidth(), ofGetWindowHeight(), GL_RGBA32F_ARB);
	rgbaFboFloat.begin();
	ofClear(255,255,255, 0);
    rgbaFboFloat.end();
    
    enableDepthTest = true;


}

//--------------------------------------------------------------
void testApp::update(){
    //ofEnableAlphaBlending();
   
    player.update();
    rgbaFboFloat.begin();
    drawIntoFBO();
	rgbaFboFloat.end();

}

//--------------------------------------------------------------
void testApp::draw(){
    rgbaFboFloat.draw(0,0);
}


//--------------------------------------------------------------
void testApp::drawIntoFBO(){
    //we clear the fbo if c is pressed.
	//this completely clears the buffer so you won't see any trails
	if( ofGetKeyPressed('c') ){
		ofClear(255,255,255, 0);
	}
	
	//some different alpha values for fading the fbo
	//the lower the number, the longer the trails will take to fade away.
	fadeAmnt = 20;
	if(ofGetKeyPressed('1')){
		fadeAmnt = 1;
	}else if(ofGetKeyPressed('2')){
		fadeAmnt = 5;
	}else if(ofGetKeyPressed('3')){
		fadeAmnt = 15;
	}
    
	//1 - Fade Fbo
	
	//this is where we fade the fbo
	//by drawing a rectangle the size of the fbo with a small alpha value, we can slowly fade the current contents of the fbo.
    
     ofPushStyle();
     ofFill();
     ofSetColor(0,0,0, fadeAmnt);
     ofRect(0,0,ofGetWindowWidth(),ofGetWindowHeight());
     ofPopStyle();
    
    
	//2 - Draw graphics
	
    float movementSpeed = .1;
	float cloudSize = ofGetWidth() / 2;
	float maxBoxSize = 100;
	float spacing = 1;
	
    cam.begin();
	
	for(int i = 0; i < 20; i++) {
        
		ofPushMatrix();
		
		float t = (ofGetElapsedTimef() + i * spacing) * movementSpeed;
		ofVec3f pos(
                    ofSignedNoise(t, 0, 0),
                    ofSignedNoise(0, t, 0),
                    ofSignedNoise(0, 0, t));
		
		float boxSize = maxBoxSize * ofNoise(pos.x, pos.y, pos.z);
		
		pos *= cloudSize;
		ofTranslate(pos);
        ofPushStyle();
        ofEnableNormalizedTexCoords();
        player.getTextureReference().bind();
		ofFill();
        
        if (enableDepthTest) {
            ofEnableDepthTest();
        }
		
        ofDrawBox(boxSize);
        
        if (enableDepthTest) {
            ofDisableDepthTest();
        }
        
        player.getTextureReference().unbind();
        ofDisableNormalizedTexCoords();
        ofPopStyle();
		ofPopMatrix();
    }
    cam.end();
    
}

void testApp::keyPressed(int key){
    if(key=='d'){
        enableDepthTest = !enableDepthTest;
    }
}