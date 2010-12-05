﻿package{	import flash.display.Sprite;	import flash.events.Event;	import flash.events.MouseEvent;	import flash.text.TextField;	import flash.text.TextFieldAutoSize;	public class Box extends Sprite	{		private var rotInc	: Number = 0;		public  var boxW	: int = 0;		public  var boxH	: int = 0;		public  var tf		: TextField;		public function Box( w : int, h : int  )		{//			rotInc	= Math.random() - 0.5;			rotInc	= 0;			boxW	= w;			boxH	= h;			drawOutState();			tf = new TextField();			tf.selectable	= false;			tf.mouseEnabled	= false;			tf.autoSize		= TextFieldAutoSize.LEFT;			addChild( tf );			addEventListener( MouseEvent.MOUSE_OVER,	drawOverState );			addEventListener( MouseEvent.MOUSE_OUT,		drawOutState  );			addEventListener( MouseEvent.MOUSE_DOWN,	drawDownState );			addEventListener( MouseEvent.MOUSE_UP,		drawOverState );			addEventListener( Event.ENTER_FRAME, update );		}		private function update ( e : * = null ):void		{			tf.text	 = "mouseEnabled  :: " + mouseEnabled + "\n";			tf.text += "mouseChildren :: " + mouseChildren;			tf.x	 = (int)( tf.width  * 0.5 ) * -1;			tf.y	 = (int)( tf.height * 0.5 ) * -1;			rotation += rotInc;		}		private function drawOutState ( e : * = null ):void		{			graphics.clear();			graphics.beginFill( 0x888888 );			graphics.drawRect( -boxW * 0.5, -boxH * 0.5, boxW, boxH );			graphics.endFill();			drawBorder();		}		private function drawOverState ( e : * = null ):void		{			graphics.clear();			graphics.beginFill( 0xFF00FF );			graphics.drawRect( -boxW * 0.5, -boxH * 0.5, boxW, boxH );			graphics.endFill();			drawBorder();		}		private function drawDownState ( e : * = null ):void		{			graphics.clear();			graphics.beginFill( 0x00FFFF );			graphics.drawRect( -boxW * 0.5, -boxH * 0.5, boxW, boxH );			graphics.endFill();			drawBorder();		}		private function drawBorder ():void		{			graphics.lineStyle( 1, 0x444444 );			graphics.drawRect( -boxW * 0.5, -boxH * 0.5, boxW, boxH );		}	}}