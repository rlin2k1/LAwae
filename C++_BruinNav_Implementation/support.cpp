//
//  support.cpp
//  Project 4310
//
//  Created by Roy Sanga Lin on 3/13/17.
//  Copyright © 2017 Roy Sanga Lin. All rights reserved.
//

#include "support.h"
bool operator>(const GeoCoord&a,const GeoCoord &b)
{
    if(a.latitude > b.latitude)
        return true;
    if(a.latitude == b.latitude)
    {
        if(a.longitude > b.longitude)
            return true;
    }
    return false;
}

bool operator<(const GeoCoord&a,const GeoCoord &b)
{
    if(a.latitude < b.latitude)
        return true;
    if(a.latitude == b.latitude)
    {
        if(a.longitude < b.longitude)
            return true;
    }
    return false;
}
bool operator==(const GeoCoord&a,const GeoCoord &b)
{
    if(a.latitude == b.latitude && a.longitude == b.longitude)
        return true;
    return false;
}

bool operator>(const StreetSegment&a,const StreetSegment &b)
{
    if(a.segment.start > b.segment.start)
        return true;
    if(a.segment.start == b.segment.start)
    {
        if(a.segment.end > b.segment.end)
            return true;
    }
    return false;
}

bool operator<(const StreetSegment&a,const StreetSegment &b)
{
    if(a.segment.start < b.segment.start)
        return true;
    if(a.segment.start == b.segment.start)
    {
        if(a.segment.end < b.segment.end)
            return true;
    }
    return false;
}

bool operator==(const StreetSegment&a,const StreetSegment &b)
{
    if(a.segment.start == b.segment.start && a.segment.end == b.segment.end)
        return true;
    return false;
}

bool operator!=(const GeoCoord&a,const GeoCoord &b)
{
    if(a.latitude != b.latitude && a.longitude != b.longitude)
        return true;
    return false;
}
//string directionOfLine(const GeoSegment& gs)
std::string directionOfLine(const GeoSegment& gs)
{
    double angle = angleOfLine(gs);
    if(0 <= angle && angle <= 22.5)
        return "east";
    else if(22.5 < angle && angle <= 67.5)
        return "northeast";
    else if(67.5 < angle && angle <= 112.5)
        return "north";
    else if(112.5 < angle && angle <= 157.5)
        return "northwest";
    else if(157.5 < angle && angle <= 202.5)
        return "west";
    else if(202.5 < angle && angle <=247.5)
        return "southwest";
    else if(247.5 < angle && angle <= 292.5)
        return "south";
    else if(292.5 < angle && angle <= 337.5)
        return "southeast";
    else if(337.5 < angle && angle < 360)
        return "east";
    else
        return "no direction";
}

