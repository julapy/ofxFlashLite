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
	_root->name = "root1";
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
	updateChildren( children );
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

void ofxFlashStage :: updateChildren ( vector<ofxFlashDisplayObject*>& children )
{
	for( int i=0; i<children.size(); i++ )
	{
		ofxFlashDisplayObject* child;
		child = children[ i ];
		
		child->globalX = child->parent->globalX + child->x;
		child->globalY = child->parent->globalY + child->y;
		child->globalZ = child->parent->globalZ + child->z;
		
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
				updateChildren( container->children );
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
		bIdentity = ( child->mat_a == 1.0 ) && bIdentity;
		bIdentity = ( child->mat_b == 0.0 ) && bIdentity;
		bIdentity = ( child->mat_c == 0.0 ) && bIdentity;
		bIdentity = ( child->mat_d == 1.0 ) && bIdentity;
		bIdentity = false;
		
		if( !bIdentity )		// matrix is not an identity matrix.
		{						// transform using openGL.
			glPushMatrix();
			
			float mat_a		= child->mat_a;
			float mat_b		= child->mat_b;
			float mat_c		= child->mat_c;
			float mat_d		= child->mat_d;
//			float mat_tx	= child->mat_tx;
//			float mat_ty	= child->mat_ty;
			float mat_tx	= child->x;
			float mat_ty	= child->y;
			
			float* mat = new float[ 16 ];
			mat[ 0 ]  = mat_a;		mat[ 1 ]  = mat_b;		mat[ 2 ]  = 0.0;		mat[ 3 ]  = 0.0;
			mat[ 4 ]  = mat_c;		mat[ 5 ]  = mat_d;		mat[ 6 ]  = 0.0;		mat[ 7 ]  = 0.0;
			mat[ 8 ]  = 0.0;		mat[ 9 ]  = 0.0;		mat[ 10 ] = 1.0;		mat[ 11 ] = 0.0;
			mat[ 12 ] = mat_tx;		mat[ 13 ] = mat_ty;		mat[ 14 ] = 0.0;		mat[ 15 ] = 1.0;
			
//			mat[ 0 ]  = 1.0;		mat[ 1 ]  = 0.0;		mat[ 2 ]  = 0.0;		mat[ 3 ]  = 0.0;
//			mat[ 4 ]  = 0.0;		mat[ 5 ]  = 1.0;		mat[ 6 ]  = 0.0;		mat[ 7 ]  = 0.0;
//			mat[ 8 ]  = 0.0;		mat[ 9 ]  = 0.0;		mat[ 10 ] = 1.0;		mat[ 11 ] = 0.0;
//			mat[ 12 ] = 0.0;		mat[ 13 ] = 0.0;		mat[ 14 ] = 0.0;		mat[ 15 ] = 1.0;
			
			glMultMatrixf( mat );
			
			delete[] mat;
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