#!/usr/bin/perl

use strict;



my @colors = ('r', 'g', 'b');

my $i = 0;
while( $i < 200){
	my $color = int(rand(3));
	my $time = int(rand(400));
	$time += 200;
	print '0'.$time.' '.@colors[$color].' 1000'."\n";
	$i++;
}

