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
	ofxFlashDisplayObject* flashIcon;
	flashIcon = stage->root()->getChildByName( "fl_icon" );
	
	flashIcon->x( x );
	flashIcon->y( y );
}

void testApp::mousePressed(int x, int y, int button)
{

}

void testApp::mouseReleased(int x, int y, int button)
{

}

void testApp::windowResized(int w, int h)
{

}

