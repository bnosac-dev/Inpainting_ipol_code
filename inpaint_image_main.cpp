
//main function for the image inpainting routine


#include <cstring>
#include <cstdio>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "image_inpainting.h"

int main(int argc, char* argv[])
{
	time_t startTime,stopTime;

	const char *fileIn = (argc >= 2) ? argv[1] : "American.png";
	const char *fileInOcc = (argc >= 3) ? argv[2] : "American_occlusion.png";
	const char *fileOut = (argc >= 4) ? argv[3] : "American_inpainted";
	
	bool useFeatures=true;
	
	time(&startTime);//startTime = clock();
	
	inpaint_image(fileIn,fileInOcc,fileOut,useFeatures);
	
	time(&stopTime);
	printf("\n\nTotal execution time: %f\n",fabs(difftime(startTime,stopTime)));
	//MY_PRINTF("\n\nTotal execution time: %f\n",((double)(clock()-startTime)) / CLOCKS_PER_SEC);

	
	return(0);

}
