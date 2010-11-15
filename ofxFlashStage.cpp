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
	
	showRedrawRegions( false );
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
		
		ofxFlashMatrix worldMatrix;
		worldMatrix = parent->concatenatedMatrix();
		worldMatrix.concatenate( child->matrix() );
		
		child->transform( worldMatrix );
		
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