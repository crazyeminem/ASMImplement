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
	/*形状向量，（x1,y1,x2,y2,……,xn,yn）^t,用opencv的1-D矩阵表示
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
		ShapeVector (ShapeInfo &spInfo);//从shapeInfo文件初始化
		void alignTo(const ShapeVector & a);//对齐到形状a
		void COGToZero();//重心移动到原点
		void normalizeToOne();//归一化向量
		Rect_<double> getBoundRect();//找到外接矩形，用来初始定位
		int nPoints()const{ return rows / 2; }//返回特征点数
		void translateXY(double x, double y);//平移
		void scaleR(double r);//缩放
		double calcMeanX()const;//X方向均值
		double calcMeanY()const;//Y方向均值
		double X(int i)const{ return (*this)(2 * i, 0); }//第i个点的x坐标
		double &X(int i){ return(*this)(2 * i, 0); }
		double Y(int i)const{ return(*this)(2 * i + 1); }//第i个特征点的y坐标
		double &Y(int i){ return(*this)(2 * i + 1); }
		vector<Point> vec2Pts()const;//转化成点的形式
		static Mat_<double> loadFromShapeInfo(ShapeInfo &spInfo);
		void show();
		AffineTransform at;

	};

}
#endif 