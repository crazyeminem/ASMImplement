#ifndef _TRAININGSETINFO_H_
#define _TRAININGSETINFO_H_
#include <vector>
#include <string>
#include "shapevector.h"
#include "txml/tinystr.h"
#include "txml/tinyxml.h"
using namespace std;
namespace ASMMmodel{
	class PointInfo
	{
	public:
		double x;
		double y;
		int  id;
		int pre;
		int next;
	};
	class ShapeInfo
	{
	public:
		string imgname;
		vector<PointInfo> ptsInfos;
		void imitate(ShapeInfo &spinfo, const ShapeVector& shapvec, const string &imgname);
		template<typename T>
		void imitate(ShapeInfo &spinfo, const vector<cv::Point_<T>> &ptsList, const string &imgname)
		{
			spinfo.imgname = imgname;
			for (size_t i = 0; i < ptsList.size(); i++)
			{
				PointInfo pinfo;
				pinfo.x = ptsList[i].x;
				pinfo.y = ptsList[i].y;
				pinfo.pre = ptsInfos[i].pre;
				pinfo.next = ptsInfos[i].next;
				pinfo.id = ptsInfos[i].id;
				spinfo.ptsInfos.push_back(p);
			}
		}

	};
	class TrainingSetInfo
	{
	public:
		TrainingSetInfo(){}
		~TrainingSetInfo(){}
		vector<ShapeInfo> alShapeInfos;
		bool loadFromXml(const char* filename);
		void dump_to_shapeInfo(TiXmlNode *pParent);
		void get_attributes(TiXmlElement *pElement);
		int nSamples(){ return alShapeInfos.size(); }
	private:
		int shapeNums = 0;
		int ptsindex;
		int pre = 0;
	};
}

#endif


