#include "provided.h"
#include <vector>
#include "MyMapFirstCompare.h"
#include <algorithm>
#include <iostream>

using namespace std;

class SegmentMapperImpl
{
public:
	SegmentMapperImpl();
	~SegmentMapperImpl();
	void init(const MapLoader& ml);
	vector<StreetSegment> getSegments(const GeoCoord& gc) const;
private:
    MyMapFirstCompare m_map;
    
    bool compareGeo(const GeoCoord& G1, const GeoCoord&G2)
    {
        return G1.latitudeText == G2.latitudeText && G2.longitudeText == G2.longitudeText;
    }
};

SegmentMapperImpl::SegmentMapperImpl()
{
    
}

SegmentMapperImpl::~SegmentMapperImpl()
{
    
}

void SegmentMapperImpl::init(const MapLoader& ml)
{
    for(int i = 0; i < ml.getNumSegments(); i++) //For each segment
    {
        StreetSegment s1;
        if(ml.getSegment(i, s1)) //puts segments into s1
        {
            for(int k = 0; k < s1.attractions.size(); k++) //Check Attractions First
            {
                GeoCoord aCoord = s1.attractions[k].geocoordinates;
                vector<StreetSegment>* attV = m_map.find(aCoord); //Sees if we find aCoord
                if(attV != nullptr)
                {
                    (*attV).push_back(s1);
                }
                else
                {
                    vector<StreetSegment> newA1; //Makes a new vector to associate
                    newA1.push_back(s1);
                    m_map.associate(aCoord, newA1); //Associates the coord and the vector
                }
            }

            GeoCoord g1 = s1.segment.start; //test start of segment
            vector<StreetSegment>* ss = m_map.find(g1); //Sees if we find it
            if(ss != nullptr)
            {
                if(find((*ss).begin(), (*ss).end(), s1) == (*ss).end())
                    (*ss).push_back(s1);
                //Sees if the segment is already in the vector
            }
            else
            {
                vector<StreetSegment> newS; //Makes a new vector to associate
                newS.push_back(s1);
                m_map.associate(g1, newS); //Associate the coord and the vector
            }
            
            GeoCoord g2 = s1.segment.end; //test end of segment
            vector<StreetSegment>* ss1 = m_map.find(g2); //See if we find ot
            if(ss1 != nullptr) //
            {
                if(find((*ss1).begin(), (*ss1).end(), s1) == (*ss1).end())
                    (*ss1).push_back(s1);
                //Sees if the segment is already in the vector
            }
            else
            {
                vector<StreetSegment> newS2; //Make a new vector to associate
                newS2.push_back(s1);
                m_map.associate(g2, newS2);//Associate the coord and the vector
            }
        }
    }
}

vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
	const vector<StreetSegment>* segments;
    segments = m_map.find(gc); //Returns the vector of segments
    if(segments == nullptr)
    {
        //if no segment was found return empty segment vector
        vector<StreetSegment> stupid;
        return stupid;
    }
    return (*segments);
	// This compiles, but may not be correct
}
//******************** SegmentMapper functions ********************************

// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
	m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
	delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
	m_impl->init(ml);
}

vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
	return m_impl->getSegments(gc);
}
