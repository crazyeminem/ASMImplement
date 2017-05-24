#ifndef _ASM_H_
#define _ASM_H_
#include "shapemodel.h"
#include "asmimages.h"
#include <random>
namespace ASMMmodel{
	class ASM
	{
	public:
		ASM();
		~ASM();
		//构建灰度模型
		void buildGrayModel();
		//构建asm模型
		void buildModel(const char* xmlFile);
		//搜索与拟合
		//param:srcImage 需要搜索与拟合的图像
		//return:拟合出的点集
		vector<Point> fit(const Mat &srcImage);
		vector<Point> fit(const string ImageFileNmae);
		//初始位置确定
		void initPose();
		void initPose(Rect_<double> bRect);
		//根据局部灰度特征移动特征点
		void shiftThroughGrayStructure();
		void fitGrayStructure(int level);


		ShapeModel shapemodel;
		ShapeVector shapevec;
		vector<Point_<int>> fitPts;
		AsmImages  imageToFit;
		//灰度结构特征(均值)金字塔
		map<int, vector<Mat_<double>>> grayFeatureMap;
		//每个特征点的协方差金字塔
		map<int, vector<Mat_<double>>> covarMap;
		//权值矩阵
		Mat_<double> W;
		//形状参数b
		Mat_<double> b;
		//局部特征搜索半径
		int k=5;
		//局部特征采样半径
		int np;
		
	};
}


#endif

