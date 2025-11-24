#include "videoProcess.h"
#include "xil_cache.h"

//extern char Buffer[FrameSize];

/*****************************************************************************/
/**
 * This function copies the buffer data from image buffer to video buffer
 *
 * @param	displayHSize is Horizontal size of video in pixels
 * @param   displayVSize is Vertical size of video in pixels
 * @param	imageHSize is Horizontal size of image in pixels
 * @param   imageVSize is Vertical size of image in pixels
 * @param   hOffset is horizontal position in the video frame where image should be displayed
 * @param   vOffset is vertical position in the video frame where image should be displayed
 * @param   imagePointer pointer to the image buffer
 * @return
 * 		-  0 if successfully copied
 * 		- -1 if copying failed
 *****************************************************************************/

int fillFrameBuffer(
u32 variant,
u32 dispHSize,
u32 dispVSize,
u32 imageHSize,
u32 imageVSize,
u32 hOffset,
u32 vOffset,
int numColors,
char *imagePointer,
char *videoFramePointer)
{
	int i1,i2;
	Xil_DCacheInvalidateRange((u32)videoFramePointer,(dispHSize*dispVSize));
	for(i1=0; i1<vOffset; i1++)
	{
		for(i2=0; i2<(dispHSize/3); i2++)
		{
			videoFramePointer[(i1*dispHSize*3) + (i2*3)]	= 0x00;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 1]	= (variant == 1)? 0xcc : 0x00;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 2]	= (variant == 1)? 0x00 : 0xcc;
		}
		for(i2=dispHSize/3; i2<(2*dispHSize/3); i2++)
		{
			videoFramePointer[(i1*dispHSize*3) + (i2*3)]	= 0xee;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 1]	= 0x00;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 2]	= (variant == 1)? 0xcc : 0x00;

		}
		for(i2=2*dispHSize/3; i2<dispHSize; i2++)
		{
			videoFramePointer[(i1*dispHSize*3) + (i2*3)]	= 0x00;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 1]	= (variant == 1)? 0x00 : 0xdd;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 2]	= (variant == 1)? 0xdd : 0x00;
		}
	}
	for(i1=vOffset; i1<vOffset+imageVSize; i1++)
	{
		for(i2=0; i2<hOffset; i2++)
		{
			videoFramePointer[(i1*dispHSize*3) + (i2*3)]	= 0x00;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 1]	= (variant == 1)? 0xcc : 0x00;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 2]	= (variant == 1)? 0x00 : 0xcc;
		}
		for(i2=hOffset; i2<hOffset+imageHSize; i2++)
		{
			videoFramePointer[(i1*dispHSize*3) + (i2*3)]	= (variant == 1)? *imagePointer : *imagePointer;//*imagePointer/16;//(variant == 1)? *imagePointer/16 : 0xcc;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 1]	= (variant == 1)? *imagePointer : *imagePointer/2;//*imagePointer/16;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 2]	= (variant == 1)? *imagePointer/2 : *imagePointer;//*imagePointer/16;//(variant == 1)? *imagePointer/16 : 0x00;
			imagePointer++;
		}
		for(i2=hOffset+imageHSize; i2<dispHSize; i2++)
		{
			videoFramePointer[(i1*dispHSize*3) + (i2*3)]	= 0x00;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 1]	= (variant == 1)? 0x00 : 0xdd;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 2]	= (variant == 1)? 0xdd : 0x00;
		}
	}
	for(i1=vOffset+imageVSize; i1<dispVSize; i1++)
	{
		for(i2=0; i2<(dispHSize/3); i2++)
		{
			videoFramePointer[(i1*dispHSize*3) + (i2*3)]	= 0x00;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 1]	= (variant == 1)? 0xcc : 0x00;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 2]	= (variant == 1)? 0x00 : 0xcc;
		}
		for(i2=dispHSize/3; i2<(2*dispHSize/3); i2++)
		{
			videoFramePointer[(i1*dispHSize*3) + (i2*3)]	= 0xee;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 1]	= 0x00;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 2]	= (variant == 1)? 0xcc : 0x00;

		}
		for(i2=2*dispHSize/3; i2<dispHSize; i2++)
		{
			videoFramePointer[(i1*dispHSize*3) + (i2*3)]	= 0x00;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 1]	= (variant == 1)? 0x00 : 0xdd;
			videoFramePointer[(i1*dispHSize*3) + (i2*3) + 2]	= (variant == 1)? 0xdd : 0x00;
		}
	}
	Xil_DCacheFlush();
	return 1;

}

