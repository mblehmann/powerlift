//
//  editResultsPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef editResultsPanel_hpp
#define editResultsPanel_hpp

#include "event.hpp"
#include "editLiftsPanel.hpp"

class EditResultsPanel : public wxPanel
{
    // attributes
    wxBoxSizer *verticalBox;
    map<Lift, EditLiftsPanel*> *liftPanels;
    
public:
    // constructor
    EditResultsPanel(wxWindow *parent);
    
    // setters
    void resetAttempts();
    void populateAttempts(Event *event);
    
    // getters
    double getWeight(Lift lift, int attempt);
    Status getResult(Lift lift, int attempt);
};

#endif /* editResultsPanel_hpp */
