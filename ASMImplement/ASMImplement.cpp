// ASMImplement.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "TrainingSetInfo.h"
#include "ASMImplement.h"
using namespace ASMMmodel;
using namespace std;
using namespace cv;
int main()
{
	ASM debugSVM;
	debugSVM.buildModel("midep.fad");
	debugSVM.fit("test.jpg");
	system("pause");
	return 0;
}
