#ifndef COMBODEMOG_H
#define COMBODEMOG_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "raceDemogData.h"

/*
  class to represent combined demographic data 
*/
class demogCombo : public demogData {
    public:
        // constructor
        demogCombo(shared_ptr<demogData> t): demogData{"comboData",t->getState(),t->getpopOver65Count(),
            t->getpopUnder18Count(),t->getpopUnder5Count(),t->getBAupCount(),t->getHSupCount(),
            t->getUnderPovertyLineCount(), t->getPop(),t->getInfo()}, counties(1) {}

        demogCombo(string state): demogData{"comboData",state,0,
            0,0,0,0,0, 0,raceDemogData()}, counties(1) {}
      
      

        void add(shared_ptr<demogData> t){
            addState(t->getState());
            int pop = population + t->getPop();
            popOver65 = (t->getpopOver65Count()+getpopOver65Count())*100.0/pop;
            popUnder18 = (t->getpopUnder18Count() + getpopUnder18Count()) *100.0/pop;
            popUnder5 = (t->getpopUnder5Count() + getpopUnder5Count()) *100.0/pop;
            bachelorsOrHigher = (t->getBAupCount() + getBAupCount()) *100.0/pop;
            highSchoolOrHigher = (t->getHSupCount() + getHSupCount()) *100.0/pop;
            underPovertyLine = (t->getUnderPovertyLineCount() + getUnderPovertyLineCount());
            info += t->getInfo();
            population += t->getPop();
            counties++;
        }
           void add(demogData * t){
            addState(t->getState());
            int pop = population + t->getPop();
            popOver65 = (t->getpopOver65Count()+getpopOver65Count())*100.0/pop;
            popUnder18 = (t->getpopUnder18Count() + getpopUnder18Count()) *100.0/pop;
            popUnder5 = (t->getpopUnder5Count() + getpopUnder5Count()) *100.0/pop;
            bachelorsOrHigher = (t->getBAupCount() + getBAupCount()) *100.0/pop;
            highSchoolOrHigher = (t->getHSupCount() + getHSupCount()) *100.0/pop;
            underPovertyLine = (t->getUnderPovertyLineCount() + getUnderPovertyLineCount());
            info += t->getInfo();
            population += t->getPop();
            counties++;
        }

        int getCounties() const {return counties;}

        friend std::ostream& operator<<(std::ostream &out, const demogCombo &SD);
            void accept(Visitor &v);

    private:
        int counties;
};
#endif
