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
	
	
	stage = ofxFlashStage :: getInstance();			// ofxFlash setup.
	stage->addListeners();
	stage->showRedrawRegions( bShowRedrawRegions = false );

	
	xfl.loadFile( "assets/DOMDocument.xml" );		// load XFL flash file.
	xfl.build();
	
	flashIcon = (ofxFlashMovieClip*)( stage->root()->getChildByName( "fl_icon" ) );
	
	stage->addChild( &instructions );				// add child to stage.
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
	if( key == 'd' )
	{
		stage->showRedrawRegions( bShowRedrawRegions = !bShowRedrawRegions );
	}
}

void testApp::keyReleased(int key)
{

}

void testApp::mouseMoved(int x, int y )
{

}

void testApp::mouseDragged(int x, int y, int button)
{
	flashIcon->x( x );
	flashIcon->y( y );
}

void testApp::mousePressed(int x, int y, int button)
{
	flashIcon->x( x );
	flashIcon->y( y );
}

void testApp::mouseReleased(int x, int y, int button)
{

}

void testApp::windowResized(int w, int h)
{

}

