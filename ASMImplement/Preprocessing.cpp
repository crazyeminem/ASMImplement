#include "Preprocess.h"
using namespace cv;
using namespace std;
//�������
double dis(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) * 1.0 + (a.y - b.y) * (a.y - b.y));
}
//����ˮƽ�����ϵ�ƽ��ֵ
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
//����ֲ���ֵ,���������趨Ϊ1/8��ָ����, ���ǳ߹����������ʼ��
vector<int> getLocalMax(vector<int> Xavg, int type /*�ǽṹ����*/)
{
	int length = Xavg.size();//��������
	//int range= length / 5;//�ֲ�����뾶,�趨Ϊ1/5��ָ����
	int range = length / 8;//�ֲ�����뾶,�趨Ϊ1/8��ָ����
	int MaxIndex;
	const int minDiff = 10;//����ֵ��Сֵ��ֵ
	const int minMaxVal = 10;//��С����ֵ
	vector<int>MaxVec;
	double MaxVal = 0;
	double Minval = 0;
	Point MinLoc, MaxLoc;
	Mat mGlobal(Xavg);
	if (type == 0)
	{
		for (size_t loc = range; loc < length - range; loc++)
		{
			Mat mLocal = mGlobal.rowRange(loc - range, loc + range);//�ֲ�����
			minMaxLoc(mLocal, &Minval, &MaxVal, &MinLoc, &MaxLoc);//����ֲ����ֵ
			if (MaxLoc.y == range&&MaxVal>minMaxVal&&MaxVal - Minval>minDiff)//�жϼ�ֵ�Ƿ����
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
			Mat mLocal = mGlobal.rowRange(loc - range / 2, loc + range / 2);//�ֲ�����
			minMaxLoc(mLocal, &Minval, &MaxVal, &MinLoc, &MaxLoc);//����ֲ����ֵ
			if (MaxLoc.y == range / 2)//�жϼ�ֵ�Ƿ����
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
//ָ�ǵĹ�����ȡ��Ĵָ2����ָ3��Сָ2
Rect getPhalanxEpiphysis(Mat srcImage, int PhalanxType )
{
	Rect bRect;
	int EpiNumber = 0;
	Mat x_gradient, x_gradient_abs, y_gradient_abs, y_gradient;
	Sobel(srcImage, y_gradient, CV_16S, 0, 1, 3, 1, 0, BORDER_DEFAULT);//��ֱ�����ݶ�
	Sobel(srcImage, x_gradient, CV_16S, 1, 0, 3, 1, 0, BORDER_DEFAULT);//ˮƽ�����ݶ�
	convertScaleAbs(x_gradient, x_gradient_abs);//ת��ΪCV_8U
	convertScaleAbs(y_gradient, y_gradient_abs);
	imshow("srcImage", srcImage);
	imshow("vertical_Gradient_with_GaussianBlur", y_gradient_abs);
	imshow("x_gradient", x_gradient_abs);
	vector<int> Xavg = calcXavg(y_gradient_abs);
	vector<int> MaxIndex = getLocalMax(Xavg);//�ֲ���ֵ����
	bRect = Rect(10, 10, srcImage.cols - 20, MaxIndex[1]);
	//for (auto t = MaxIndex.begin(); t != MaxIndex.end(); t++)
	//{
	//	char WinName[20];
	//	sprintf_s(WinName, 20, "WinName+%d", *t);
	//	Mat LocalMax = srcImage(Rect(0, *t - Xavg.size() / 8 / 2, srcImage.cols, Xavg.size() / 8));//�����СΪ:1/8*Image.length*Image.width
	//	//imshow(WinName, LocalMax);
	//	waitKey(0);
	//	/*
	//	�������򱣴棬�ļ�������ԭ�ļ���+��ָID+��������λ�ã�
	//	��ָID�� 0Ĵָ 1��ָ 2Сָ
	//	��������λ�ã� 0Զ��ָ�� 1�н�ָ�� 2����ָ��
	//	��20160507484943_012(��ָID��1����ָ������λ�ã�2 ����ָ�ǣ�
	//	*/
	//	char EpiFileName[20];
	//	//��to_string
	//	EpiNumber++;
	//	//����Ĵָ��Сָ��ȡ������������
	//	if ((PhalanxType == Epi_Thumbs || PhalanxType == Epi_LFingers) && EpiNumber == 2)
	//	{
	//		break;
	//	}

	//}
	return bRect;
}