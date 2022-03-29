#ifndef POLICE_H
#define POLICE_H

#include <string>
#include <iostream>
#include <utility>
#include "regionData.h"
#include "raceDemogData.h"
#include <memory>
using namespace std;

/*
  class to represent police shooting data
  from CORGIS
*/
class psData : public regionData, public std::enable_shared_from_this<psData> {
  public:
    // Constructor
    psData(string inState, string maleOrFemale, string r, string c, string fleeing, string n, bool mi, int ag) :
        regionData{c,inState},  age(ag), gender(maleOrFemale),race(r),
        signsOfMentalIllness(mi),flee(fleeing), name(n){}

    // Getter functions
    int getIfMentalI(){
        if(signsOfMentalIllness) {
            return 1;
        }
        return 0;
    }

    int getIfO65(){
        if(age >= 65) {
            return 1;
        }
        return 0;
    }

    int getIfU18(){
        if(age <= 18) {
            return 1;
        }
        return 0;
    }

    int getIfMale(){
        if(gender == "M") {
            return 1;
        }
        return 0;
    }

    int getIfFemale(){
        if(gender == "F") {
            return 1;
        }
        return 0;
    }

    int getIfFlee(){
        if(flee == "Foot" || flee == "Car" || flee == "Other") {
            return 1;
        }
        return 0;
    }

    int getIfO18U65(){
        if(age > 18 && age < 65) {
            return 1;
        }
        return 0;
    }

    string getRace() {return race;}

    raceDemogData getInfo(){
        if(race == "W") {
            return raceDemogData(0,0,0,0,0,0,1,1,1);
        } else if (race == "H") {
            return raceDemogData(0,0,0,1,0,0,0,0,1);
        } else if (race == "A") {
            return raceDemogData(0,1,0,0,0,0,0,0,1);
        } else if(race == "B") {
            return raceDemogData(0,0,1,0,0,0,0,0,1);
        } else if(race == "O") {
            return raceDemogData(0,1,0,0,0,0,0,1,1);
        } else {
            return raceDemogData();
        }
    }

    friend std::ostream& operator<<(std::ostream &out, const psData &PD);
    void accept(class Visitor &v);
    void toString(ostream& os) const
    {
        os;
    }

private:
    string name;
    int age;
    string gender;
    string race;
    string county;
    bool signsOfMentalIllness;
    string flee;

};

#endif
