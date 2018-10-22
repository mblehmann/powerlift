//
//  lifterPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "lifterPanel.hpp"

LifterPanel::LifterPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());

    wxStaticBoxSizer *inputBox = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Lifter")), wxVERTICAL);

    wxFlexGridSizer *inputGrid = new wxFlexGridSizer(2, wxSize(5, 5));

    nameInput = new wxTextCtrl(this, wxID_ANY);
    teamInput = new wxTextCtrl(this, wxID_ANY);
    genderChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, WXSIZEOF(genders), genders);
    weightInput = new wxTextCtrl(this, wxID_ANY);
    registrationChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, WXSIZEOF(registrations), registrations);
    flightChoice = new wxChoice(this, wxID_ANY);
    
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Name")));
    inputGrid->Add(nameInput, 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Team")));
    inputGrid->Add(teamInput, 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Gender")));
    inputGrid->Add(genderChoice, 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Weight")));
    inputGrid->Add(weightInput, 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Registration")));
    inputGrid->Add(registrationChoice, 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Flight")));
    inputGrid->Add(flightChoice, 1, wxEXPAND);
    
    inputGrid->AddGrowableCol(1, 1);
    inputBox->Add(inputGrid, 1, wxEXPAND);

    SetSizer(inputBox);
    Layout();
}

// initialization
void LifterPanel::setNumberFlights(int numberFlights)
{
    flightChoice->Clear();
    wxArrayString flights;
    for (int i = 0; i < numberFlights; i++)
        flights.Add(wxString::Format(wxT("%i"), i+1));
    flightChoice->Append(flights);
    Layout();
}

void LifterPanel::setLifter(Lifter *lifter)
{
    setName(lifter->getName());
    setTeam(lifter->getTeam());
    setGender(lifter->getGender());
    setWeight(lifter->getWeight());
    setRegistration(lifter->getRegistration());
    setFlight(lifter->getFlight());
    Layout();
}

// setters
void LifterPanel::setName(wxString name)
{
    nameInput->SetLabel(name);
}

void LifterPanel::setTeam(wxString team)
{
    teamInput->SetLabel(team);
}

void LifterPanel::setGender(wxString gender)
{
    genderChoice->SetSelection(genderChoice->FindString(gender));
}

void LifterPanel::setWeight(double weight)
{
    weightInput->SetLabel(wxString::Format(wxT("%.1f"), weight));
}

void LifterPanel::setRegistration(wxString registration)
{
    registrationChoice->SetSelection(registrationChoice->FindString(registration));
}

void LifterPanel::setFlight(int flight)
{
    wxString flightString = wxString::Format(wxT("%i"), flight);
    flightChoice->SetSelection(flightChoice->FindString(flightString));
}

// getters
wxString LifterPanel::getName()
{
    return nameInput->GetValue();
}

wxString LifterPanel::getTeam()
{
    return teamInput->GetValue();
}
wxString LifterPanel::getGender()
{
    return genderChoice->GetString(genderChoice->GetSelection());
}

double LifterPanel::getWeight()
{
    double weight;
    weightInput->GetValue().ToDouble(&weight);
    return weight;
}

wxString LifterPanel::getRegistration()
{
    return registrationChoice->GetString(registrationChoice->GetSelection());
}

int LifterPanel::getFlight()
{
    return wxAtoi(flightChoice->GetString(flightChoice->GetSelection()));
}

