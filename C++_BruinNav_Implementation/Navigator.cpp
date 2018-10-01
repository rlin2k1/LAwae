#include "provided.h"
#include "MyMap.h"
#include "support.h"
#include <queue>
#include <iostream>
#include <math.h>
#include <ctime>

using namespace std;

class NavigatorImpl
{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(GeoCoord start, float end, vector<NavSegment>& directions) const;
private:
    MapLoader m_loader;
    AttractionMapper m_amapper;
    SegmentMapper m_smapper;
    StreetSegment mapSegment(GeoCoord a, GeoCoord b) const
    {
        vector<StreetSegment> v = m_smapper.getSegments(a);
        vector<StreetSegment> w = m_smapper.getSegments(b);
        for(int i = 0; i < v.size(); i++)
            for(int k = 0; k < w.size(); k++)
                if(v[i] == w[k])
                {   //Makes a new PROPER STREETSEGMENT
                    StreetSegment temp;
                    temp.streetName = v[i].streetName;
                    GeoSegment tempG;
                    tempG.start = a;
                    tempG.end = b;
                    temp.segment = tempG;
                    return temp;
                    //TO DO ADD ATTRACTION
                }
        StreetSegment trash;
        return trash;
    }
    double distanceC(GeoCoord a, GeoCoord b) const
    {
        return distanceEarthMiles(a, b); //Finds the distance between two geoCoords
    }
    
    vector<NavSegment> createdSegs(const vector<StreetSegment> ss1, const vector<double> distance) const
    {
        //cout << ss1.size() << endl;
        //cout << distance.size() << endl;
        
        vector<NavSegment> returned;
        //cout << "fdsa " << endl;
        //cout << ss1[0].streetName << endl;
        
        string prevStreet = ss1[0].streetName;
        GeoSegment s1 = ss1[0].segment;
        
        //double angleProceed = angleOfLine(ss1[0].segment);
        
        for(int i = 0; i < ss1.size(); i++)
        {
            //cout << "REACHED " << endl;
            if(prevStreet == ss1[i].streetName)
            {
                s1 = ss1[i].segment;
                NavSegment a(directionOfLine(s1), prevStreet, distance[i], ss1[i].segment);
                //angleProceed = angleOfLine(ss1[i].segment);
                returned.push_back(a);
                
            }
            else
            {
                //Make a new TURN NavSegment
                double angleTurn = angleBetween2Lines(s1, ss1[i].segment);
                string turnD;
                if(angleTurn >= 180.0)
                    turnD = "right";
                else
                    turnD = "left";
                NavSegment b(turnD, ss1[i].streetName);
                
                returned.push_back(b);
                prevStreet = ss1[i].streetName;
                s1 = ss1[i].segment;
                //angleProceed = angleOfLine(ss1[i].segment);
                i--;
            }
        }
        return returned;
    }
    
    vector<GeoCoord> pathFind(GeoCoord AttractionStart, float end) const
    {
        //DONE LOAD FOR EVERYTHING
        
        queue<GNode> open; //Make a priority Queue THAT PUTS LOWER PRIORITY FIRST
        
        GNode* next; //Next One - Changes Alot!
        
        next = nullptr; //TO MAKE IT NOT DANGLING
        
        GeoCoord startG = AttractionStart;
        
        vector<GeoCoord> pathy; //Make A Vector Of the Current Path
        
        GNode startGN(startG, 0, 0, pathy); //Makes the first Node
        
        GNode current = startGN;//Makes Current the START
        
        //current.updatePriority(endG); //Makes Priority of First Node
        
        open.push(current); //Pushes First Node onto the Priority Queue
        
        //MyMap<GeoCoord, double> notVisited;
        
        MyMap<GeoCoord, double> visited;//Makes Sure we don't A Visited Node onto the Queue Again
        
        while(!(open.empty())) //While the Queue is not empty
        {
            //cout << "Reached " << endl;
            current = open.front(); //Sets the Current to Be tested to be the one on the Top of Queue
            //FIX LATER
            
            open.pop();
            //cout << "Top Priority: " << current.getPriority() << endl;
            //cout << "Lat: << " << current.getGeoC().latitudeText << " Long: " << current.getGeoC().longitudeText;
            
            if(current.getdT() >= end)
            {
                /* We are finished! Implement the ending Code Where we Trace back the vectors to Construct GeoSegment -> Street Segments to find the Valid Street Segment */
                /*ALSO DO NOT FORGET TO DELETE ALL THE NODES AT THE VERY END SO THE BOOLS ARE STILL THERE. DO NOT FORGET */
                //cout << "FOUND" << endl;
                return current.getPath();
            }
            //cerr <<"Reached2" << endl;
            visited.associate(current.getGeoC(), current.getPriority());
            //cerr <<"Reached1 " << endl;
            
            //PARENT IS CURRENT NODE
            //CHILD IS NEXT NODE
            
            //We are now going to generate All the moves possible due to the CURRENT GEO COORD
            
            vector<StreetSegment> ss = m_smapper.getSegments(current.getGeoC());
            //cerr <<"reached 3" << endl;
            for(int i = 0; i < ss.size(); i++)
            {
                //*****WHAT IF GEOCOORD IS NOT ON THE START OR THE END *****
                if(ss[i].attractions.size() != 0)
                {
                    for(int k = 0; k < ss[i].attractions.size(); k++)
                    {
                        GNode* next2 = new GNode(ss[i].attractions[k].geocoordinates, current.getdT(), current.getPriority(), current.getPath());
                        next2->nextLevel(current);
                        //next2->updatePriority(endG);
//                        if(ss[i].attractions[k].geocoordinates == endG)
//                        {
//                            double* test1 = visited.find(next2->getGeoC());
//                            if(test1 != nullptr)
//                            {
//                                if(next2->getPriority() < *test1) //DON'T THINK WE NEED THIS
//                                {
//                                    visited.associate(next2->getGeoC(), next2->getPriority());
//                                    //open.push(*next2); //Just Added
//                                }
//                            }
//                            else //if(test1 == nullptr)
//                            {
//                                open.push(*next2);
//                                visited.associate(next2->getGeoC(), next2->getPriority());
//                            }
//                        }
//                        delete next2;
//                        next2 = nullptr;
                    }
                }
                //START TO GENERATE THE CHILD NODE
                if(ss[i].segment.start == current.getGeoC() || ss[i].segment.end == current.getGeoC())
                {
                    if(ss[i].segment.start == current.getGeoC())
                        next = new GNode(ss[i].segment.end, current.getdT(), current.getPriority(), current.getPath());
                    else if(ss[i].segment.end == current.getGeoC())
                        next = new GNode(ss[i].segment.start, current.getdT(), current.getPriority(), current.getPath());
                    
                    next->nextLevel(current);
                    //next->updatePriority(endG);
                    
                    double* test1 = visited.find(next->getGeoC());
                    if(test1 != nullptr)
                    {
                        if(next->getPriority() < *test1) //DON'T THINK WE NEED THIS
                        {
                            visited.associate(next->getGeoC(), next->getPriority());
                            //open.push(*next);
                        }
                    }
                    else //if(test1 == nullptr)
                    {
                        open.push(*next);
                        visited.associate(next->getGeoC(), next->getPriority());
                    }
                    delete next;
                    next = nullptr;
                }
                else if(ss[i].segment.start != current.getGeoC() && ss[i].segment.end != current.getGeoC()) //GEOCOORD IS NOT ON THE START OR THE END. NEED TO TEST BOTH DIRECTION
                {
                    next = new GNode(ss[i].segment.start, current.getdT(), current.getPriority(), current.getPath());
        
                    next->nextLevel(current); //Changes it to Distance Traveled toN
                    //next->updatePriority(endG);
                    
                    double* test1 = visited.find(next->getGeoC());
                    if(test1 != nullptr)
                    {
                        if(next->getPriority() < *test1) //DON'T THINK WE NEED THIS
                        {
                            //open.push(*next);
                            visited.associate(next->getGeoC(), next->getPriority());
                        }
                    }
                    else //if(test1 == nullptr)
                    {
                        open.push(*next);
                        visited.associate(next->getGeoC(), next->getPriority());
                    }
                    delete next;
                    next = nullptr;
                    //***************************************************************************************************
                    
                    GNode* next1 = new GNode(ss[i].segment.end, current.getdT(), current.getPriority(), current.getPath());
                    next1->nextLevel(current);
                    //next1->updatePriority(endG);
                    
                    double* test2 = visited.find(next1->getGeoC());
                    if(test2 != nullptr)
                    {
                        if(next1->getPriority() < *test2) //DON'T THINK WE NEED THIS
                        {
                            //open.push(*next);
                            visited.associate(next1->getGeoC(), next1->getPriority());
                        }
                    }
                    else //if(test2 == nullptr)
                    {
                        open.push(*next1);
                        visited.associate(next1->getGeoC(), next1->getPriority());
                    }
                    delete next1;
                    next1 = nullptr;
                    
                }
            }
        }
        //notVisited.clear(); THIS WILL DOUBLE CLEAR
        //visited.clear(); //THIS WILL DOUBLE CLEAR
        vector<GeoCoord> empty;
        //cout << "Not Found" << endl;
        return empty;
    }
};

NavigatorImpl::NavigatorImpl()
{
    
}

NavigatorImpl::~NavigatorImpl()
{
    
}

bool NavigatorImpl::loadMapData(string mapFile)
{
    m_loader.load(mapFile);
    m_amapper.init(m_loader);
    m_smapper.init(m_loader);
	return true;  // This compiles, but may not be correct
}

NavResult NavigatorImpl::navigate(GeoCoord start, float end, vector<NavSegment> &directions) const
{
    
    GeoCoord startG;
//    cout << "Starting Latitude " << start.latitudeText << " Starting Longitude " << start.longitudeText;
    //GeoCoord endG;
    
    if(!(m_loader.getGeoCoordS(start, startG))) //Gets Starting GeoCoord
    {
        return NAV_BAD_SOURCE;
    }
    
//    cout << "Think Starting Latitude " << startG.latitudeText << " Think Starting Longitude " << startG.longitudeText;
    
    vector <StreetSegment> ss;
    if(end == 0)
    {
        directions.clear();
        ss = m_smapper.getSegments(startG);
        NavSegment a(directionOfLine(ss[0].segment), ss[0].streetName, 0, ss[0].segment);
        directions.push_back(a);
        return NAV_SUCCESS;
    }
    vector<double> distances;
    vector<GeoCoord> path = pathFind(startG, end);
    if(path.empty())
        return NAV_NO_ROUTE;
    //cout << "THIS IS PATH: " << path.size() << endl;
    if(path.size() != 0)
    {
        for(int i = 0; i < path.size() - 1; i++)
        {
            ss.push_back(mapSegment(path[i], path[i+1]));
            distances.push_back(distanceC(path[i], path[i + 1]));
        }
    }
//    for (int i = 0; i < ss.size(); i++)
//        cout << ss[i].streetName << endl;
    //cout << "Hello" << endl;
    vector<NavSegment> ns = createdSegs(ss, distances);
    directions = ns;
	return NAV_SUCCESS;  // This compiles, but may not be correct
}
//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(GeoCoord start, float end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}
