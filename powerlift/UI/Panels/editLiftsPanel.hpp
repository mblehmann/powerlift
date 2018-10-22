//
//  editLiftsPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef editLiftsPanel_hpp
#define editLiftsPanel_hpp

#include "attempt.hpp"
#include "liftPanel.hpp"

class EditLiftsPanel : public wxPanel
{
    // attributes
    wxStaticBoxSizer *liftBoxSizer;
    map<int, LiftPanel*> *liftPanels;
    
public:
    // constructor
    EditLiftsPanel(wxWindow *parent);
    
    // setters
    void resetAttempts();
    void populateAttempts(vector<Attempt*> attempts);
    
    // getters
    double getWeight(int attempt);
    Status getResult(int attempt);
};

#endif /* editLiftsPanel_hpp */
