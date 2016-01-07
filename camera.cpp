#include "stdio.h"
#include "ASICamera.h"
#include <sys/time.h>
#include <time.h>

static unsigned long GetTickCount()
{
   #ifdef FAKE
   #else 
   struct timespec ts;
   clock_gettime(CLOCK_MONOTONIC,&ts);
   return (ts.tv_sec*1000 + ts.tv_nsec/(1000*1000));
   #endif
}

int  camera_init()
{
	int width;
	int height;
	int i;
	char c;
	bool bresult;
	unsigned char *pdata;

	int time1,time2;
	int count=0;

	char buf[128]={0};

	int CamNum=0;
	
	///long exposure, exp_min, exp_max, exp_step, exp_flag, exp_default;
	//long gain, gain_min, gain_max,gain_step, gain_flag, gain_default;

//	IplImage *pRgb;


	int numDevices = getNumberOfConnectedCameras();
	if(numDevices <= 0)
	{
		printf("no camera connected\n");
		return -1;
	}
	CamNum = 0;


	bresult = openCamera(CamNum);
	if(!bresult)
	{
		printf("OpenCamera error,are you root?,press any key to exit\n");
		return -1;
	}
	initCamera(); //this must be called before camera operation. and it only need init once
	
	printf("%s information\n",getCameraModel(CamNum));
	printf("resolution:%dX%d\n", getMaxWidth(),getMaxHeight());
	pdata = new unsigned char[getMaxWidth()*getMaxHeight()*2];
	
 	width = 1280;
	height = 960;


	
	
	while(!setImageFormat(width, height, 1, IMG_RAW16)) {
		printf("incorrect image size\n");
		return -1;	
	}
	setValue(CONTROL_EXPOSURE, 33*1000, true); //auto exposure
	setValue(CONTROL_GAIN,50, true); //auto exposure
	setValue(CONTROL_BANDWIDTHOVERLOAD, getMin(CONTROL_BANDWIDTHOVERLOAD), false); //lowest transfer speed

	startCapture(); //start privew

	time1 = GetTickCount();

	int count2 = 0;
	while(1)
	{

		getImageData(pdata,width*height , -1);

		count++;
		time2 = GetTickCount();
		if(time2-time1 > 1000 )
		{
			sprintf(buf, "fps:%d dropped frames:%lu",count, getDroppedFrames());
			printf("%s\n",buf);
			count = 0;
			time1=GetTickCount();


		}

	}
END:
	delete pdata;
	stopCapture();
	printf("over\n");
	return 1;
}






