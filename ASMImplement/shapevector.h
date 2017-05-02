#ifndef _SHAPEVECTOR_H_
#define _SHAPEVECTOR_H_
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include "affinetransform.h"
using cv::Mat_;
using cv::Point;
using std::vector;
using cv::Mat;
using cv::Rect;
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
		void alignTo(const ShapeVector & a);//���뵽��״a
		void COGToZero();//�����ƶ���ԭ��
		void normalizeToOne();//��һ������
		Rect getBoundRect();//�ҵ���Ӿ��Σ�������ʼ��λ
		int nPoints(){ return rows / 2; }//������������
		void translateXY(double x, double y);//ƽ��
		void scaleR(double r);//����
		double calcMeanX();//X�����ֵ
		double calcMeanY();//Y�����ֵ
		double X(int i)const{ return (*this)(2 * i, 0); }//��i�����x����
		double &X(int i){ return(*this)(2 * i, 0); }
		double Y(int i)const{ return(*this)(2 * i + 1); }//��i���������y����
		double &Y(int i){ return(*this)(2 * i + 1); }

	};

}
#endif 