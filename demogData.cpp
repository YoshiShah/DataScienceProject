#include "demogData.h"
#include <sstream>
#include <iomanip>
#include "visitor.h"
/* print county demographic data */
std::ostream& operator<<(std::ostream &out, const demogData &DD) {
    out << "County Demographics Info: " << DD.getRegionName() << ", " << DD.getState();
    out << std::setprecision(2) << std::fixed;
    out << "\nPopulation info: \n(\% over 65): " << DD.popOver65;
    out <<  " and total: " << DD.getpopOver65Count();
    out << "\n(\% under 18): " << DD.popUnder18;
    out <<  " and total: " << DD.getpopUnder18Count();
    out << "\n(\% under 5): " << DD.popUnder5;
    out <<  " and total: " << DD.getpopUnder5Count();
    out << "\nEducation info: " << "\n(\% Bachelor degree or more): " << DD.bachelorsOrHigher;
    out << " and total: " << DD.getBAupCount();
    out << "\n(\% high school or more): " << DD.highSchoolOrHigher;
    out << " and total: " << DD.getHSupCount() << "\n";
    out << "\npersons below poverty: " << DD.getUnderPovertyLine() << "and total: " << DD.getUnderPovertyLineCount();
    out << "\nTotal population: " << DD.getPop();
    out << DD.getInfo();
    //fill in
    return out;
}
void demogData:: accept(class Visitor &v) {
    v.visit(shared_from_this());
}
