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
		int nPoints;//点数
		int ns;//局部灰度模型的采样点数
		vector<Mat>imgPyramid;//图像金字塔
		vector<Mat_<uchar>>gryPyramid;//灰度金字塔
		vector<Mat_<double>>gradientPyramid;//梯度金字塔
		string filename;//图像名（绝对路径）
		Mat srcImage;//原始训练图像
		ShapeVector shape;
		Mat_<double> localStruct;

		// 计算局部特征
		void getLocalStructures();
		//返回level层图像
		Mat& getTrainImage(int level);
		// 返回level层的梯度图
		Mat& getGradientImage(int level);
	};
}
#endif