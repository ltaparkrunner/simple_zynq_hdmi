
#ifndef VIDPROCESS_H_   /* prevent circular inclusions */
#define VIDPROCESS_H_

#include "xil_types.h"
#include "xil_cache.h"
//#include "xaxidma.h"
#include "xscugic.h"

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
		char *videoFramePointer);

int fillFrameBuffer2(
u32 variant,
u32 dispHSize,
u32 dispVSize,
u32 imageHSize,
u32 imageVSize,
u32 hOffset,
u32 vOffset,
int numColors,
char *imagePointer,
char *videoFramePointer,
s32 offset);

#endif /* end of protection macro */
