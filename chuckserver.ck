//HID for prototyping and testing
Hid hi;
HidMsg msg;

//Arrays of lisa objects
250::ms => dur sampleLength;
LiSa button1[20];
LiSa button2[20];
LiSa button3[20];
LiSa button4[20];
0 => int button1Iter;
0 => int button2Iter;
0 => int button3Iter;
0 => int button4Iter;
for( 0 => int i ; i < 20; i++){
	sampleLength => button1[i].duration;
	sampleLength => button2[i].duration;
	sampleLength => button3[i].duration;
	sampleLength => button4[i].duration;
	button1[i] => dac;
	button2[i] => dac;
	button3[i] => dac;
	button4[i] => dac;
	//button1[i].play(1);
	button1[i].loop(0);
	button2[i].loop(0);
	button3[i].loop(0);
	button4[i].loop(0);
	adc => button1[i];
	adc => button2[i];
	adc => button3[i];
	adc => button4[i];
}




// which keyboard
0 => int device;
// get from command line
if( me.args() ) me.arg(0) => Std.atoi => device;

// open keyboard (get device number from command line)
if( !hi.openKeyboard( device ) ) me.exit();
<<< "keyboard '" + hi.name() + "' ready", "" >>>;


// osc event creator function
fun OscEvent createOscEvent( string address, int port ) {
    OscRecv recv;
    port => recv.port;
    recv.listen();
    recv.event( address ) @=> OscEvent oe;
    return oe;
}



// chfreq shred definition
fun void play_button() {
    -1 => int button;
    createOscEvent( "/play, i", 9001 ) @=> OscEvent oe;
    
    while( oe => now ) {
		//play all entries in button1 array

        //button => s.freq;
        if( oe.nextMsg() ) {
            oe.getInt() => button;
			<<< "received play (via OSC):", button >>>;
			if(button == 1){
				for( 0 => int i ; i < 20; i++){
					button1[i].play(1);
					button1[i].playPos(0::ms);
				}
				250::ms => now;
				for( 0 => int i ; i < 20; i++){
					button1[i].play(0);
				}
			}
			if(button == 2){
				for( 0 => int i ; i < 20; i++){
					button2[i].play(1);
					button2[i].playPos(0::ms);
				}
				250::ms => now;
				for( 0 => int i ; i < 20; i++){
					button2[i].play(0);
				}
			}
			if(button == 3){
				for( 0 => int i ; i < 20; i++){
					button3[i].play(1);
					button3[i].playPos(0::ms);
				}
				250::ms => now;
				for( 0 => int i ; i < 20; i++){
					button3[i].play(0);
				}
			}
			
			if(button == 4){
				for( 0 => int i ; i < 20; i++){
					button4[i].play(1);
					button4[i].playPos(0::ms);
				}
				250::ms => now;
				for( 0 => int i ; i < 20; i++){
					button4[i].play(0);
				}
			}
        }
		me.yield();
    }
}

fun void record_button() {
	-1 => int button;
	createOscEvent( "/rec, i", 9001 ) @=> OscEvent oe;
	while (oe => now ) {
		if( oe.nextMsg() ) {
			oe.getInt() => button;
			<<< "received rec (via OSC):", button >>>;
			if(button == 1){
					button1[button1Iter].recPos(0::ms);
					button1[button1Iter].record(1);
					250::ms => now;
					button1[button1Iter].record(0);
					button1Iter++;
					if(button1Iter > 19){
						0 => button1Iter;
					}
			}
			if(button == 2){
					button1[button2Iter].recPos(0::ms);
					button1[button2Iter].record(1);
					250::ms => now;
					button1[button2Iter].record(0);
					button2Iter++;
					if(button2Iter > 19){
						0 => button2Iter;
					}
			}
			if(button == 3){
					button3[button3Iter].recPos(0::ms);
					button3[button3Iter].record(1);
					250::ms => now;
					button3[button3Iter].record(0);
					button3Iter++;
					if(button3Iter > 19){
						0 => button3Iter;
					}
			}
			if(button == 4){
					button4[button4Iter].recPos(0::ms);
					button4[button4Iter].record(1);
					250::ms => now;
					button4[button4Iter].record(0);
					button4Iter++;
					if(button4Iter > 19){
						0 => button4Iter;
					}
			}
			
		}
		
		me.yield();
	}


}





spork ~ play_button() @=> Shred cf;
me.yield();

spork ~ record_button() @=> Shred cf1;
me.yield();


// print the id number
//<<< cf.id() >>>;


// mic-in to audio out

// the patch
//adc => dac;

// infinite time-loop


//parent thread
while( true )
{
    // advance time
    100::ms => now;
}
