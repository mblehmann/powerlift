//
//  addLifterDialog.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/7/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "addLifterDialog.hpp"

AddLifterDialog::AddLifterDialog(wxFrame *parent, wxString title, wxSize size) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, size)
{
    lifterPanel = new LifterPanel(this);
}

void AddLifterDialog::setupDialog()
{
    wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);
    
    verticalBox->Add(lifterPanel, 1, wxEXPAND);
    verticalBox->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALIGN_CENTER | wxBOTTOM | wxTOP, 10);

    SetSizer(verticalBox);
    Centre();
    Layout();
}

// configuration
void AddLifterDialog::setNumberFlights(int numberFlights)
{
    lifterPanel->setNumberFlights(numberFlights);
}

// getters
wxString AddLifterDialog::getName()
{
    return lifterPanel->getName();
}

wxString AddLifterDialog::getTeam()
{
    return lifterPanel->getTeam();
}

wxString AddLifterDialog::getGender()
{
    return lifterPanel->getGender();
}

double AddLifterDialog::getWeight()
{
    return lifterPanel->getWeight();
}

wxString AddLifterDialog::getRegistration()
{
    return lifterPanel->getRegistration();
}

int AddLifterDialog::getFlight()
{
    return lifterPanel->getFlight();
}

// validation
bool AddLifterDialog::validateFields()
{
    return !getName().IsEmpty() && getWeight() >= MIN_LIFT_WEIGHT;
}

wxString AddLifterDialog::getError()
{
    wxString error = "";
    if (getName().IsEmpty())
    {
        error.Append("Name must not be empty\n");
    }
    if (getWeight() < MIN_LIFT_WEIGHT)
    {
        error.Append(wxString::Format(wxT("Invalid weight: %.1f\nWeight must be at least %i\n"), getWeight(), MIN_LIFT_WEIGHT));
    }
    return error;
}
