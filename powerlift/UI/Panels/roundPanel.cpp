//
//  roundPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/24/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "roundPanel.hpp"

// constructor
RoundPanel::RoundPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    liftersWeight = new map<int, wxControl*>;
    
    roundGridSizer = new wxFlexGridSizer(ROUND_COLUMNS, wxSize(5, 5));
    
    for (wxString label : roundLabels)
        roundGridSizer->Add(new wxStaticText(this, wxID_ANY, label), 1, wxALIGN_CENTER);
    
    roundGridSizer->AddGrowableCol(1, 1);
    roundGridSizer->AddGrowableCol(3, 1);
    
    SetSizer(roundGridSizer);
}

// setters
void RoundPanel::setEditable(bool editable)
{
    this->editable = editable;
}

// accessors
void RoundPanel::resetList()
{
    liftersWeight->clear();
    while (roundGridSizer->GetItemCount() > ROUND_COLUMNS)
    {
        roundGridSizer->Hide((int) roundGridSizer->GetItemCount()-1);
        roundGridSizer->Remove((int) roundGridSizer->GetItemCount()-1);
    }
}

void RoundPanel::populateLifters(vector<Lifter*> lifters, Lift lift, int attempt)
{
    resetList();
    for (int i = 0; i < lifters.size(); i++)
    {
        wxString lifterName = lifters[i]->getName();
        int lifterID = lifters[i]->getLifterID();
        double weight = lifters[i]->getAttemptWeight(lift, attempt);
        
        roundGridSizer->Add(new wxStaticText(this, wxID_ANY, wxString::Format(wxT("%i"), i+1)), 1, wxALIGN_CENTER);
        roundGridSizer->Add(new wxStaticText(this, wxID_ANY, lifterName), 1, wxALIGN_CENTER);
        roundGridSizer->Add(new wxStaticText(this, wxID_ANY, wxString::Format(wxT("%i"), lifterID)), 1, wxALIGN_CENTER);

        wxControl *weightInput;
        if (editable)
            weightInput = new wxTextCtrl(this, ID_ChangeRoundWeight, wxString::Format("%.1f", weight));
        else
            weightInput = new wxStaticText(this, wxID_ANY, wxString::Format("%.1f", weight));
        roundGridSizer->Add(weightInput, 1, wxALIGN_CENTER);
        
        liftersWeight->insert(pair<int, wxControl*>(lifterID, weightInput));
        lifterMap[lifterID] = lifterName;
    }
    Layout();
}

// getters
double RoundPanel::getRoundWeight(int lifterID)
{
    double weight;
    if (editable)
        ((wxTextCtrl*) liftersWeight->at(lifterID))->GetValue().ToDouble(&weight);
    else
        liftersWeight->at(lifterID)->GetLabel().ToDouble(&weight);
    return weight;
}

wxString RoundPanel::getLifterName(int lifterID)
{
    return lifterMap[lifterID];
}
