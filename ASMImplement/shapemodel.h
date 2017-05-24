#ifndef _SHAPEMODEL_H_
#define _SHAPEMODEL_H_
#include "shapevector.h"
#include "affinetransform.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
#include "TrainingSetInfo.h"
#include "asmimages.h"
#include <random>
using cv::Mat_;
using cv::PCA;
using std::vector;
namespace ASMMmodel{
	class ShapeModel
	{
	public:

		ShapeModel(int py = 3, int it = 100, double ft = 1e-8, double si=0.95):pyramidLevel(py),itol(it),ftol(ft),sigma(si){};
		~ShapeModel();
		
		vector < AsmImages > imgSet;//训练图像信息集
		TrainingSetInfo alShapeInfo;//形状信息集
		ShapeVector meanShape;//平均形状
		Mat_<double> alshapeMat;//所有原始样本形状向量
		vector<ShapeVector> normShape;//归一化向量
		vector<ShapeVector> alShapeVec;

		

		PCA *pcaShape;//PCA模型
		PCA *pcaFullShape;
		Mat_<double> clampParameter;
		Mat_<double> projectedShape;
		Mat_<double>reconstructedShape;
		//归一化
		void normalizeShapes();
		// 建立PCA模型
		void buildPCA();
		// Procrustes对齐
		void procrustesAlign();
		// 建立模型
		void buildModel(const char* shapeInfoFile);
		
		// 显示模型
		void showModel();
		//返回点数
		int  nPoint(){ return nPoints; }
		//返回样本数
		int nSample(){ return nSamples; }
		//返回金字塔层数
		int nPyramid(){ return pyramidLevel; }
		//设置建模参数，迭代次数itol，收敛阈值ftol，pca参数sigma,采样长度，金字塔层数
		void setParam(int it, double ft, double si,int sl,int pl)
		{
			itol = it;
			ftol = ft;
			sigma = si;
			np = sl;
			pyramidLevel = pl;
		}
		int nSampleLength(){ return np; }
		void write(const string filename);
	private:
		int itol = 100;//最大迭代次数
		double ftol = 1e-8;//收敛阈值
		double sigma = 0.95;//Pca参数，信息比

		int np = 7;//采样长度
		int pyramidLevel = 3;//金字塔层数
		int nPoints;//标记点数
		int nSamples;//样本数
		int clampFactor = 2;
	}; 
	template<typename T>
	Mat_<T> mergeMatsByCol(const vector<Mat_<T>> &Mats);
}

#endif
