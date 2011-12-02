/*
 *  ofxStage.cpp
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxFlashStage.h"


ofxFlashStage* ofxFlashStage :: _instance = NULL;


/////////////////////////////////////////////
//	
/////////////////////////////////////////////

ofxFlashStage :: ofxFlashStage ()
{
	typeID = OFX_FLASH_TYPE_STAGE;
    
    this->stage = this;     // this is the stage.
	
	_root = new ofxFlashMovieClip();
	_root->name( "root1" );
	this->addChild( _root );
	
	_stageMouseX = 0;
	_stageMouseY = 0;
	
	topMostHitDisplayObject		= NULL;
	topMostHitDisplayObjectPrev	= NULL;
	
	bUsingListeners		= false;
	bTouchMode			= false;
	
	bMouseDown			= false;
	bMousePressed		= false;
	bMouseReleased		= false;
	bMouseChanged		= false;
	mouseID				= 0;
	
	showRedrawRegions( false );
	
#ifdef OF_USING_POCO	
	ofAddListener( ofEvents.mouseMoved,		this, &ofxFlashStage::mouseMoved	);		//-- add mouse event handlers.
	ofAddListener( ofEvents.mouseDragged,	this, &ofxFlashStage::mouseDragged	);
	ofAddListener( ofEvents.mousePressed,	this, &ofxFlashStage::mousePressed	);
	ofAddListener( ofEvents.mouseReleased,	this, &ofxFlashStage::mouseReleased	);
#endif
}

ofxFlashStage :: ~ofxFlashStage ()
{
#ifdef OF_USING_POCO	
	ofRemoveListener( ofEvents.mouseMoved,		this, &ofxFlashStage::mouseMoved	);	//-- remove mouse event handlers.
	ofRemoveListener( ofEvents.mouseDragged,	this, &ofxFlashStage::mouseDragged	);
	ofRemoveListener( ofEvents.mousePressed,	this, &ofxFlashStage::mousePressed	);
	ofRemoveListener( ofEvents.mouseReleased,	this, &ofxFlashStage::mouseReleased	);
#endif
}

/////////////////////////////////////////////
//	LISTENERS.
/////////////////////////////////////////////

void ofxFlashStage :: addListeners ()
{
	if( bUsingListeners )
		return;
	
	bUsingListeners = true;
	
#ifdef OF_USING_POCO	
	ofAddListener( ofEvents.update,		this, &ofxFlashStage::update	);
	ofAddListener( ofEvents.draw,		this, &ofxFlashStage::draw		);
#endif
}

void ofxFlashStage :: removeListeners ()
{
	if( !bUsingListeners )
		return;
	
	bUsingListeners = false;
	
#ifdef OF_USING_POCO	
	ofRemoveListener( ofEvents.update,	this, &ofxFlashStage::update	);
	ofRemoveListener( ofEvents.draw,	this, &ofxFlashStage::draw		);
#endif
}

/////////////////////////////////////////////
//	
/////////////////////////////////////////////

void ofxFlashStage :: showRedrawRegions ( bool value )
{
	bShowRedrawRegions = value;
}

void ofxFlashStage :: setTouchMode ( bool value )
{
	bTouchMode = value;
}

ofxFlashMovieClip* ofxFlashStage :: root ()
{
	return _root;
}

/////////////////////////////////////////////
//	MOUSEX / MOUSEY.
/////////////////////////////////////////////

const int& ofxFlashStage :: mouseX ()
{
	return _stageMouseX;
}

const int& ofxFlashStage :: mouseY ()
{
	return _stageMouseY;
}

/////////////////////////////////////////////
//	CORE.
/////////////////////////////////////////////

void ofxFlashStage :: setup ()
{
	//
}

void ofxFlashStage :: update ()
{
	topMostHitDisplayObjectPrev	= topMostHitDisplayObject;
	topMostHitDisplayObject		= NULL;
	
	updateChildrenOne( this, children );
	updateMouse();
	
	updateChildrenTwo( this, children );
	
	bMousePressed	= false;		// set back to false on every frame, so its only picked up once.
	bMouseReleased	= false;		// set back to false on every frame, so its only picked up once.
	bMouseChanged	= false;		// set back to false on every frame, so its only picked up once.
}

void ofxFlashStage :: draw ()
{
	ofEnableAlphaBlending();
	
	drawChildren( this, children );
	
	if( bShowRedrawRegions )
	{
		drawChildrenDebug( this, children );
	}
	
	ofDisableAlphaBlending();
}

/////////////////////////////////////////////
//	EVENT HANDLERS.
/////////////////////////////////////////////

#ifdef OF_USING_POCO

void ofxFlashStage :: update ( ofEventArgs &e )
{
	update();
}

void ofxFlashStage :: draw ( ofEventArgs &e )
{
	draw();
}

#endif

/////////////////////////////////////////////
//	UPDATE CHILDREN.
/////////////////////////////////////////////

void ofxFlashStage :: updateChildrenOne ( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children )
{
	parent->resetPixelBounds();		// clear pixel bounds on every loop and recalculate.
	
	for( int i=0; i<children.size(); i++ )
	{
		ofxFlashDisplayObject* child;
		child = children[ i ];
		
		if( !child->visible() )		// if set to invisible, ignore it and all it's children.
			continue;
		
		//=========================================== MATRIX.
		
		ofxFlashMatrix worldMatrix;						// transform child matrix by world matrix.
		worldMatrix = parent->concatenatedMatrix();
		worldMatrix.concatenate( child->matrix() );
		child->transform( worldMatrix );
		
		child->_compoundAlpha = parent->_compoundAlpha * child->_alpha;		// compound alpha adds up down the parent-child chain.
		
		child->updateOnFrame();
		
		//=========================================== FIND TOP MOST HIT DISPLAY OBJECT BY MOUSE.
		
		if( child->hitTestPoint( _stageMouseX, _stageMouseY ) )				// check if its the top most display object hit by mouse.
		{
			topMostHitDisplayObject = child;
		}
		
		//=========================================== UPDATE CHILDREN.
		
		if( canHaveChildren( child ) )
		{
			ofxFlashDisplayObjectContainer* container;
			container = (ofxFlashDisplayObjectContainer*)child;
			
			if( container->children.size() > 0 )
			{
				updateChildrenOne( child, container->children );
			}
		}
		
		parent->addToPixelBounds( child->pixelBounds() );	// compound pixel bounds from children.
	}
}

void ofxFlashStage :: updateMouse ()
{
	bool bHitDisplayObjectChanged = false;
	bHitDisplayObjectChanged = ( topMostHitDisplayObject != topMostHitDisplayObjectPrev );
	
	if( !bHitDisplayObjectChanged && !bMousePressed && !bMouseReleased && !bMouseChanged )	// update if either of these is true, otherwise return.
	{
		return;
	}
	
	if( false )	// debug
	{
		char frame[ 10 ];
		sprintf( frame, "%05d", ofGetFrameNum() );
		
		cout << "" << endl;
		cout << frame << " :: bHitDisplayObjectChanged = "	<< ( bHitDisplayObjectChanged ? "true" : "false" ) << endl;
		cout << frame << " :: bMousePressed = "				<< ( bMousePressed ? "true" : "false" ) << endl;
		cout << frame << " :: bMouseReleased = "			<< ( bMouseReleased ? "true" : "false" ) << endl;
		cout << frame << " :: bMouseChanged = "				<< ( bMouseChanged ? "true" : "false" ) << endl;
	}

	//=========================================== CREATE CHILD / PARENT LINES.

	ofxFlashDisplayObject* dispObj;
	ofxFlashInteractiveObject* intObj;
	
	if( bHitDisplayObjectChanged )
	{
		lineTopDownPrev		= lineTopDown;
		lineBottomUpPrev	= lineBottomUp;
		lineTopDown.clear();
		lineBottomUp.clear();
		
		if( topMostHitDisplayObject )			// check topMostHitDisplayObject is not null.
		{
			dispObj = topMostHitDisplayObject;
			while( dispObj != this )			// go down through child / parent nesting until stage is reached.
			{
				if( isInteractiveObject( dispObj ) )
				{
					ofxFlashInteractiveObject* intObj;
					intObj = (ofxFlashInteractiveObject*)dispObj;
					
					lineTopDown.push_back( intObj );
					lineBottomUp.insert( lineBottomUp.begin(), intObj );
				}
				
				dispObj	= dispObj->parent;
			}
		}
	}
	
	//=========================================== RESET PREVIOUS MOUSE STATES.
	
	if( topMostHitDisplayObjectPrev )		// if there is a previous line of display objects, clear mouse states.
	{
		for( int i=0; i<lineTopDownPrev.size(); i++ )			// go down through child / parent nesting until stage is reached.
		{
			intObj = lineTopDownPrev[ i ];
			intObj->mouseOverDirty = false;		// reset mouse over, dirty value used for further checks.
			intObj->mouseDownDirty = false;		// reset mouse down, dirty value used for further checks.
		}
	}
	
	if( !topMostHitDisplayObject )				// nothing is hit. mouse must not be over any objects.
	{
		if( topMostHitDisplayObjectPrev )		// if there is a previous line of display objects, clear mouse states.
		{
			for( int i=0; i<lineTopDownPrev.size(); i++ )	// go down through child / parent nesting until stage is reached.
			{
				intObj = lineTopDownPrev[ i ];
				intObj->mouseOver( false );		// reset mouse over.
				intObj->mouseDown( false );		// reset mouse down.
			}
		}
		
		return;									// objects cleared, nothing more to do.
	}
	
	if( bTouchMode && bMouseReleased )			// when in touch mode, object do not return to the over state.
	{
		if( topMostHitDisplayObject )			// if there is a current line of display objects, clear mouse states.
		{
			for( int i=0; i<lineTopDown.size(); i++ )	// go down through child / parent nesting until stage is reached.
			{
				intObj = lineTopDown[ i ];
				intObj->mouseOver( false );		// reset mouse over.
				intObj->mouseDown( false );		// reset mouse down.
			}
		}
		
		if( topMostHitDisplayObjectPrev )		// if there is a previous line of display objects, clear mouse states.
		{
			for( int i=0; i<lineTopDownPrev.size(); i++ )	// go down through child / parent nesting until stage is reached.
			{
				intObj = lineTopDownPrev[ i ];
				intObj->mouseOver( false );		// reset mouse over.
				intObj->mouseDown( false );		// reset mouse down.
			}
		}
		
		return;									// objects cleared, nothing more to do.
	}
	
	//=========================================== CHECK MOUSE ENABLED FLAG - TOP DOWN.
	
	bool bMouseEnabled = false;			// assume all display objects in nest have mouseEnabled set to false.
	
	for( int i=0; i<lineTopDown.size(); i++ )			// go down through child / parent nesting until stage is reached.
	{
		intObj = lineTopDown[ i ];

		// if bEnabled is still false, check if next display object down has mouseEnabled set to true.
		// once one mouseEnable has been found, all display objects below are now considered to be enabled.
		
		if( !bMouseEnabled )
		{
			bMouseEnabled = bMouseEnabled || intObj->mouseEnabled();
		}
		
		intObj->mouseOverDirty = bMouseEnabled;
	}
	
	//=========================================== CHECK MOUSE CHILDREN FLAG - BOTTOM UP.
	
	bool bMouseChildren = true;		// assume all display objects in nest have mouseChildren set to true.
	
	for( int i=0; i<lineBottomUp.size(); i++ )
	{
		intObj = lineBottomUp[ i ];

		bool bMouseOver;
		bMouseOver = intObj->mouseOverDirty;			// check if display object has already been set to mouse over with previous checks.
		bMouseOver = bMouseOver && bMouseChildren;		// if bMouseChildren is false from previous display object, then turn off mouse over.
		
		intObj->mouseOverDirty = bMouseOver;
		
		if( bMouseChildren )						// if still true, check if mouseChildren has changed to false.
		{
			if( canHaveChildren( intObj ) )
			{
				ofxFlashDisplayObjectContainer* objCont;
				objCont = (ofxFlashDisplayObjectContainer*)intObj;
				
				bMouseChildren = bMouseChildren && objCont->mouseChildren();
			}
		}
	}
	
	//=========================================== CHECK MOUSE DOWN.
	
	// this part checks if there have been any changes in the over / active states in any of the objects from current and previous frame.
	// if so, the mouse or finger while being pressed down has moved and has gone outside a valid region.
	// this means that mouse or touch is no longer down and bMouseDown is set to false.
	// the only one exception is when bMousePressed is true as we know that the mouse or touch has been pressed on the current frame.
	// and therefore guarantees that it is valid, until the next frame where we check if it has moved.
	
	if( !bMousePressed )		// mouse if pressed on current frame. no need to check if states are valid and as we know they are.
	{
		if( bMouseDown )		// if any of the states change in the line while the mouse is down, turn mouse down off.
		{
			for( int i=0; i<lineTopDown.size(); i++ )		// go down through child / parent nesting until stage is reached.
			{
				intObj = lineTopDown[ i ];
				
				if( intObj->mouseOver() != intObj->mouseOverDirty )		// check for a state change. if true, mouse is no longer down.
				{
					bMouseDown = false;
					break;
				}
			}
		}
		
		if( bMouseDown )		// if any of the states change in the line while the mouse is down, turn mouse down off.
		{
			for( int i=0; i<lineTopDownPrev.size(); i++ )		// go down through child / parent nesting until stage is reached.
			{
				intObj = lineTopDownPrev[ i ];
				
				if( intObj->mouseOver() != intObj->mouseOverDirty )		// check for a state change. if true, mouse is no longer down.
				{
					bMouseDown = false;
					break;
				}
			}
		}
	}
	
	//=========================================== FINALISE MOUSE VALUES.

	for( int i=0; i<lineTopDown.size(); i++ )					// go down through child / parent nesting until stage is reached.
	{
		intObj = lineTopDown[ i ];
		
		intObj->mouseOver( intObj->mouseOverDirty );
		intObj->mouseDown( intObj->mouseOverDirty && bMouseDown );
	}
	
	if( !topMostHitDisplayObjectPrev )
		return;
	
	for( int i=0; i<lineTopDownPrev.size(); i++ )				// go down through child / parent nesting until stage is reached.
	{
		intObj = lineTopDownPrev[ i ];
		
		intObj->mouseOver( intObj->mouseOverDirty );
		intObj->mouseDown( intObj->mouseOverDirty && bMouseDown );
	}
}

void ofxFlashStage :: updateChildrenTwo ( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children )
{
	for( int i=0; i<children.size(); i++ )
	{
		ofxFlashDisplayObject* child;
		child = children[ i ];

		if( !child->visible() )		// if set to invisible, ignore it and all it's children.
			continue;
		
		if( canHaveChildren( child ) )
		{
			ofxFlashDisplayObjectContainer* container;
			container = (ofxFlashDisplayObjectContainer*)child;
			
			if( container->children.size() > 0 )
			{
				updateChildrenTwo( child, container->children );
			}
		}

		child->update();	// last thing we do is call the update method for each child.
	}
}

/////////////////////////////////////////////
//	DRAW CHILDREN.
/////////////////////////////////////////////

void ofxFlashStage :: drawChildren ( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children )
{
	for( int i=0; i<children.size(); i++ )
	{
		ofxFlashDisplayObject* child;
		child = children[ i ];
		
		if( !child->visible() )		// if set to invisible, ignore it and all it's children.
			continue;
		
		//-- matrix transform.
		
		bool bIdentity = true;
		bIdentity = child->matrix().isIdentity();
		bIdentity = false;
		
		if( !bIdentity )		// matrix is not an identity matrix.
		{						// transform using openGL.
			glPushMatrix();
			glMultMatrixf( child->matrix().getPtr() );
		}
		
		child->drawOnFrame();
		child->draw();

		if( canHaveChildren( child ) )
		{
			ofxFlashDisplayObjectContainer* container;
			container = (ofxFlashDisplayObjectContainer*)child;
			
			if( container->children.size() > 0 )
			{
				drawChildren( child, container->children );
			}
		}
		
		if( !bIdentity )
		{
			glPopMatrix();
		}
	}
}

void ofxFlashStage :: drawChildrenDebug ( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children )
{
	for( int i=0; i<children.size(); i++ )
	{
		ofxFlashDisplayObject* child;
		child = children[ i ];
		
		if( !child->visible() )		// if set to invisible, ignore it and all it's children.
			continue;
		
		child->drawTransformedOutline();
		child->drawPixelBounds();
		
		if( canHaveChildren( child ) )
		{
			ofxFlashDisplayObjectContainer* container;
			container = (ofxFlashDisplayObjectContainer*)child;
			
			if( container->children.size() > 0 )
			{
				drawChildrenDebug( child, container->children );
			}
		}
	}
}

/////////////////////////////////////////////
//	CAN HAVE CHILDREN CHECK.
/////////////////////////////////////////////

bool ofxFlashStage :: canHaveChildren ( ofxFlashDisplayObject* displayObject )
{
	bool bCanHaveChildren;
	bCanHaveChildren = false;
	bCanHaveChildren = bCanHaveChildren || ( displayObject->typeID == OFX_FLASH_TYPE_DISPLAY_OBJECT_CONTAINER );
	bCanHaveChildren = bCanHaveChildren || ( displayObject->typeID == OFX_FLASH_TYPE_SPRITE );
	bCanHaveChildren = bCanHaveChildren || ( displayObject->typeID == OFX_FLASH_TYPE_MOVIECLIP );

	return bCanHaveChildren;
}

bool ofxFlashStage :: isInteractiveObject ( ofxFlashDisplayObject* displayObject )
{
	bool bIsInteractiveObject;
	bIsInteractiveObject = false;
	bIsInteractiveObject = bIsInteractiveObject || ( displayObject->typeID == OFX_FLASH_TYPE_DISPLAY_OBJECT_CONTAINER );	// not sure this one needs to be here.
	bIsInteractiveObject = bIsInteractiveObject || ( displayObject->typeID == OFX_FLASH_TYPE_SPRITE );
	bIsInteractiveObject = bIsInteractiveObject || ( displayObject->typeID == OFX_FLASH_TYPE_MOVIECLIP );

	return bIsInteractiveObject;
}

/////////////////////////////////////////////
//	MOUSE CHANGE LISTENERS.
/////////////////////////////////////////////

void ofxFlashStage :: mouseMoved ( int x, int y, int id )
{
	if( mouseID != id )
		return;
	
	_stageMouseX = x;
	_stageMouseY = y;
}

void ofxFlashStage :: mouseDragged ( int x, int y, int id )
{
	if( mouseID != id )
		return;
	
	_stageMouseX = x;
	_stageMouseY = y;
}

void ofxFlashStage :: mousePressed ( int x, int y, int id )
{
	_stageMouseX = x;
	_stageMouseY = y;
	
	bMouseDown		= true;
	bMousePressed	= true;		// this gets reset on every update loop. flag that mouse state has changed.
	
	bMouseChanged	= ( mouseID != id );
	if( bMouseChanged )
	{
		mouseID = id;
	}
}

void ofxFlashStage :: mouseReleased ( int x, int y, int id )
{
	if( mouseID != id )
		return;
	
	_stageMouseX = x;
	_stageMouseY = y;
	
	bMouseDown		= false;
	bMouseReleased	= true;		// this gets reset on every update loop. flag that mouse state has changed.
}
