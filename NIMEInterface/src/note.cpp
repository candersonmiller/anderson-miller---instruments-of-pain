/*
 *  note.cpp
 *  openFrameworks
 *
 *  Created by C. Anderson Miller on 11/29/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "note.h"


note::note(float xstart, float ystart, char rgby){
	X = xstart;
	Y = ystart;
	size = 50;
	color = rgby;
	hit = false;
}


void note::draw(){
	glPushMatrix();
	
	glTranslatef(X, Y, 0);
	if(color == 'r'){
		//printf("!!!!!!!!!!!\n");
		glColor3f(0.7, 0.0,0);
		float mcolor[] = { 0.7f, 0.0f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
		glMaterialf(GL_FRONT, GL_AMBIENT, 0.8f);
		glMaterialf(GL_FRONT, GL_DIFFUSE, 1.0f);
		glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);
		glMaterialf(GL_FRONT, GL_SPECULAR, 1.0f);
		glMaterialf(GL_FRONT, GL_EMISSION, 0.2f);
	}else if(color == 'g'){
		glColor3f(0.0, 0.7,0);
		float mcolor[] = { 0.0f, 0.7f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
		glMaterialf(GL_FRONT, GL_AMBIENT, 0.8f);
		glMaterialf(GL_FRONT, GL_DIFFUSE, 1.0f);
		glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);
		glMaterialf(GL_FRONT, GL_SPECULAR, 1.0f);
		glMaterialf(GL_FRONT, GL_EMISSION, 0.2f);
	}else if(color == 'b'){
		glColor3f(0.0, 0.0,0.7);
		float mcolor[] = { 0.0f, 0.0f, 0.7f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
		glMaterialf(GL_FRONT, GL_AMBIENT, 0.8f);
		glMaterialf(GL_FRONT, GL_DIFFUSE, 1.0f);
		glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);
		glMaterialf(GL_FRONT, GL_SPECULAR, 1.0f);
		glMaterialf(GL_FRONT, GL_EMISSION, 0.2f);
	}else if(color == 'y'){
		glColor3f(0.9, 0.9,0.0);
		float mcolor[] = { 0.9f, 0.9f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
		glMaterialf(GL_FRONT, GL_AMBIENT, 0.8f);
		glMaterialf(GL_FRONT, GL_DIFFUSE, 1.0f);
		glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);
		glMaterialf(GL_FRONT, GL_SPECULAR, 1.0f);
		glMaterialf(GL_FRONT, GL_EMISSION, 0.2f);
	}else{
		glColor3f(1.0, 1.0, 1.0);
	}
	glutSolidSphere(size, 30, 30);
	glPopMatrix();
	
}


void note::move(float xmove, float ymove){
	X += xmove;
	Y += ymove;
}


void note::print(){
	printf("%f %f %s\n", X, Y, color);
}


bool note::target(float ytarget, char targetrgb){
	if( (Y + size) >= ytarget && (Y - size) <= ytarget && color == targetrgb && !hit ){
		hit = true;
		printf("!!!!!!!!!!!!!\n");
		return true;
	}else{
		return false;
	}
}

int note::isMissed(float ytarget){
	if(ytarget < (Y - size) && !hit){
		hit = true;
		if(color == 'r'){
			return 1;
		}
		if(color == 'g'){
			return 2;
		}
		if(color == 'b'){
			return 3;
		}
		if(color == 'y'){
			return 4;
		}
		
		return 0;
		
	}
		return 0;
}

void note::setSize(float sizeset){
	size = sizeset;	
}

