#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "Clone.h"
//#include "ofxOpenCv.h"
#include "ofxFaceTracker.h"
#include "ofxFaceTrackerThreaded.h"
#include "ofx3DModelLoader.h"


class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void dragEvent(ofDragInfo dragInfo);
	void loadFace(string face);
	
	void keyPressed(int key);

	void checkGamestateChange(int oldstate, int newstate);

	ofxFaceTrackerThreaded camTracker;
	ofVideoGrabber cam;
	
	ofxFaceTracker srcTracker;
	ofImage src;
	vector<ofVec2f> srcPoints;
	
	bool cloneReady;
	Clone clone;
	ofFbo srcFbo, maskFbo;

	ofDirectory faces;
	int currentFace;
	
	
	ofImage mirrored;
	ofTrueTypeFont ourfont;
	
	bool faceTrackerOn;

	float width, height;
	
	
	ofImage tacoImg, mikuImg;
	
	float rTime;
	
	
	ofx3DModelLoader helmetModel;
	//ofx3DModelLoader helmetModelA1;
	//ofx3DModelLoader helmetModelA2;
	//ofx3DModelLoader helmetModelA3;
	
	ofImage sen0;
	ofImage sen1;
	ofImage sen2;
	
	
	ofImage shaderT, shaderN;
	ofTexture tnoise, tpattern;

	
	//ofImage noise;
	ofImage fire;
	//ofImage pattern;
	ofImage patternf;
	ofImage logo, logo2;
	ofImage mask, mask2;
	
	//ofTexture tnoise;
	ofTexture tfire;
	//ofTexture tpattern;
	ofTexture tpatternf;
	ofTexture tlogo;
	ofTexture tmask, tmask2;
	
	ofShader shader, fireshader, logoshader;
	
	ofImage ofLogo; // the OF logo

	
	
	int showModel;
	int showSen;

	ofVideoPlayer 		crowdMovie;
	ofVideoPlayer 		challengeMovie;
	bool playMovie;
	
	int gamestate;
	bool showFrameRate;
	
};
