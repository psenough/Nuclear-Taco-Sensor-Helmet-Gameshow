#include "testApp.h"

using namespace ofxCv;


GLfloat ambientColor[] = {0.8f, 0.8f, 0.8f, 1.0f}; //Color (0.2, 0.2, 0.2)
/*
GLfloat lightOnePosition[] = {140.0, 140, 0.0, 0.0};
GLfloat lightOneColor[] = {0.99, 0.99, 0.99, 1.0};

GLfloat lightTwoPosition[] = {-140.0, 140, 0.0, 0.0};
GLfloat lightTwoColor[] = {0.99, 0.99, 0.99, 1.0};*/


void testApp::setup() {

	showFrameRate = true;
	faceTrackerOn = true;
	
	ofSetVerticalSync(true);
	
	
	//
	// host face substitution
	//
	
	if (faceTrackerOn) {
		cloneReady = false;
		cam.initGrabber(640, 480);
	
		srcTracker.setup();
		clone.setup(cam.getWidth(), cam.getHeight());
		ofFbo::Settings settings;
		settings.width = cam.getWidth();
		settings.height = cam.getHeight();
		maskFbo.allocate(settings);
		srcFbo.allocate(settings);
		camTracker.setup();
		srcTracker.setup();
		srcTracker.setIterations(25);
		srcTracker.setAttempts(4);

		/*faces.allowExt("jpg");
		faces.allowExt("png");
		faces.listDir("faces");
		currentFace = 0;
		if(faces.size()!=0){
			loadFace(faces.getPath(currentFace));
		}*/
		loadFace("faces/shido_fix.jpg");
	}


	//
	// background shader effect
	//
	
	shaderT.setUseTexture(false);
	shaderT.loadImage("shader/p1.png");  
	tpattern.texData.textureTarget = GL_TEXTURE_2D;
	tpattern.allocate(shaderT.getWidth(), shaderT.getHeight(), GL_RGB, false);
	tpattern.loadData(shaderT.getPixelsRef());
	tpattern.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	tpattern.setTextureWrap(GL_REPEAT, GL_REPEAT);
	
	shaderN.setUseTexture(false);
	shaderN.loadImage("shader/fur.png"); 
	tnoise.texData.textureTarget = GL_TEXTURE_2D;
	tnoise.allocate(shaderN.getWidth(), shaderN.getHeight(), GL_LUMINANCE, false);
	tnoise.loadData(shaderN.getPixelsRef());
	tnoise.setTextureMinMagFilter(GL_LINEAR, GL_LINEAR);
	tnoise.setTextureWrap(GL_REPEAT, GL_REPEAT);
	
	shader.load("shader/0.vs", "shader/0.fs");
	
	
	//
	// taco image
	//
	
	tacoImg.loadImage("images/taco.png");
	
	//ourfont.loadFont("verdana.ttf", 60, true, true);
	//ourfont.setLineHeight(34.0f);
	//ourfont.setLetterSpacing(1.035);
	

	
	//
	// helmet model
	//
	
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	helmetModel.loadModel("helmet/helmet03.3ds", 20);
	helmetModel.setRotation(0, 180, 1, 0, 0);
    helmetModel.setRotation(1, 180, 0, 1, 0);
    helmetModel.setScale(1.75, 1.75, 1.75);
    helmetModel.setPosition(ofGetWidth()/2, ofGetHeight()/2 - 20, 250);
	
/*
	helmetModelA1.loadModel("helmet/helmet04.3ds", 20);
	helmetModelA1.setRotation(0, 180, 1, 0, 0);
    helmetModelA1.setRotation(1, 180, 0, 1, 0);
    helmetModelA1.setScale(1.6, 1.6, 1.6);
    helmetModelA1.setPosition(ofGetWidth()/2, ofGetHeight()/2 + 10, 220);

	helmetModelA2.loadModel("helmet/helmet05.3ds", 20);
	helmetModelA2.setRotation(0, 180, 1, 0, 0);
    helmetModelA2.setRotation(1, 180, 0, 1, 0);
    helmetModelA2.setScale(1.6, 1.6, 1.6);
    helmetModelA2.setPosition(ofGetWidth()/2, ofGetHeight()/2 + 10, 220);

	helmetModelA3.loadModel("helmet/helmet06.3ds", 20);
	helmetModelA3.setRotation(0, 180, 1, 0, 0);
    helmetModelA3.setRotation(1, 180, 0, 1, 0);
    helmetModelA3.setScale(1.6, 1.6, 1.6);
    helmetModelA3.setPosition(ofGetWidth()/2, ofGetHeight()/2 + 10, 220);*/
	
	showModel = 0;

	sen0.loadImage("images/tmp.png");
	sen1.loadImage("images/wa.png");
	sen2.loadImage("images/hum.png");
	
	showSen = 0;
	
	//
	// title screen
	//

	mikuImg.loadImage("helmet/miku_helmet_14.png");

/*	pattern.setUseTexture(false);
	pattern.loadImage("title/p.png");
	
	tpattern.texData.textureTarget = GL_TEXTURE_2D;
	
	tpattern.allocate(pattern.getWidth(), pattern.getHeight(), GL_RGB, false);
	tpattern.loadData(pattern.getPixelsRef());
	
	tpattern.setTextureMinMagFilter(GL_NEAREST, GL_NEAREST);
	tpattern.setTextureWrap(GL_REPEAT, GL_REPEAT);
	*/
	patternf.setUseTexture(false);
	patternf.loadImage("title/pfire.png");
	
	tpatternf.texData.textureTarget = GL_TEXTURE_2D;
	
	tpatternf.allocate(patternf.getWidth(), patternf.getHeight(), GL_RGB, false);
	tpatternf.loadData(patternf.getPixelsRef());
	
	tpatternf.setTextureMinMagFilter(GL_LINEAR, GL_LINEAR);
	tpatternf.setTextureWrap(GL_REPEAT, GL_REPEAT);
	
	fire.setUseTexture(false);
	fire.loadImage("title/distortion.png");
	
	tfire.texData.textureTarget = GL_TEXTURE_2D;
	
	tfire.allocate(fire.getWidth(), fire.getHeight(), GL_RGB, false);
	tfire.loadData(fire.getPixelsRef());
	
	tfire.setTextureMinMagFilter(GL_LINEAR, GL_LINEAR);
	tfire.setTextureWrap(GL_REPEAT, GL_REPEAT);
	
	mask.setUseTexture(false);
	mask.loadImage("title/mask.png");
	
	tmask.texData.textureTarget = GL_TEXTURE_2D;
	
	tmask.allocate(mask.getWidth(), mask.getHeight(), GL_RGB, false);
	tmask.loadData(mask.getPixelsRef());
	
	tmask.setTextureMinMagFilter(GL_LINEAR, GL_LINEAR);
	tmask.setTextureWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
	
	//logo.setUseTexture(false);
	logo.loadImage("title/logo.png");
	
	//tlogo.texData.textureTarget = GL_TEXTURE_2D;
	
	//tlogo.allocate(logo.getWidth(), logo.getHeight(), GL_RGB, false);
	//tlogo.loadData(logo.getPixelsRef());
	
	//tlogo.setTextureMinMagFilter(GL_LINEAR, GL_LINEAR);
	//tlogo.setTextureWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);

	
	mask2.setUseTexture(false);
	mask2.loadImage("title/mask2.png");
	
	tmask2.texData.textureTarget = GL_TEXTURE_2D;
	
	tmask2.allocate(mask2.getWidth(), mask2.getHeight(), GL_RGB, false);
	tmask2.loadData(mask2.getPixelsRef());
	
	tmask2.setTextureMinMagFilter(GL_LINEAR, GL_LINEAR);
	tmask2.setTextureWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
	
	//logo.setUseTexture(false);
	logo2.loadImage("title/logo2.png");
	
	
/*	noise.setUseTexture(false);
	noise.loadImage("title/n.png");
	tnoise.texData.textureTarget = GL_TEXTURE_2D;
	
	tnoise.allocate(noise.getWidth(), noise.getHeight(), GL_LUMINANCE, false);
	tnoise.loadData(noise.getPixelsRef());
	
	tnoise.setTextureMinMagFilter(GL_LINEAR, GL_LINEAR);
	tnoise.setTextureWrap(GL_REPEAT, GL_REPEAT);
*/	
	//shader0.load("shader0.vert", "shader0.frag");
	fireshader.load("title/fire.vert", "title/fire.frag");
	logoshader.load("title/logo.vert", "title/logo.frag");


	//
	// crowd movie
	//
	
	crowdMovie.loadMovie("videos/audiencia_novo.mp4");
	crowdMovie.setLoopState(OF_LOOP_NONE);

	
	
	//
	// taco challenge movie
	//
	
	challengeMovie.loadMovie("videos/TheShorterGameShow.mp4");
	challengeMovie.setLoopState(OF_LOOP_NONE);
	playMovie = false;
	
	gamestate = 0;
	
}

void testApp::update() {

	switch(gamestate) {
		default:
		case 0: // host
			if (faceTrackerOn) {
				ofSetColor(255);
				
				cam.update();
				if(cam.isFrameNew()) {
					
					camTracker.update(toCv(cam));
					
					cloneReady = camTracker.getFound();
					if(cloneReady) {

						ofMesh camMesh = camTracker.getImageMesh();
						camMesh.clearTexCoords();
						camMesh.addTexCoords(srcPoints);
						
						maskFbo.begin();
						ofClear(0, 255);
						camMesh.draw();
						maskFbo.end();
						
						srcFbo.begin();
						ofClear(0, 255);
						src.bind();
						camMesh.draw();
						src.unbind();
						srcFbo.end();
						
						clone.setStrength(16);
						clone.update(srcFbo.getTextureReference(), cam.getTextureReference(), maskFbo.getTextureReference());
					}
				//}
				//cam.update();
				//if(cam.isFrameNew()) {
					srcTracker.update(toCv(cam));
				}
				
			}
			break;
		case 1: // taco
			break;
		case 2: // burn coming in and burn coming out
			break;
		case 3: // helmet
			helmetModel.setRotation(1, 180 + ofGetElapsedTimef() * 90, 0, 1, 0);
			//helmetModelA1.setRotation(1, 180 + ofGetElapsedTimef() * 60, 0, 1, 0);
			//helmetModelA2.setRotation(1, 180 + ofGetElapsedTimef() * 60, 0, 1, 0);
			//helmetModelA3.setRotation(1, 180 + ofGetElapsedTimef() * 60, 0, 1, 0);
			break;
		case 4: // title screen
			break;
		case 5: // video of crowd
			if (playMovie) {
				crowdMovie.idleMovie();
				if (crowdMovie.getIsMovieDone()) {
					//playMovie = false;
					//gamestate = 6;
				}
			}
			break;
		case 6: // video of challenge
			if (playMovie) {
				challengeMovie.idleMovie();
				if (challengeMovie.getIsMovieDone()) {
					playMovie = false;
				}
			}
			break;
	}

}

void testApp::draw() {
	//ofSetColor(255,255,255);	

	switch(gamestate) {
		default:
		case 0: // host
			if (faceTrackerOn) {
				
				ofSetColor(255);
				
				if(src.getWidth() > 0 && cloneReady) {
					//clone.mirror(true, false);
					clone.draw(0, 0);
				} else {
					//cam.mirror(true, false);
					cam.draw(0, 0);
				}
				
				/*if(!camTracker.getFound()) {
				 drawHighlightString("camera face not found", 10, 10);
				 }
				 if(src.getWidth() == 0) {
				 drawHighlightString("drag an image here", 10, 30);
				 } else if(!srcTracker.getFound()) {
				 drawHighlightString("image face not found", 10, 30);
				 }*/
				
			}
			break;
		case 1: // taco
			{
				ofSetColor(255,255,255);

				shader.begin();
				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, tnoise.getTextureData().textureID);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, tpattern.getTextureData().textureID);
				shader.setUniform1i("N", 0);
				shader.setUniform1i("T", 1);
				shader.setUniform2f("s", ofGetWidth()/ofGetHeight(), 1.0f );
				shader.setUniform1f("a", 0.1f );
				shader.setUniform1f("time", ofGetElapsedTimef() );
				ofRect(-5.0, -5.0, 20.0, 20.0);
				shader.end();
				
				ofEnableAlphaBlending();
				float zoomer = 1.0 - exp(-(ofGetElapsedTimef()-rTime));
				if (zoomer > 1.0) zoomer = 1.0;
				float tw = (tacoImg.getWidth()/2) * zoomer;
				float th = (tacoImg.getHeight()/2) * zoomer;
				float centerx = ofGetWidth()/2.0f;
				float centery = ofGetHeight()/2.0f;
				tacoImg.draw(centerx - tw*.5, centery - th*.5, tw, th);
				ofDisableAlphaBlending();
			}
			break;
		case 2: // burn coming in and burn coming out
		{
			float zoomer = 1.0 - exp(-(ofGetElapsedTimef()-rTime))*3.0f;
			if (zoomer > 1.0) zoomer = 1.0;
			float s = sin(ofGetElapsedTimef()-rTime) * 0.1f;
			
			ofSetColor(255,255,255);
			shader.begin();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tnoise.getTextureData().textureID);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tpattern.getTextureData().textureID);
			shader.setUniform1i("N", 0);
			shader.setUniform1i("T", 1);
			shader.setUniform2f("s", ofGetWidth()/ofGetHeight(), 1.0f );
			shader.setUniform1f("a", 0.1f );
			shader.setUniform1f("time", ofGetElapsedTimef() );
			ofRect(-5.0, -5.0, 20.0, 20.0);
			shader.end();
			
			fireshader.begin();
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tfire.getTextureData().textureID);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tpatternf.getTextureData().textureID);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, tmask2.getTextureData().textureID);
			fireshader.setUniform1f("time", ofGetElapsedTimef());
			fireshader.setUniform1i("M", 2);
			fireshader.setUniform1i("N", 0);
			fireshader.setUniform1i("G", 1);
			fireshader.setUniform2f("s", (s + zoomer)*1.1, -(s + zoomer)*1.1);
			ofRect(-5.0, -5.0, 20.0, 20.0);
			glDisable(GL_BLEND);
			fireshader.end();
			
			ofSetColor(255,255,255);
			ofEnableAlphaBlending();
			float tw = (logo.getWidth()/2) * (s + zoomer) * 1.25;
			float th = (logo.getHeight()/2) * (s + zoomer) * 1.9;
			float centerx = ofGetWidth()/2.0f;
			float centery = ofGetHeight()/2.0f;
			logo2.draw(centerx-tw*.5,centery-th*.5, tw, th);
			ofDisableAlphaBlending();
		}
			break;
		case 3: // helmet
			ofSetColor(255,255,255);

			shader.begin();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tnoise.getTextureData().textureID);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tpattern.getTextureData().textureID);
			shader.setUniform1i("N", 0);
			shader.setUniform1i("T", 1);
			shader.setUniform2f("s", ofGetWidth()/ofGetHeight(), 1.0f );
			shader.setUniform1f("a", 0.1f );
			shader.setUniform1f("time", ofGetElapsedTimef() );
			ofRect(-5.0, -5.0, 20.0, 20.0);
			shader.end();
			
			if (showModel != -1) {
				ofEnableAlphaBlending();
				glEnable(GL_DEPTH_TEST);
				glEnable(GL_LIGHTING);
				glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
				glEnable(GL_COLOR_MATERIAL);
				float zoomer = 1.0 - exp(-(ofGetElapsedTimef()-rTime));
				//pushMatrix();
				helmetModel.setScale(zoomer*1.75,zoomer*1.75,zoomer*1.75);
				helmetModel.setPosition(ofGetWidth()/2, ofGetHeight()/2 - 20*zoomer, 250*zoomer);

				helmetModel.draw();
				//popMatrix();
				/*switch(showModel) {
					case 0:
						helmetModel.draw();
						break;
					case 1:
						helmetModelA1.draw();
						break;
					case 2:
						helmetModelA2.draw();
						break;
					case 3:
						helmetModelA3.draw();
						break;
				}*/
				glDisable(GL_COLOR_MATERIAL);
				glDisable(GL_DEPTH_TEST);
				glDisable(GL_LIGHTING);
				ofDisableAlphaBlending();
			}
			
			ofEnableAlphaBlending();
			switch (showSen) {
				case 1:
					sen0.draw(0,0,640,480);
					break;
				case 2:
					sen1.draw(0,0,640,480);
					break;
				case 3:
					sen2.draw(0,0,640,480);
					break;
			}
			ofDisableAlphaBlending();
			
			
			break;

		case 21: // old pads
		{
			ofSetColor(255,255,255);

			float centerx = ofGetWidth()/2.0f;
			float centery = ofGetHeight()/2.0f;
			float centerz = 10.0f;
			float radius = 160.0f;
			
			int npads = 10;
			for (int i = 0; i < npads; i++) {
				
				float space = HALF_PI/10;
				
				
				float padposx1 = centerx + sin(ofGetElapsedTimef() + i*TWO_PI/npads - space) * radius;
				float padposx2 = centerx + sin(ofGetElapsedTimef() + i*TWO_PI/npads + space) * radius;
				
				float padposy1 = centery - cos(ofGetElapsedTimef() + i*TWO_PI/npads - space) * radius;
				float padposy2 = centery - cos(ofGetElapsedTimef() + i*TWO_PI/npads + space) * radius;
				
				
				ofSetColor(245, 245, 245);
				
				ofTriangle(centerx, centery, centerz,
						   padposx1+10, padposy1+10, centerz,
						   padposx2+10, padposy2+10, centerz);
				
				
				if (i%2 == 0) {
					ofSetColor(245, 58, 135);
				} else {
					ofSetColor(45, 158, 135);
				}
				
				ofTriangle(centerx, centery, centerz,
						   padposx1, padposy1, centerz,
						   padposx2, padposy2, centerz);
				
			}
			ofEnableAlphaBlending();
			float zoomer = 1.0 - exp(-(ofGetElapsedTimef()-rTime));
			if (zoomer > 1.0) zoomer = 1.0;
			float tw = (tacoImg.getWidth()/2) * zoomer;
			float th = (tacoImg.getHeight()/2) * zoomer;
			tacoImg.draw(centerx - tw, centery - th, tw, th);
			ofDisableAlphaBlending();
			
		}
		case 4: // title screen
		{
			float zoomer = 1.0 - exp(-(ofGetElapsedTimef()-rTime))*3.0f;
			if (zoomer > 1.0) zoomer = 1.0;
			float s = sin(ofGetElapsedTimef()-rTime) * 0.1f;

			
			ofSetColor(255,255,255);
			shader.begin();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tnoise.getTextureData().textureID);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tpattern.getTextureData().textureID);
			shader.setUniform1i("N", 0);
			shader.setUniform1i("T", 1);
			shader.setUniform2f("s", ofGetWidth()/ofGetHeight(), 1.0f );
			shader.setUniform1f("a", 0.1f );
			shader.setUniform1f("time", ofGetElapsedTimef() );
			ofRect(-5.0, -5.0, 20.0, 20.0);
			shader.end();
			
			fireshader.begin();
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tfire.getTextureData().textureID);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, tpatternf.getTextureData().textureID);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, tmask.getTextureData().textureID);
			fireshader.setUniform1f("time", ofGetElapsedTimef());
			fireshader.setUniform1i("M", 2);
			fireshader.setUniform1i("N", 0);
			fireshader.setUniform1i("G", 1);
			fireshader.setUniform2f("s", (s + zoomer), -(s + zoomer));
			ofRect(-5.0, -5.0, 20.0, 20.0);
			glDisable(GL_BLEND);
			fireshader.end();

			ofSetColor(255,255,255);
			//ofEnableAlphaBlending();
/*			logoshader.begin();
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tlogo.getTextureData().textureID);
			logoshader.setUniform1i("T", 0);
			logoshader.setUniform2f("s", (s + zoomer), -(s + zoomer));
			ofRect(-5.0, -5.0, 20.0, 20.0);
			glDisable(GL_BLEND);
			logoshader.end();*/
			//ofDisableAlphaBlending();
			
			ofEnableAlphaBlending();
			float tw = (logo.getWidth()/2) * (s + zoomer) * 1.25;
			float th = (logo.getHeight()/2) * (s + zoomer) * 1.9;
			float centerx = ofGetWidth()/2.0f;
			float centery = ofGetHeight()/2.0f;
			logo.draw(centerx-tw*.5,centery-th*.5, tw, th);
			//logo.draw(-5.0, -5.0, 20.0, 20.0);

			ofDisableAlphaBlending();
			
			
			ofEnableAlphaBlending();
			tw = mikuImg.getWidth();
			th = mikuImg.getHeight();
			centerx = ofGetWidth()/2.0f;
			centery = ofGetHeight()/2.0f;
			mikuImg.draw((1.0f-zoomer)*1000.0f-600.0f,centery-th+500.0f, tw*.7, th*.7);
			//logo.draw(-5.0, -5.0, 20.0, 20.0);
			
			ofDisableAlphaBlending();
			
			
		}
			break;
		case 5: // movie
			if (playMovie) {
				ofSetColor(255);
				crowdMovie.draw(0,0);
			}
			break;
		case 6: // movie
			if (playMovie) {
				ofSetColor(255);
				challengeMovie.draw(0,0);
			}
			break;
	}
	
	/*if (showFrameRate) {
		ofSetHexColor(0xfffff);
		ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, 15);
		ofDrawBitmapString("time: "+ofToString(ofGetElapsedTimef(), 2), 10, 45);

	}*/
}

void testApp::loadFace(string face){
	src.loadImage(face);
	if(src.getWidth() > 0) {
		srcTracker.update(toCv(src));
		srcPoints = srcTracker.getImagePoints();
	}
}

void testApp::dragEvent(ofDragInfo dragInfo) {
	if (faceTrackerOn) {
		loadFace(dragInfo.files[0]);
	}
}


void testApp::keyPressed(int key){
	switch(key){
			
		case OF_KEY_RIGHT:
			checkGamestateChange(gamestate,++gamestate);
			break;
			
		case OF_KEY_LEFT:
			checkGamestateChange(gamestate,--gamestate);
			break;

		case 'f':
			ofToggleFullscreen();
			break;

		case 'r':
			rTime = ofGetElapsedTimef();
			break;

		case '0':
			//showModel = 0;
			showSen = 0;
			break;
		case '1':
			//showModel = 1;
			showSen = 1;
			break;
		case '2':
			//showModel = 2;
			showSen = 2;
			break;
		case '3':
			//showModel = 3;
			showSen = 3;
			break;
		case '9':
			//showModel = -1;
			break;
	}
	

}

void testApp::checkGamestateChange(int oldstate, int newstate) {
	
	cout << "change to state: " << newstate << endl;
	
	
	if (oldstate == 5) {
		//playMovie = false;
		crowdMovie.stop();
		//challengeMovie.setFrame(0);
	}
	
	switch(newstate) {
		default:
		case 0:
			faceTrackerOn = true;
			break;
		case 1:
		case 2:
		case 3:
		case 4:
			faceTrackerOn = false;
			rTime = ofGetElapsedTimef();
			break;
		case 5:
			faceTrackerOn = false;
			playMovie = true;
			crowdMovie.play();
			break;
		case 6:
			faceTrackerOn = false;
			playMovie = true;
			challengeMovie.play();
			break;
	}

}

