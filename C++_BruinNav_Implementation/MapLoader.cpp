#include "provided.h"
#include "support.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
int counter = 0; // GET RID OF LATEr
class MapLoaderImpl
{
public:
	MapLoaderImpl();
	~MapLoaderImpl();
	bool load(string mapFile);
	size_t getNumSegments() const;
	bool getSegment(size_t segNum, StreetSegment& seg) const;
    bool getGeoCoordS(GeoCoord start, GeoCoord& gc) const;
private:
    vector<StreetSegment> m_streets;
    void setCoords(string &coord, string &lat1, string &long1, string &lat2, string &long2)
    {
        int i = 0;
        while(i < coord.size())
        {
            while(coord[i] == ' ') //Go through the spaces
                i++;
            while(isdigit(coord[i]) || coord[i] == '.' || coord[i] == '-')
            {
                lat1 = lat1 + coord[i]; //Put latitude into the temp variable
                i++;
            }
            while(coord[i] == ' ' || coord[i] == ',') //Go through spaces and commas
                i++;
            while(isdigit(coord[i]) || coord[i] == '.' || coord[i] == '-') //Put long into the temp variable
            {
                long1 = long1 + coord[i];
                i++;
            }
            while(coord[i] == ' ') //Go through the spaces
                i++;
            while(isdigit(coord[i]) || coord[i] == '.' || coord[i] == '-') //Put latitude into the lat2
            {
                lat2 = lat2 + coord[i];
                i++;
            }
            while(coord[i] == ' ' || coord[i] == ',') //Go through spaces and commas
                i++;
            while(isdigit(coord[i]) || coord[i] == '.' || coord[i] == '-')
            {
                long2 = long2 + coord[i];//Put longitude  into long2
                i++;
            }
        }
    }

};

MapLoaderImpl::MapLoaderImpl()
{
    
}

MapLoaderImpl::~MapLoaderImpl()
{
    
}


bool MapLoaderImpl::load(string mapFile)
{
    ifstream ifs(mapFile);
    if(!ifs)
    {
        return false; //map doesnt load
    }
    string street;
    while(getline(ifs, street))
    {
        counter++;
        //cerr << counter << endl;
        StreetSegment temp;
        temp.streetName = street;
        //cerr << temp.streetName << endl;
        string coord;
        getline(ifs, coord);
        string lat1;
        string long1;
        string lat2;
        string long2;
        setCoords(coord, lat1, long1, lat2, long2);
        temp.segment.start.latitudeText = lat1;
        temp.segment.start.latitude = stod(lat1);
        //cerr <<temp.segment.start.latitudeText << endl;
        temp.segment.start.longitudeText = long1;
        temp.segment.start.longitude = stod(long1);
        //cerr <<temp.segment.start.longitudeText << endl;
        temp.segment.end.latitudeText = lat2;
        temp.segment.end.latitude = stod(lat2);
        //cerr <<temp.segment.end.latitudeText << endl;
        temp.segment.end.longitudeText = long2;
        temp.segment.end.longitude = stod(long2);
        //cerr <<temp.segment.end.longitudeText << endl;
        
        string attract; //Attraction number
        getline(ifs, attract);
        //cerr << attract << endl;
        for(int i = 0; i < stoi(attract); i++) //Go through the attractions
        {
            string aName;
            string alat1;
            string along1;
            string attractCoord;
            getline(ifs, attractCoord);
            //Go through just like going though the latitude and longitude 
            int k = 0;
            while(attractCoord[k] == ' ')
                k++;
            while(attractCoord[k] != '|')
            {
                aName = aName + attractCoord[k];
                k++;
            }
            k++; // To get past the brackets
            while(attractCoord[k] == ' ')
                k++;
            while(isdigit(attractCoord[k]) || attractCoord[k] == '.' || attractCoord[k] == '-')
            {
                alat1 = alat1 + attractCoord[k];
                k++;
            }
            while(attractCoord[k] == ' ' || attractCoord[k] == ',')
                k++;
            while(isdigit(attractCoord[k]) || attractCoord[k] == '.' || attractCoord[k] == '-')
            {
                along1 = along1 + attractCoord[k];
                k++;
            }
            Attraction att;
            att.name = aName;
            //cerr << att.name << endl;
            att.geocoordinates.latitudeText = alat1;
            att.geocoordinates.latitude = stod(alat1);
            //cerr << att.geocoordinates.latitude << endl;
            att.geocoordinates.longitudeText = along1;
            att.geocoordinates.longitude = stod(along1);
            //cerr << att.geocoordinates.longitude << endl;
            temp.attractions.push_back(att);
        }
        m_streets.push_back(temp);
    }
    return true;  // This compiles, but may not be correct
}


size_t MapLoaderImpl::getNumSegments() const
{
	return m_streets.size(); // This compiles, but may not be correct
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
    if(segNum < m_streets.size())
    {
        seg = m_streets[segNum];
        return true;  // This compiles, but may not be correct
    }
    return false;
}

bool MapLoaderImpl::getGeoCoordS(GeoCoord start, GeoCoord& gc) const
{
    for ( const auto& i : m_streets ) {
        if(start == i.segment.start) {
            gc = i.segment.start;
            return true;
        }
        else if(start == i.segment.end) {
            gc = i.segment.end;
            return true;
        }
        else if(start.latitude < i.segment.end.latitude && start.latitude > i.segment.start.latitude && start.longitude < i.segment.end.longitude && start.longitude > i.segment.start.latitude) {
            //Can Add Choice
            gc = i.segment.start;
            return true;
        }
        else if(start.latitude > i.segment.end.latitude && start.latitude < i.segment.start.latitude && start.longitude > i.segment.end.longitude && start.longitude < i.segment.start.latitude) {
            //Can Add Choice
            gc = i.segment.start;
            return true;
        }
    }
    return true;
}

//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
	m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
	delete m_impl;
}

bool MapLoader::load(string mapFile)
{
	return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
	return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
   return m_impl->getSegment(segNum, seg);
}

bool MapLoader::getGeoCoordS(GeoCoord start, GeoCoord& gc) const
{
    return m_impl->getGeoCoordS(start, gc);
}

