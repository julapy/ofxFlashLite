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
	ofxFlashMatrix worldMatrix;		// identity matrix.
	
	updateChildren( children, worldMatrix );
}

void ofxFlashStage :: draw ()
{
	drawChildren( children );
	
	if( bShowRedrawRegions )
	{
		drawChildrenDebug( children );
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

void ofxFlashStage :: updateChildren ( vector<ofxFlashDisplayObject*>& children, const ofxFlashMatrix& mat )
{
	for( int i=0; i<children.size(); i++ )
	{
		ofxFlashDisplayObject* child;
		child = children[ i ];
		
		ofxFlashMatrix worldMatrix;
		worldMatrix = mat;
		worldMatrix.concatenate( child->matrix() );
		
		child->transform( worldMatrix );
		
		child->update();
		
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
				updateChildren( container->children, worldMatrix );
			}
		}
	}
}

/////////////////////////////////////////////
//	DRAW CHILDREN.
/////////////////////////////////////////////

void ofxFlashStage :: drawChildren ( vector<ofxFlashDisplayObject*>& children )
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
				drawChildren( container->children );
			}
		}
		
		if( !bIdentity )
		{
			glPopMatrix();
		}
	}
}

void ofxFlashStage :: drawChildrenDebug ( vector<ofxFlashDisplayObject*>& children )
{
	for( int i=0; i<children.size(); i++ )
	{
		ofxFlashDisplayObject* child;
		child = children[ i ];
		
		child->drawTransformedOutline();
		child->drawBoundingBox();
		
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
				drawChildrenDebug( container->children );
			}
		}
	}
}