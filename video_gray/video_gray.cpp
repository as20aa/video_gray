// video_gray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main()
{
	//测试图书馆环境下的人体轮廓识别大概阈值范围为61（目前阈值可调，可以自行调节到合适的范围）
	VideoCapture video;
	int deviceid = 0;//打开默认的相机
	int apiid = cv::CAP_ANY;//打开默认的相机
	int threhold = 1; int maxthrehold = 100; int ratio = 3;
	int blur_size = 3; int max_blur_size = 10;
	video.open(deviceid + apiid);
	if (!video.isOpened())
	{
		return -1;
	}
	namedWindow("gray", WINDOW_AUTOSIZE);
	//cvResizeWindow("gray", 500, 500);
	moveWindow("gray", 500, 150);
	//对阈值的控制
	createTrackbar("threhold", "gray", &threhold, maxthrehold, nullptr);
	//对高斯核大小的控制
	createTrackbar("blur", "gray", &blur_size, max_blur_size, nullptr);
	Mat frame,gray;
	for (;;)
	{
		video.read(frame);
		if (frame.empty()) {
			break;
		}
		cvtColor(frame, gray, COLOR_BGR2GRAY);
		blur(gray, gray, Size(blur_size, blur_size));
		Canny(gray, gray, threhold, ratio*threhold, 3, false);
		imshow("Live", frame);
		imshow("gray", gray);
		if (waitKey(2) >= 0)
		{
			break;
		}
	}
	video.release();
    return 0;
}
