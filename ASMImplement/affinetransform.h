#ifndef _AFFINETRANSFORM_H_
#define _AFFINETRANSFORM_H_
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using cv::Mat_;
namespace ASMMmodel{
	class ShapeVector;
	class AffineTransform{
	public:
		double a;//s*cos
		double b;//s*sin
		//double theta;//��ת�Ƕ�
		//double s;//����ϵ��
		double Tx;//x����ƽ��
		double Ty;//y����ƽ��
		AffineTransform() :a(1), b(0), Tx(0), Ty(0){}
		void transform(const ShapeVector &src, ShapeVector &dst)const;//��srcִ�иñ任
		void getTransformFromAlign(const ShapeVector &A, const ShapeVector &B);//����A��B�õ�һ����ѱ任
		double getScale()const
		{
			return a*a + b*b;

		}
		double getRotateAngle()const
		{
			return cv::fastAtan2(b,a);//arc tan b/a
		}
		AffineTransform operator *(const AffineTransform &T)const
		{
			AffineTransform T2;
			T2.a = a*T.a - b*T.b;
			T2.b = T.a*b + T.b*a;
			T2.Tx = a*T.Tx - b*T.Ty + Tx;
			T2.Ty = b*T.Tx + a*T.Ty + Ty;
			return T2;
		}










	};
}
#endif