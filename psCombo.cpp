#include <iomanip>
#include "psCombo.h"
#include "visitor.h"

/* print state data - as aggregate of all incidents in this state */
std::ostream& operator<<(std::ostream &out, const psCombo& PD) {
    
    out << "State Info: " << PD.printState();
    out << "\nNumber of incidents: " <<  PD.getNumberOfCasesc();
    out << std::setprecision(2) << std::fixed;
    out << "\nIncidents with age \n(over 65): " << PD.getCasesOver65c() << " %: " << PD.getCasesOver65c()*100.0/PD.getNumberOfCasesc();
    out << "\n(19 to 64): " << PD.getCasesOver18c() << " %: " << PD.getCasesOver18c() * 100.0 / PD.getNumberOfCasesc();
    out << "\n(under 18): " << PD.getCasesUnder18c() << " %: " << PD.getCasesUnder18c() * 100.0 / PD.getNumberOfCasesc();
    out << "\nIncidents involving fleeing: " << PD.getFleeingCountc() << " %: " << PD.getFleeingCountc() * 100.0/PD.getNumberOfCasesc();
    out << "\nIncidents involving mental illness: " << PD.getNumMentalIc() << " %: " << PD.getNumMentalIc() * 100.0 / PD.getNumberOfCasesc();
    out << "\nMale incidents: " << PD.getnumMalesc() << " female incidents: " << PD.getnumFemalesc();
    out << "\nRacial demographics of state incidents: "  << PD.getRacialDatac();
    return out;
}
void psCombo:: accept(class Visitor &v) {
    v.visit(this);
}
