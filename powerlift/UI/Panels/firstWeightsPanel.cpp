//
//  firstWeightsPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "firstWeightsPanel.hpp"

// constructor
FirstWeightsPanel::FirstWeightsPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    wxStaticBoxSizer *inputBox = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("First Weights")), wxVERTICAL);
    
    wxFlexGridSizer *inputGrid = new wxFlexGridSizer(2, wxSize(5, 5));

    weightInput = new map<Lift, wxTextCtrl*>;
    for (Lift lift : lifts)
        weightInput->insert(pair<Lift, wxTextCtrl*>(lift, new wxTextCtrl(this, wxID_ANY, wxEmptyString)));
    checkedInInput = new wxStaticText(this, wxID_ANY, wxEmptyString);
    
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Squat")));
    inputGrid->Add(weightInput->at(SQUAT), 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Bench")));
    inputGrid->Add(weightInput->at(BENCH), 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Deadlift")));
    inputGrid->Add(weightInput->at(DEADLIFT), 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Checked-In?")));
    inputGrid->Add(checkedInInput, 1, wxEXPAND);
    
    inputGrid->AddGrowableCol(1, 1);
    
    inputBox->Add(inputGrid, 1, wxEXPAND);
    SetSizer(inputBox);
    Layout();
}

// setters
void FirstWeightsPanel::setWeight(Lift lift, double weight)
{
    weightInput->at(lift)->SetValue(wxString::Format(wxT("%.1f"), weight));
}

void FirstWeightsPanel::setCheckedIn(bool checkedIn)
{
    checkedIn ? checkedInInput->SetLabel("Yes") : checkedInInput->SetLabel("No");
}

// getters
double FirstWeightsPanel::getWeight(Lift lift)
{
    double weight;
    weightInput->at(lift)->GetValue().ToDouble(&weight);
    return weight;
}
