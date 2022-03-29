/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include "psData.h"
#include <iostream>
#include <algorithm>
#include <iomanip>
#include "visitorReport.h"
dataAQ::dataAQ() {}

string makeKeyExample(shared_ptr<demogData> theData) {

    string theKey = "Key";

    if (theData->getUnderPovertyLine() < 10) {
        theKey += "BelowPovLessTenPer";
    } else if (theData->getUnderPovertyLine() < 20) {
        theKey += "BelowPovLessTwentyPer";
    } else if (theData->getUnderPovertyLine() < 30) {
        theKey += "BelowPovLessThirtyPer";
    } else {
        theKey += "BelowPovAboveThirtyPer";
    }

    return theKey;
}

string makeKeyExample(shared_ptr<psData> theData) {

    string theKey = "Key";
    if (theData->getRace() == "W") {
        theKey += "WhiteVictim";
    } else if (theData->getRace() == "A") {
        theKey += "AsianVictim";
    } else if (theData->getRace() == "H") {
        theKey += "HispanicVictim";
    } else if (theData->getRace() == "N") {
        theKey += "NativeAmericanVictim";
    } else if (theData->getRace() == "B") {
        theKey += "AfricanAmericanVictim";
    } else if (theData->getRace() == "O") {
        theKey += "OtherRaceVictim";
    } else {
        theKey += "RaceUnspecifiedVictim";
    }
    return theKey;
}
void dataAQ::comboReport(double thresh){
 
    for(const auto& elem: allComboDemogData){
        if(elem.second->getHSup() >= thresh){
            pileData.push_back(elem.second);
            pileData.push_back(allComboDemogData[elem.first]);
        }
    }
    visitorReport report;
    for (const auto &obj : pileData) {
        obj->accept(report);
    }
}


//switch to a function parameter
void dataAQ::createComboDemogDataKey(std::vector<shared_ptr<demogData> >& theData) {
    int count = 0;
    map<string,shared_ptr<demogCombo>>::iterator it;
    for(int i = 0; i < theData.size();i++){
        keyValue = makeKeyExample(theData[i]);

        it = allComboDemogData.find(keyValue);
        // Aggregates data if found; otherwise, creates new entry
        if(it != allComboDemogData.end()){
            allComboDemogData[keyValue]->add(theData[i]);
        } else {
            allComboDemogData[keyValue] = make_shared<demogCombo>(theData[i]);
        }
    }
}



void dataAQ::createComboPoliceDataKey(std::vector<shared_ptr<psData> >& theData) {
    for(auto policeData : theData)
    {
        keyValue = makeKeyExample(policeData);
        map<string,shared_ptr<psCombo>>::iterator iq =  allComboPoliceData.find(keyValue);
        // Creates a new entry if not found key
        if(iq == allComboPoliceData.end()){
            allComboPoliceData[keyValue] = make_shared<psCombo>(policeData->getState());
        }
        // Aggregates data
        allComboPoliceData[keyValue]->add(policeData);
    }
}



/******************************************/
/* state examples */
void dataAQ::createComboDemogData(std::vector<shared_ptr<demogData> >&  theData) {
    map<string,shared_ptr<demogCombo>>::iterator it;
    for(int i = 0; i < theData.size();i++){
        it = allComboDemogData.find(theData[i]->getState());
        if(it != allComboDemogData.end()){
            allComboDemogData[theData[i]->getState()]->add(theData[i]);
        }
        else{
            allComboDemogData[theData[i]->getState()] = make_shared<demogCombo>(theData[i]);
        }
    }
}

void dataAQ::createComboPoliceData(std::vector<shared_ptr<psData> >& theData) {
    map<string,shared_ptr<psCombo>>::iterator iq;
    for(int i = 0; i < theData.size();i++){
        iq = allComboPoliceData.find(theData[i]->getState());
        if(iq == allComboPoliceData.end()){
            allComboPoliceData[theData[i]->getState()] = make_shared<psCombo>(theData[i]->getState());
        }
        allComboPoliceData[theData[i]->getState()]->add(theData[i]);

    }
}

bool compareTopTenPS(shared_ptr<psCombo> left, shared_ptr<psCombo>  right){
    return left->getNumberOfCases() < right->getNumberOfCases();
}

//sort and report the top ten states in terms of number of police shootings 
void dataAQ::reportTopTenStatesPS() {
    std::vector<shared_ptr<psCombo>> temp;
    map<string,shared_ptr<psCombo>>::iterator iq;
    for(iq = allComboPoliceData.begin(); iq != allComboPoliceData.end();iq++){
        temp.push_back(iq->second);
    }
    sort(temp.begin(),temp.end(),compareTopTenPS);
    int t = temp.size();
    std::cout << "Top ten states sorted on Police Shooting data & the associated state data:\n";
    for(int i = 1;i < 11; i++){
        std::cout << temp[t-i]->getState() << endl;
        std::cout << "Total population: "<<allComboDemogData[temp[t-i]->getState()]->getPop() << endl;
        std::cout << "Police shooting incidents: " << std::fixed << std::setprecision(2) << temp[t-i]->getNumberOfCases() << endl;
        std::cout << "Percent below poverty: " << allComboDemogData[temp[t-i]->getState()]->getUnderPovertyLine() << endl;
    }
    std::cout << "Top ten states sorted on Police Shooting data & the associated state data:";
    for(int i = 1; i < 4; i++){
        std::cout << allComboDemogData[temp[t-i]->getState()];;
        std::cout << temp[t-i];
    }
}

bool compareTopTenBP(shared_ptr<demogCombo> left, shared_ptr<demogCombo>  right){
    return left->getUnderPovertyLine() < right->getUnderPovertyLine();
}

//sort and report the top ten states with largest population below poverty
void dataAQ::reportTopTenStatesBP() {
    std::vector<shared_ptr<demogCombo>> temp;
    map<string,shared_ptr<demogCombo>>::iterator it;
    for(it = allComboDemogData.begin(); it != allComboDemogData.end();it++){
        temp.push_back(it->second);
    }
    sort(temp.begin(),temp.end(),compareTopTenBP);

    int t = temp.size();
    std::cout << "Top ten states sorted on Below Poverty data & the associated police shooting data:\n";
    for(int i = 1;i < 11; i++){
        std::cout << temp[t-i]->getState();
        std::cout << "\nTotal population: "<< temp[t-i]->getPop() << endl;
        std::cout << "Percent below poverty: " << std::fixed << std::setprecision(2) <<temp[t-i]->getUnderPovertyLine() << endl;
        std::cout << "Police shooting incidents: " << allComboPoliceData[temp[t-i]->getState()]->getNumberOfCases()  << endl;
    }

    std::cout << "**Full listings for top 3 Below Poverty data & the associated police shooting data for top 3:";
    for(int i = 1; i < 4; i++){
        std::cout << temp[t-i];
        std::cout << allComboPoliceData[temp[t-i]->getState()];
    }
}

/* print all combo data */
std::ostream& operator<<(std::ostream &out, const dataAQ &theAnswers) {
    out << "Combo Demographic Info: ";
    for (auto const& entry : theAnswers.allComboDemogData) {
        out << "key: " << entry.first << endl;
        out << *(entry.second) << "\n";
    }

    for (auto const& entry : theAnswers.allComboPoliceData) {
        out << "key: " << entry.first << endl;
        out << *(entry.second) << "\n";
    }

    return out;
}