#include "testApp.h"

///////////////////////////////////////////
//	INIT.
///////////////////////////////////////////

void testApp::setup()
{
	ofSetFrameRate( 30 );							// OF setup.
	ofSetVerticalSync( true );
	ofSetCircleResolution( 100 );
	ofEnableSmoothing();
	ofBackground( 255, 255, 255 );


	ofxFlashStage* stage;
	stage = ofxFlashStage :: getInstance();			// ofxFlash setup.
	stage->addListeners();							// by adding listeners, stage and all it's content is automatically updated and drawn for you.
	stage->showRedrawRegions( false );				// if set to true, it will draw the bounding rectangle around the object's pixels.


	for( int i=0; i<20; i++ )						// adding Box sprites to stage.
	{
		Box* box;
		box	= new Box();

		string boxName = "";
		boxName = "box_";
		boxName += ofToString( i, 0 );

		box->name( boxName );
		box->mouseEnabled( true );
		box->mouseUpOutside( true );

		box->x( ofRandom( 0, ofGetWidth() ) );
		box->y( ofRandom( 0, ofGetHeight() ) );
		box->rotation( ofRandom( 0, 360 ) );

		stage->addChild( box );
	}
}

///////////////////////////////////////////
//	UPDATE.
///////////////////////////////////////////

void testApp::update()
{
	//
}

///////////////////////////////////////////
//	DRAW.
///////////////////////////////////////////

void testApp::draw()
{
	//
}

///////////////////////////////////////////
//	HANDLERS.
///////////////////////////////////////////

void testApp::keyPressed(int key)
{

}

void testApp::keyReleased(int key)
{

}

void testApp::mouseMoved(int x, int y )
{
//	cout << "mouseMoved" << endl;
}

void testApp::mouseDragged(int x, int y, int button)
{
//	cout << "mouseDragged" << endl;
}

void testApp::mousePressed(int x, int y, int button)
{
//	cout << "mousePressed" << endl;
}

void testApp::mouseReleased(int x, int y, int button)
{
//	cout << "mouseReleased" << endl;
}

void testApp::windowResized(int w, int h)
{
	//
}

