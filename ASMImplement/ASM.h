#ifndef _ASM_H_
#define _ASM_H_
#include "shapemodel.h"
#include "asmimages.h"
#include <random>
namespace ASMMmodel{
	class ASM
	{
	public:
		ASM();
		~ASM();
		//�����Ҷ�ģ��
		void buildGrayModel();
		//����asmģ��
		void buildModel(const char* xmlFile);
		//���������
		//param:srcImage ��Ҫ��������ϵ�ͼ��
		//return:��ϳ��ĵ㼯
		vector<Point> fit(const Mat &srcImage);
		vector<Point> fit(const string ImageFileNmae);
		//��ʼλ��ȷ��
		void initPose();
		void initPose(Rect_<double> bRect);
		//���ݾֲ��Ҷ������ƶ�������
		void shiftThroughGrayStructure();
		void fitGrayStructure(int level);


		ShapeModel shapemodel;
		ShapeVector shapevec;
		vector<Point_<int>> fitPts;
		AsmImages  imageToFit;
		//�ҶȽṹ����(��ֵ)������
		map<int, vector<Mat_<double>>> grayFeatureMap;
		//ÿ���������Э���������
		map<int, vector<Mat_<double>>> covarMap;
		//Ȩֵ����
		Mat_<double> W;
		//��״����b
		Mat_<double> b;
		//�ֲ����������뾶
		int k=5;
		//�ֲ����������뾶
		int np;
		
	};
}


#endif

