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

		int pyramidLevel;//����������
		double pcaRatio;//PCA���ɷֱ�
		int nPoints;//��ǵ���
		int nSamples;//������
		vector < AsmImages > imgSet;//ѵ��ͼ����Ϣ��
		TrainingSetInfo alShapeInfo;//��״��Ϣ��
		ShapeVector meanShape;//ƽ����״
		Mat_<double> alShapeVecMat;//����������״����
		vector<ShapeVector> alShapeVec;
		
		PCA *pcaShape;//PCAģ��

		// ����PCAģ��
		void buildPCA();
		// Procrustes����
		void procrustesAlign();
		// ����ģ��
		void buildModel();
		
		// ��ʾģ��
		void showModel();
	};
}
#endif
