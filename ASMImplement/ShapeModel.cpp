#include "stdafx.h"
#include "shapemodel.h"

namespace ASMMmodel{
	ShapeModel::ShapeModel()
	{
	}


	ShapeModel::~ShapeModel()
	{
	}

	// 建立PCA模型
	void ShapeModel::buildPCA()
	{
	}


	// Procrustes对齐
	void ShapeModel::procrustesAlign()
	{

	}

	// 建立模型
	void ShapeModel::buildModel(const char* shapeInfoFile)
	{
		vector<Mat_<double>> matVec;
		alShapeInfo.loadFromXml(shapeInfoFile);
		nSamples = alShapeInfo.alShapeInfos.size();
		nPoints = alShapeInfo.alShapeInfos[0].ptsInfos.size();
		for (auto sp:alShapeInfo.alShapeInfos)
		{
			AsmImages asImg(sp);
			asImg.init_build();
			imgSet.push_back(asImg);
			alShapeVec.push_back(asImg.shape);
			matVec.push_back(static_cast<Mat_<double>>(asImg.shape));
		}
		alshapeMat = mergeMatsByCol(matVec);
	}


	// 显示模型
	void ShapeModel::showModel()
	{
	}
	template<typename T>
	Mat_<T> mergeMatsByCol(const vector<Mat_<T>> &Mats)
	{
		if (Mats.empty())
		{
			return Mat_<T>();
		}

		int totalcol = 0;
		int rows = Mats[0].rows;
		auto typ = Mats[0].type();
		for (auto m : Mats)
		{
			totalcol += m.cols;
			CV_Assert(rows == m.rows&&m.type() == typ);
		}
		Mat_<T> mergedMat(rows, totalcol, typ);
		int pos = 0;
		for (auto it = Mats.begin(); it != Mats.end(); ++it)
		{
			(*it).copyTo(mergedMat.colRange(pos, pos + (*it).cols));
			pos += (*it).cols;
		}
		return mergedMat;
	}
}