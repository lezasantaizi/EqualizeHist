#ifndef EQUALIZE_HIST
#define EQUALIZE_HIST

#include<iostream>
#include "../3rdparty/include/opencv.hpp"
#include<math.h>
#include <vector>
using namespace std;
using namespace cv;

class EqualizeHist
{
public:
	float pixelArr[256] ;
	float sumPixelArr[256] ;

	int pixelMax ;
	int pixelMin ;
	EqualizeHist();
	~EqualizeHist();

	void process(Mat src, Mat& dst);


};
#endif