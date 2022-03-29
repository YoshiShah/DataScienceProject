#ifndef DEMOG_H
#define DEMOG_H

#include "regionData.h"
#include "raceDemogData.h"
#include <string>
#include<iostream>
#include <cmath>
#include <memory>
using namespace std;

/*
  class to represent county demographic data
  from CORGIS - LAB01 starter - replace with your FULL version!
*/
class demogData : public regionData, public std::enable_shared_from_this<demogData> {
  public:
    // Constructors
    demogData(string inN, string inS, double in65, double in18,
        double in5, double bOrH, double hsOrH, double pov,int totPop14, int FN, int A, int B, int L, int HI, int MR, int W, int WNH) :
            regionData{inN, inS, totPop14},popOver65(in65), popUnder18(in18),
            popUnder5(in5), bachelorsOrHigher(bOrH), highSchoolOrHigher(hsOrH), underPovertyLine(round(pov*totPop14)), 
            info(raceDemogData(FN,A,B,L,HI,MR,W,WNH,totPop14)) {}
            
    // Takes in integer counts of the population
    demogData(string inN, string inS, int in65, int in18,
        int in5, int bOrH, int hsOrH, int pov,int totPop14, raceDemogData a) :
            regionData{inN, inS, totPop14},popOver65(in65*100.0f / totPop14), popUnder18(in18*100.0f / totPop14),
            popUnder5(in5*100.0f / totPop14), bachelorsOrHigher(bOrH*100.0f / totPop14),
            highSchoolOrHigher(hsOrH*100.0f / totPop14), underPovertyLine(pov), info(a) {}

 
    int getpopOver65Count() const {return (round)(popOver65/100.0*population);}
    int getpopUnder18Count() const{return (round)(popUnder18/100.0*population);}
    int getpopUnder5Count() const {return (round)(popUnder5/100.0*population);}
    int getBAupCount() const {return (round)(bachelorsOrHigher/100.0*population);}
    int getHSupCount() const {return (round)(highSchoolOrHigher/100.0*population);}
    int getUnderPovertyLineCount() const {return underPovertyLine;}
    int getPop() const {return population;}
    double getpopOver65() const {return popOver65;}
    double getpopUnder18() const  {return popUnder18;}
    double getpopUnder5() const {return popUnder5;}
    double getBAup() const {return bachelorsOrHigher;}
    double getHSup() const {return highSchoolOrHigher;}
    double getUnderPovertyLine() const {return 100.0f*((double)(underPovertyLine))/population;}
    double getBelowPoverty() const {return 100.0f*((double)(underPovertyLine))/population;}
    raceDemogData getInfo() const {return info;}
    raceDemogData getCommunityRaceMix() const {return info;}
    int getBelowPovertyCount() const  {return underPovertyLine;}

    friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

    void accept(Visitor &v);
protected:
     double popOver65;
     double popUnder18;
     double popUnder5;
     double bachelorsOrHigher;
     double highSchoolOrHigher;
     int underPovertyLine;
     raceDemogData info;

};
#endif
