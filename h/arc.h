#ifndef ARC_H
#define ARC_H

#include <iostream>
#include <vector> 
#include "point.h"
using namespace std;

class arc {

    private: 
        string id; 
        string name;
        string o; 
        string d; 
        bool oneway; 
        int lanes; 
        string highway; 
        bool reversed; 
        double length; 
        vector<point> geometry; 
        int maxspeed; 
        double speed_kph; 
        double travel_time; 

    public:
        arc(string id);
        void afficher();
        
        // Setters pour initialiser les attributs
        void setName(string name);
        void setO(string o);
        void setD(string d);
        void setOneway(bool oneway);
        bool setLanes(int lanes);
        void setHighway(string highway);
        bool setReversed(bool reversed);
        bool setLength(double length);
        bool setGeometry(vector<point> geometry);
        bool setMaxspeed(int maxspeed);
        bool setSpeed_kph(double speed_kph);
        bool setTravel_time(double travel_time);

        // Getters car les attributs sont en private
        string getName();
        string getId();
        string getO();
        string getD();
        bool getOneway();
        int getLanes();
        string getHighway();
        bool getReversed();
        double getLength();
        vector<point> getGeometry();
        int getMaxspeed();
        double getSpeed_kph();
        double getTravel_time();

};

#endif