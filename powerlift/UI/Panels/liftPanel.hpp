//
//  liftPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef liftPanel_hpp
#define liftPanel_hpp

#include "attempt.hpp"

class LiftPanel : public wxPanel
{
    // attributes
    bool editable;
    
    wxStaticBoxSizer *attemptBoxSizer;
    wxFlexGridSizer *liftGridSizer;
    wxControl *weightInput;
    wxChoice *resultInput;
    
public:
    // constructor
    LiftPanel(wxWindow *parent);
    
    // setters
    void setEditable(bool editable);
    void setLift(Lift lift);
    void setAttempt(Attempt *attempt);
    
    void resetAttempt();

    // getters
    double getWeight();
    Status getResult();
};

#endif /* liftPanel_hpp */
