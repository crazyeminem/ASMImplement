
#include "TrainingSetInfo.h"


namespace ASMMmodel{
	void ShapeInfo::imitate(ShapeInfo &spinfo ,const ShapeVector& shapvec, const string &imgname)
	{
		spinfo.imgname = imgname;
		for (size_t i = 0; i <ptsInfos.size();i++)
		{
			PointInfo p;
			p.id = ptsInfos[i].id;
			p.pre =ptsInfos[i].pre;
			p.next = ptsInfos[i].next;
			p.x = shapvec(2 * i, 0);
			p.y = shapvec(2 * i + 1, 0);
			spinfo.ptsInfos.push_back(p);
		}
	
	}
	
	void TrainingSetInfo::get_attributes(TiXmlElement *pElement)
	{
		if (!pElement)
		{
			return;
		}
		PointInfo pInfo;
		TiXmlAttribute *pAttrib = pElement->FirstAttribute();
		int ival;
		double dval;
		if (pAttrib)
		{
			string aName = pAttrib->Name();
			string eName = pElement->Value();
			if (aName == "fileName")
			{
				ptsindex = -1;
				shapeNums++;
				ShapeInfo  sp;
				sp.imgname = pAttrib->Value();
				alShapeInfos.push_back(sp);
				return;
			}
			if (eName == "Feature")
			{
				PointInfo pi;
				pre = 0;
				while (pAttrib)
				{
					string pname = pAttrib->Name();
					if (pname == "id")
					{
						pAttrib->QueryIntValue(&pi.id);
					}
					if (pname == "x")
					{
						pAttrib->QueryDoubleValue(&pi.x);
					}
					if (pname == "y")
					{
						pAttrib->QueryDoubleValue(&pi.y);
					}
					pAttrib = pAttrib->Next();

				}
				alShapeInfos[shapeNums - 1].ptsInfos.push_back(pi);
				ptsindex++;
			}

			if (eName == "Target"&&pre == 0)
			{
				pAttrib->QueryIntValue(&alShapeInfos[shapeNums - 1].ptsInfos[ptsindex].pre);
				pre = 1;
			}
			else if (eName == "Target"&&pre == 1)
			{
				pAttrib->QueryIntValue(&alShapeInfos[shapeNums - 1].ptsInfos[ptsindex].next);
			}

		}
	}
	void TrainingSetInfo::dump_to_shapeInfo(TiXmlNode *pParent)
	{
		if (!pParent) return;

		TiXmlNode* pChild;
		TiXmlText* pText;
		int t = pParent->Type();
		int num;

		switch (t)
		{
		case TiXmlNode::TINYXML_DOCUMENT:
			//printf("Document");
			break;

		case TiXmlNode::TINYXML_ELEMENT:
			//printf("Element [%s]", pParent->Value());
			get_attributes(pParent->ToElement());
			break;

		case TiXmlNode::TINYXML_COMMENT:
			//printf("Comment: [%s]", pParent->Value());
			break;

		case TiXmlNode::TINYXML_UNKNOWN:
			//printf("Unknown");
			break;

		case TiXmlNode::TINYXML_TEXT:
			pText = pParent->ToText();
			//printf("Text: [%s]", pText->Value());
			break;

		case TiXmlNode::TINYXML_DECLARATION:
			//printf("Declaration");
			break;
		default:
			break;
		}
		//printf("\n");
		for (pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
		{
			dump_to_shapeInfo(pChild);
		}
	}
	bool TrainingSetInfo::loadFromXml(const char* filename)
	{
		TiXmlDocument doc(filename);
		bool loadOkay = doc.LoadFile();
		if (loadOkay)
		{
			//printf("\n%s:\n", filename);
			//dump_to_stdout(&doc);
			dump_to_shapeInfo(&doc);

		}
		else
		{
			printf("Failed to load file \"%s\"\n", filename);
		}
		return loadOkay;
	}
}
