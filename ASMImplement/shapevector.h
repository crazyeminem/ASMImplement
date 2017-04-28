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
		void alignTo(ShapeVector & a);//���뵽��״a
		void COGToZero();//�����ƶ���ԭ��
		void normalizeToOne();//��һ������
		cv::Rect getBoundRect();//�ҵ���Ӿ��Σ�������ʼ��λ
		int nPoints();//������������

	

	};

}
#endif 