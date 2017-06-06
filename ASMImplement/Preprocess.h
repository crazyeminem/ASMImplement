#ifndef _PREPROCESS_H_
#define _PREPROCESS_H_
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
#include <iostream>

enum Reg
{
	Epiphysis = 0,//����
	Carpals = 1//���
};
enum Epi
{
	Epi_Thumbs = 0,//Ĵָ
	Epi_MFingers = 1,//��ָ
	Epi_LFingers = 2,//Сָ
	Epi_Ulna = 3,//���
	Epi_Radius = 4//�߹�
};
double dis(cv::Point a, cv::Point b);
std::vector<int> calcXavg(cv::Mat y_gradient);
std::vector<int> getLocalMax(std::vector<int> Xavg, int type = 0/*�ǽṹ����*/);
cv::Rect getPhalanxEpiphysis(cv::Mat srcImage, int PhalanxType = Epi_MFingers);
#endif