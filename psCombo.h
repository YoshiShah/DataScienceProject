#ifndef POLICECOMBODATA_H
#define POLICECOMBODATA_H

#include "raceDemogData.h"
#include "psData.h"
#include "regionData.h"
#include <memory>
#include <cassert>
using namespace std;

class psCombo : public regionData  {
public:
    //write psCombo constructor
    psCombo(string inS) : regionData{inS, inS, 0}, mentallyIll(0), fleeing(0), caseO65(0), caseU18(0), males(0), females(0), totalCases(0), racialData(raceDemogData()) {} //add
    
    //Getter and adder functions
    int getNumMentalI()const{return mentallyIll;}
    int getFleeingCount()const{return fleeing;}
    int getCasesOver65()const{return caseO65;}
    int getCasesUnder18()const{return caseU18;}
    raceDemogData getRacialData()const{return racialData;}
    int getWhiteCount() const{return racialData.getWhiteCount();}
    int getBlackCount() const {return racialData.getBlackCount();}
    int getnumMales()const{return males;}
    int getnumFemales()const{return females;}
    int getNumberOfCases()const{return totalCases;}
    void addMentalI(int inSum){mentallyIll += inSum;}
    void addFleeing(int inSum ){fleeing += inSum; }
    void addCasesO65(int inSum){caseO65 += inSum;}
    void addCaseU18(int inSum) {caseU18 += inSum;}
    void addCaseO18U65(int inSum){caseU18 += inSum;}
    void addFlee(int inSum) {fleeing += inSum;}
    void addMale(int inSum) {males+= inSum;}
    void addFemale(int inSum) {females += inSum;}

    // Getter functions to print out in the .cpp
    int getNumMentalIc() const{return mentallyIll;}
    int getFleeingCountc()const{return fleeing;}
    int getCasesOver65c()const{return caseO65;}
    int getCasesUnder18c()const{return caseU18;}
    int getCasesOver18c()const {return caseO18U65;}
    raceDemogData getRacialDatac()const{return racialData;}
    int getnumMalesc()const{return males;}
    int getnumFemalesc()const{return females;}
    int getNumberOfCasesc()const{return totalCases;}

    void add(shared_ptr<psData> i){
        addState(i->getState());
        addMentalI(i->getIfMentalI());
        addFleeing(i->getIfFlee());
        addCasesO65(i->getIfO65());
        addCaseU18(i->getIfU18());
        addCaseO18U65(i->getIfO18U65());
        
        addMale(i->getIfMale());
        addFemale(i->getIfFemale());
        racialData.add(i->getInfo());
        totalCases++;
    }
        void add(psData * i){
        addState(i->getState());
        addMentalI(i->getIfMentalI());
        addFleeing(i->getIfFlee());
        addCasesO65(i->getIfO65());
        addCaseU18(i->getIfU18());
        addCaseO18U65(i->getIfO18U65());
        
        addMale(i->getIfMale());
        addFemale(i->getIfFemale());
        racialData.add(i->getInfo());
        totalCases++;
    }
     
    friend std::ostream& operator<<(std::ostream &out, const psCombo& PD);
    void accept(Visitor &v);
protected:
    const string state;
    int mentallyIll;
    int fleeing;
    int caseO65;
    int caseU18;
    int caseO18U65;
    raceDemogData racialData;
    int males;
    int females;
    int totalCases;
};

#endif