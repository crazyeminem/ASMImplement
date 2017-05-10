#ifndef _SHAPEMODEL_H_
#define _SHAPEMODEL_H_
#include "shapevector.h"
#include "affinetransform.h"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <vector>
#include "TrainingSetInfo.h"
#include "asmimages.h"
using cv::Mat_;
using cv::PCA;
using std::vector;
namespace ASMMmodel{
	class AsmImages;
	class ShapeModel
	{
	public:

		ShapeModel();
		~ShapeModel();

		int pyramidLevel;//金字塔层数
		double pcaRatio;//PCA主成分比
		int nPoints;//标记点数
		int nSamples;//样本数
		vector < AsmImages > imgSet;//训练图像信息集
		TrainingSetInfo alShapeInfo;//形状信息集
		ShapeVector meanShape;//平均形状
		Mat_<double> alShapeVecMat;//所有样本形状向量
		vector<ShapeVector> alShapeVec;
		
		PCA *pcaShape;//PCA模型

		// 建立PCA模型
		void buildPCA();
		// Procrustes对齐
		void procrustesAlign();
		// 建立模型
		void buildModel();
		
		// 显示模型
		void showModel();
	};
}
#endif
