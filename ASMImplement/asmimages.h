#ifndef _ASMIMAGES_H_
#define _ASMIMAGES_H_
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <string>
#include <map>
#include "opencv2/highgui.hpp"
#include "shapevector.h"
#include "TrainingSetInfo.h"
using namespace cv;
using namespace std;
namespace ASMMmodel{
	class AsmImages
	{
	public:
		AsmImages(ShapeInfo sp, int n = 7, int npy = 3) :shapeInfo(sp), np(n), nPyramids(npy), filename(sp.imgname){ loadShapeInfo = 1; }//自定义采样数，金字塔层数
		~AsmImages(){}
		AsmImages(int n=7,int npy=3):np(n),nPyramids(npy){};
		int nPoints;//点数
		int np;//局部灰度模型的采样长度,应该为奇数，中心在特征点
		int nPyramids;//金字塔层数
		bool isEmpty=1;
		bool loadShapeInfo = 0;
		bool shapeLoaded = 0;
		vector<Mat>imgPyramid;//图像金字塔
		vector<Mat_<uchar>>gryPyramid;//灰度金字塔
		vector<Mat_<double>>gradientPyramid;//梯度金字塔
		string filename;//图像名（绝对路径）
		Mat srcImage;//原始训练图像
		ShapeVector shape;
		ShapeInfo shapeInfo;//形状信息
		map<int,vector<Mat_<double>>> LocalFeatureMap;//各层局部特征
		vector<Point> pts;//特征点集
		// 计算所有层局部特征
		void getLocalStructuresMap();
		//计算某层图局部特征
		Mat_<double> localGrysStrcut(int pId,int level ,double step=1.0);
		//返回level层图像
		Mat& getTrainImage(int level);
		// 返回level层的梯度图
		Mat& getGradientImage(int level);
		// 载入图像
		bool loadImage(const Mat& img);
		// 载入图像
		bool loadImage(const string& imgname);
		//判空（未载入图像）
		bool empty();
		//从shapeinfo读取shapevector
		void loadShapeVec();
		void loadShapeVec(const ShapeVector &spvec);
		//读取特征点集
		void loadPts();
		//采样profile normal
		//param pId 当前点id
		//param level 所在图像层
		//param normPoints 所需法线点集
		//param pOffset 搜索中心
		//param rad 搜索半径
		//param step 步长
		void getNormalPoints(int pId,int rad,int level, vector<Point> &normPoints,int pOffset=0,double step=1.0);
		//初始化图像信息
		void init_build();
		//搜索最佳点位置
		void show(int l);
		void refresh(const ShapeVector &newshape);
	};
}
#endif