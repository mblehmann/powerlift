//
//  editResultsPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "editResultsPanel.hpp"

// constructor
EditResultsPanel::EditResultsPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    verticalBox = new wxBoxSizer(wxVERTICAL);

    liftPanels = new map<Lift, EditLiftsPanel*>;
    
    SetSizer(verticalBox);
}

// setters
void EditResultsPanel::resetAttempts()
{
    liftPanels->clear();
    while (verticalBox->GetItemCount() > 0)
    {
        verticalBox->Hide((int) verticalBox->GetItemCount()-1);
        verticalBox->Remove((int) verticalBox->GetItemCount()-1);
    }
}

void EditResultsPanel::populateAttempts(Event *event)
{
    resetAttempts();
    for (Lift lift : lifts)
    {
        EditLiftsPanel *editLiftsPanel = new EditLiftsPanel(this);
        editLiftsPanel->populateAttempts(event->getAttempts(lift));
        liftPanels->insert(pair<Lift, EditLiftsPanel*>(lift, editLiftsPanel));
        
        verticalBox->Add(editLiftsPanel, 1, wxEXPAND);
    }
}

// getters
double EditResultsPanel::getWeight(Lift lift, int attempt)
{
    return liftPanels->at(lift)->getWeight(attempt);
}

Status EditResultsPanel::getResult(Lift lift, int attempt)
{
    return liftPanels->at(lift)->getResult(attempt);

}

