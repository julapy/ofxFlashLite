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
	
	showRedrawRegions( false );
	
	ofAddListener( ofEvents.mouseMoved,		this, &ofxFlashStage::mouseMoved	);
	ofAddListener( ofEvents.mouseDragged,	this, &ofxFlashStage::mouseDragged	);
}

ofxFlashStage :: ~ofxFlashStage ()
{
	//
}

/////////////////////////////////////////////
//	LISTENERS.
/////////////////////////////////////////////

void ofxFlashStage :: addListeners ()
{
	ofAddListener( ofEvents.update,		this, &ofxFlashStage::update	);
	ofAddListener( ofEvents.draw,		this, &ofxFlashStage::draw		);
}

void ofxFlashStage :: removeListeners ()
{
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
	updateChildren( this, children );
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

void ofxFlashStage :: updateChildren ( ofxFlashDisplayObject* parent, vector<ofxFlashDisplayObject*>& children )
{
	parent->resetPixelBounds();		// clear pixel bounds on every loop and recalculate.
	
	for( int i=0; i<children.size(); i++ )
	{
		ofxFlashDisplayObject* child;
		child = children[ i ];
		
		if( !child->visible() )		// if set to invisible, ignore it and all it's children.
			continue;
		
		ofxFlashMatrix worldMatrix;
		worldMatrix = parent->concatenatedMatrix();
		worldMatrix.concatenate( child->matrix() );
		
		child->transform( worldMatrix );
		
		bool bCanHaveChildren;
		bCanHaveChildren = false;
		bCanHaveChildren = bCanHaveChildren || ( child->typeID == OFX_FLASH_DISPLAY_OBJECT_CONTAINER_TYPE );
		bCanHaveChildren = bCanHaveChildren || ( child->typeID == OFX_FLASH_SPRITE_TYPE );
		bCanHaveChildren = bCanHaveChildren || ( child->typeID == OFX_FLASH_MOVIE_CLIP_TYPE );
		
		bool bIsInteractive;
		bIsInteractive   = bCanHaveChildren || ( child->typeID == OFX_FLASH_INTERACTIVE_OBJECT_TYPE );
		
		// two things we need to consider.
		// 1) mouseEnabled
		// 2) mouseChildren
		//
		// .... more on this later.
		
		if( bIsInteractive )
		{
			//
		}
		
		if( bCanHaveChildren )
		{
			ofxFlashDisplayObjectContainer* container;
			container = (ofxFlashDisplayObjectContainer*)child;
			
			if( container->children.size() > 0 )
			{
				updateChildren( child, container->children );
			}
		}
		
		parent->addToPixelBounds( child->pixelBounds() );	// compound pixel bounds from children.
		
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

		bool bCanHaveChildren;
		bCanHaveChildren = false;
		bCanHaveChildren = bCanHaveChildren || ( child->typeID == OFX_FLASH_DISPLAY_OBJECT_CONTAINER_TYPE );
		bCanHaveChildren = bCanHaveChildren || ( child->typeID == OFX_FLASH_SPRITE_TYPE );
		bCanHaveChildren = bCanHaveChildren || ( child->typeID == OFX_FLASH_MOVIE_CLIP_TYPE );
		
		if( bCanHaveChildren )
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
		
		bool bCanHaveChildren;
		bCanHaveChildren = false;
		bCanHaveChildren = bCanHaveChildren || ( child->typeID == OFX_FLASH_DISPLAY_OBJECT_CONTAINER_TYPE );
		bCanHaveChildren = bCanHaveChildren || ( child->typeID == OFX_FLASH_SPRITE_TYPE );
		bCanHaveChildren = bCanHaveChildren || ( child->typeID == OFX_FLASH_MOVIE_CLIP_TYPE );
		
		if( bCanHaveChildren )
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