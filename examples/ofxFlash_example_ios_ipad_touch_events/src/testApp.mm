#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	ofxAccelerometer.setup();
	ofxiPhoneAlerts.addListener( this );
	ofxiPhoneSetOrientation( OFXIPHONE_ORIENTATION_LANDSCAPE_LEFT );
	
	ofBackground( 255, 255, 255 );
	
	//----- flash.
	
	stage = ofxFlashStage :: getInstance();			// ofxFlash setup.
	stage->showRedrawRegions( false );				// if set to true, it will draw the bounding rectangle around the object's pixels.
	stage->setTouchMode( true );					// touch input is handled differently from mouse input - set to true on iphone / ipad.
	
	int		w;
	int		h;
	float	r;
	Box*	pb;		// parent box.
	
	Box* box_0;
	box_0 = new Box( 500, 500 );
	box_0->mouseEnabled( true );
	box_0->x( ofGetWidth()  * 0.5 );
	box_0->y( ofGetHeight() * 0.5 );
	box_0->mouseEnabled( true );
	box_0->mouseChildren( true );
	stage->root()->addChild( box_0 );
	
	//-- two stems.
	
	r	= 0.35;
	pb	= box_0;
	w	= pb->boxW * 0.5;
	h	= pb->boxH * 0.5;
	
	Box* box_1_0;
	box_1_0		= new Box( w, h );
	box_1_0->x( (int)( pb->boxW * r ) );
	box_1_0->y(	(int)( pb->boxH * r * -1 ) );
	box_1_0->mouseEnabled( false );
	box_1_0->mouseChildren( true );
	pb->addChild( box_1_0 );
	
	Box* box_1_1;
	box_1_1		= new Box( w, h );
	box_1_1->x( (int)( pb->boxW * r ) );
	box_1_1->y( (int)( pb->boxH * r ) );
	box_1_1->mouseEnabled( true );
	box_1_1->mouseChildren( false );
	pb->addChild( box_1_1 );
	
	//-- top branch.
	
	r 	= 0.35;
	w 	= box_1_0->boxW * 0.5;
	h 	= box_1_0->boxH * 0.5;
	pb	= box_1_0;
	
	Box* box_1_0_0;
	box_1_0_0		= new Box( w, h );
	box_1_0_0->x( (int)( pb->boxW * r ) );
	box_1_0_0->y( (int)( pb->boxH * r * -1 ) );
	box_1_0_0->mouseEnabled( true );
	box_1_0_0->mouseChildren( true );
	pb->addChild( box_1_0_0 );
	
	Box* box_1_0_1;
	box_1_0_1		= new Box( w, h );
	box_1_0_1->x( (int)( pb->boxW * r ) );
	box_1_0_1->y( (int)( pb->boxH * r ) );
	box_1_0_1->mouseEnabled( false );
	box_1_0_1->mouseChildren( true );
	pb->addChild( box_1_0_1 );
	
	//-- bottom branch.
	
	r	= 0.35;
	w	= box_1_1->boxW * 0.5;
	h	= box_1_1->boxH * 0.5;
	pb	= box_1_1;
	
	Box* box_1_1_0;
	box_1_1_0		= new Box( w, h );
	box_1_1_0->x( (int)( pb->boxW * r ) );
	box_1_1_0->y( (int)( pb->boxH * r * -1 ) );
	box_1_1_0->mouseEnabled( false );
	box_1_1_0->mouseChildren( true );
	pb->addChild( box_1_1_0 );
	
	Box* box_1_1_1;
	box_1_1_1		= new Box( w, h );
	box_1_1_1->x( (int)( pb->boxW * r ) );
	box_1_1_1->y( (int)( pb->boxH * r ) );
	box_1_1_1->mouseEnabled( true );
	box_1_1_1->mouseChildren( true );
	pb->addChild( box_1_1_1 );
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

