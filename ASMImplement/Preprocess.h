#ifndef _PREPROCESS_H_
#define _PREPROCESS_H_
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
#include <iostream>

enum Reg
{
	Epiphysis = 0,//骨骺
	Carpals = 1//腕骨
};
enum Epi
{
	Epi_Thumbs = 0,//拇指
	Epi_MFingers = 1,//中指
	Epi_LFingers = 2,//小指
	Epi_Ulna = 3,//桡骨
	Epi_Radius = 4//尺骨
};
double dis(cv::Point a, cv::Point b);
std::vector<int> calcXavg(cv::Mat y_gradient);
std::vector<int> getLocalMax(std::vector<int> Xavg, int type = 0/*骨结构类型*/);
cv::Rect getPhalanxEpiphysis(cv::Mat srcImage, int PhalanxType = Epi_MFingers);
#endif