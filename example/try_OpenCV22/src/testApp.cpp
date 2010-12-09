#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(320,240);	
	
	colorImg.allocate(320,240);
	grayImage.allocate(320,240);
	grayBg.allocate(320,240);
	grayDiff.allocate(320,240);
	
	bLearnBakground = true;
	threshold = 80;	
}

//--------------------------------------------------------------
void testApp::update(){

	bool bNewFrame = false;
	vidGrabber.grabFrame();
	bNewFrame = vidGrabber.isFrameNew();
	
	if (bNewFrame) {
		colorImg.setFromPixels(vidGrabber.getPixels(), 320,240);
		
        grayImage = colorImg;
		if (bLearnBakground == true){
			grayBg = grayImage;
			bLearnBakground = false;
		}
		
		grayDiff.absDiff(grayBg, grayImage);
		grayDiff.threshold(threshold);
		
		contourFinder.findContours(grayDiff, 20, (340*240)/3, 10, true);
	}
	
}

//--------------------------------------------------------------
void testApp::draw(){

	ofSetColor(0xffffff);
	colorImg.draw(20,20);
	grayImage.draw(360,20);
	grayBg.draw(20,280);
	grayDiff.draw(360,280);
	
	ofFill();
	ofSetColor(0x333333);
	ofRect(360,540,320,240);
	ofSetColor(0xffffff);
	
    for (int i = 0; i < contourFinder.nBlobs; i++){
        contourFinder.blobs[i].draw(360,540);
    }
	
	ofSetColor(0xffffff);
	char reportStr[1024];
	sprintf(reportStr, "bg subtraction and blob detection\npress ' ' to capture bg\nthreshold %i (press: +/-)\nnum blobs found %i, fps: %f", threshold, contourFinder.nBlobs, ofGetFrameRate());
	ofDrawBitmapString(reportStr, 20, 600);
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

	switch (key){
		case ' ':
			bLearnBakground = true;
			break;
		case '+':
			threshold ++;
			if (threshold > 255) threshold = 255;
			break;
		case '-':
			threshold --;
			if (threshold < 0) threshold = 0;
			break;
	}	
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

