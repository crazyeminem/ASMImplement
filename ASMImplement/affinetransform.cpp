#include "affinetransform.h"
#include "shapevector.h"

namespace ASMMmodel{

	void AffineTransform::transform(const ShapeVector &src, ShapeVector &dst)const//��srcִ�иñ任
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
		��С�����бպϽ�
	*/
	void AffineTransform::getTransformFromAlign(const ShapeVector &Sa, const ShapeVector &Sb)//����A��B�õ�һ����ѱ任,��Ȩֵw,�ƶ�������
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
		//��COG����ԭ�㣬����Tx,Ty
		Tx = -a*Sa.calcMeanX() + b*Sa.calcMeanY() + Sb.calcMeanX();
		Ty = -b*Sa.calcMeanX() - a*Sa.calcMeanY() + Sb.calcMeanY();
	}

}
