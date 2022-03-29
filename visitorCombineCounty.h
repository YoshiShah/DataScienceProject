#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "psData.h"
#include "psCombo.h"
#include "demogData.h"
#include "demogCombo.h"
#include "visitorCombine.h"
#include "parse.h"
#include <memory>
#include <fstream>
#include <cassert>

class visitorCombineCounty : public visitorCombine {
public:
    visitorCombineCounty() {
    }

    //store demographic data by county name
	void visit(shared_ptr<demogData> obj) {
      string temp1 = obj->getRegionName();
      string temp2 = " County";
      string temp3 = obj->getState();
      std::string::size_type i = temp1.find(temp2);
      if (i != std::string::npos){
          temp1.erase(i,temp2.length());
          
      }
      temp1 += temp3;
    ComboDemog[temp1] = make_shared<demogCombo>(obj);
       

    }
    
    //aggregate police shooting data by county
    void visit(shared_ptr<psData> obj) {
        string temp1 = obj->getRegionName();
      string temp2 = " County";
      string temp3 = obj->getState();
      std::string::size_type i = temp1.find(temp2);
      if (i != std::string::npos){
          temp1.erase(i,temp2.length());
          
      }
      temp1 += temp3;
      map<string,shared_ptr<psCombo>>::iterator iq;
       iq = ComboPolice.find(temp1);
        if(iq == ComboPolice.end()){
    ComboPolice[temp1] = make_shared<psCombo>(temp1);
        }
    ComboPolice[temp1]->add(obj);   
    }
 void visit(demogData *e) {}
   void visit(psData *e){}
   void visit(psCombo *e) {}
 
    private:
        //only inherited data at this point
};

#endif
