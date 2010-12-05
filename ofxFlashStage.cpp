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
	typeID = OFX_FLASH_STAGE_TYPE;
	
	_root = new ofxFlashMovieClip();
	_root->name( "root1" );
	this->addChild( _root );
	
	_stageMouseX = 0;
	_stageMouseY = 0;
	
	topMostHitDisplayObject		= NULL;
	topMostHitDisplayObjectPrev	= NULL;
	
	bUsingListeners		= false;
	bMouseDown			= false;
	bMousePressed		= false;
	bMouseReleased		= false;
	
	showRedrawRegions( false );
	
	ofAddListener( ofEvents.mouseMoved,		this, &ofxFlashStage::mouseMoved	);		//-- add mouse event handlers.
	ofAddListener( ofEvents.mouseDragged,	this, &ofxFlashStage::mouseDragged	);
	ofAddListener( ofEvents.mousePressed,	this, &ofxFlashStage::mousePressed	);
	ofAddListener( ofEvents.mouseReleased,	this, &ofxFlashStage::mouseReleased	);
}

ofxFlashStage :: ~ofxFlashStage ()
{
	ofRemoveListener( ofEvents.mouseMoved,		this, &ofxFlashStage::mouseMoved	);	//-- remove mouse event handlers.
	ofRemoveListener( ofEvents.mouseDragged,	this, &ofxFlashStage::mouseDragged	);
	ofRemoveListener( ofEvents.mousePressed,	this, &ofxFlashStage::mousePressed	);
	ofRemoveListener( ofEvents.mouseReleased,	this, &ofxFlashStage::mouseReleased	);
}

/////////////////////////////////////////////
//	LISTENERS.
/////////////////////////////////////////////

void ofxFlashStage :: addListeners ()
{
	if( bUsingListeners )
		return;
	
	bUsingListeners = true;
	
	ofAddListener( ofEvents.update,		this, &ofxFlashStage::update	);
	ofAddListener( ofEvents.draw,		this, &ofxFlashStage::draw		);
}

void ofxFlashStage :: removeListeners ()
{
	if( !bUsingListeners )
		return;
	
	bUsingListeners = false;
	
	ofRemoveListener( ofEvents.update,	this, &ofxFlashStage::update	);
	ofRemoveListener( ofEvents.draw,	this, &ofxFlashStage::draw		);
}

/////////////////////////////////////////////
//	
/////////////////////////////////////////////

void ofxFlashStage :: showRedrawRegions ( bool value )
{
	bShowRedrawRegions = value;
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
}

void ofxFlashStage :: draw ()
{
	drawChildren( this, children );
	
	if( bShowRedrawRegions )
	{
		drawChildrenDebug( this, children );
	}
}

/////////////////////////////////////////////
//	EVENT HANDLERS.
/////////////////////////////////////////////

void ofxFlashStage :: update ( ofEventArgs &e )
{
	update();
}

void ofxFlashStage :: draw ( ofEventArgs &e )
{
	draw();
}

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
	
	if( !bHitDisplayObjectChanged && !bMousePressed && !bMouseReleased )	// update if either of these is true, otherwise return.
	{
		return;
	}
	
//	cout << ofGetFrameNum() << endl;		// debug - check when this method gets to this point by spitting out the frame num.

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
					lineBottomUp.insert ( lineBottomUp.begin(), intObj );
				}
				
				dispObj	= dispObj->parent;
			}
		}
	}
	
	//=========================================== RESET PREVIOUS MOUSE STATES.
	
	if( topMostHitDisplayObjectPrev )		// clear mouse states from previous line of display objects.
	{
		for( int i=0; i<lineTopDownPrev.size(); i++ )			// go down through child / parent nesting until stage is reached.
		{
			intObj = lineTopDownPrev[ i ];

			if( topMostHitDisplayObject )
			{
				intObj->mouseOverDirty = false;		// reset mouse over, dirty value used for further checks.
				intObj->mouseDownDirty = false;		// reset mouse down, dirty value used for further checks.
			}
			else
			{
				intObj->mouseOver( false );			// reset mouse over.
				intObj->mouseDown( false );			// reset mouse down.
			}
		}
	}
	
	if( !topMostHitDisplayObject )		// check if anything is hit, return if not.
	{
		bMouseDown = false;				// if topMostHitDisplayObject is not found, mouse is not over anything and so mouse down is no longer valid.
		return;							// no display object registered under mouse, nothing to update.
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
	bCanHaveChildren = bCanHaveChildren || ( displayObject->typeID == OFX_FLASH_DISPLAY_OBJECT_CONTAINER_TYPE );
	bCanHaveChildren = bCanHaveChildren || ( displayObject->typeID == OFX_FLASH_SPRITE_TYPE );
	bCanHaveChildren = bCanHaveChildren || ( displayObject->typeID == OFX_FLASH_MOVIE_CLIP_TYPE );

	return bCanHaveChildren;
}

bool ofxFlashStage :: isInteractiveObject ( ofxFlashDisplayObject* displayObject )
{
	bool bIsInteractiveObject;
	bIsInteractiveObject = false;
	bIsInteractiveObject = bIsInteractiveObject || ( displayObject->typeID == OFX_FLASH_DISPLAY_OBJECT_CONTAINER_TYPE );	// not sure this one needs to be here.
	bIsInteractiveObject = bIsInteractiveObject || ( displayObject->typeID == OFX_FLASH_SPRITE_TYPE );
	bIsInteractiveObject = bIsInteractiveObject || ( displayObject->typeID == OFX_FLASH_MOVIE_CLIP_TYPE );

	return bIsInteractiveObject;
}

/////////////////////////////////////////////
//	MOUSE CHANGE LISTENERS.
/////////////////////////////////////////////

void ofxFlashStage :: mouseMoved ( ofMouseEventArgs& e )
{
	_stageMouseX = e.x;
	_stageMouseY = e.y;
}

void ofxFlashStage :: mouseDragged ( ofMouseEventArgs& e )
{
	_stageMouseX = e.x;
	_stageMouseY = e.y;
}

void ofxFlashStage :: mousePressed ( ofMouseEventArgs& e )
{
	bMouseDown		= true;
	bMousePressed	= true;
}

void ofxFlashStage :: mouseReleased ( ofMouseEventArgs& e )
{
	bMouseDown		= false;
	bMouseReleased	= true;
}
