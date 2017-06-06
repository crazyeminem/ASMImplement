#ifndef _ASM_H_
#define _ASM_H_
#include "shapemodel.h"
#include "asmimages.h"
#include <random>
#include<set>
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
		vector<Point> fit(const string &ImageFileName);
		vector<Point> fit(const string &imageFileName, const Rect &bRect);
		//初始位置确定
		void initPose();
		void initPose(Rect bRect);
		//根据局部灰度特征移动特征点
		void iterateSearch();
		void iterateSearch(int level);
		void showResult(int level=0);
		void showResult(vector<Point>FitPoints,int level,int i);


		ShapeModel shapemodel;
		ShapeVector shapevec;
		vector<Point_<int>> fitPts;
		AsmImages  imageToFit;
		ShapeInfo spInfo;
		//灰度结构特征(均值)金字塔
		map<int, vector<Mat_<double>>> grayFeatureMap;
		//每个特征点的协方差金字塔
		map<int, vector<Mat_<double>>> icovarMap;
		//权值矩阵
		Mat_<double> W;
		//形状参数b
		Mat_<double> b;
		//局部特征搜索半径
		int k=9;
		//局部特征采样半径
		int np;
		
	};
}


#endif

