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
		double theta;//旋转角度
		double s;//缩放系数
		double Tx;//x方向平移
		double Ty;//y方向平移
		AffineTransform() :a(1), b(0), theta(0), s(1), Tx(0), Ty(0){}
		void transform(const ShapeVector &src, ShapeVector &dst)const;//对src执行该变换
		void getTransformFromAlain(const ShapeVector &A, const ShapeVector &B);//对齐A，B得到一个最佳变换
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