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
		
		vector < AsmImages > imgSet;//ѵ��ͼ����Ϣ��
		TrainingSetInfo alShapeInfo;//��״��Ϣ��
		ShapeVector meanShape;//ƽ����״
		Mat_<double> alshapeMat;//����ԭʼ������״����
		vector<ShapeVector> normShape;//��һ������
		vector<ShapeVector> alShapeVec;

		

		PCA *pcaShape;//PCAģ��
		PCA *pcaFullShape;
		Mat_<double> clampParameter;
		Mat_<double> projectedShape;
		Mat_<double>reconstructedShape;
		//��һ��
		void normalizeShapes();
		// ����PCAģ��
		void buildPCA();
		// Procrustes����
		void procrustesAlign();
		// ����ģ��
		void buildModel(const char* shapeInfoFile);
		
		// ��ʾģ��
		void showModel();
		//���ص���
		int  nPoint(){ return nPoints; }
		//����������
		int nSample(){ return nSamples; }
		//���ؽ���������
		int nPyramid(){ return pyramidLevel; }
		//���ý�ģ��������������itol��������ֵftol��pca����sigma,�������ȣ�����������
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
		int itol = 100;//����������
		double ftol = 1e-8;//������ֵ
		double sigma = 0.95;//Pca��������Ϣ��

		int np = 7;//��������
		int pyramidLevel = 3;//����������
		int nPoints;//��ǵ���
		int nSamples;//������
		int clampFactor = 2;
	}; 
	template<typename T>
	Mat_<T> mergeMatsByCol(const vector<Mat_<T>> &Mats);
}

#endif
