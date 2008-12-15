#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"

#define OF_ADDON_USING_OFXOSC

#include "ofAddons.h"

#include "note.h"
#include <iostream>
#include <fstream>
#include <vector>

#define HOST "localhost"
#define PORT 9001

//--------------------------------------------------------
class testApp : public ofSimpleApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased();
		
		ofTrueTypeFont		font;

	private:
		vector <int>duration;
		vector <int>timekey;
		vector <string>color;
		vector <note>pianoroll;
		int currTime;
		int iter;
		float speed;
		float targetline;
	
		int failtime;
		bool paused;
		bool recording;
		bool playing;
		bool redpressed;
		bool greenpressed;
		bool bluepressed;
		bool yellowpressed;
		ofxOscSender sender;
		ofSerial	serial;
			
		
		
};

#endif	
