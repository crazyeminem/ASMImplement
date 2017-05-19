// ASMImplement.cpp : 定义控制台应用程序的入口点。
//
#include "TrainingSetInfo.h"
#include "ASMImplement.h"
using namespace ASMMmodel;
using namespace std;
using namespace cv;
int main()
{
	ShapeModel spModel;
	spModel.buildModel("midfinger.xml");
	spModel.imgSet[0].show(0);
	spModel.showModel();
	return 0;
}
