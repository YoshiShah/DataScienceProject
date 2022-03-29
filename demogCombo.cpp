#include "demogCombo.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>
#include "visitor.h"
/* print state data - as aggregate of all the county data */
std::ostream& operator<<(std::ostream &out, const demogCombo& ComboD) {
    out << "Combo Info: " << ComboD.printState() << "\n";
    out << "Number of Counties: " << ComboD.getCounties();
    out << " County Demographics Info: " << ComboD.getRegionName() << ", " << ComboD.getState();
    out << std::setprecision(2) << std::fixed;
    out << "\nPopulation info: \n(\% over 65): " << ComboD.popOver65;
    out <<  "% and total: " << ComboD.getpopOver65Count();
    out << "\n(\% under 18): " << ComboD.popUnder18;
    out <<  "% and total: " << ComboD.getpopUnder18Count();
    out << "\n(\% under 5): " << ComboD.popUnder5;
    out <<  "% and total: " << ComboD.getpopUnder5Count();
    out << "\nEducation info: " << "\n(Bachelor or more): " << ComboD.bachelorsOrHigher;
    out << "% and total: " << ComboD.getBAupCount();
    out << "\n(high school or more): " << ComboD.highSchoolOrHigher;
    out << "% and total: " << ComboD.getHSupCount();
    out << "\npersons below poverty: " << ComboD.getUnderPovertyLine() << "% and total: " << ComboD.getUnderPovertyLineCount();
    out << "\nTotal population: " << ComboD.getPop() << endl;
    out << ComboD.getInfo();

    return out;
}
void demogCombo:: accept(class Visitor &v) {
    v.visit(this);
}