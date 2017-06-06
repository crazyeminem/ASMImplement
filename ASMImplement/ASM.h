#ifndef _ASM_H_
#define _ASM_H_
#include "shapemodel.h"
#include "asmimages.h"
#include <random>
#include<set>
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
		vector<Point> fit(const string &ImageFileName);
		vector<Point> fit(const string &imageFileName, const Rect &bRect);
		//��ʼλ��ȷ��
		void initPose();
		void initPose(Rect bRect);
		//���ݾֲ��Ҷ������ƶ�������
		void iterateSearch();
		void iterateSearch(int level);
		void showResult(int level=0);
		void showResult(vector<Point>FitPoints,int level,int i);


		ShapeModel shapemodel;
		ShapeVector shapevec;
		vector<Point_<int>> fitPts;
		AsmImages  imageToFit;
		ShapeInfo spInfo;
		//�ҶȽṹ����(��ֵ)������
		map<int, vector<Mat_<double>>> grayFeatureMap;
		//ÿ���������Э���������
		map<int, vector<Mat_<double>>> icovarMap;
		//Ȩֵ����
		Mat_<double> W;
		//��״����b
		Mat_<double> b;
		//�ֲ����������뾶
		int k=9;
		//�ֲ����������뾶
		int np;
		
	};
}


#endif

