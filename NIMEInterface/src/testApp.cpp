#include "testApp.h"

int GetIntVal(string strConvert) {
	int intReturn;
	
	// NOTE: You should probably do some checks to ensure that
	// this string contains only numbers. If the string is not
	// a valid integer, zero will be returned.
	intReturn = atoi(strConvert.c_str());
	
	return(intReturn);
}


void initrand()
{
    srand((unsigned)(time(0)));
}

float randfloat()
{
    return rand()/(float(RAND_MAX)+1);
} 

float randfloat(float max){
    return randfloat()*max;
} 


void drawLine(float targetline){
	glPushMatrix();
	glTranslatef(0,targetline,0);
	glColor3f(0.7, 0.7,0.7);
	float mcolor[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
	glMaterialf(GL_FRONT, GL_AMBIENT, 0.8f);
	glMaterialf(GL_FRONT, GL_DIFFUSE, 1.0f);
	glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);
	glMaterialf(GL_FRONT, GL_SPECULAR, 1.0f);
	glMaterialf(GL_FRONT, GL_EMISSION, 0.2f);
	glBegin(GL_QUADS);
	glVertex3f(0,0,0);
	glVertex3f(1440,0,0);
	glVertex3f(1440,10,0);
	glVertex3f(0,10,0);
	glEnd();
	glPopMatrix();	
	
}

void sendPlay(int channel, ofxOscSender sender, ofSerial serial){
	ofxOscMessage m;
	m.setAddress( "/play" );
	m.addIntArg( channel );
	sender.sendMessage( m );
}

void sendRec(int channel, ofxOscSender sender, ofSerial serial){
	ofxOscMessage m;
	m.setAddress( "/rec" );
	m.addIntArg( channel );
	sender.sendMessage( m );
	channel += 48;
	serial.setup("/dev/tty.usbserial-A70062Z4", 19200);
	serial.writeByte(channel);
}


//--------------------------------------------------------------
void testApp::setup(){
	string line;
	/* Using Full Path because I don't feel like debugging the file heirarchy */
	//time from last one
	// followed by color
	// followed by time to cross the screen
	
	ifstream myfile ("/Users/andersonmiller/Downloads/of_preRelease_v0.05_xcode_FAT/apps/addonsExamples/NIMEExampleWithOSC/data/sequence.txt");
	if(myfile.is_open()){
		while(!myfile.eof()){
			getline (myfile,line);
			timekey.push_back(GetIntVal(line.substr(0,4)));
			duration.push_back(GetIntVal(line.substr(7,4)));
			color.push_back(line.substr(5,1));
			cout << line << endl;
		}
		myfile.close();
	}else cout << "Unable to upen file" << endl;
	
	/* populating the pianoroll */
	float X = 400;
	float Y = 0;
	
	initrand();
	
	for(int i = 0; i < timekey.size(); i++){
		Y -= timekey[i];
		
		note temp = note(100 + randfloat(800), Y, color[i].at(0));
		temp.setSize(50 + randfloat(50));
		pianoroll.push_back(temp);
	}
	
	
	
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_COLOR_MATERIAL);
	GLfloat global_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	
	/* starting the currTime variable */
	currTime = ofGetElapsedTimeMillis();
	iter = 0;
	
	
	targetline = 700;
	recording = false;
	playing = false;
	redpressed = false;
	greenpressed = false;
	bluepressed = false;
	yellowpressed = false;
	paused = false;
	speed = 2.2;
	ofBackground( 0, 0, 0 );

	// open an outgoing connection to HOST:PORT
	sender.setup( HOST, PORT );
	serial.enumerateDevices();
	
	
	//----------------------------------- note:
	serial.setup("/dev/tty.usbserial-A70062Z4", 19200);		// < this should be set
}

//--------------------------------------------------------------
void testApp::update(){
	currTime = ofGetElapsedTimeMillis();
	if(!paused){
		for(int i = 0; i < pianoroll.size(); i++){
			pianoroll[i].move(0, speed);
		}
	}
}


//--------------------------------------------------------------
void testApp::draw(){
	//glMatrixMode(GL_PROJECTION);
	//gluPerspective(45.0, ofGetScreenWidth()/ofGetScreenHeight(), 10.0, -10.0);
	
	glPushMatrix();
	
	//glTranslated(500, 400, -200);
	GLfloat ambient[] = { 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	
	glPushMatrix();
	
	glTranslated(700, 500, 400);
	GLfloat position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat specularLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	
	glPopMatrix();
	glPopMatrix();
	
	//glEnable(GL_LIGHT2);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	
	
	for(int i = 0; i < pianoroll.size(); i++){
		pianoroll[i].draw();
		//pianoroll[i].print();
		pianoroll[i].move(0, 0.001);
	}
	
	
	
	
	
	
	if(playing){
		glPushMatrix();
		glTranslatef(500,0,0);
		glColor3f(0.0, 0.7,0.0);
		float mcolor[] = { 0.0f, 0.7f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
		glMaterialf(GL_FRONT, GL_AMBIENT, 0.8f);
		glMaterialf(GL_FRONT, GL_DIFFUSE, 1.0f);
		glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);
		glMaterialf(GL_FRONT, GL_SPECULAR, 1.0f);
		glMaterialf(GL_FRONT, GL_EMISSION, 0.2f);
		ofTriangle(700, 700, 700, 750, 750, 725);
		glPopMatrix();
	}
	
	if(recording){
		glPushMatrix();
		glTranslatef(500,0,0);
		glColor3f(0.7, 0.0,0.0);
		float mcolor[] = { 0.7f, 0.0f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
		glMaterialf(GL_FRONT, GL_AMBIENT, 0.8f);
		glMaterialf(GL_FRONT, GL_DIFFUSE, 1.0f);
		glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);
		glMaterialf(GL_FRONT, GL_SPECULAR, 1.0f);
		glMaterialf(GL_FRONT, GL_EMISSION, 0.2f);
		ofCircle(800,725,25);
		glPopMatrix();
	}
	
	
	drawLine(targetline);
	if(redpressed){
		float ecolor[] = { 0.7f, 0.0f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ecolor);
		ofRect(1200, 95, 30, 30);
		for(int i = 0; i < pianoroll.size(); i++){
			if( pianoroll[i].target(targetline, 'r') ){
				//send play osc message to chuck
				sendPlay(1, sender, serial);
			}
		}
	}
	
	
	if(greenpressed){
		float ecolor[] = { 0.0f, 0.7f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ecolor);
		ofRect(1235, 95, 30, 30);
		for(int i = 0; i < pianoroll.size(); i++){
			if( pianoroll[i].target(targetline, 'g') ){
				sendPlay(2,sender, serial);
			}
		}
	}
	
	
	if(bluepressed){
		float ecolor[] = { 0.0f, 0.0f, 0.7f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ecolor);
		ofRect(1270, 95, 30, 30);
		for(int i = 0; i < pianoroll.size(); i++){
			if( pianoroll[i].target(targetline, 'b') ){
				sendPlay(3,sender, serial);
			}
		}
	}
	
	
	if(yellowpressed){
		float ecolor[] = { 0.7f, 0.7f, 0.0f, 1.0f };
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ecolor);
		ofRect(1305, 95, 30, 30);
		for(int i = 0; i < pianoroll.size(); i++){
			if( pianoroll[i].target(targetline, 'y') ){
				sendPlay(4,sender, serial);
			}
		}
	}
	
	
	if(!redpressed && !greenpressed && !bluepressed && !yellowpressed ){
		for(int i = 0; i < pianoroll.size(); i++){
			int toHitMe = pianoroll[i].isMissed(targetline);
			if( toHitMe ){
				cout << toHitMe << endl;
				sendRec(toHitMe,sender, serial);
			}
		}
	}
	
	glColor3f(0.0, 0.0,0.0);
	float mcolor[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mcolor);
	glMaterialf(GL_FRONT, GL_AMBIENT, 0.8f);
	glMaterialf(GL_FRONT, GL_DIFFUSE, 1.0f);
	glMaterialf(GL_FRONT, GL_SHININESS, 1.0f);
	glMaterialf(GL_FRONT, GL_SPECULAR, 1.0f);
	glMaterialf(GL_FRONT, GL_EMISSION, 0.2f);
	glTranslatef(200,0,0);
	ofCircle(1000,100, 50);
	ofCircle(1150,100, 50);
	ofRect(1000,50, 150, 100);
	glColor3f(0.7,0,0);
	
	
	
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){ 
	if(key == 'r'){
		redpressed = true;
	}
	
	if(key == 'g'){
		greenpressed = true;
	}
	
	if(key == 'b'){
		bluepressed = true;
	}
	
	if(key == 'y'){
		yellowpressed = true;
	}
	
	if ( key =='a' || key == 'A' )
	{
		ofxOscMessage m;
		m.setAddress( "/test" );
		m.addIntArg( 1 );
		m.addFloatArg( 3.5f );
		m.addStringArg( "hello" );
		m.addFloatArg( ofGetElapsedTimef() );
		sender.sendMessage( m );
	}
}

//--------------------------------------------------------------
void testApp::keyReleased  (int key){ 
	if(key == 'r'){
		redpressed = false;
	}
	
	if(key == 'g'){
		greenpressed = false;
	}
	
	if(key == 'b'){
		bluepressed = false;
	}
	
	if(key == 'y'){
		yellowpressed = false;
	}
	if(key == 'p'){
		if(paused){
			paused = false;
		}else{
			paused = true;
		}
	}
}
//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	ofxOscMessage m;
	m.setAddress( "/mouse/button" );
	m.addStringArg( "down" );
	sender.sendMessage( m );
}

//--------------------------------------------------------------
void testApp::mouseReleased(){
	ofxOscMessage m;
	m.setAddress( "/mouse/button" );
	m.addStringArg( "up" );
	sender.sendMessage( m );	
}
