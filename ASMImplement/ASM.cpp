#include "stdafx.h"
#include "ASM.h"
namespace ASMMmodel{
	ASM::ASM()
	{
	}
	ASM::~ASM()
	{
	}
	void ASM::buildModel(const char* xmlFile)
	{
		shapemodel.buildModel(xmlFile);
		buildGrayModel();
		
	}
	void ASM::initPose()//初始化位置，方法待修改
	{
		//随机对齐到某一训练样本
		default_random_engine e;
		uniform_int_distribution<int> u(0, shapemodel.alShapeVec.size() - 1);
		shapevec = shapemodel.meanShape.clone();
		shapevec.alignTo(shapemodel.alShapeVec[u(e)]);

	}
	vector<Point> ASM::fit(const Mat &srcImage)
	{
		initPose();
		imageToFit.loadImage(srcImage);
		imageToFit.loadShapeVec(shapevec);
		imageToFit.init_build();


	}
	vector<Point>ASM::fit(const string ImageFileNmae)
	{
		Mat srcImage = imread(ImageFileNmae);
		return fit(srcImage);
	}
	void ASM::buildGrayModel()
	{
		np = (shapemodel.nSampleLength() - 1) / 2;
		for (int level = 0; level < shapemodel.nPyramid();level++)//层
		{
	
			vector<Mat_<double>> vm;
			vector<Mat_<double>> cm;
			for (int p = 0; p < shapemodel.nPoint();p++)//点
			{
				Mat_<double> m=Mat_<double>::zeros(np,1);
				vector<Mat_<double>> alFeature;
				for (int i = 0; i < shapemodel.nSample();i++)//样本
				{
					m += (shapemodel.imgSet[i].LocalFeatureMap[level])[p];
					Mat_<double> tp = (shapemodel.imgSet[i].LocalFeatureMap[level])[p].clone();
					alFeature.push_back(tp);
				}
				m = 1 / shapemodel.nSample()*m;
				vm.push_back(m);//第i个点在level层的平均特征
				Mat_<double> alF=mergeMatsByCol(alFeature);
				Mat_<double> covar;
				calcCovarMatrix(alF, covar, Mat_<double>(), CV_COVAR_COLS);
				cm.push_back(covar);
			}
			grayFeatureMap[level] = vm;
			covarMap[level] = cm;
		}

	}
	void ASM::shiftThroughGrayStructure()
	{
		
	}
	void ASM::fitGrayStructure(int level)//寻找特征点最佳匹配
	{
		double minDis = 65534;
		for (int i = 0; i < shapevec.nPoints();i++)//特征点i
		{
			for (int offset = k; offset >= -k;offset--)//搜索半径k，长度2k+1
			{
				vector<Point> V;
				Mat_<double> localFeaure=Mat_<double>::zeros(2*np+1,1);
				Mat_<double> deriveImage = imageToFit.gradientPyramid[level];
				imageToFit.getNormalPoints(i, np, level, V,offset);
				double absSum = 0;
				for (int i = -np; i <= np;i++)
				{
					localFeaure(i + np,0) = deriveImage(V[i + np]);
					absSum += fabs(localFeaure(i + np, 0));//L1范数
				}
				localFeaure *= 1 / absSum;
				//计算马氏距离
				Mahalanobis(localFeaure, (grayFeatureMap[level])[i], (covarMap[level])[i]);

			}
		}
	}
}

