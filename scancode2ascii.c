#include <stdio.h>
#include <stdbool.h>
unsigned char scancode, ascii;
bool breakFlag, prevScanFlag, newScanFlag, e0Code, asciiNew;

void ready() {
	if(prevScanFlag == false && newScanFlag == true) {
	 	asciiNew = false;
		newCode(scancode);
	}
	else{
		ready();
	}
}

bool newCode(scancode) {
	if(scancode == 0xF0) {
		bool breakFlag = true;
		ready();
	}
	else if(scancode == 0xE0) {
		e0Code = true;
		ready();
	}
	else {
		translate(scancode);
	}
	return e0Code
}

unsigned char translate(scancode){
	bool ctrlLeft, ctrlRight, shiftRight, shiftLeft, caps;

	breakFlag = false;
	e0Code = false;

	switch(scancode) {
		//caps mode
		case 0x58 :
			if(breakFlag = false) {
				caps = ~ caps;
			}
			break;
		//code for ctrl keys
		case 0x14 : 
			// ctrl right code
			if(e0Code = true) {
				ctrlRight = ~ breakFlag;
			}
			// ctrl left code
			else {
				ctrlLeft = ~ breakFlag;
			}
			break;
		// shift left code
		case 0x12 :
			shiftLeft = ~ breakFlag;
			break;
		// shift right code
		case 0x59 :
			shiftRight = ~ breakFlag;
			break;
	}

	//control codes
	if(ctrlLeft == true || ctrlRight == true) {
		switch(scancode) {
			//^@ NUL
			case 0x1E :
				ascii = 0x00;
				break;
			//^A SOH
			case 0x1C :
				ascii = 0x01;
				break;
			//^B STX
			case 0x32 :
				ascii = 0x02;
				break;
			//^C ETX
			case 0x21 :
				ascii = 0x03;
				break;
			//^D EOT
			case 0x23 :
				ascii = 0x04;
				break;
			//^E ENQ
			case 0x24 :
				ascii = 0x05;
				break;
			//^F ACK
			case 0x2B :
				ascii = 0x06;
				break;
			//^G BEL
			case 0x34 :
				ascii = 0x07;
				break;
			//^H BS
			case 0x33 :
				ascii = 0x08;
				break;
			//^I HT
			case 0x43 :
				ascii = 0x09;
				break;
			//^J LF
			case 0x3B :
				ascii = 0x0A;
				break;
			//^K VT
			case 0x42 :
				ascii = 0x0B;
				break;
			//^L FF
			case 0x4B :
				ascii = 0x0C;
				break;
			//^M CR
			case 0x3A :
				ascii = 0x0D;
				break;
			//^N SO
			case 0x31 :
				ascii = 0x0E;
				break;
			//^O SI
			case 0x44 :
				ascii = 0x0F;
				break;
			//^P DLE
			case 0x4D :
				ascii = 0x10;
				break;
			//^Q DC1
			case 0x15 : 
				ascii = 0x11;
				break;
			//^R DC2
			case 0x2D :
				ascii = 0x12;
				break;
			//^S DC3
			case 0x1B :
				ascii = 0x13;
				break;'
			//^T DC4
			case 0x2C :
				ascii = 0x14;
				break;
			//^U NAK
			case 0x3C :
				ascii = 0x15;
				break;
			//^V SYN
			case 0x2A :
				ascii = 0x16;
				break;
			//^W ETB
			case 0x1D :
				ascii = 0x17;
				break;
			//^X CAN
			case 0x22 :
				ascii = 0x18;
				break;
			//^Y EM
			case 0x35 :
				ascii = 0x19;
				break;
			//^Z SUB
			case 0x1A :
				ascii = 0x1A;
				break;
			//^[ ESC
			case 0x54 :
				ascii = 0x1B;
				break;
			//^\ FS
			case 0x5D :
				ascii = 0x1C;
				break;
			//^] GS
			case 0x5B :
				ascii = 0x1D;
				break;
			//^^ RS
			case 0x36 :
				ascii = 0x1E;
				break;
			//^_ US
			case 0x4E :
				ascii = 0x1F;
				break;
			//^? DEL
			case 0x4A :
				ascii = 0x7F;
				break;
		}
	}
	else {
		switch(scancode) {
			//space
			case 0x29 :
				ascii = 0x20;
				break;
			//backspace
			case 0x66 :
				ascii = 0x08;
				break;
			//tab 
			case 0x0D :
				ascii = 0x09;
				break;
			//enter
			case 0x5A :
				ascii = 0x0D;
				break;
			//escape
			case 0x76 :
				ascii = 0x1B;
				break;
			//delete
			case 0x71 :
				if e0Code = true {
					ascii = 0x7F;
				}
				break;
		}
	}
	// Lowercase
	if((shiftRight == false && shiftLeft == false && caps == false) ||
		((shiftRight == true || shiftLeft == true) && caps == true) {
		switch(scancode) {
			//a
			case 0x1C :
				ascii = 0x61;
				break;
			//b
			case 0x32 :
				ascii = 0x62;
				break;
			//c
			case 0x21 :
				ascii = 0x63;
				break;
			//d
			case 0x23 :
				ascii = 0x64;
				break;
			//e
			case 0x24 :
				ascii = 0x65;
				break;
			//f
			case 0x2B :
				ascii = 0x66;
				break;
			//g
			case 0x34 :
				ascii = 0x67;
				break;
			//h
			case 0x33 :
				ascii = 0x68;
				break;
			//i
			case 0x43 :
				ascii = 0x69;
				break;
			//j
			case 0x3B :
				ascii = 0x6A;
				break;
			//k
			case 0x42 :
				ascii = 0x6B;
				break;
			//l
			case 0x4B :
				ascii = 0x6C;
				break;
			//m
			case 0x3A :
				ascii = 0x6D;
				break;
			//n
			case 0x31 :
				ascii = 0x6E;
				break;
			//o
			case 0x44 :
				ascii = 0x6F;
				break;
			//p
			case 0x4D :
				ascii = 0x70;
				break;
			//q
			case 0x15 :
				ascii = 0x71;
				break;
			//r
			case 0x2D :
				ascii = 0x72;
				break;
			//s
			case 0x1B :
				ascii = 0x73;
				break;
			//t
			case 0x2C :
				ascii = 0x74;
				break;
			//u
			case 0x3C :
				ascii = 0x75;
				break;
			//v
			case 0x2A :
				ascii = 0x76;
				break;
			//w
			case 0x1D :
				ascii = 0x77;
				break;
			//x
			case 0x22 :
				ascii = 0x78;
				break;
			//y
			case 0x35 :
				ascii = 0x79;
				break;
			//z
			case 0x1A : 
				ascii = 0x7A;
				break;
		}
	}
	//Uppercase
	else {
		switch(scancode) {
			//A
			case 0x1C :
				ascii = 0x41;
				break;
			//B
			case 0x32 :
				ascii = 0x42;
				break;
			//C
			case 0x21 :
				ascii = 0x43;
				break;
			//D
			case 0x23 :
				ascii = 0x44;
				break;
			//E
			case 0x24 :
				ascii = 0x45;
				break;
			//F
			case 0x2B :
				ascii = 0x46;
				break;
			//G
			case 0x34 :
				ascii = 0x47;
				break;
			//H
			case 0x33 :
				ascii = 0x48;
				break;
			//I
			case 0x43 :
				ascii = 0x49;
				break;
			//J
			case 0x3B :
				ascii = 0x4A;
				break;
			//K
			case 0x42 : 
				ascii = 0x4B;
				break;
			//L
			case 0x4B :
				ascii = 0x4C;
				break;
			//M
			case 0x3A :
				ascii = 0x4D;
				break;
			//N
			case 0x31 :
				ascii = 0x4E;
				break;
			//O
			case 0x44 :
				ascii = 0x4F;
				break;
			//P
			case 0x4D :
				ascii = 0x50;
				break;
			//Q
			case 0x15 :
				ascii = 0x51;
				break;
			//R
			case 0x2D :
				ascii = 0x52;
				break;
			//S
			case 0x1B :
				ascii = 0x53;
				break;
			//T
			case 0x2C :
				ascii = 0x54;
				break;
			//U
			case 0x3C :
				ascii = 0x55;
				break;
			//V
			case 0x2A :
				ascii = 0x56;
				break;
			//W
			case 0x1D :
				ascii = 0x57;
				break;
			//X
			case 0x22 :
				ascii = 0x58;
				break;
			//Y
			case 0x35 :
				ascii = 0x59;
				break;
			//Z
			case 0x1A :
				ascii = 0x5A;
				break;
		}
	}
	// # symbols
	if(shiftLeft == true || shiftRight == true) {
		switch(scancode) {
			//!
			case 0x16 :
				ascii = 0x21;
				break;
			//"	
			case 0x52 :
				ascii = 0x22;
				break;
			//# 
			case 0x26 :
				ascii = 0x23;
				break;
			//$
			case 0x25 :
				ascii = 0x24;
				break;
			//%
			case 0x2E :
				ascii = 0x25;
				break;
			//& 
			case 0x3D :
				ascii = 0x26;
				break;
			//(
			case 0x46 :
				ascii = 0x28;
				break;
			//)
			case 0x45 :
				ascii = 0x29;
				break;
			//* 
			case 0x3E :
				ascii = 0x2A;
				break;
			//+
			case 0x55 :
				ascii = 0x2B;
				break;
			//:
			case 0x4C :
				ascii = 0x3A;
				break;
			//<
			case 0x41 :
				ascii = 0x3C;
				break;
			//>
			case 0x49 :
				ascii = 0x3E;
				break;
			//?
			case 0x4A :
				ascii = 0x3F;
				break;
			//@
			case 0x1E :
				ascii = 0x40;
				break;
			//^
			case 0x36 :
				ascii = 0x5E;
				break;
			//_
			case 0x4E :
				ascii = 0x5F;
				break;
			//{
			case 0x54 :
				ascii = 0x7B;
				break;
			//|
			case 0x5D :
				ascii = 0x7C;
				break;
			//}
			case 0x5B :
				ascii = 0x7D;
				break;
			//~
			case 0x0E :
				ascii = 0x7E;
				break; 
		}
	}

	// primary character
	else {
		switch(scancode) {
			//0
			case 0x45 :
				ascii = 0x30;
				break;
			//1
			case 0x16 :
				ascii = 0x31;
				break;
			//2
			case 0x1E :
				ascii = 0x32;
				break;
			//3
			case 0x26 :
				ascii = 0x33;
				break;
			//4
			case 0x25 :
				ascii = 0x34;
				break;
			//5
			case 0x2E :
				ascii = 0x35;
				break;
			//6
			case 0x36 :
				ascii = 0x36;
				break;
			//7
			case 0x3D :
				ascii = 0x37;
				break;
			//8
			case 0x3E :
				ascii = 0x38;
				break;
			//9
			case 0x46 :
				ascii = 0x39;
				break;
			//'
			case 0x52 :
				ascii = 0x27;
				break;
			//,
			case 0x41 :
				ascii = 0x2C;
				break;
			//-
			case 0x4E :
				ascii = 0x2D;
				break;
			//.
			case 0x49 :
				ascii = 0x2E;
				break;
			// /
			case 0x4A :
				ascii = 0x2F;
				break;
			//;
			case 0x4C :
				ascii = 0x3B;
				break;
			//= 
			case 0x55 :
				ascii = 0x3D;
				break;
			//[
			case 0x54 :
				ascii = 0x5B;
				break;
			// backslash
			case 0x5D:
				ascii = 0x5C;
				break;
			//]
			case 0x5B :
				ascii = 0x5D;
				break;
			//`
			case 0x0E :
				ascii = 0x60;
				break;
		}
	}
	//if(breakFlag = false) {
	//	char binAscii[];
	

	//	if(ascii[7] == 0) {
	//		asciiNew = true;
	//	}
	//	ready();
	//}
	//else {
	//	ready();
	//}
	return ascii;
}
