#include "Preprocess.h"
using namespace cv;
using namespace std;
//两点距离
double dis(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) * 1.0 + (a.y - b.y) * (a.y - b.y));
}
//计算水平方向上的平均值
vector<int> calcXavg(Mat y_gradient)
{
	vector<int> Xavg;
	int avg = 0;
	for (int i = 0; i < y_gradient.rows; i++)
	{
		for (int j = 0; j < y_gradient.cols; j++)
		{
			avg += y_gradient.at<uchar>(i, j);

		}
		avg /= y_gradient.cols;
		Xavg.push_back(avg);
		avg = 0;
	}
	return Xavg;

}
//计算局部极值,搜索区域设定为1/8手指长度, 若是尺骨桡骨则从最后开始找
vector<int> getLocalMax(vector<int> Xavg, int type /*骨结构类型*/)
{
	int length = Xavg.size();//向量长度
	//int range= length / 5;//局部区域半径,设定为1/5手指长度
	int range = length / 8;//局部区域半径,设定为1/8手指长度
	int MaxIndex;
	const int minDiff = 10;//极大值极小值差值
	const int minMaxVal = 10;//最小极大值
	vector<int>MaxVec;
	double MaxVal = 0;
	double Minval = 0;
	Point MinLoc, MaxLoc;
	Mat mGlobal(Xavg);
	if (type == 0)
	{
		for (size_t loc = range; loc < length - range; loc++)
		{
			Mat mLocal = mGlobal.rowRange(loc - range, loc + range);//局部区域
			minMaxLoc(mLocal, &Minval, &MaxVal, &MinLoc, &MaxLoc);//计算局部最大值
			if (MaxLoc.y == range&&MaxVal>minMaxVal&&MaxVal - Minval>minDiff)//判断极值是否合理
			{
				MaxIndex = loc;
				cout << "Index:" << MaxIndex << endl;
				cout << "MaxVal:" << Xavg[MaxIndex] << endl;
				cout << endl;
				MaxVec.push_back(MaxIndex);
			}


		}
	}

	if (type == 1)
	{
		int Find = 0;
		for (size_t loc = length - range / 2; loc>1 / 2 * length - range / 2; loc--)
		{
			if (Find == 1)
				break;
			Mat mLocal = mGlobal.rowRange(loc - range / 2, loc + range / 2);//局部区域
			minMaxLoc(mLocal, &Minval, &MaxVal, &MinLoc, &MaxLoc);//计算局部最大值
			if (MaxLoc.y == range / 2)//判断极值是否合理
			{
				MaxIndex = loc;
				cout << "Index:" << MaxIndex << endl;
				cout << "MaxVal:" << Xavg[MaxIndex] << endl;
				cout << endl;
				MaxVec.push_back(MaxIndex);
				Find = 1;
			}


		}
	}

	return MaxVec;
}
//指骨的骨骺提取，拇指2，中指3，小指2
Rect getPhalanxEpiphysis(Mat srcImage, int PhalanxType )
{
	Rect bRect;
	int EpiNumber = 0;
	Mat x_gradient, x_gradient_abs, y_gradient_abs, y_gradient;
	Sobel(srcImage, y_gradient, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);//垂直方向梯度
	Sobel(srcImage, x_gradient, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);//水平方向梯度
	convertScaleAbs(x_gradient, x_gradient_abs);//转换为CV_8U
	convertScaleAbs(y_gradient, y_gradient_abs);
	imshow("srcImage", srcImage);
	imshow("vertical_Gradient_with_GaussianBlur", y_gradient_abs);
	imshow("x_gradient", x_gradient_abs);
	vector<int> Xavg = calcXavg(y_gradient_abs);
	vector<int> MaxIndex = getLocalMax(Xavg);//局部极值区域
	bRect = Rect(10, 10, srcImage.cols - 20, MaxIndex[1]);
	//for (auto t = MaxIndex.begin(); t != MaxIndex.end(); t++)
	//{
	//	char WinName[20];
	//	sprintf_s(WinName, 20, "WinName+%d", *t);
	//	Mat LocalMax = srcImage(Rect(0, *t - Xavg.size() / 8 / 2, srcImage.cols, Xavg.size() / 8));//窗体大小为:1/8*Image.length*Image.width
	//	//imshow(WinName, LocalMax);
	//	waitKey(0);
	//	/*
	//	骨骺区域保存，文件名规则：原文件名+手指ID+骨骺区域位置，
	//	手指ID： 0拇指 1中指 2小指
	//	骨骺区域位置： 0远节指骨 1中节指骨 2近节指骨
	//	如20160507484943_012(手指ID：1，中指，区域位置：2 近节指骨）
	//	*/
	//	char EpiFileName[20];
	//	//或to_string
	//	EpiNumber++;
	//	//若是拇指或小指，取两个骨骺区域
	//	if ((PhalanxType == Epi_Thumbs || PhalanxType == Epi_LFingers) && EpiNumber == 2)
	//	{
	//		break;
	//	}

	//}
	return bRect;
}