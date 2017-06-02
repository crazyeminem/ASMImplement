#include "stdafx.h"
#include "ASM.h"
namespace ASMMmodel{
	ASM::ASM()
	{
	}
	ASM::~ASM()
	{
	}
	void ASM::buildModel(const char* xmlFile)
	{
		//debug
		shapemodel.setParam(100, 1e-8, 0.95, 9, 3);

		shapemodel.buildModel(xmlFile);
		buildGrayModel();
		//debug
		//cout << "feature" << (grayFeatureMap[2])[0];
	}
	void ASM::initPose(Rect bRect)
	{
		shapevec = shapemodel.meanShape.clone();
		//������Ӿ���
		Rect_<double> curRect = shapevec.getBoundRect();
		ShapeVector s1 = (Mat_<double>(8, 1) << curRect.x, curRect.y, curRect.x + curRect.width, curRect.y, curRect.x + curRect.width, curRect.y + curRect.height, curRect.x, curRect.y + curRect.height);
		ShapeVector s2 = (Mat_<double>(8, 1) << bRect.x, bRect.y, bRect.x + bRect.width, bRect.y, bRect.x + bRect.width, bRect.y + bRect.height, bRect.x, bRect.y + bRect.height);
		s1.alignTo(s2);
		s1.at.transform(shapevec, shapevec);
	}
	void ASM::initPose()//��ʼ��λ�ã��������޸�
	{
		//������뵽ĳһѵ������
		/*default_random_engine e;
		uniform_int_distribution<int> u(0, shapemodel.alShapeVec.size() - 1);
		shapevec = shapemodel.meanShape.clone();
		int i = u(e);
		shapevec.alignTo(shapemodel.alShapeVec[i]);*/
		shapevec = shapemodel.meanShape.clone();
		shapevec.alignTo(shapemodel.alShapeVec[1]);


	}
	vector<Point> ASM::fit(const string &ImageFileName,const Rect &bRect)
	{
		initPose(bRect);
		shapemodel.alShapeInfo.alShapeInfos[0].imitate(spInfo, shapevec, ImageFileName);//����������Ϣ
		imageToFit.shapeInfo = spInfo;
		Mat srcImage = imread(ImageFileName);
		imageToFit.loadImage(ImageFileName);
		return fit(srcImage);

	}
	vector<Point> ASM::fit(const Mat &srcImage)
	{
		
		
		imageToFit.loadShapeVec(shapevec);
		imageToFit.init_build();
		//debug
		showResult();
		//debug
		iterateSearch();
		return shapevec.vec2Pts();
	}
	vector<Point>ASM::fit(const string &ImageFileName)
	{
		initPose();
		shapemodel.alShapeInfo.alShapeInfos[0].imitate(spInfo,shapevec, ImageFileName);//����������Ϣ
		imageToFit.shapeInfo = spInfo;
		Mat srcImage = imread(ImageFileName);
		imageToFit.loadImage(ImageFileName);
		return fit(srcImage);
	}
	void ASM::buildGrayModel()
	{
		np = (shapemodel.nSampleLength() - 1) / 2;
		for (int level = 0; level < shapemodel.nPyramid();level++)//��
		{
	
			vector<Mat_<double>> vm;
			vector<Mat_<double>> cm;
			for (int p = 0; p < shapemodel.nPoint();p++)//��
			{
				Mat_<double> m=Mat_<double>::zeros(np*2+1,1);
				vector<Mat_<double>> alFeature;
				for (int i = 0; i < shapemodel.nSample();i++)//����
				{
					m += (shapemodel.imgSet[i].LocalFeatureMap[level])[p];
					Mat_<double> tp = (shapemodel.imgSet[i].LocalFeatureMap[level])[p].clone();
					alFeature.push_back(tp);
				}
				m *= 1.0 / shapemodel.nSample();
				//cout << "feature :"<<m<<endl;
				Mat_<double> alF=mergeMatsByCol(alFeature);
				Mat_<double> covar;
				Mat_<double> mean;
				calcCovarMatrix(alF, covar, mean, CV_COVAR_COLS|CV_COVAR_SCALE|CV_COVAR_NORMAL);
				vm.push_back(mean);//��i������level���ƽ������
				//cout << "feature  " << p << "at level  " << level << "  "<<mean<<endl;
				invert(covar, covar, DECOMP_SVD);
				cm.push_back(covar);
			}
			grayFeatureMap[level] = vm;
			icovarMap[level] = cm;
		}

	}
	void ASM::iterateSearch()
	{
		for (int i = shapemodel.nPyramid()-1; i >= 0; i--)
		{
			iterateSearch(i);
		}
	
	}
	void ASM::iterateSearch(int level)//Ѱ�����������ƥ��
	{
		int iteration = 20;
		if (level>0)
		{
			iteration = 5;
		}
		vector<Point> bestFit;
		string DEBUG_INFO;
		Mat_<double> DX = Mat_<double>::zeros(shapevec.nPoints() * 2, 1);//ƫ�ƾ���
		bestFit.resize(shapevec.nPoints());
		
		int convergePoints = 0;
		for (size_t it = 0; it < iteration;it++)//��������
		{
			bestFit = shapevec.vec2Pts();
			for (int i = 0; i < shapevec.nPoints(); i++)//������i
			{
				int searchDis = 0;
				double minDis = 65534;
				for (int offset = k; offset >= -k; offset--)//�����뾶k������2k+1
				{
					vector<Point> V;
					Mat_<double> localFeaure = Mat_<double>::zeros(2 * np + 1, 1);
					Mat_<double> deriveImage = imageToFit.gradientPyramid[level];
					imageToFit.getNormalPoints(i, np, level, V, offset);//�õ�level���º�ѡ�㼯V
					double absSum = 0;
					for (int j = -np; j <= np; j++)
					{
						localFeaure(j + np, 0) = deriveImage(V[j + np]);
						absSum += fabs(localFeaure(j + np, 0));//�ú�ѡ��ľֲ�����
					}
					localFeaure *= 1 / absSum;
					//cout << "icovar"<<(icovarMap[level])[i];
					//cout << "grayfeature" << (grayFeatureMap[level])[i] << endl;

					//�������Ͼ���
					double mDis = Mahalanobis(localFeaure, (grayFeatureMap[level])[i], (icovarMap[level])[i]);
					if (offset==0)
					{
						//cout << "��ǰ�� " << i << "+ " << offset << "	Mahalanobis����= " << mDis << "	" << "��СMahalanobis����= " << minDis << endl;
						
					}
					//cout << "��ǰ��" <<i<<"+ " <<offset<< "	Mahalanobis����= " << mDis << "	" << "��СMahalanobis����= " << minDis << endl;
					if (mDis < minDis)//����������Ϣ
					{
						minDis = mDis;
						bestFit[i] = V[np];
						searchDis = abs(offset);
						DEBUG_INFO = "��ǰ�� " + to_string(i) +"offset "+to_string(offset)+ "��СM����" + to_string(minDis) + "--��������" + to_string(it);

						//cout << DEBUG_INFO << endl;
						showResult(bestFit, level, i);
					}
				
					
				}

				
			}
			//�ָ�������߶�
			vector<Point> ShiftFit;
			for (int i = 0; i < bestFit.size();i++)
			{
				Point t;
				t.x = bestFit[i].x << level;
				t.y = bestFit[i].y << level;
				ShiftFit.push_back(t);

			}
			cout << "Deform In: " << it<<"th"<<"  iteration"<< endl;

			ShapeVector shiftShape(ShiftFit);
			
			shapevec.alignTo(shiftShape);
			ShapeVector currShape = shapevec.clone();
			shapevec.alignTo(shapemodel.meanShape);
			Mat_<double> projected;
			shapemodel.pcaShape->project(shapevec, projected);
			//clamp
			for (size_t i = 0; i < projected.rows; i++)
			{
				if (projected(i, 0) > shapemodel.clampParameter(i, 0))
				{
					projected(i, 0) = shapemodel.clampParameter(i, 0);
				}
				else if (projected(i, 0) < -shapemodel.clampParameter(i, 0))
				{
					projected(i, 0) = -shapemodel.clampParameter(i, 0);
				}
			}
			shapemodel.pcaShape->backProject(projected, shapevec);
			//���뵽��ʼλ��
			shapevec.alignTo(currShape);

			imageToFit.refresh(shapevec);
			showResult(level);
			//showResult();
			
		}

		//


	}
	void ASM::showResult(int level)
	{
		Mat debugImg = this->imageToFit.imgPyramid[level].clone();
		vector<Point> pts = imageToFit.shape.vec2Pts();
		for (auto p : pts)
		{
			Point pt = Point(p.x >> level, p.y >> level);
			circle(debugImg, pt, 2, Scalar(0, 0, 255));
		}
		set<int> pipeLine;
		for (int i = 0; i < shapemodel.nPoint(); i++)
		{
			if (pipeLine.find(i) == pipeLine.end())
			{
				Point p1 = Point(pts[imageToFit.shapeInfo.ptsInfos[i].pre].x >> level, pts[imageToFit.shapeInfo.ptsInfos[i].pre].y >> level);
				Point p2 = Point(pts[imageToFit.shapeInfo.ptsInfos[i].next].x >> level, pts[imageToFit.shapeInfo.ptsInfos[i].next].y >> level);
				Point p3 = Point(pts[imageToFit.shapeInfo.ptsInfos[i].id].x >> level, pts[imageToFit.shapeInfo.ptsInfos[i].id].y >> level);
				line(debugImg,p1,p3,Scalar(255, 0, 0));
				line(debugImg,p2 ,p3, Scalar(155, 0, 0));
				pipeLine.insert(i);
				pipeLine.insert(imageToFit.shapeInfo.ptsInfos[i].pre);
				pipeLine.insert(imageToFit.shapeInfo.ptsInfos[i].next);
			}
		}
		imshow("debug", debugImg);
		waitKey(400);
	}
	void ASM::showResult(vector<Point>FitPoints,int level,int i)
	{
		Mat debugImg = this->imageToFit.imgPyramid[level].clone();
		for (int j=0; j < FitPoints.size();j++)
		{
			if (j == i)
				circle(debugImg, FitPoints[j], 2, Scalar(0, 0, 255));
			else
				circle(debugImg, FitPoints[j], 2, Scalar(255, 0, 0));
		}
	
		namedWindow("iteration");
		imshow("iteration", debugImg);
		waitKey(200);
		//destroyWindow(info);
	}
}

