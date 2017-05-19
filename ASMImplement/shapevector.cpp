
#include "shapevector.h"
namespace ASMMmodel{
	
	 ShapeVector::ShapeVector(ShapeInfo &spInfo)
	{
		size_t nums = spInfo.ptsInfos.size();
		Mat_<double>shapeMat;
		shapeMat.create(2 * nums, 1);
		for (size_t i = 0; i < nums; i++)
		{
			shapeMat(i * 2, 0) = spInfo.ptsInfos[i].x;
			shapeMat(i * 2 + 1, 0) = spInfo.ptsInfos[i].y;
		}
		*this = shapeMat;
	}
	double ShapeVector::calcMeanX()const
	{
		double x=0;
		for (int i = 0; i < rows / 2;i++)
		{
			x += (*this)(2 * i, 0);

		}
		x = x / (rows / 2);
		return x;
	}
	double ShapeVector::calcMeanY()const
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
	cv::Rect_<double> ShapeVector::getBoundRect()
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
		at.getTransformFromAlign((*this), a);
		at.transform(*this,*this);

	}
	vector<Point> ShapeVector::vec2Pts()const
	{
		vector<Point>Points;
		for (int i = 0; i < rows / 2;i++)
		{
			Points.push_back(Point(static_cast<int>((*this).X(i)),static_cast<int>((*this).Y(i))));
		}
		return Points;
	}
	 Mat_<double> ShapeVector::loadFromShapeInfo(ShapeInfo &spInfo)
	{
		size_t nums = spInfo.ptsInfos.size();
		Mat_<double>shapeMat;
		shapeMat.create(2 * nums, 1);
		for (size_t i = 0; i < nums; i++)
		{
			shapeMat(i * 2, 0) = spInfo.ptsInfos[i].x;
			shapeMat(i * 2 + 1, 0) = spInfo.ptsInfos[i].y;
		}
		return shapeMat;
	}
	 void ShapeVector::show()
	 {
		 cout << *this << endl;
		 vector<Point> pts = this->vec2Pts();
		 Mat vec_img = Mat::zeros(Size(255,255),CV_8U);
		 for (auto p:pts)
		 {
			 circle(vec_img, p, 2, Scalar(255, 255, 255));
		 }
		 imshow("vec_img", vec_img);
		 waitKey(100);
	 }


}