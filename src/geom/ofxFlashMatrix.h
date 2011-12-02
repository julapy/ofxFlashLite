/*
 *  ofxFlashMatrix.h
 *  emptyExample
 *
 *  Created by Lukasz Karluk on 11/11/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 *	Original code ported from Gnash :: SWFMatrix
 *	http://www.gnu.org/software/gnash/
 *
 */

#pragma once

#include "ofMain.h"
#include "ofMatrix4x4.h"

class ofxFlashMatrix : public ofMatrix4x4
{

public:
	
	ofxFlashMatrix()
	{
		set( 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 );		// identity.
	}

	ofxFlashMatrix( float a, float b, float c, float d, float tx, float ty )
	{
		set( a, b, c, d, tx, ty );
	}
	
	~ofxFlashMatrix()
	{
		//
	}
	
	//===============================================
	//
	//   http://help.adobe.com/en_US/FlashPlatform/reference/actionscript/3/flash/geom/Matrix.html
	//
	//	[  a   c   tx  ]		flash matrix
	//	[  b   d   ty  ]
	//	[  0   0   1   ]
	//
	//
	//	[  a   b   0   0  ]		ofxFlash 4x4 matrix.
	//	[  c   d   0   0  ]
	//	[  0   0   0   0  ]
	//	[  tx  ty  0   0  ]
	//
	//===============================================
	
//	void set ( const ofxMatrix4x4& mat )
//	{
//		ofxMatrix4x4 :: set
//		(
//			mat._mat[ 0 ][ 0 ], mat._mat[ 0 ][ 1 ], mat._mat[ 0 ][ 2 ], mat._mat[ 0 ][ 3 ],
//			mat._mat[ 1 ][ 0 ], mat._mat[ 1 ][ 1 ], mat._mat[ 1 ][ 2 ], mat._mat[ 1 ][ 3 ],
//			mat._mat[ 2 ][ 0 ], mat._mat[ 2 ][ 1 ], mat._mat[ 2 ][ 2 ], mat._mat[ 2 ][ 3 ],
//			mat._mat[ 3 ][ 0 ], mat._mat[ 3 ][ 1 ], mat._mat[ 3 ][ 2 ], mat._mat[ 3 ][ 3 ]
//		);
//	}
    
    void set ( const ofxFlashMatrix &matrix )
    {
        set( matrix.getA(), matrix.getB(), matrix.getC(), matrix.getD(), matrix.getTx(), matrix.getTy() );
    }
	
	void set ( float a, float b, float c, float d, float tx, float ty )
	{
		ofMatrix4x4 :: set
		(
			a,  b,  0,  0,
			c,  d,  0,  0,
			0,  0,  1,  0,
			tx, ty, 0,  1
		);
	}

	void setA	( float v ) { _mat[ 0 ][ 0 ] = v; }
	void setB	( float v ) { _mat[ 0 ][ 1 ] = v; }
	void setC	( float v ) { _mat[ 1 ][ 0 ] = v; }
	void setD	( float v ) { _mat[ 1 ][ 1 ] = v; }
	void setTx	( float v ) { _mat[ 3 ][ 0 ] = v; }
	void setTy	( float v ) { _mat[ 3 ][ 1 ] = v; }
	
	float getA	() const { return _mat[ 0 ][ 0 ]; }
	float getB	() const { return _mat[ 0 ][ 1 ]; }
	float getC	() const { return _mat[ 1 ][ 0 ]; }
	float getD	() const { return _mat[ 1 ][ 1 ]; }
	float getTx	() const { return _mat[ 3 ][ 0 ]; }
	float getTy	() const { return _mat[ 3 ][ 1 ]; }
    
    bool isEqual ( const ofxFlashMatrix &matrix )
    {
        if( getA()  != matrix.getA()  ) return false;
        if( getB()  != matrix.getB()  ) return false;
        if( getC()  != matrix.getC()  ) return false;
        if( getD()  != matrix.getD()  ) return false;
        if( getTx() != matrix.getTx() ) return false;
        if( getTy() != matrix.getTy() ) return false;
        
        return true;
    }
	
	//===============================================
	
	void transform ( ofPoint& p ) const
	{
		float sx;		// 'a'  in AS Matrix.
		float shx;		// 'b'  in AS Matrix.
		float shy;		// 'c'  in AS Matrix.
		float sy;		// 'd'  in AS Matrix.
		float tx;		// 'tx' in AS Matrix.
		float ty;		// 'ty' in AS Matrix.

		sx	= _mat[ 0 ][ 0 ];
		shx	= _mat[ 0 ][ 1 ];
		shy	= _mat[ 1 ][ 0 ];
		sy	= _mat[ 1 ][ 1 ];
		tx	= _mat[ 3 ][ 0 ];
		ty	= _mat[ 3 ][ 1 ];
		
		float t0 = ( sx  * p.x ) + ( shy * p.y ) + tx;
		float t1 = ( shx * p.x ) + ( sy  * p.y ) + ty;
		
		p.x = t0;
		p.y = t1;
	}
	
	//===============================================
	
	void concatenate ( const ofxFlashMatrix& m )
	{
		float a;
		float b;
		float c;
		float d;
		float tx;
		float ty;
		
		a	= ( this->getA() * m.getA()  ) + ( this->getC() * m.getB()  );
		b	= ( this->getB() * m.getA()  ) + ( this->getD() * m.getB()  );
		c	= ( this->getA() * m.getC()  ) + ( this->getC() * m.getD()  );
		d	= ( this->getB() * m.getC()  ) + ( this->getD() * m.getD()  );
		tx	= ( this->getA() * m.getTx() ) + ( this->getC() * m.getTy() ) + this->getTx();
		ty	= ( this->getB() * m.getTx() ) + ( this->getD() * m.getTy() ) + this->getTy();
		
		set( a, b, c, d, tx, ty );
	}
	
//	void
//	SWFMatrix::concatenate_translation(int xoffset, int yoffset)
//	// Concatenate a translation onto the front of our
//	// SWFMatrix.  When transforming points, the translation
//	// happens first, then our original xform.
//	{
//		tx += Fixed16Mul(sx,  xoffset) + Fixed16Mul(shy, yoffset);
//		ty += Fixed16Mul(shx, xoffset) + Fixed16Mul(sy, yoffset);
//	}
//	
//	void
//	SWFMatrix::concatenate_scale(double xscale, double yscale)
//	// Concatenate scales to our SWFMatrix. When transforming points, these 
//	// scales happen first, then our matirx.
//	{
//		sx  = Fixed16Mul(sx, DoubleToFixed16(xscale));
//		shy = Fixed16Mul(shy,DoubleToFixed16(yscale));
//		shx = Fixed16Mul(shx,DoubleToFixed16(xscale));
//		sy  = Fixed16Mul(sy, DoubleToFixed16(yscale)); 
//	}
	
	//=============================================== INVERT.
	
	ofxFlashMatrix& invert ()
	{
		float det = determinant();
		
		if( det == 0 )
		{
			set( 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 );	// set identity.
			
			return *this;
		}
		
		const float d	= 1.0 / det;
		const float t0	= getD() * d;
		
		setD(  getA() * d );
		setC( -getC() * d );
		setB( -getB() * d );
		
		float t4 = -( ( getTx() * t0 ) + ( getTy() * getC() ) );
		setTy( -( ( getTx() * getB() ) + ( getTy() * getD() ) ) );
		
		setA( t0 );
		setTx( t4 );
		
		return *this;
	}
	
	float determinant() const
	{
		return getA() * getD() - getB() * getC();
	}
	
	//=============================================== SETTERS.
	
	void set_scale_rotation ( float x_scale, float y_scale, float angle )
	{
		const float cos_angle = cos( angle );
		const float sin_angle = sin( angle );
		
		setA( x_scale *  cos_angle );
		setB( x_scale *  sin_angle );
		setC( y_scale * -sin_angle );
		setD( y_scale *  cos_angle );
	}
	
	void set_x_scale ( float xscale )
	{
		const double rot_x = atan2( getB(), getA() );
		
		setA( xscale * cos( rot_x ) );
		setB( xscale * sin( rot_x ) );
	}
	
	void set_y_scale ( float yscale )
	{
		const float rot_y = atan2( -getC(), getD() );
		
		setC( yscale * sin( rot_y ) );
		setD( yscale * cos( rot_y ) );
	}
	
	void set_scale ( float xscale, float yscale )
	{
		const float rotation = get_rotation();
		set_scale_rotation( xscale, yscale, rotation ); 
	}
	
	void set_rotation ( float rotation )
	{   
		const float rot_x	= atan2(  getB(), getA() );
		const float rot_y	= atan2( -getC(), getD() );
		const float scale_x	= get_x_scale();
		const float scale_y	= get_y_scale();
		
		setA( scale_x * cos( rotation ) );
		setB( scale_x * sin( rotation ) );
		setC( scale_y * sin( rot_y - rot_x + rotation ) * -1 );		// reverse sign.
		setD( scale_y * cos( rot_y - rot_x + rotation ) );
	}
	
	//=============================================== GETTERS.
	
	float get_x_scale () const
	{
		float a	= getA();
		float b	= getB();
		float s = sqrt( ( a * a + b * b ) ) / 1.0;
		
		return s;
	}
	
	float get_y_scale () const
	{
		float c	= getC();
		float d	= getD();
		float s = sqrt( ( d * d + c * c ) ) / 1.0;
		
		return s;
	}
	
	float get_rotation () const
	{
		float a = getA();
		float b = getB();
		float r = atan2( b, a ); 
		
		return r;
	}
	
};