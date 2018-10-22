//
//  editLiftsPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "editLiftsPanel.hpp"

// constructor
EditLiftsPanel::EditLiftsPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    liftBoxSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxEmptyString), wxHORIZONTAL);
    liftPanels = new map<int, LiftPanel*>;
    
    SetSizer(liftBoxSizer);
}

// setters
void EditLiftsPanel::resetAttempts()
{
    liftPanels->clear();
    while (liftBoxSizer->GetItemCount() > 0)
    {
        liftBoxSizer->Hide((int) liftBoxSizer->GetItemCount()-1);
        liftBoxSizer->Remove((int) liftBoxSizer->GetItemCount()-1);
    }
}

void EditLiftsPanel::populateAttempts(vector<Attempt*> attempts)
{
    resetAttempts();
    for (int i = 0; i < attempts.size(); i++)
    {
        LiftPanel *liftPanel = new LiftPanel(this);
        liftPanel->setEditable(true);
        liftPanel->setAttempt(attempts[i]);
        
        liftPanels->insert(pair<int, LiftPanel*>(attempts[i]->getAttempt(), liftPanel));
        liftBoxSizer->Add(liftPanel, 1, wxEXPAND);
        if (i != attempts.size()-1)
            liftBoxSizer->Add(new wxStaticLine(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL), 0, wxEXPAND | wxLEFT | wxRIGHT, 5);
            
    }
}

// getters
double EditLiftsPanel::getWeight(int attempt)
{
    return liftPanels->at(attempt)->getWeight();
}

Status EditLiftsPanel::getResult(int attempt)
{
    return liftPanels->at(attempt)->getResult();
}
