/*
 * Copyright (c) 2020 Owen Osborn, Critter & Gutiari, Inc.
 *
 * BSD Simplified License.
 * For information on usage and redistribution, and for a DISCLAIMER OF ALL
 * WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 *
*/

#include "ofApp.h"
#include <stddef.h>
#include <stdint.h>
#include <string>

float 		h; 
float 		w; 

ofImage		img;

bool		confirmPage;
int		currentSel;

//--------------------------------------------------------------
void ofApp::setup() {
    
    // declare the OS version
    string 	Version = "oFLua 1.0";
    
    // declare screen size
    w = ofGetScreenWidth();
    h = ofGetScreenHeight(); 
   
    // listen on the given port
    cout << "listening for osc messages on port " << PORT << "\n";
    receiver.setup(PORT);  
    sender.setup("localhost", PORT+1);  
    
    ofSetVerticalSync(true);
    
    ofSetLogLevel("ofxLua", OF_LOG_VERBOSE);
    
    // hide the cursor
    ofHideCursor();

        
    // init the lua state
    lua.init( true ); // true because we want to stop on an error
    
    // listen to error events
    lua.addListener(this);
    
        
    // call the script's setup() function
    lua.scriptSetup();

    // load font
    font.load("CGFont_0.18.otf", 74, true, false, false, 1, 24);

    // load image
    img.load("images/eyesy-engine.png");

    // clear main screen
    ofClear(0,0,0);

    // init selection
    selection = 0;
    finalSel = 0;
    
    currentSel = getCurrentSel();
}

//--------------------------------------------------------------
void ofApp::update() {
    
    saved = false;
    up = false;
    down = false;
    osdTrig = false;

    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
	
	// get various key messages
        if(m.getAddress() == "/key") {   
            	//cout << m.getArgAsInt32(0) << "\n";
		// grab screen
            	if (m.getArgAsInt32(0) == 8 && m.getArgAsInt32(1) > 0) {
            		saved = true; 	
		}
	    	
		// scene up
	   	if (m.getArgAsInt32(0) == 50 && m.getArgAsInt32(1) > 0) {
			up = true;
		}
	    	
		// scene down
       	    	if (m.getArgAsInt32(0) == 49 && m.getArgAsInt32(1) > 0) {
			down = true;
		}

		// osd toggle
       	    	if (m.getArgAsInt32(0) == 1 && m.getArgAsInt32(1) > 0) {
			osdTrig = true;
		}

	    	
	}	

	////// the knobs
        if(m.getAddress() == "/knob1") {
		//knob1Local = m.getArgAsInt32(0);
		
	}
	if(m.getAddress() == "/knob2") {
		
	}
	if(m.getAddress() == "/knob3") {
		
	}
	if(m.getAddress() == "/knob4") {
		
	}	
	if(m.getAddress() == "/knob5") {
		
	}
    } // end of receiving messages from pure data
   
} // end of update function

//--------------------------------------------------------------
void ofApp::draw() {
	
	string currentRez = nameSel( currentSel );
	
	string 	intro1 = "Hi - please select the Video Engine and Resolution.";
	string 	intro2 = "Use 'Scene Select' buttons to navigate to your choice.";
	string	which = "Your Current Video Engine and Resolution is: " + currentRez;
	string	intro3 = "When finished, press 'Scene Save' button, the EYSEY will ask for confirmation than reboot";
	string	happy = "Happy video time!";

	if( up ) { 
		if( selection >= 5 ) {
			selection = 0;
		} else {
			selection++;
		}	
	}
	if( down ) { 
		if( selection <= 0 ) {
			selection = 5;
		} else {
			selection--;
		}	
	}
	
	if( saved ) {
		finalSel = selection;
	}
	
	// draw the graphics
	int space = font.stringHeight( intro1 );
	ofSetBackgroundColor(0,191,230);
	// draw the background rectangles
	ofPushMatrix();
		// main rect	
		ofSetColor(0,115,230);
		//ofSetColor(0);
		ofFill();
		ofTranslate(w/6, h/6);
		ofDrawRectangle( 0, 0, (w/3)*2, (h/3)*2 );
		// small top pink
		ofTranslate(w/6, h/6);
		ofSetColor(230, 152, 210);
		ofDrawRectangle( 0, 0, w/3, h/6);
		// small bottom green
		ofTranslate(0, h/6);
		ofSetColor(45, 200, 130);
		ofDrawRectangle( 0, 0, w/3, h/6);
	ofPopMatrix();
	
	// draw the text
	ofPushMatrix();	
		ofSetColor(255);
		ofTranslate( w/6, h/6 );
		ofTranslate( space, space);
		font.drawString( intro1, 0, 0);
        	ofTranslate( 0, h/18 );
		font.drawString( which, 0, 0);
		ofTranslate( 0, h/18 );
		font.drawString( intro2, 0, 0);
	ofPopMatrix();
	ofPushMatrix();	
		ofTranslate( (w/6)+space, h - (h/6) );
		font.drawString( intro3, 0, -(space*4));
	ofPopMatrix();
	ofPushMatrix();	
		ofTranslate( w/2, h - (h/6) );
		font.drawString( happy, -(font.stringWidth(happy)/2 ), -(space) );
	ofPopMatrix();
	/*
	// draw the image
	ofPushMatrix();
		ofTranslate( w/2, h/6);
		ofTranslate( space*8, space);
		ofSetColor(255);
		ofScale( 0.5, 0.5);		
		img.draw(0,0);
	ofPopMatrix();
	*/

	/*	
	// draw selection highlite
	ofPushMatrix();
		ofTranslate( w/2, h/3 );
		ofSetColor(200,200,0);
		ofFill();
		int highlite1 = finalSel * (h/9);
        	ofDrawRectangle(0, highlite1, w/4, h/9);
	ofPopMatrix();
	*/

	// draw texts
	ofPushMatrix();
		// draw openframeworks title
		ofTranslate( w/2, (h/3)+(h/12) );
		ofTranslate( -space, 0);
		string titleOF = "openFrameworks";
		ofSetColor(0);
		font.drawString( titleOF, -font.stringWidth( titleOF ), font.stringHeight( titleOF) / 2);
		
		//// draw the 3 rez
		ofTranslate( (w/12)+space, -(h/12) );
		ofTranslate( 0, space+(space/2));
		font.drawString("1080p", -(font.stringWidth("1080p")/2), 0 );
		ofTranslate( 0, h/18);
		font.drawString( "720p", -(font.stringWidth("720p")/2), 0 );
		ofTranslate( 0, h/18);
		font.drawString( "480p", -(font.stringWidth("480p")/2), 0 );
	ofPopMatrix();
	
	ofPushMatrix();
		// draw python title
		ofTranslate( w/2, ((h/3)+(h/6)) + (h/12) );
		ofTranslate( -space, 0 );
		string titlePY = "Pygame";
		ofSetColor(0);
		font.drawString( titlePY, -font.stringWidth( titlePY ), font.stringHeight( titlePY) / 2 );
		
		//// draw the 3 rez
		ofTranslate( (w/12)+space, -(h/12) );
		ofTranslate( 0, space+(space/2));
		font.drawString("1080p(Slow)", -(font.stringWidth("1080p(Slow)")/2), 0 );
		ofTranslate( 0, h/18);
		font.drawString( "720p", -(font.stringWidth("720p")/2), 0 );
		ofTranslate( 0, h/18);
		font.drawString( "480p", -(font.stringWidth("480p")/2), 0 );
	ofPopMatrix();
	
	// display selection box
	ofPushMatrix();
		ofTranslate( w/2, h/3 );
		ofNoFill();
		int highlite = selection * (h/18);
        	ofDrawRectangle(0, highlite, w/6, h/18);
		ofDrawRectangle(1, highlite+1, (w/6)-2, (h/18)-2 );
	ofPopMatrix();
	
	// display window for confirmation
	if( saved == true && confirmPage == false ) {
		confirmPage = true;
	}
	
	// draw confirmation page
	if( confirmPage == true ) {
		string		selString;
		selString = nameSel( selection);
		
		ofPushMatrix();
			ofTranslate(w/3, h/3);
			ofFill();
			ofSetColor(0);
			ofDrawRectangle( h/128, h/128, w/3, h/3);
			ofSetColor(255);
			ofDrawRectangle( 0, 0, w/3, h/3);
			ofSetColor(0);
			font.drawString("Press The OSD Button to Reboot your EYESY", space, space*2);
			font.drawString("with your selection:", space, space*4);
			font.drawString( selString, (w/6)-(font.stringWidth(selString)/2), space*10);
		ofPopMatrix();	
	}

	// turn off confirmation page if any of the scene buttons are pressed
	if( confirmPage == true && (up == true || down == true ) ) {
		confirmPage = false;
	}
	
	// rewrite config.txt and reboot
	if( confirmPage == true && osdTrig == true ) {
		cout << "it is rebooting and stuff" << "\n";
	}
}

//--------------------------------------------------------------
void ofApp::exit() {
	lua.clear();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    /*
    switch(key) {
    
        case 'r':
            reloadScript();
            break;
    
        case OF_KEY_LEFT:
            prevScript();
            break;
            
        case OF_KEY_RIGHT:
            nextScript();
            break;
            
        case ' ':
            lua.doString("print(\"this is a lua string saying you hit the space bar!\")");
            cout << "fps: " << ofGetFrameRate() << "\n";    
            break;
    }
    
    lua.scriptKeyPressed(key);
    */
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
    //lua.scriptMouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
    //lua.scriptMouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
   // lua.scriptMousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
//    lua.scriptMouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::errorReceived(std::string& msg) {
    ofLogNotice() << "got a script error: " << msg;
}

//--------------------------------------------------------------
int ofApp::getCurrentSel() {
    return 0;
}

string ofApp::nameSel( int select ) {
	string	sel;
	if ( select == 0 ) {
		sel = "openFrameworks: 1080p";
	} else if (select == 1) {
		sel = "openFrameworks: 720p";
	} else if (select == 2) {
		sel = "openFrameworks: 480p";
	} else if (select == 3) {
		sel = "Pygame: 1080p (Slow)";
	} else if (select == 4) {
		sel = "Pygame: 720p";
	} else if( select == 5) {
		sel = "Pygame: 480p";
	}
	return sel;
}

//--------------------------------------------------------------
