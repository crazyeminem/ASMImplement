#ifndef _TRAININGSETINFO_H_
#define _TRAININGSETINFO_H_
#include <vector>
#include <string>
#include "txml/tinystr.h"
#include "txml/tinyxml.h"
using namespace std;
namespace ASMMmodel{
	struct PointInfo
	{
		double x;
		double y;
		int  id;
		int pre;
		int next;
	};
	struct ShapeInfo
	{
		string imgname;
		vector<PointInfo> ptsInfos;
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


