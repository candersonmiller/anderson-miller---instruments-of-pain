// launch with OSC_recv.ck

// host name and port
"localhost" => string hostname;
9001 => int port;

// get command line
//if( me.args() ) me.arg(0) => hostname;
//if( me.args() > 1 ) me.arg(1) => Std.atoi => port;

// send object
OscSend xmit;

0 => int iter;
// aim the transmitter
xmit.setHost( hostname, port );

// infinite time loop
while( true )
{
    // start the message...
    // the type string ',f' expects a single float argument
    xmit.startMsg( "/play", "i" );

    // a message is kicked as soon as it is complete 
    // - type string is satisfied and bundles are closed
    //Std.rand2f( .5, 2.0 ) => float temp => xmit.addFloat;
	1 => int temp => xmit.addInt;
    <<< "sent (via OSC):", temp >>>;

	1::second => now;
	if(iter < 10){
		xmit.startMsg("/rec", "i");
		1 => int temp1 => xmit.addInt;
		iter++;
		// advance time
	    0.25::second => now;
	}
	
	
	// advance time
    0.25::second => now;
    
}