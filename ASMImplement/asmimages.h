#ifndef _ASMIMAGES_H_
#define _ASMIMAGES_H_
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <string>
#include <map>
#include "opencv2/highgui.hpp"
#include "shapevector.h"
#include "TrainingSetInfo.h"
using namespace cv;
using namespace std;
namespace ASMMmodel{
	class AsmImages
	{
	public:
		AsmImages(ShapeInfo sp,int n = 7, int np = 3) :shapeInfo(sp),nPoints(np), np(n),nPyramids(np),filename(sp.imgname){}//�Զ��������������������
		~AsmImages(){}
		AsmImages(){};
		int nPoints;//����
		int np;//�ֲ��Ҷ�ģ�͵Ĳ�������,Ӧ��Ϊ������������������
		int nPyramids;//����������
		bool isEmpty=1;
		vector<Mat>imgPyramid;//ͼ�������
		vector<Mat_<uchar>>gryPyramid;//�ҶȽ�����
		vector<Mat_<double>>gradientPyramid;//�ݶȽ�����
		string filename;//ͼ����������·����
		Mat srcImage;//ԭʼѵ��ͼ��
		ShapeVector shape;
		ShapeInfo shapeInfo;//��״��Ϣ
		map<int,vector<Mat_<double>>> LocalFeatureMap;//����ֲ�����
		vector<Point> pts;//�����㼯
		// �������в�ֲ�����
		void getLocalStructuresMap();
		//����ĳ��ͼ�ֲ�����
		Mat_<double> localGrysStrcut(int pId,int level ,double step=1.0);
		//����level��ͼ��
		Mat& getTrainImage(int level);
		// ����level����ݶ�ͼ
		Mat& getGradientImage(int level);
		// ����ͼ��
		bool loadImage(const Mat& img);
		// ����ͼ��
		bool loadImage(const string& imgname);
		//�пգ�δ����ͼ��
		bool empty();
		//��shapeinfo��ȡshapevector
		void loadShapeVec();
		//��ȡ�����㼯
		void loadPts();
		//����profile normal
		//param pId ��ǰ��id
		//param level ����ͼ���
		//param normPoints ���跨�ߵ㼯
		//param pOffset ��������
		//param step ����
		void getNormalPoints(int pId,int level, vector<Point> &normPoints,int pOffset=0,double step=1.0);
		//��ʼ��ͼ����Ϣ
		void init_build();

		void show(int l);
	};
}
#endif