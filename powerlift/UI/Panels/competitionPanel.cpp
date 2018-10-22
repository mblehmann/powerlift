//
//  competitorPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/4/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "competitionPanel.hpp"

CompetitionPanel::CompetitionPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    wxFlexGridSizer *inputGrid = new wxFlexGridSizer(2, wxSize(5, 5));

    nameInput = new wxTextCtrl(this, wxID_ANY);
    numberFlightsInput = new wxTextCtrl(this, wxID_ANY);
    descriptionInput = new wxTextCtrl(this, wxID_ANY);
    
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Competition Name")));
    inputGrid->Add(nameInput, 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Number of Flights")));
    inputGrid->Add(numberFlightsInput, 1, wxEXPAND);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Description")));
    inputGrid->Add(descriptionInput, 1, wxEXPAND);
    
    inputGrid->AddGrowableRow(2, 1);
    inputGrid->AddGrowableCol(1, 1);
    
    SetSizer(inputGrid);
    Layout();
}

// setters
void CompetitionPanel::setName(wxString name)
{
    nameInput->SetLabel(name);
}

void CompetitionPanel::setNumberFlights(int numberFlights)
{
    numberFlightsInput->SetLabel(wxString::Format(wxT("%i"), numberFlights));
}

void CompetitionPanel::setDescription(wxString description)
{
    descriptionInput->ChangeValue(description);
}

// getters
wxString CompetitionPanel::getName()
{
    return nameInput->GetValue();
}

int CompetitionPanel::getNumberFlights()
{
    return wxAtoi(numberFlightsInput->GetValue());
}

wxString CompetitionPanel::getDescription()
{
    return descriptionInput->GetValue();
}

