/*
 *  ofxFlashDisplayObjectContainer.cpp
 *  emptyExample
 *
 *  Created by lukasz karluk on 1/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxFlashDisplayObjectContainer.h"

ofxFlashDisplayObjectContainer :: ofxFlashDisplayObjectContainer()
{
	typeID				= OFX_FLASH_DISPLAY_OBJECT_CONTAINER_TYPE;
	
	_mouseChildren		= true;
	_tabChildren		= false;
	_numChildren		= 0;
}

ofxFlashDisplayObjectContainer :: ~ofxFlashDisplayObjectContainer()
{

}

///////////////////////////////////////////////
//	GETTER / SETTERS.
///////////////////////////////////////////////

//============================================================= MOUSE CHILDREN.

const bool& ofxFlashDisplayObjectContainer :: mouseChildren ()
{
	return _mouseChildren;
}

void ofxFlashDisplayObjectContainer :: mouseChildren ( bool value )
{
	_mouseChildren = value;
}

//============================================================= TAB CHILDREN.

const bool&	ofxFlashDisplayObjectContainer :: tabChildren ()
{
	return _tabChildren;
}

void ofxFlashDisplayObjectContainer :: tabChildren ( bool value )
{
	_tabChildren = value;
}

//============================================================= NUMBER OF CHILDREN.

const int& ofxFlashDisplayObjectContainer :: numChildren ()
{
	return _numChildren;
}

///////////////////////////////////////////////
//	DISPLAY OBJECT CONTAINER METHODS.
///////////////////////////////////////////////

ofxFlashDisplayObject* ofxFlashDisplayObjectContainer :: addChild ( ofxFlashDisplayObject* child )
{
	children.push_back( child );
	child->stage	= this->stage;
	child->parent	= this;
	child->level( this->level() + 1 );
}

ofxFlashDisplayObject* ofxFlashDisplayObjectContainer :: addChildAt ( ofxFlashDisplayObject* child, int index )
{
	if( index < 0 || index > children.size() - 1 )
		return NULL;
	
	children.insert( children.begin() + index, child );
	child->stage	= this->stage;
	child->parent	= this;
	child->level( this->level() + 1 );
}

bool ofxFlashDisplayObjectContainer :: contains ( ofxFlashDisplayObject* child )
{
	for( int i=0; i<children.size(); i++ )
	{
		if( children[ i ] == child )
		{
			return true;
		}
	}
	
	return false;
}

ofxFlashDisplayObject* ofxFlashDisplayObjectContainer :: getChildAt ( int index )
{
	if( index < 0 || index > children.size() - 1 )
		return NULL;
	
	return children[ index ];
}

ofxFlashDisplayObject* ofxFlashDisplayObjectContainer :: getChildByName ( string name )
{
	for( int i=0; i<children.size(); i++ )
	{
		if( children[ i ]->name() == name )
		{
			return children[ i ];
		}
	}
	
	return NULL;
}

int ofxFlashDisplayObjectContainer :: getChildIndex ( ofxFlashDisplayObject* child )
{
	for( int i=0; i<children.size(); i++ )
	{
		if( children[ i ] == child )
		{
			return i;
		}
	}
	
	return -1;
}

vector<ofxFlashDisplayObject*> ofxFlashDisplayObjectContainer :: getObjectsUnderPoint ( ofPoint point )
{
	//
}

ofxFlashDisplayObject* ofxFlashDisplayObjectContainer :: removeChild ( ofxFlashDisplayObject* child )
{
	for( int i=0; i<children.size(); i++ )
	{
		if( children[ i ] == child )
		{
			child->stage	= NULL;
			child->parent	= NULL;
			child->level( -1 );
			
			children.erase( children.begin() + i );
			
			return child;
		}
	}
	
	return child;
}

ofxFlashDisplayObject* ofxFlashDisplayObjectContainer :: removeChildAt ( int index )
{
	if( index < 0 || index > children.size() - 1 )
		return NULL;
	
	ofxFlashDisplayObject* child;
	child = children[ index ];
	child->stage	= NULL;
	child->parent	= NULL;
	child->level( -1 );
	
	children.erase( children.begin() + index );
	
	return child;
}

void ofxFlashDisplayObjectContainer :: setChildIndex ( ofxFlashDisplayObject* child, int index )
{
	if( index < 0 || index > children.size() - 1 )
		return;
	
	for( int i=0; i<children.size(); i++ )
	{
		if( children[ i ] == child )
		{
			children.erase( children.begin() + i );
			children.insert( children.begin() + index, child );
			
			return;
		}
	}
}

void ofxFlashDisplayObjectContainer :: swapChildren ( ofxFlashDisplayObject* child1, ofxFlashDisplayObject* child2 )
{
	int index1 = getChildIndex( child1 );
	int index2 = getChildIndex( child2 );
	
	if( index1 == -1 || index2 == -1 )
		return;
	
	for( int i=0; i<children.size(); i++ )
	{
		if( children[ i ] == child1 || children[ i ] == child2 )
		{
			children.erase( children.begin() + i-- );
		}
	}
	
	if( index1 < index2 )
	{
		children.insert( children.begin() + index1, child2 );
		children.insert( children.begin() + index2, child1 );
	}
	else
	{
		children.insert( children.begin() + index2, child1 );
		children.insert( children.begin() + index1, child2 );
	}
}

void ofxFlashDisplayObjectContainer :: swapChildrenAt ( int index1, int index2 )
{
	if( index1 == index2 )
		return;
	
	ofxFlashDisplayObject* child1 = getChildAt( index1 );
	ofxFlashDisplayObject* child2 = getChildAt( index2 );
	
	if( child1 == NULL || child2 == NULL )
		return;
	
	if( index2 > index1 )
	{
		children.erase( children.begin() + index2 );
		children.erase( children.begin() + index1 );
	}
	else
	{
		children.erase( children.begin() + index1 );
		children.erase( children.begin() + index2 );
	}
	
	if( index1 < index2 )
	{
		children.insert( children.begin() + index1, child2 );
		children.insert( children.begin() + index2, child1 );
	}
	else
	{
		children.insert( children.begin() + index2, child1 );
		children.insert( children.begin() + index1, child2 );
	}
}
