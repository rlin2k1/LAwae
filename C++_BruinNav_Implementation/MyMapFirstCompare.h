//
//  MyMapFirstCompare.h
//  Project 4
//
//  Created by Roy Sanga Lin on 3/7/17.
//  Copyright © 2017 Roy Sanga Lin. All rights reserved.
//

#ifndef MyMapFirstCompare_h
#define MyMapFirstCompare_h

#include <iostream>
#include <stdio.h>
#include "support.h"
#include "provided.h"
#include <vector>
#include <string>

using namespace std;

// Skeleton for the MyMapFirstCompare class template.  You must implement the first six
// member functions.
struct Node; //To define for later

class MyMapFirstCompare
{
public:
    MyMapFirstCompare()
    {   //Sets the size and the root to default values;
        m_counter = 0;
        rootPtr = nullptr;
    }
    ~MyMapFirstCompare()
    {
        //Calls helper destructor
        clear();
    }
    void clear()
    {
        //Reset size and gets rid of the rest of the nodes in the tree
        m_counter = 0;
        cleanUpAuxilliary(rootPtr);
    }
    int size() const
    {
        //return counter
        return m_counter;
    }
    void associate(const GeoCoord& key, const vector<StreetSegment>& value)
    {
        if(rootPtr == nullptr) //Makes the root of the tree since nothing was made yet
        {
            rootPtr = new Node(key, value);
            m_counter++;
            return;
        }
        Node *cur = rootPtr; //Creates iterator of cur
        for (;;)
        {
            if (key == cur->m_key) //Checks if the node already exists
            {
                cur->m_value = value; //Update the value
                return;
            }
            if (key < cur->m_key) //If key is less than the current key
            {
                if (cur->left != nullptr)
                    cur = cur->left; //Go left to try to find
                else
                {
                    cur->left = new Node(key, value); //Make a new Node
                    cur = cur->left;
                    m_counter++;
                    return;
                }
            }
            else if (key > cur->m_key) //If key is greater than the current key
            {
                if (cur->right != nullptr)
                    cur = cur->right; //Go to the right to try to find
                else
                {
                    cur->right = new Node(key, value); //Make a new Node
                    cur = cur->right;
                    m_counter++;
                    return;
                }
            }
        }
    }
    // for a map that can't be modified, return a pointer to const ValueType
    const vector<StreetSegment>* find(const GeoCoord& key) const
    {
        Node* ptr = rootPtr;
        while (ptr != NULL) //Go until a nullpointer
        {
            if (key == ptr->m_key) //checks key for the current value
                return &(ptr->m_value); //return the value at the poiunter
            else if (key < ptr->m_key) //Check if the key is less than curr value
                ptr = ptr->left; //Go to the left
            else
                ptr = ptr->right; //Go to the right
        }
        return nullptr; // nope

    }
    
    const GeoCoord* firstFind(const GeoCoord& key) const
    {
        Node* ptr = rootPtr;
        Node* parent = rootPtr;
        
        int currentMax = 0;
        while (ptr != NULL) //Go until a nullpointer
        {
            if (key == ptr->m_key) //checks key for the current value
                return &(ptr->m_key); //return the key at the pointer
            int tempMax = 0;
            int len = ptr->m_key.latitudeText.length();
            for(int i = 0; i < len; i++) {
                int testLetter = key.latitudeText[i] - '0';
                int keyLetter = ptr->m_key.latitudeText[i] - '0';
                
                if (testLetter < keyLetter) {
                    if(tempMax >= currentMax) {
                        currentMax = tempMax;
                    }
                    else {
                        return &(parent->m_key);
                    }
                    parent = ptr;
                    ptr = ptr -> left;
                    continue;
                }
                else if(testLetter > keyLetter) {
                    if(tempMax >= currentMax) {
                        currentMax = tempMax;
                    }
                    else {
                        return &(parent->m_key);
                    }
                    parent = ptr;
                    ptr = ptr -> right;
                    continue;
                }
                tempMax++;
                cout << tempMax << endl;
                if(tempMax == 7) {
                    return &(ptr->m_key);
                }
            }
        }
        return nullptr; // nope
    }
    
    // for a modifiable map, return a pointer to modifiable ValueType THIS IS DONE
    vector<StreetSegment>* find(const GeoCoord& key)
    {
        return const_cast<vector<StreetSegment>*>(const_cast<const MyMapFirstCompare*>(this)->find(key));
    }
    
    // C++11 syntax for preventing copying and assignment
    MyMapFirstCompare(const MyMapFirstCompare&) = delete;
    MyMapFirstCompare& operator=(const MyMapFirstCompare&) = delete;

private:
    struct Node
    {
        Node(GeoCoord key, vector<StreetSegment> value)
        {
            m_key = key;
            m_value = value;
            left = nullptr;
            right = nullptr;
        }
        GeoCoord m_key;
        vector<StreetSegment> m_value;
        Node *left;
        Node *right;
    };
    Node *rootPtr;
    int m_counter;
    void cleanUpAuxilliary(Node* cur)
    {
        if (cur == nullptr) //check if its the nullptr
            return;
        if(cur != nullptr) //else
        {
            cleanUpAuxilliary(cur->right); //Go right
            cleanUpAuxilliary(cur-> left); //Go left
            delete cur; //delete cur
            cur = nullptr;
        }
    }
};
#endif /* MyMapFirstCompare_h */
