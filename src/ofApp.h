/*
 * Copyright (c) 2020 Owen Osborn, Critter & Gutiari, Inc.
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
 */
#pragma once

#include "ofMain.h"
#include "ofxLua.h"
#include "ofxOsc.h"

#define PORT 4000





class ofApp : public ofBaseApp, ofxLuaListener {

    public:
	
	
	// main
        void setup();
        void update();
        void draw();
        void exit();
        
        // input
        void 	keyPressed(int key);
        void 	mouseMoved(int x, int y);
        void 	mouseDragged(int x, int y, int button);
        void 	mousePressed(int x, int y, int button);
        void 	mouseReleased(int x, int y, int button);
	int 	getCurrentSel();
	string	nameSel( int select );
        
        // ofxLua error callback
        void errorReceived(std::string& msg);
        
      	ofxLua 		lua;
               
        // osc control
        ofxOscReceiver 	receiver;
	ofxOscSender 	sender;
	ofxOscMessage 	mess;
	bool		up;
	bool		down;
	bool		saved;
	bool		osdTrig;
	int		selection;
	int		finalSel;

	// font
	ofTrueTypeFont	font;
	

};


