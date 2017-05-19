#ifndef _SHAPEVECTOR_H_
#define _SHAPEVECTOR_H_
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include "affinetransform.h"
#include "TrainingSetInfo.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
using namespace cv;

namespace ASMMmodel {
	/*��״��������x1,y1,x2,y2,����,xn,yn��^t,��opencv��1-D�����ʾ
	*/
	class ShapeVector:public Mat_<double>
	{
	public:
		ShapeVector(const Mat_< double > &a) :Mat_< double >(a){}
		ShapeVector & operator =(const Mat_< double > &a) {
			Mat_< double >::operator=(a);
			return *this;
		}
		ShapeVector(){}
		~ShapeVector(){}
		ShapeVector (ShapeInfo &spInfo);//��shapeInfo�ļ���ʼ��
		void alignTo(const ShapeVector & a);//���뵽��״a
		void COGToZero();//�����ƶ���ԭ��
		void normalizeToOne();//��һ������
		Rect_<double> getBoundRect();//�ҵ���Ӿ��Σ�������ʼ��λ
		int nPoints()const{ return rows / 2; }//������������
		void translateXY(double x, double y);//ƽ��
		void scaleR(double r);//����
		double calcMeanX()const;//X�����ֵ
		double calcMeanY()const;//Y�����ֵ
		double X(int i)const{ return (*this)(2 * i, 0); }//��i�����x����
		double &X(int i){ return(*this)(2 * i, 0); }
		double Y(int i)const{ return(*this)(2 * i + 1); }//��i���������y����
		double &Y(int i){ return(*this)(2 * i + 1); }
		vector<Point> vec2Pts()const;//ת���ɵ����ʽ
		static Mat_<double> loadFromShapeInfo(ShapeInfo &spInfo);
		void show();
		AffineTransform at;

	};

}
#endif 