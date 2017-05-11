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
	class ShapeModel
	{
	public:

		ShapeModel();
		~ShapeModel();
		int pyramidLevel=3;//����������
		double pcaRatio;//PCA���ɷֱ�
		int nPoints;//��ǵ���
		int nSamples;//������
		double sigma=0.95;//Pca��������Ϣ��
		vector < AsmImages > imgSet;//ѵ��ͼ����Ϣ��
		TrainingSetInfo alShapeInfo;//��״��Ϣ��
		ShapeVector meanShape;//ƽ����״
		Mat_<double> alshapeMat;//����������״����
		Mat_<double> alignShapes;//��������
		vector<ShapeVector> alShapeVec;


		PCA *pcaShape;//PCAģ��

		void setPyramid(int pl){ pyramidLevel = pl; }
		// ����PCAģ��
		void buildPCA();
		// Procrustes����
		void procrustesAlign();
		// ����ģ��
		void buildModel(const char* shapeInfoFile);
		
		// ��ʾģ��
		void showModel();
	}; 
	template<typename T>
	Mat_<T> mergeMatsByCol(const vector<Mat_<T>> &Mats);
}

#endif
