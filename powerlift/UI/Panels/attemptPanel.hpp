//
//  attemptPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/11/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef attemptPanel_hpp
#define attemptPanel_hpp

#include "attempt.hpp"

#include "formPanel.hpp"
#include "liftPanel.hpp"

class AttemptPanel : public wxPanel
{
    // attributes
    FormPanel *formPanel;
    LiftPanel *liftPanel;
    
public:
    // constructor
    AttemptPanel(wxWindow *parent);
    
    // setters
    void setWeightEditable(bool editable);
    void setLift(Lift lift);
    void reset();
    
    // filling
    void populateAttempt(Attempt *attempt);
    void populateForm(vector<Attempt*> attempts);

    // getters
    double getWeight();
    Status getResult();
};

#endif /* attemptPanel_hpp */
