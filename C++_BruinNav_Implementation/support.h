//
//  support.h
//  Project 4310
//
//  Created by Roy Sanga Lin on 3/13/17.
//  Copyright © 2017 Roy Sanga Lin. All rights reserved.
//

#ifndef support_h
#define support_h

#include <stdio.h>
#include "provided.h"
#include <vector>


bool operator>(const GeoCoord&a,const GeoCoord &b);
bool operator<(const GeoCoord&a,const GeoCoord &b);
bool operator==(const GeoCoord&a,const GeoCoord &b);
bool operator>(const StreetSegment&a,const StreetSegment &b);
bool operator<(const StreetSegment&a,const StreetSegment &b);
bool operator==(const StreetSegment&a,const StreetSegment &b);
bool operator!=(const GeoCoord&a,const GeoCoord &b);
std::string directionOfLine(const GeoSegment &gs);

struct GNode
{
private:
    GeoCoord geo;
    double distanceTraveled; //Distance From Start to This Node
    double priority; //The F() Value Answer?
    std::vector<GeoCoord> path;
public:
    GNode(GeoCoord g, int dT, int pr, std::vector<GeoCoord> pa)
    :geo(g.latitudeText, g.longitudeText), distanceTraveled(dT), priority(pr)
    {
        path = pa;
        path.push_back(this->getGeoC()); //Push Back so that we do the first two first
    }
    GeoCoord getGeoC() const
    {
        return geo;
    }
    double getdT() const
    {
        return distanceTraveled;
    }
    double getPriority() const
    {
        return priority;
    }
    void updatePriority(GeoCoord nextSegment) //Our F() Function
    {
        priority=distanceTraveled+fabs(distanceEarthMiles(this->getGeoC(), nextSegment)); //A*
    }
    void nextLevel(GNode previous) // i: direction
    {
        distanceTraveled = previous.getdT() + fabs(distanceEarthMiles(previous.getGeoC(), this->getGeoC()));
    }
    std::vector<GeoCoord> getPath() const
    {
        return path;
    }
    //RETURNS A VECTOR OF DIRECTION
    friend bool operator<(const GNode & a, const GNode & b) //WANT OPPOSITE SO QUEUE WILL DO THE OPPOSITE
    {
        return a.getPriority() > b.getPriority();
    }
};
#endif /* support_h */
