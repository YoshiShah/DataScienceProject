#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
#include "visitorCombineCounty.h"
#include "visitorCombineState.h"
#include "statTool.h"
#include "demogData.h"
#include "psData.h"
#include "parse.h"
#include "dataAQ.h"
#include "regionData.h"
using namespace std;

int main() {
 //create a visitor to combine the state data

std::vector<shared_ptr<regionData>> pileOfData;
    visitorCombineState theStates;
      read_csv(pileOfData, "police_shootings_cleaned.csv", POLICE);
   
  //read in the demographic data
  read_csv(pileOfData, "county_demographics.csv", DEMOG); 
    statTool::createStateData(pileOfData, theStates);
    theStates.printAllCombo(&demogData::getBelowPovertyCount, &psCombo::getNumberOfCases);

    //create a visitor to combine the county data
    visitorCombineCounty theCounties;
    statTool::createCountyData(pileOfData, theCounties);
    theCounties.printAllCombo(&demogData::getBelowPovertyCount, &psCombo::getNumberOfCases);
     cout << "State data Pop under 18 and below poverty up: " << endl;
    statTool::computeStatsDemogRegionData(&theStates, &demogData::getpopUnder18, &demogData::getBelowPoverty,
        &demogData::getpopUnder18Count, &demogData::getBelowPovertyCount);
    cout << "County data Pop under 18 and below poverty up: " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &demogData::getpopUnder18, &demogData::getBelowPoverty,
        &demogData::getpopUnder18Count, &demogData::getBelowPovertyCount);

    //Do stats work here
    cout << "State data Pop under poverty and HS up: " << endl;
    statTool::computeStatsDemogRegionData(&theStates, &demogData::getBelowPoverty, &demogData::getHSup,
        &demogData::getBelowPovertyCount, &demogData::getHSupCount);
    cout << "County data Pop under poverty and HS up: " << endl;
    statTool::computeStatsDemogRegionData(&theCounties, &demogData::getBelowPoverty, &demogData::getHSup,
        &demogData::getBelowPovertyCount, &demogData::getHSupCount);

    cout << "State data Pop mentally ill and white victims: " << endl;
    statTool::computeStatsPSData(&theStates, &psCombo::getNumMentalI, &psCombo::getWhiteCount);
       
    cout << "County data Pop mentally ill and white victims: " << endl;
statTool::computeStatsPSData(&theCounties, &psCombo::getNumMentalI, &psCombo::getWhiteCount);
      cout << "County data Pop mentally ill and black victims: " << endl;
statTool::computeStatsPSData(&theCounties, &psCombo::getNumMentalI, &psCombo::getBlackCount);
     cout << "County data county pop and total number of incidents: " << endl;
statTool::computeStatsMixRegionData(&theCounties, &demogCombo::getPop, &psCombo::getNumberOfCases);

statTool::computeStatsMixRegionData(&theCounties, &demogCombo::getpopUnder18Count, &psCombo::getCasesUnder18);
statTool::computeStatsRaceProportion(&theCounties, &raceDemogData::getWhiteNHCount,  &raceDemogData::getWhiteNHCount);
statTool::computeStatsRaceProportion(&theCounties, &raceDemogData::getBlackCount,  &raceDemogData::getBlackCount);
statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getWhiteNHCount,  &raceDemogData::getWhiteNHCount);
statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getLatinxCount,  &raceDemogData::getLatinxCount);
statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getFirstNationCount,  &raceDemogData::getFirstNationCount);
statTool::computeStatsRaceProportion(&theStates, &raceDemogData::getAsianCount,  &raceDemogData::getAsianCount);
    return 0;
}

