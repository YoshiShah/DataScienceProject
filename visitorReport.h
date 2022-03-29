#ifndef VISITREP_H
#define VISITREP_H

#include "psData.h"
#include "demogData.h"
#include "psCombo.h"
#include "visitor.h"
#include <iomanip>

class visitorReport : public Visitor {
public:
void visit(demogData *e){
    std::cout << "print summary demog Data:\n";
    std::cout << "Region info: " << e->getRegionName() << ", " << e->getState();
    std::cout << "\nEducation info:";
    std::cout << "\n(Bachelor or more): "  << e->getBAup() << "% and total: " << e->getBAupCount();
    std::cout << "\n(high school or more): " << e->getHSup() << "% and total: " << e->getHSupCount();
    std::cout << "\nTotal population: " << e->getPop() << endl;
    std::cout << e->getInfo();
 
}
void visit(psData *e){
    std::cout << "temp";
}
void visit(psCombo *e){
    std::cout << "print aggregate police shooting data";
    std::cout << "State Info: " << e->printState();
    std::cout << "\nNumber of incidents: " <<  e->getNumberOfCasesc();
    std::cout << "\nRacial demographics of state incidents: "  << e->getRacialDatac();
}
  private:
    	int numVisited;
};

#endif