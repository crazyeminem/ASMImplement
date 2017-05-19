#ifndef _ASM_H_
#define _ASM_H_
#include "shapemodel.h"
#include "asmimages.h"
namespace ASMMmodel{
	class ASM
	{
	public:
		ASM();
		~ASM();
		//构建灰度模型
		void buildGrayModel();
		//构建asm模型
		void buildModel();
		//搜索与拟合
		//param:srcImage 需要搜索与拟合的图像
		//param:boundrect 目标所在大致区域，用以初始化形状参数
		//return:拟合出的点集
		vector<Point> fit(Mat srcImage,Rect boundRect){

		}
		ShapeModel shapemodel;
		//每个特征点的均值金字塔
		vector<vector<Mat_<double>>> meanG;
		//每个特征点的协方差金字塔
		vector<vector<Mat_<double>>> covarG;
		//权值矩阵
		Mat_<double> W;
		//形状参数b
		Mat_<double> b;
		//局部特征搜索半径
		int k;
		
	};
}


#endif

