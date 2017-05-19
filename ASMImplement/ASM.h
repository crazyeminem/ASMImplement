#ifndef _ASM_H_
#define _ASM_H_
#include "shapemodel.h"
#include "asmimages.h"
namespace ASMMmodel{
	class ASM
	{
	public:
		ASM();
		~ASM();
		//�����Ҷ�ģ��
		void buildGrayModel();
		//����asmģ��
		void buildModel();
		//���������
		//param:srcImage ��Ҫ��������ϵ�ͼ��
		//param:boundrect Ŀ�����ڴ����������Գ�ʼ����״����
		//return:��ϳ��ĵ㼯
		vector<Point> fit(Mat srcImage,Rect boundRect){

		}
		ShapeModel shapemodel;
		//ÿ��������ľ�ֵ������
		vector<vector<Mat_<double>>> meanG;
		//ÿ���������Э���������
		vector<vector<Mat_<double>>> covarG;
		//Ȩֵ����
		Mat_<double> W;
		//��״����b
		Mat_<double> b;
		//�ֲ����������뾶
		int k;
		
	};
}


#endif

