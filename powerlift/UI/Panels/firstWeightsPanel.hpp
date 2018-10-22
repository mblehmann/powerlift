//
//  firstWeightsPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef firstWeightsPanel_hpp
#define firstWeightsPanel_hpp

#include "definition.h"

class FirstWeightsPanel : public wxPanel
{
    // attributes
    map<Lift, wxTextCtrl*> *weightInput;
    wxStaticText *checkedInInput;
    
public:
    // constructor
    FirstWeightsPanel(wxWindow *parent);
    
    // setters
    void setWeight(Lift lift, double weight);
    void setCheckedIn(bool checkedIn);

    // getters
    double getWeight(Lift lift);
};

#endif /* firstWeightsPanel_hpp */
