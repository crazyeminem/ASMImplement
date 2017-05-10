// ASMImplement.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "TrainingSetInfo.h"
#include "ASMImplement.h"
using namespace ASMMmodel;
using namespace std;
using namespace cv;
int main()
{
	ShapeModel spModel;
	spModel.alShapeInfo.loadFromXml("test6.xml");
	ShapeInfo spInfo = spModel.alShapeInfo.alShapeInfos[0];
	AsmImages asImg(spInfo);
	cout << asImg.filename << endl;
	asImg.loadImage("20160117261153_0.jpg");
	asImg.loadShapeVec();
	asImg.loadPts();
	Mat_<double>gryFeature=asImg.localGrysStrcut(0, 0, 0.5);
	cout << gryFeature;
	return 0;
}
