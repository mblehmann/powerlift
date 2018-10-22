//
//  lifterSummaryPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/9/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "lifterSummaryPanel.hpp"

// constructor
LifterSummaryPanel::LifterSummaryPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    wxStaticBoxSizer *inputBox = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxEmptyString), wxVERTICAL);
    wxFlexGridSizer *inputGrid = new wxFlexGridSizer(2, wxSize(5, 5));
    
    lifterNameText = new wxStaticText(this, wxID_ANY, wxEmptyString);
    lifterTeamText = new wxStaticText(this, wxID_ANY, wxEmptyString);
    lifterGenderText = new wxStaticText(this, wxID_ANY, wxEmptyString);
    lifterWeightText = new wxStaticText(this, wxID_ANY, wxEmptyString);
    lifterCategoryText = new wxStaticText(this, wxID_ANY, wxEmptyString);
    lifterRegistrationText = new wxStaticText(this, wxID_ANY, wxEmptyString);
    lifterFlightText = new wxStaticText(this, wxID_ANY, wxEmptyString);
    
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Name")));
    inputGrid->Add(lifterNameText, 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Team")));
    inputGrid->Add(lifterTeamText, 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Gender")));
    inputGrid->Add(lifterGenderText, 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Weight")));
    inputGrid->Add(lifterWeightText, 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Category")));
    inputGrid->Add(lifterCategoryText, 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Registration")));
    inputGrid->Add(lifterRegistrationText, 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Flight")));
    inputGrid->Add(lifterFlightText, 1, wxEXPAND);
    
    inputGrid->AddGrowableCol(1, 1);
    
    inputBox->Add(inputGrid, 1, wxEXPAND);
    SetSizer(inputBox);
    Layout();
}

// configuration
void LifterSummaryPanel::setStaticBoxLabel(wxString label)
{
    ((wxStaticBoxSizer*) GetSizer())->GetStaticBox()->SetLabel(label);
}

void LifterSummaryPanel::resetLifter()
{
    setName(wxEmptyString);
    setTeam(wxEmptyString);
    setGender(wxEmptyString);
    setWeight(INVALID_VALUE);
    setCategory(wxEmptyString);
    setRegistration(wxEmptyString);
    setFlight(INVALID_VALUE);
    Layout();
}

void LifterSummaryPanel::setLifter(Lifter *lifter)
{
    setName(lifter->getName());
    setTeam(lifter->getTeam());
    setGender(lifter->getGender());
    setWeight(lifter->getWeight());
    setCategory(lifter->getCategoryDescription());
    setRegistration(lifter->getRegistration());
    setFlight(lifter->getFlight());
    Layout();
}

// setters
void LifterSummaryPanel::setName(wxString name)
{
    lifterNameText->SetLabel(name);
}

void LifterSummaryPanel::setTeam(wxString team)
{
    lifterTeamText->SetLabel(team);
}

void LifterSummaryPanel::setGender(wxString gender)
{
    lifterGenderText->SetLabel(gender);
}

void LifterSummaryPanel::setWeight(double weight)
{
    if (weight != INVALID_VALUE)
        lifterWeightText->SetLabel(wxString::Format(wxT("%.1f"), weight));
    else
        lifterWeightText->SetLabel(wxEmptyString);
}

void LifterSummaryPanel::setCategory(wxString category)
{
    lifterCategoryText->SetLabel(category);
}

void LifterSummaryPanel::setRegistration(wxString registration)
{
    lifterRegistrationText->SetLabel(registration);
}

void LifterSummaryPanel::setFlight(int flight)
{
    if (flight != INVALID_VALUE)
        lifterFlightText->SetLabel(wxString::Format(wxT("%i"), flight));
    else
        lifterFlightText->SetLabel(wxEmptyString);
}

