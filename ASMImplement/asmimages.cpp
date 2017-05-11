
#include "asmimages.h"
namespace ASMMmodel{

	void AsmImages::getNormalPoints(int pId, int level, vector<Point> &normPoints, int pOffset,double step)
	{
		//计算norm方向
		Point_<double>va,vb, vDirection;
		va = pts[shapeInfo.ptsInfos[pId].pre] - pts[pId];
		vb = pts[shapeInfo.ptsInfos[pId].next] - pts[pId];
		double  td;
		td = norm(va);
		if (td>1e-10)
		{
			va *= 1 / td;
		}
		td = norm(vb);
		if (td>1e-10)
		{
			vb *= 1 / td;
		}
		vDirection.x = -va.y + vb.y;
		vDirection.y = va.x - vb.x;
		if (norm(vDirection) < 1e-10)
		{
			if (norm(va) > 1e-10)
				vDirection = -va;
			else
			{
				vDirection.x = 1;
				vDirection.y = 0;
			}
		}
		else
			vDirection *= 1 / norm(vDirection);//单位方向向量
		int i, j;
		int nx, ny;
		int offsetX, offsetY;
		int prevX, prevY;

		// Find the center point, here step===1
		prevX = 0;
		prevY = 0;
		nx = ny = 0;
		j = 1;
		for (i = 1; i <= abs(pOffset); i++){
			do {
				nx = cvRound(j*vDirection.x);
				ny = cvRound(j*vDirection.y);
				j++;
			} while (nx == prevX && ny == prevY);

			prevX = nx;
			prevY = ny;
		}
		j--;
		if (pOffset > 0)
			offsetX = nx, offsetY = ny;
		else
			offsetX = -nx, offsetY = -ny;

		// Apply the "step", and find points
		vDirection *= step;
		prevX = 0;
		prevY = 0;
		nx = ny = 0;

		// Test best j
		j = 1;
		for (i = 1; i <= (np-1)/2; i++){
			do {
				nx = cvRound(j*vDirection.x);
				ny = cvRound(j*vDirection.y);
				j++;
			} while (nx == prevX && ny == prevY);

			prevX = nx;
			prevY = ny;
		}
		j--;

		normPoints.resize(np);
		int rX, rY;
		for (i = (np-1)/2; i >= -(np-1)/2; i--){
			rX = (pts[pId].x >> level) + nx + offsetX;
			rY = (pts[pId].y >> level) + ny + offsetY;
			if (rX < 0) rX = 0;
			if (rY < 0) rY = 0;
			if (rX >= (srcImage.cols >> level)) rX = (srcImage.cols >> level) - 1;
			if (rY >= (srcImage.rows >> level)) rY = (srcImage.rows >> level) - 1;
			normPoints[i + (np-1)/2] = Point_< int >(rX, rY);
			//v(i+(k+1), 0) = this->imgdata.at< char >(nx, ny);
			do {
				nx = cvRound(j*vDirection.x);
				ny = cvRound(j*vDirection.y);
				j--;
			} while (nx == prevX && ny == prevY);
			prevX = nx;
			prevY = ny;
		}

	}
	// 计算level层pID点局部特征
	Mat_<double> AsmImages::localGrysStrcut(int pId, int level, double step)
	{
		Mat debug = gryPyramid[level].clone();
		vector< Point_< int > > pV;
		this->getNormalPoints(pId, level, pV);
		//circle(debug, pts[pId], 3,Scalar(0,0,0));
		//for (auto p:pV)
		//{
		//	circle(debug, p, 2, Scalar(255, 255, 255));
		//}
		//namedWindow("debug");
		//imwrite("debug.jpg", debug);
		//imshow("debug", debug);
		//waitKey(0);
		Mat_< double > diffV(np, 1);
		int k = (np - 1) / 2;
		double absSum = 0;
		for (int i = k; i >= -k; i--){
			diffV(i + k, 0) = gradientPyramid[level](pV[i + k]);
			absSum += fabs(diffV(i + k, 0));
		}
		if (absSum == 0){
			printf("Warning: absSum=0....Level: %d, pID: %d\n", level, pId);
		}
		else
			diffV *= 1 / absSum;

		return diffV;
	}
	void AsmImages::getLocalStructuresMap()
	{
		for (int l = 0; l < nPyramids;l++)
		{
			vector<Mat_<double>> levelFeature;
			for (int i = 0; i < nPoints;i++)
			{
				levelFeature.push_back(localGrysStrcut(i,l,0.5));
			}
			LocalFeatureMap.insert({l,levelFeature});
		}
	}

	//返回level层图像//
	Mat& AsmImages::getTrainImage(int level)
	{
		//TODO: insert return statement here
		return imgPyramid[level];
	}


	// 返回level层的梯度图
	Mat& AsmImages::getGradientImage(int level)
	{
		//TODO: insert return statement here
		return gryPyramid[level];
	}
	// 载入图像
	bool AsmImages::loadImage(const Mat& img)
	{
		if (img.empty())
		{
			return false;
		}
		isEmpty = 0;
		srcImage = img;
		buildPyramid(srcImage, this->imgPyramid, nPyramids-1);
		if (img.channels() == 3)
		{
			for (int i = 0; i < nPyramids; i++)
			{
				Mat t;
				cvtColor(imgPyramid[i], t, CV_BGR2GRAY);
				gryPyramid.push_back(t);
			}
		}
		else
		{
			for (auto s : imgPyramid)
			{
				gryPyramid.push_back(s);
			}
		}
		gradientPyramid.resize(nPyramids);
		for (int i = 0; i < nPyramids; i++)
		{
			gryPyramid[i].convertTo(gradientPyramid[i], CV_64F);
			Sobel(gradientPyramid[i], gradientPyramid[i], CV_64F, 1, 1);
		}

		return true;
	}


	// 载入图像
	bool AsmImages::loadImage(const string& imgname)
	{
		Mat img;
		filename = imgname;
		img = imread(filename);
		return loadImage(img);
	}
	bool AsmImages::empty()
	{
		return isEmpty;
	}
	
	void AsmImages::loadPts()
	{
		pts = shape.vec2Pts();
		nPoints = pts.size();
	}
	//shapevec初始化
	void AsmImages::loadShapeVec()
	{
		this->shape = ShapeVector::loadFromShapeInfo(shapeInfo);

	}
	//初始化图像信息
	void AsmImages::init_build()
	{
				
			loadImage(filename);
			loadShapeVec();
			loadPts();
			getLocalStructuresMap();



	}
	void AsmImages::show(int l)
	{
		Mat ImgShow = imgPyramid[l].clone();
		for (auto p:pts)
		{
			Point temp;
			temp.x= p.x >> l;
			temp.y = p.y >> l;
			circle(ImgShow, temp, 2, Scalar(255, 0, 0));

		}
		imshow(filename, ImgShow);
		waitKey(0);
	}

}

