#ifndef _SHAPEVECTOR_H_
#define _SHAPEVECTOR_H_
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using cv::Mat_;
using cv::Point;
using std::vector;
using cv::Mat;

namespace ASMMmodel {
	class ShapeVector:public Mat_<double>
	{
	public:
		ShapeVector(const Mat_< double > &a) :Mat_< double >(a){}

		ShapeVector & operator =(const Mat_< double > &a) {
			Mat_< double >::operator=(a);
			return *this;
		}

		ShapeVector(){}
		void alignTo(ShapeVector & a);//对齐到形状a
		void COGToZero();//重心移动到原点
		void normalizeToOne();//归一化向量
		cv::Rect getBoundRect();//找到外接矩形，用来初始定位
		int nPoints();//返回特征点数

	

	};

}
#endif 