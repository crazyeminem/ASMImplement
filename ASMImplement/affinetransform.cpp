#include "affinetransform.h"
#include "shapevector.h"

namespace ASMMmodel{

	void AffineTransform::transform(const ShapeVector &src, ShapeVector &dst)const//对src执行该变换
	{
		int n = src.nPoints();
		dst.create(n*2, 1);
		double xt, yt;
		for (int i = 0; i < n;i++)
		{
			xt = src.X(i);
			yt = src.Y(i);
			dst.X(i) = a*xt - b*yt + Tx;
			dst.Y(i) = b*xt + a*yt + Ty;
		}
	}
	/*
		最小二乘有闭合解
	*/
	void AffineTransform::getTransformFromAlign(const ShapeVector &Sa, const ShapeVector &Sb)//对齐A，B得到一个最佳变换,无权值w,移动到中心
	{
		int n = Sa.nPoints();

		double s=0, t=0, m=0;
		s = Sa.dot(Sa);
		for (int i = 0; i < n;i++)
		{
			t+=Sa.X(i)*Sb.X(i) + Sa.Y(i)*Sb.Y(i);
			m += Sa.X(i)*Sb.Y(i) - Sa.Y(i)*Sb.X(i);
		}
		a = t / s;
		b = m / s;
		//若COG不在原点，更新Tx,Ty
		Tx = -a*Sa.calcMeanX() + b*Sa.calcMeanY() + Sb.calcMeanX();
		Ty = -b*Sa.calcMeanX() - a*Sa.calcMeanY() + Sb.calcMeanY();
	}

}
