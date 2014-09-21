#include<iostream>
#include "../3rdparty/include/opencv.hpp"
#include<math.h>
#include <vector>
using namespace std;
using namespace cv;

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
	const char* filename = argc >= 2 ? argv[1] : "hello4.jpg";
	Mat src = imread(filename,1);

	if(src.empty())
	{
		cout << "can not open " << filename << endl;
		return -1;
	}
	Mat dst;
	src.copyTo(dst);
	imshow("hello",src);

	float pixelArrR[256] = {0};
	float pixelArrG[256] = {0};
	float pixelArrB[256] = {0};

	float sumPixelArrR[256] = {0};
	float sumPixelArrG[256] = {0};
	float sumPixelArrB[256] = {0};

	int width = src.cols;
	int height = src.rows;

	int pixelMax[3] = {0};
	int pixelMin[3] = {256};

	for (int i = 0; i< height; i++)
	{
		for (int j = 0; j< width; j++)
		{
			pixelArrR[src.at<Vec3b>(i,j)[2]] += 1;
			pixelArrG[src.at<Vec3b>(i,j)[1]] += 1;
			pixelArrB[src.at<Vec3b>(i,j)[0]] += 1;

			pixelMax[0] = pixelMax[0]>src.at<Vec3b>(i,j)[0]?pixelMax[0]:src.at<Vec3b>(i,j)[0];
			pixelMax[1] = pixelMax[1]>src.at<Vec3b>(i,j)[1]?pixelMax[1]:src.at<Vec3b>(i,j)[1];
			pixelMax[2] = pixelMax[2]>src.at<Vec3b>(i,j)[2]?pixelMax[2]:src.at<Vec3b>(i,j)[2];

			pixelMin[0] = pixelMin[0]<src.at<Vec3b>(i,j)[0]?pixelMin[0]:src.at<Vec3b>(i,j)[0];
			pixelMin[1] = pixelMin[1]<src.at<Vec3b>(i,j)[1]?pixelMin[1]:src.at<Vec3b>(i,j)[1];
			pixelMin[2] = pixelMin[2]<src.at<Vec3b>(i,j)[2]?pixelMin[2]:src.at<Vec3b>(i,j)[2];
		}
	}

	for (int i = 0; i< 256; i++)
	{
		pixelArrR[i] /= width*height;
		pixelArrG[i] /= width*height;
		pixelArrB[i] /= width*height;

		for (int j = 0; j<= i; j++)
		{
			sumPixelArrR[i] += pixelArrR[j];
			sumPixelArrG[i] += pixelArrG[j];
			sumPixelArrB[i] += pixelArrB[j];
		}
	}



	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			int temp11 = src.at<Vec3b>(i,j)[2];
			int temp22 = src.at<Vec3b>(i,j)[1];
			int temp33 = src.at<Vec3b>(i,j)[0];
			float temp1 = sumPixelArrR[temp11]*(pixelMax[2]-pixelMin[2])+(pixelMin[2]);
			float temp2 = sumPixelArrG[temp22]*(pixelMax[1]-pixelMin[1])+(pixelMin[1]);
			float temp3 = sumPixelArrB[temp33]*(pixelMax[0]-pixelMin[0])+(pixelMin[0]);
			dst.at<Vec3b>(i,j)[2] = temp1;
			dst.at<Vec3b>(i,j)[1] = temp2;
			dst.at<Vec3b>(i,j)[0] = temp3;
		}

	}

	imshow("dst",dst);

	waitKey(0);
}