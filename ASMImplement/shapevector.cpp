#include "shapevector.h"
namespace ASMMmodel{
	double ShapeVector::calcMeanX()
	{
		double x=0;
		for (int i = 0; i < rows / 2;i++)
		{
			x += (*this)(2 * i, 0);

		}
		x = x / (rows / 2);
		return x;
	}
	double ShapeVector::calcMeanY()
	{
		double y = 0;
		for (int i = 0; i < rows / 2; i++)
		{
			y += (*this)(2 * i+1, 0);

		}
		y = y / (rows / 2);
		return y;
	}
	void ShapeVector::translateXY(double x, double y)
	{
		for (int i = 0; i < rows / 2;i++)
		{
			(*this)(i * 2, 0) += x;
			(*this)(i * 2 + 1, 0) += y;
		}
	}
	void ShapeVector::COGToZero()
	{
		translateXY(-calcMeanX(), -calcMeanY());

	}
	void ShapeVector::scaleR(double r)
	{
		(*this)*=r;
	}
	void ShapeVector::normalizeToOne()
	{
		scaleR(1 / norm(*this));
	}
	cv::Rect ShapeVector::getBoundRect()
	{
		int nP = nPoints();
		double minX = 1e10, minY = 1e10, maxX = -1e10, maxY = -1e10;
		double x, y;
		for (int i = 0; i < nP; i++) {
			x = X(i);
			y = Y(i);
			if (x < minX) minX = x;
			if (x > maxX) maxX = x;
			if (y < minY) minY = y;
			if (y > maxY) maxY = y;
		}
		return cv::Rect_< double >(
			cv::Point_<double>(minX, minY),
			cv::Size_<double>(maxX - minX, maxY - minY));
	}
	void ShapeVector::alignTo(const ShapeVector &a)
	{
		AffineTransform at;
		at.getTransformFromAlain((*this), a);
		at.transform(*this,*this);

	}
	
}