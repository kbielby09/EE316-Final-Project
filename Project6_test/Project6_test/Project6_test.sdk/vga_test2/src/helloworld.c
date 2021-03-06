/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>

// Header files for IP cores
#include "kybd_slv.h"
#include "slv.h"

#include "xgpio.h"
#include "platform.h"
#include "xil_printf.h"
#include "xil_types.h"
#include "xparameters.h"
#include "xil_io.h"
#include <stdbool.h>

#define F0_BREAK_CODE 0xF0
#define E0_BREAK_CODE 0xE0
#define BACKSPACE 0x66
#define ENTER 0x5A
#define CTRL 0x14

#define L_SHIFT 0x12
#define R_SHIFT 0x59

// GPIO instance
XGpio gpioInstance;

unsigned char ascii;
bool  breakFlag, prevScanFlag, newScanFlag, e0Code, asciiNew;
bool ctrlLeft = false;
bool ctrlRight = false;
bool shiftRight = false;
bool shiftLeft = false;
bool caps = false;
int row = 0;
int column = 0;

void delayMs(int n);

void ready(int scancode);
bool newCode(int scancode);
unsigned char translate(int scancode);

int main()
{
	int var;

	int Status;

	/* Initialize the GPIO driver. If an error occurs then exit */
	Status = XGpio_Initialize(&gpioInstance, XPAR_AXI_GPIO_0_DEVICE_ID);
	if (Status != XST_SUCCESS) {
		return XST_FAILURE;
	}

	printf("gpio initialized\n");

	while(1){
		// read data from the keyboard
		u32 data;

		if(XGpio_DiscreteRead(&gpioInstance, 1) > 0){

			var = KYBD_SLV_mReadReg(XPAR_KYBD_SLV_0_S00_AXI_BASEADDR, 0);

			// send var to scancode2ascii
//			bool nulvar = newCode(var);

			if(var == F0_BREAK_CODE) {
				breakFlag = true;
				continue;
			}
			else if(var == E0_BREAK_CODE) {
				e0Code = true;
				printf("e0Code set\n");
//				breakFlag = true;
				continue;
			}
			else if(breakFlag == true && (var != F0_BREAK_CODE && var != E0_BREAK_CODE)) {
				breakFlag = false;

				// check for shift pressed
				if(var == R_SHIFT) {
					shiftRight = false;
				}
				else if(var == L_SHIFT) {
					shiftLeft = false;
				}

				// check for ctrl pressed
				if(var == CTRL && e0Code == false) {
					ctrlLeft = false;
				}

				if(var == CTRL && e0Code == true){
					ctrlRight = false;
				}

				continue;
			}
			else if(breakFlag == false && var != F0_BREAK_CODE && var != E0_BREAK_CODE){

//				e0Code = false;

				// Check for Shift presses
				if(var == L_SHIFT) {
					shiftLeft = true;
					continue;
				}
				else if(var == R_SHIFT) {
					shiftRight = true;
					continue;
				}


				unsigned char result;

				if(var != BACKSPACE){
					if(var == CTRL && e0Code == false) {
						printf("here\n");
						ctrlLeft = true;
						continue;
					}
					else if(var == CTRL && e0Code == true){
						ctrlRight = true;
//						e0Code = false;
						printf("ctrlRight %d\n", ctrlRight);
						continue;
					}
					else{
						if(ctrlLeft == true || ctrlRight == true){
							printf("ctrl on\n");
							switch(var) {
							//^@ NUL
							case 0x1E :
								printf("hello2\n");
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
								break;
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
							printf("hello4\n");
							data = ascii | (column << 16) | (row << 8);

						}
						else {
							printf("hello6\n");

							result = translate(var);
							data = result | (column << 16) | (row << 8);
						}
					}



					// write data to the display
					SLV_mWriteReg(XPAR_SLV_0_S00_AXI_BASEADDR, 0, data);
					column++;
				}
				else if(var == BACKSPACE){
					result = translate(0x29);
					column--;

					data = result | (column << 16) | (row << 8);

					// write data to the display
					SLV_mWriteReg(XPAR_SLV_0_S00_AXI_BASEADDR, 0, data);
				}

				if(var == ENTER){
					row++;
					column = 0;
				}

				if(column > 79){
					row++;
					column = 0;
				}

				if(row > 39){
					row = 0;
				}

				// add row and column to sent axi data




			}

			while(XGpio_DiscreteRead(&gpioInstance, 1) > 0){
				printf("IRQ not reset\n");
			}
		}
	}
    return 0;
}

//void ready(int scancode) {
//	bool nullBool;
//	if(prevScanFlag == false && newScanFlag == true) {
//	 	asciiNew = false;
//	 	nullBool = newCode(scancode);
//	}
//	else{
//		ready(scancode);
//	}
//}

bool newCode(int scancode) {
	printf("newcode \n");
	if(scancode == 0xF0) {
		printf("make code\n");
		breakFlag = true;
		return breakFlag;
	}
	else if(scancode == 0xE0) {
		printf("ecode\n");
		e0Code = true;
		return e0Code;
	}
	else {
		translate(scancode);
	}
	return false;
}

unsigned char translate(int scancode){
	printf(": %d\n", caps);
	printf("breakflag: %d\n", breakFlag);

//	breakFlag = false;
//	e0Code = false;
//	shiftLeft = false;

	switch(scancode) {
	//caps mode
			case 0x58 :
				if(breakFlag == false) {
					caps = ! caps;
				}
				break;
			//code for ctrl keys
			case 0x14 :
				// ctrl right code
				if(e0Code == true) {
//					ctrlRight = ! breakFlag;
//					while(breakFlag == false) {
//						ctrlRight = true;
//						break;
//					}
//					ctrlRight = false;
				}
				// ctrl left code
				else {
//					ctrlLeft = ! breakFlag;
//					while(breakFlag == false) {
//						ctrlLeft = true;
//						break;
//					}
//					ctrlLeft = false;
				}
				break;
			// shift left code
			case 0x12 :
//				shiftLeft = ! breakFlag;
//				if(breakFlag == false){
//					shiftLeft = true;
//				}
//				else {
//					shiftLeft = false;
//				}
//				while(breakFlag == false) {
//					shiftLeft = true;
//					break;
//				}
//				shiftLeft = false;
				break;

			// shift right code
			case 0x59 :
//				shiftRight = ! breakFlag;
	//			if(breakFlag == false) {
	//				shiftRight = true;
	//			}
	//			else {
	//				shiftRight = false;
	//			}
//				while(breakFlag == false) {
//					shiftRight = true;
//					break;
//				}
//				shiftRight = false;
				break;
		}

	//control codes
	if(ctrlLeft == true || ctrlRight == true) {
//		switch(scancode) {
//			//^@ NUL
//			case 0x1E :
//				printf("hello2\n");
//				ascii = 0x00;
//				break;
//			//^A SOH
//			case 0x1C :
//				ascii = 0x01;
//				break;
//			//^B STX
//			case 0x32 :
//				ascii = 0x02;
//				break;
//			//^C ETX
//			case 0x21 :
//				ascii = 0x03;
//				break;
//			//^D EOT
//			case 0x23 :
//				ascii = 0x04;
//				break;
//			//^E ENQ
//			case 0x24 :
//				ascii = 0x05;
//				break;
//			//^F ACK
//			case 0x2B :
//				ascii = 0x06;
//				break;
//			//^G BEL
//			case 0x34 :
//				ascii = 0x07;
//				break;
//			//^H BS
//			case 0x33 :
//				ascii = 0x08;
//				break;
//			//^I HT
//			case 0x43 :
//				ascii = 0x09;
//				break;
//			//^J LF
//			case 0x3B :
//				ascii = 0x0A;
//				break;
//			//^K VT
//			case 0x42 :
//				ascii = 0x0B;
//				break;
//			//^L FF
//			case 0x4B :
//				ascii = 0x0C;
//				break;
//			//^M CR
//			case 0x3A :
//				ascii = 0x0D;
//				break;
//			//^N SO
//			case 0x31 :
//				ascii = 0x0E;
//				break;
//			//^O SI
//			case 0x44 :
//				ascii = 0x0F;
//				break;
//			//^P DLE
//			case 0x4D :
//				ascii = 0x10;
//				break;
//			//^Q DC1
//			case 0x15 :
//				ascii = 0x11;
//				break;
//			//^R DC2
//			case 0x2D :
//				ascii = 0x12;
//				break;
//			//^S DC3
//			case 0x1B :
//				ascii = 0x13;
//				break;
//			//^T DC4
//			case 0x2C :
//				ascii = 0x14;
//				break;
//			//^U NAK
//			case 0x3C :
//				ascii = 0x15;
//				break;
//			//^V SYN
//			case 0x2A :
//				ascii = 0x16;
//				break;
//			//^W ETB
//			case 0x1D :
//				ascii = 0x17;
//				break;
//			//^X CAN
//			case 0x22 :
//				ascii = 0x18;
//				break;
//			//^Y EM
//			case 0x35 :
//				ascii = 0x19;
//				break;
//			//^Z SUB
//			case 0x1A :
//				ascii = 0x1A;
//				break;
//			//^[ ESC
//			case 0x54 :
//				ascii = 0x1B;
//				break;
//			//^\ FS
//			case 0x5D :
//				ascii = 0x1C;
//				break;
//			//^] GS
//			case 0x5B :
//				ascii = 0x1D;
//				break;
//			//^^ RS
//			case 0x36 :
//				ascii = 0x1E;
//				break;
//			//^_ US
//			case 0x4E :
//				ascii = 0x1F;
//				break;
//			//^? DEL
//			case 0x4A :
//				ascii = 0x7F;
//				break;
//		}
	}
	else {
		switch(scancode) {
			//space
			case 0x29 :
				ascii = 0x20;
				break;
			//backspace
			case 0x66 :
//				ascii = 0x08;
				break;
			//tab
			case 0x0D :
				ascii = 0x09;
				break;
			//enter
			case 0x5A :
//				ascii = 0x0D;
				break;
			//escape
			case 0x76 :
				ascii = 0x1B;
				break;
			//delete
			case 0x71 :
				if (e0Code == true) {
					ascii = 0x7F;
				}
				break;
		}
	}
	// Lowercase
	if((shiftRight == false && shiftLeft == false && caps == false) ||
		((shiftRight == true || shiftLeft == true) && caps == true)) {
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
				printf("hello3\n");
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
	printf("Ascii: %c\n", ascii);
//	printf("Ascii Hex: %x\n", ascii);
	return ascii;
}

void delayMs(int n){
	int i;
	int j;

	for(i = 0; i < n; i++)
		for(j = 0; j < 7000; j++) {}
}

