#ifndef VCOMBOS_H
#define VCOMBOS_H


#include "visitorCombine.h"
#include <memory>

class visitorCombineState : public visitorCombine {
public:
    visitorCombineState() {}

	void visit(shared_ptr<demogData> obj) {
        map<string,shared_ptr<demogCombo>>::iterator it;
        it = ComboDemog.find(obj->getState());
        if(it != ComboDemog.end()){
            ComboDemog[obj->getState()]->add(obj);
        }
        else{
            ComboDemog[obj->getState()] = make_shared<demogCombo>(obj);
        }
    
    }
    
    void visit(shared_ptr<psData> obj) {
         map<string,shared_ptr<psCombo>>::iterator iq;
    
        iq = ComboPolice.find(obj->getState());
        if(iq == ComboPolice.end()){
            ComboPolice[obj->getState()] = make_shared<psCombo>(obj->getState());
        }
        ComboPolice[obj->getState()]->add(obj);
    }
    void visit(demogData *e) {
        //    map<string,shared_ptr<demogCombo>>::iterator it;
        // it = ComboDemog.find(e->getState());
        // if(it != ComboDemog.end()){
        //     ComboDemog[e->getState()]->add(e);
        // }
        // else{
        //     ComboDemog[e->getState()] = make_shared<demogCombo>(e);
        // }
    
    }
   void visit(psData *e){
    //    map<string,shared_ptr<psCombo>>::iterator iq;
    //      iq = ComboPolice.find(e->getState());
    //     if(iq == ComboPolice.end()){
    //         ComboPolice[e->getState()] = make_shared<psCombo>(e->getState());
    //     }
    //     ComboPolice[e->getState()]->add(e);
   }
   void visit(psCombo *e) {}
 
    private:
       //inherited
};

#endif
