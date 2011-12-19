#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxFlash.h"

#include "Box.h"
#include "Cross.h"

class testApp : public ofxiPhoneApp {

public:

	void setup	();
	void update	();
	void draw	();
	void exit	();

	void touchDown		( int x, int y, int id );
	void touchMoved		( int x, int y, int id );
	void touchUp		( int x, int y, int id );
	void touchDoubleTap	( int x, int y, int id );

	void lostFocus					();
	void gotFocus					();
	void gotMemoryWarning			();
	void deviceOrientationChanged	(int newOrientation);

	ofxFlashStage* stage;

};


