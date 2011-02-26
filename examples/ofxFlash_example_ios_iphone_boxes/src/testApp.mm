#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofxAccelerometer.setup();
	ofxiPhoneAlerts.addListener(this);
	ofBackground( 255, 255, 255 );
	
	stage = ofxFlashStage :: getInstance();			// ofxFlash setup.
	stage->setTouchMode( true );					// set to true on iphone / ipad. value is false by default.
	
	for( int i=0; i<40; i++ )						// adding Box sprites to stage.
	{
		Box* box;
		box	= new Box();
		
		string boxName = "";
		boxName = "box_";
		boxName += ofToString( i, 0 );
		
		box->name( boxName );
		box->mouseEnabled( true );
		
		box->x( ofRandom( 0, ofGetScreenWidth() ) );
		box->y( ofRandom( 0, ofGetScreenHeight() ) );
		box->rotation( ofRandom( 0, 360 ) );
		
		stage->addChild( box );
	}
}

//--------------------------------------------------------------
void testApp::update()
{
	stage->update();
}

//--------------------------------------------------------------
void testApp::draw()
{
	stage->draw();
}

//--------------------------------------------------------------
void testApp::exit(){

}

//--------------------------------------------------------------
void testApp::touchDown( int x, int y, int id )
{
	stage->mousePressed( x, y, id );
}

//--------------------------------------------------------------
void testApp::touchMoved( int x, int y, int id )
{
	stage->mouseMoved( x, y, id );
}

//--------------------------------------------------------------
void testApp::touchUp( int x, int y, int id )
{
	stage->mouseReleased( x, y, id );
}

//--------------------------------------------------------------
void testApp::touchDoubleTap( int x, int y, int id ){

}

//--------------------------------------------------------------
void testApp::lostFocus(){

}

//--------------------------------------------------------------
void testApp::gotFocus(){

}

//--------------------------------------------------------------
void testApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void testApp::deviceOrientationChanged(int newOrientation){

}

