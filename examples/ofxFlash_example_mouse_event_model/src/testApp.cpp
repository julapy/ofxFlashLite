#include "testApp.h"

///////////////////////////////////////////
//	INIT.
///////////////////////////////////////////

void testApp::setup()
{
	ofSetFrameRate( 30 );							// OF setup.
	ofSetVerticalSync( true );
	ofSetCircleResolution( 100 );
	ofBackground( 255, 255, 255 );


	ofxFlashStage* stage;
	stage = ofxFlashStage :: getInstance();			// ofxFlash setup.
	stage->addListeners();							// by adding listeners, stage and all it's content is automatically updated and drawn for you.
	stage->showRedrawRegions( false );				// if set to true, it will draw the bounding rectangle around the object's pixels.

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


//	stage->root()->addChild( new Cross() );
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

