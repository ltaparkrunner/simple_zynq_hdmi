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
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "xaxivdma.h"
#include "xscugic.h"
#include "sleep.h"
#include "videoProcess.h"

#define HSize 1280//1920
#define VSize 720//1080
#define FrameSize HSize*VSize*3

#define imgHSize 512
#define imgVSize 512
#define imageSize imgHSize*imgVSize


extern char imageData[];
char Buffer[FrameSize];

int initIntrController(XScuGic *Intc);
//static int SetupVideoIntrSystem(XAxiVdma *AxiVdmaPtr, u16 ReadIntrId, XScuGic *Intc);

int main()
{
//	XScuGic Intc;
    init_platform();
//	initIntrController(&Intc);
//	zed_iic_axi_init(&hdmi_out_iic,"IIC Controller",XPAR_VIDEOSUBSYSTEM_AXI_IIC_0_BASEADDR);
/*
	imgProcess myImgProcess;
	char *filteredImage;
	filteredImage = malloc(sizeof(char)*(imageSize));
	myImgProcess.imageDataPointer = imageData;
	myImgProcess.imageHSize = imgHSize;
	myImgProcess.imageVSize = imgVSize;
	myImgProcess.filteredImageDataPointer = filteredImage;
//	initImgProcessSystem(&myImgProcess, (u32)XPAR_AXI_DMA_0_BASEADDR, &Intc);
//	startImageProcessing(&myImgProcess);
*/

    int status;
    int Index;
//    int choice;

	u32 Addr;

    print("Hello World 1\n\r");
	XAxiVdma myVDMA;
	XAxiVdma_Config *config = XAxiVdma_LookupConfig(XPAR_AXI_VDMA_0_DEVICE_ID);
	XAxiVdma_DmaSetup ReadCfg;
	status = XAxiVdma_CfgInitialize(&myVDMA, config, config->BaseAddress);
    if(status != XST_SUCCESS){
    	xil_printf("DMA Initialization failed");
    	print("DMA Initialization failed");
    }
    ReadCfg.VertSizeInput = VSize;
    ReadCfg.HoriSizeInput = HSize*3;
    ReadCfg.Stride = HSize*3;
    ReadCfg.FrameDelay = 0;
    ReadCfg.EnableCircularBuf = 1;
    ReadCfg.EnableSync = 1;
    ReadCfg.PointNum = 0;
    ReadCfg.EnableFrameCounter = 0;
    ReadCfg.FixedFrameStoreAddr = 0;
    status = XAxiVdma_DmaConfig(&myVDMA, XAXIVDMA_READ, &ReadCfg);
    if (status != XST_SUCCESS) {
    	xil_printf("Write channel config failed %d\r\n", status);
    	print("Write channel config failed %d\r\n");
    	return status;
    }
    print("Hello World 2\n\r");
    Addr = (u32)&(Buffer[0]);

	for(Index = 0; Index < myVDMA.MaxNumFrames; Index++) {
		ReadCfg.FrameStoreStartAddr[Index] = Addr;
		Addr +=  FrameSize;
	}
    print("Hello World 3\n\r");
	status = XAxiVdma_DmaSetBufferAddr(&myVDMA, XAXIVDMA_READ,ReadCfg.FrameStoreStartAddr);
	if (status != XST_SUCCESS) {
		xil_printf("Read channel set buffer address failed %d\r\n", status);
		print("Read channel set buffer address failed %d\r\n");
		return XST_FAILURE;
	}
    print("Hello World 4\n\r");
//    sleep(1);
//	XAxiVdma_IntrEnable(&myVDMA, XAXIVDMA_IXR_COMPLETION_MASK, XAXIVDMA_READ);
    print("Hello World 5\n\r");
//    sleep(1);
//	SetupVideoIntrSystem(&myVDMA, XPAR_FABRIC_AXI_VDMA_0_MM2S_INTROUT_INTR,&Intc);


//    while(!myImgProcess.done){
//    }
//    print("Hello World 6\n\r");
//    sleep(1);
	status = XAxiVdma_DmaStart(&myVDMA,XAXIVDMA_READ);
	if (status != XST_SUCCESS) {
		if(status == XST_VDMA_MISMATCH_ERROR){

			xil_printf("DMA Mismatch Error\r\n");
		print("DMA Mismatch Error\r\n");
		}
		print("DMA Mismatch Error_2\r\n");
		return XST_FAILURE;
	}

    print("Hello World 7\n\r");
    print("Successfully ran Hello World application");

    while(1){
		char pchar[80] = "";

    		fillFrameBuffer2(0, HSize, VSize, imgHSize, imgVSize,
    		(HSize-imgHSize)/2,(VSize-imgVSize)/4, 1, imageData, Buffer, -1280*150*3);
    		sleep(5);

    		fillFrameBuffer2(1, HSize, VSize, imgHSize, imgVSize,
    		(HSize-imgHSize)/2,(VSize-imgVSize)/4, 1, imageData, Buffer, -1280*150*3);
    		sleep(4);
			sprintf(pchar, "(VSize-imgVSize)/2 %d \n\r", (VSize-imgVSize)/2);
			print(pchar);
    	    print("Hello World 8\n\r");
    	}

    cleanup_platform();
    return 0;
}
/*
 *
 * u32 variant,
u32 dispHSize,
u32 dispVSize,
u32 imageHSize,
u32 imageVSize,
u32 hOffset,
u32 vOffset,
int numColors,
char *imagePointer,
char *videoFramePointer)
 *
 */

/*
#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"


int main()
{
    init_platform();

    print("Hello World\n\r");
    print("Successfully ran Hello World application");
    cleanup_platform();
    return 0;
}
*/
