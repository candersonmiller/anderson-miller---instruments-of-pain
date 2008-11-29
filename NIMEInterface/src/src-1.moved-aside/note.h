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
	
	note();
	note(float xstart, float ystart);
	void draw();
	void move(float xmove, float ymove);
private:
	float X;
	float Y;
	float size;
	
};

#endif
