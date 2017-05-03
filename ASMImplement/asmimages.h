#ifndef _ASMIMAGES_H_
#define _ASMIMAGES_H_
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <string>
#include "opencv2/highgui.hpp"
#include "shapevector.h"
using namespace cv;
using namespace std;
namespace ASMMmodel{
	class AsmImages
	{
	public:
		AsmImages();
		~AsmImages();
		int nPoints;//����
		int ns;//�ֲ��Ҷ�ģ�͵Ĳ�������
		vector<Mat>imgPyramid;//ͼ�������
		vector<Mat_<uchar>>gryPyramid;//�ҶȽ�����
		vector<Mat_<double>>gradientPyramid;//�ݶȽ�����
		string filename;//ͼ����������·����
		Mat srcImage;//ԭʼѵ��ͼ��
		ShapeVector shape;
		Mat_<double> localStruct;

		// ����ֲ�����
		void getLocalStructures();
		//����level��ͼ��
		Mat& getTrainImage(int level);
		// ����level����ݶ�ͼ
		Mat& getGradientImage(int level);
	};
}
#endif