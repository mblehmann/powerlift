//
//  roundPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/24/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef roundPanel_hpp
#define roundPanel_hpp

#include "lifter.hpp"

class RoundPanel : public wxPanel
{
    // attributes
    bool editable;
    wxFlexGridSizer *roundGridSizer;
    map<int, wxControl*> *liftersWeight;
    map<int, wxString> lifterMap;
    
public:
    // constructor
    RoundPanel(wxWindow *parent);

    // setters
    void setEditable(bool editable);

    // accessors
    void resetList();
    void populateLifters(vector<Lifter*> lifters, Lift lift, int attempt);

    // getters
    double getRoundWeight(int lifterID);
    wxString getLifterName(int lifterID);
};

#endif /* roundPanel_hpp */
