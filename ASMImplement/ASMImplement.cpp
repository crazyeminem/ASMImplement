// ASMImplement.cpp : 定义控制台应用程序的入口点。
//
#include "TrainingSetInfo.h"
#include "ASMImplement.h"
#include "Preprocess.h"
using namespace ASMMmodel;
using namespace std;
using namespace cv;
int main()
{
	ASM debugSVM;
	
	Mat srcImage = imread("test.jpg", 0);
	Rect bRect = getPhalanxEpiphysis(srcImage); 
	debugSVM.buildModel("epiphsis.fad");
	debugSVM.fit("test.jpg",bRect);
	system("pause");
	return 0;
}
