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
	}
}