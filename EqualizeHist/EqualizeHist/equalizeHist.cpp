#include "equalizeHist.h"

EqualizeHist::EqualizeHist()
{
	for (int i = 0; i<256; i++)
	{
		pixelArr[i] = 0;
		sumPixelArr[i] = 0;
	}
	pixelMax = 0;
	pixelMin = 256;

}

EqualizeHist::~EqualizeHist()
{

}

void EqualizeHist::process(Mat src, Mat& dst)
{
	for (int i = 0; i<256; i++)
	{
		pixelArr[i] = 0;
		sumPixelArr[i] = 0;
	}
	pixelMax = 0;
	pixelMin = 256;

	int width = src.cols;
	int height = src.rows;
	dst.create(Size(width,height),src.type());

	for (int i = 0; i< height; i++)
	{
		for (int j = 0; j< width; j++)
		{
			pixelArr[src.at<uchar>(i,j)] += 1;

			pixelMax = pixelMax>src.at<uchar>(i,j)?pixelMax:src.at<uchar>(i,j);

			pixelMin = pixelMin<src.at<uchar>(i,j)?pixelMin:src.at<uchar>(i,j);

		}
	}

	for (int i = 0; i< 256; i++)
	{
		pixelArr[i] /= width*height;

		for (int j = 0; j<= i; j++)
		{
			sumPixelArr[i] += pixelArr[j];
		}
	}



	for (int i = 0; i<height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			int temp11 = src.at<uchar>(i,j);

			float temp1 = sumPixelArr[temp11]*(pixelMax-pixelMin)+(pixelMin);

			dst.at<uchar>(i,j) = temp1;

		}

	}
}