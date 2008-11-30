/*
 *  note.h
 *  openFrameworks
 *
 *  Created by C. Anderson Miller on 11/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _NOTE
#define _NOTE


#include "ofMain.h"
#include "ofAddons.h"
using namespace std;

class note{
	
public:
	note(float xstart, float ystart, char rgby);
	void draw();
	void move(float xmove, float ymove);
	void print();
	bool target(float ytarget, char targetrgb);
	int isMissed(float ytarget);
	void setSize(float sizeset);
private:
	float X;
	float Y;
	float size;
	char color;
	bool hit;
	
};

#endif
