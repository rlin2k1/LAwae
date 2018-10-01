#include "provided.h"
#include <string>
#include "MyMap.h"
#include <iostream>
using namespace std;

class AttractionMapperImpl
{
public:
	AttractionMapperImpl();
	~AttractionMapperImpl();
	void init(const MapLoader& ml);
	bool getGeoCoord(string attraction, GeoCoord& gc) const;
private:
    MyMap<string, GeoCoord> m_map;
    string toLowerC(const string& attraction1) const
    {
        string temp;
        for(int i = 0; i < attraction1.size(); i++)
        {
            temp += tolower(attraction1[i]);
        }
        return temp;
    }
};

AttractionMapperImpl::AttractionMapperImpl()
{

}

AttractionMapperImpl::~AttractionMapperImpl()
{

}

void AttractionMapperImpl::init(const MapLoader& ml)
{
    for(int i = 0; i < ml.getNumSegments(); i++) //Go through every segment
    {
        StreetSegment temp;
        ml.getSegment(i, temp); //Gets segments in a temp street seg
        for(int k = 0; k < temp.attractions.size(); k++) //for each attraction
        {
            m_map.associate(toLowerC(temp.attractions[k].name), temp.attractions[k].geocoordinates);
            //Associate attraction name with geocoords
        }
    }
}

bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const
{
    //std::cerr << "ATTRACTION SIZE: " << m_map.size() << std::endl;
    const GeoCoord* temp;
    temp = m_map.find(toLowerC(attraction)); //put find into the temp
    if(temp != nullptr)
    {
        gc = *temp; //
        return true;  // This compiles, but may not be correct
    }
    return false;
}

//******************** AttractionMapper functions *****************************

// These functions simply delegate to AttractionMapperImpl's functions.
// You probably don't want to change any of this code.

AttractionMapper::AttractionMapper()
{
	m_impl = new AttractionMapperImpl;
}

AttractionMapper::~AttractionMapper()
{
	delete m_impl;
}

void AttractionMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
{
	return m_impl->getGeoCoord(attraction, gc);
}
