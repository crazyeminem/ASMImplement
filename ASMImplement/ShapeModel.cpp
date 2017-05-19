#include "stdafx.h"
#include "shapemodel.h"
#include <random>
namespace ASMMmodel{

	ShapeModel::~ShapeModel()
	{

	}

	// 建立PCA模型
	void ShapeModel::buildPCA()
	{
		Mat_<double> pca_data;
		vector<Mat_<double>> matVec;
		for (auto v:normShape)
		{
			matVec.push_back(static_cast<Mat_<double>>(v));
			cout << v << endl;
		}
		
		pca_data = mergeMatsByCol(matVec);

		pcaShape = new PCA(pca_data, Mat_<double>(), CV_PCA_DATA_AS_COL, sigma);
		double eigValueSum, sCur;
		eigValueSum = sum(pcaShape->eigenvalues)[0];
		sCur = 0;
		//clamp
		clampParameter.create(pcaShape->eigenvalues.rows,1);
		for (int i = 0; i < clampParameter.rows;i++)
		{
			clampParameter(i, 0) = clampFactor*sqrt(pcaShape->eigenvalues.at<double>(i, 0));

		}
		projectedShape = pcaShape->project(pca_data);
		reconstructedShape = pcaShape->backProject(projectedShape);

		
	}
	//归一化形状
	void ShapeModel::normalizeShapes()
	{
		//clone
		for (auto sp:alShapeVec)
		{
			ShapeVector s = sp.clone();
			normShape.push_back(s);
		}
		for (int i = 0; i < normShape.size();i++)
		{
			normShape[i].COGToZero();
			normShape[i].normalizeToOne();

		}
	}

	// Procrustes对齐
	void ShapeModel::procrustesAlign()
	{
		ShapeVector C= Mat_<double>::zeros(nPoints * 2, 1);
		ShapeVector C_Pre = Mat_<double>::zeros(nPoints * 2, 1);
		//最大迭代次数itol，收敛阈值itof
		for (int i = 0; i < itol;i++)
		{
			//计算平均形状C
			
			for (auto v : normShape)
			{
				C += v;
				//cout << v << endl;
			}
			C = C / nSamples;
			//cout << C << endl;
			//再归一化
			C.normalizeToOne();

			double err = norm(C, C_Pre);
			cout << err << endl;
			if (i>0)
			{
  
				if (err<=ftol)
				{
					break;
				}
			}
			//向平均形状对齐
			for (int i = 0; i < normShape.size();i++)
			{
				//cout << normShape[i] << endl;
				normShape[i].alignTo(C);
				//cout << normShape[i] << endl;
			}
			C_Pre = C.clone();

		}
		meanShape = C;
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
		normalizeShapes();
		/*
		TODO
		*/
		procrustesAlign();
		buildPCA();
	}

	// 显示模型
	void ShapeModel::showModel()
	{
		this->meanShape.show();
		//测试模型
		Mat_<double> debug_param = clampParameter.clone();
		Rect_<double> rect1 = meanShape.getBoundRect();
		Rect_<double>rect2 = alShapeVec[0].getBoundRect();
		Point2f m1[4];
		Point2f m2[4];
		m1[0] = Point2f(rect1.x, rect1.y);
		m1[1] = Point2f(rect1.x + rect1.width, rect1.y);
		m1[2] = Point2f(rect1.x + rect1.width, rect1.y + rect1.height);
		m1[3] = Point2f(rect1.x, rect1.y + rect1.height);
		m2[0] = Point2f(rect2.x, rect2.y);
		m2[1] = Point2f(rect2.x + rect2.width, rect2.y);
		m2[2] = Point2f(rect2.x + rect2.width, rect2.y + rect2.height);
		m2[3] = Point2f(rect2.x, rect2.y + rect2.height);
		Mat m;
		m = getAffineTransform(m1, m2);
		ShapeVector debug_affine;
		warpAffine(meanShape, debug_affine, m, meanShape.size());
		cout << "dst" << alShapeVec[0] << endl;
		cout << "debug"<<debug_affine << endl;
		debug_affine.show();
		cout << m;
		ShapeVector s1 = (Mat_<double>(8, 1) << rect1.x, rect1.y, rect1.x + rect1.width, rect1.y, rect1.x + rect1.width, rect1.y + rect1.height, rect1.x, rect1.y + rect1.height);
		ShapeVector s2 = (Mat_<double>(8, 1) << rect2.x, rect2.y, rect2.x + rect2.width, rect2.y, rect2.x + rect2.width, rect2.y + rect2.height, rect2.x, rect2.y + rect2.height);
		//s1.alignTo(s2);
		//Mat_<double> debug11 = pcaShape->mean + pcaShape->eigenvectors.t()*debug_param;
		//ShapeVector debug_sv11(debug11);
		//s1.at.transform(debug_sv11, debug_sv11);
		//s2.show();
		//s1.show();
		//debug_sv11.show();
		//waitKey(0);
		while (1)
		{
			Mat_<double> debug = pcaShape->mean + pcaShape->eigenvectors.t()*debug_param;
			ShapeVector debug_sv(debug);
			debug_sv.alignTo(alShapeVec[0]);
			cout << "a:" << debug_sv.at.a << endl;
			cout << "b:" << debug_sv.at.b << endl;
			cout << "Tx:" << debug_sv.at.Tx << endl;
			cout << "Ty:" << debug_sv.at.Ty << endl;
			debug_sv.at.transform(s1,s1);
			s1.show();
			namedWindow("boundRect");
			Mat imgte = Mat::zeros(Size(255, 255),CV_8U);
			rectangle(imgte, debug_sv.getBoundRect(), Scalar(255, 255, 255));
			rectangle(imgte, alShapeVec[0].getBoundRect(), Scalar(255, 255, 255));
			imshow("boundRect", imgte);
			waitKey(0);
			cout << "shape1" << alShapeVec[0] << endl;
			cout << "shape align" << debug_sv << endl;
			vector<Point> pts = debug_sv.vec2Pts();
			debug_sv.show();
			for (int i = 0; i < debug_param.rows; i++)
			{
				default_random_engine e;
				uniform_real_distribution<double> u(0, 1);
				if (u(e) < 0.8)
				{
					continue;
				}
				debug_param(i, 0) *= u(e);
			}

		}

	}
	void ShapeModel::write(const string filename)
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