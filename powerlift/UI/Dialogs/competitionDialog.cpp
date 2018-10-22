//
//  competitionDialog.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "competitionDialog.hpp"

CompetitionDialog::CompetitionDialog(wxFrame *parent, wxString title, wxSize size) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, size)
{
    wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);

    competitionPanel = new CompetitionPanel(this);

    verticalBox->Add(competitionPanel, 1, wxEXPAND | wxTOP | wxLEFT | wxRIGHT, 10);
    verticalBox->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALIGN_CENTER | wxBOTTOM | wxTOP, 10);
    
    SetSizer(verticalBox);
    Centre();
}

// set competition
void CompetitionDialog::setDefaultCompetition()
{
    setName(wxT("Powerlift Competition"));
    setNumberFlights(1);
    setDescription(wxT("First powerlift competition"));
}

void CompetitionDialog::setCompetition(Manager *manager)
{
    setName(manager->getName());
    setNumberFlights(manager->getNumberFlights());
    setDescription(manager->getDescription());
}

// setters
void CompetitionDialog::setName(wxString name)
{
    competitionPanel->setName(name);
}

void CompetitionDialog::setNumberFlights(int numberFlights)
{
    competitionPanel->setNumberFlights(numberFlights);
}

void CompetitionDialog::setDescription(wxString description)
{
    competitionPanel->setDescription(description);
}

// getters
wxString CompetitionDialog::getName()
{
    return competitionPanel->getName();
}

int CompetitionDialog::getNumberFlights()
{
    return competitionPanel->getNumberFlights();
}

wxString CompetitionDialog::getDescription()
{
    return competitionPanel->getDescription();
}

// validation
bool CompetitionDialog::validateFields()
{
    return !getName().IsEmpty() && !getDescription().IsEmpty() && getNumberFlights() >= MIN_FLIGHTS && getNumberFlights() <= MAX_FLIGHTS;
}

wxString CompetitionDialog::getError()
{
    wxString error = "";
    if (getName().IsEmpty())
    {
        error.Append("Name of the competition must not be empty\n");
    }
    if (getNumberFlights() < MIN_FLIGHTS)
    {
        error.Append(wxString::Format(wxT("Invalid number of flights: %i\nNumber of flights must be at least %i\n"), getNumberFlights(), MIN_FLIGHTS));
    }
    if (getNumberFlights() > MAX_FLIGHTS)
    {
        error.Append(wxString::Format(wxT("Invalid number of flights: %i\nNumber of flights must be at most %i\n"), getNumberFlights(), MAX_FLIGHTS));
    }
    if (getDescription().IsEmpty())
    {
        error.Append("Description of the competition must not be empty\n");
    }
    return error;
}
