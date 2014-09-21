#include "equalizeHist.h"

#ifdef _DEBUG
#pragma comment(lib, "opencv_highgui249d.lib")
#pragma comment(lib, "opencv_imgproc249d.lib")
#pragma comment(lib, "opencv_core249d.lib")
#else
#pragma comment(lib, "opencv_highgui249.lib")
#pragma comment(lib, "opencv_imgproc249.lib")
#pragma comment(lib, "opencv_core249.lib")
#endif

int main(int argc, char** argv)
{
	const char* filename = argc >= 2 ? argv[1] : "hello.jpg";
	Mat src = imread(filename,1);

	if(src.empty())
	{
		cout << "can not open " << filename << endl;
		return -1;
	}
	Mat dst;
	imshow("hello",src);

	Mat imageChannel[3] ;
	EqualizeHist eh;
	
	//split hsv image
	cvtColor(src,dst,CV_BGR2HSV);
	imshow("hsv",dst);
	split(dst,imageChannel);
	imshow("imageChannel_V",imageChannel[2]);

	Mat temp;
	eh.process(imageChannel[2],temp);
	imshow("temp",temp);
	imageChannel[2] = temp;

	Mat dst2;
	merge(imageChannel,3,dst2);
	imshow("dst",dst2);
	imshow("diff",dst2-dst);

	//split rgb image 
	split(src,imageChannel);
	Mat tempR,tempG,tempB;
	eh.process(imageChannel[0],tempB);
	imageChannel[0] = tempB;
	eh.process(imageChannel[1],tempG);
	imageChannel[1] = tempG;
	eh.process(imageChannel[2],tempR);
	imageChannel[2] = tempR;
	Mat newDst;
	merge(imageChannel,3,newDst);
	imshow("newDst",newDst);


	waitKey(0);
}