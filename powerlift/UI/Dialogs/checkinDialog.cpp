//
//  checkinDialog.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "checkinDialog.hpp"
#include "powerliftFrame.hpp"

// constructor
CheckinDialog::CheckinDialog(wxFrame *parent, wxString title, wxSize size) : EditLifterDialog(parent, title, size)
{
    checkinFilterPanel = new CheckinFilterPanel(this);
    firstWeightsPanel = new FirstWeightsPanel(this);
}

void CheckinDialog::setupDialog()
{
    wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *panelBox = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *listBox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *lifterBox = new wxBoxSizer(wxVERTICAL);

    wxButton *checkinButton = new wxButton(this, ID_CheckinLifter, wxT("Check-in"));
    int spacer = 140;

    listBox->Add(lifterListPanel, 1, wxEXPAND);
    listBox->Add(checkinFilterPanel, 0, wxALIGN_CENTER);
    
    lifterBox->Add(lifterPanel, 1, wxEXPAND | wxBOTTOM | wxTOP | wxRIGHT, 10);
    lifterBox->Add(firstWeightsPanel, 1, wxEXPAND | wxBOTTOM | wxRIGHT, 10);
    lifterBox->Add(checkinButton, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    lifterBox->AddSpacer(spacer);

    panelBox->Add(listBox, 1, wxEXPAND);
    panelBox->Add(lifterBox, 1, wxEXPAND);

    verticalBox->Add(panelBox, 1, wxEXPAND);
    verticalBox->Add(CreateButtonSizer(wxOK), 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    
    SetSizer(verticalBox);
    Centre();
    Layout();
    
    updateLifterSummary();
}

// getters
double CheckinDialog::getWeight(Lift lift)
{
    return firstWeightsPanel->getWeight(lift);
}

// accessors
void CheckinDialog::updateLifterSummary()
{
    int totalLifters = ((PowerliftFrame*) this->GetParent())->getRegisteredLifters();
    int checkedInLifters = ((PowerliftFrame*) this->GetParent())->getCheckedInLifters();
    
    checkinFilterPanel->updateLifterSummary(totalLifters, checkedInLifters);
}

// events
void CheckinDialog::OnSelectLifter(wxCommandEvent& event)
{
    EditLifterDialog::OnSelectLifter(event);
    
    for (Lift lift : lifts)
        firstWeightsPanel->setWeight(lift, currentLifter->getAttemptWeight(lift, 0));
    firstWeightsPanel->setCheckedIn(currentLifter->getCheckedIn());
}

void CheckinDialog::OnCheckInLifter(wxCommandEvent& event)
{
    if (validateFields())
    {
        updateLifter();

        vector<double> firstWeights;
        for (Lift lift : lifts)
            firstWeights.push_back(getWeight(lift));
        
        currentLifter->setFirstWeights(firstWeights);
        firstWeightsPanel->setCheckedIn(currentLifter->getCheckedIn());
        updateLifterSummary();
        populateLifterList(((PowerliftFrame*) this->GetParent())->getLifterList(checkinFilterPanel->getCheckedInFilter()));

        ((PowerliftFrame*) this->GetParent())->updateLifter();
    }
    else
    {
        wxMessageDialog(this, getError()).ShowModal();
    }
}

void CheckinDialog::OnCheckInFilter(wxCommandEvent& event)
{
    populateLifterList(((PowerliftFrame*) this->GetParent())->getLifterList(checkinFilterPanel->getCheckedInFilter()));
}

// validation
bool CheckinDialog::validateFields()
{
    if (!EditLifterDialog::validateFields())
        return false;
    
    for (Lift lift : lifts)
    {
        if (getWeight(lift) < MININUM_WEIGHT || fmod(getWeight(lift), MINIMUM_INCREASE) != 0)
            return false;
    }
    return true;
}

wxString CheckinDialog::getError()
{
    wxString error = EditLifterDialog::getError();
    for (Lift lift : lifts)
    {
        double weight = getWeight(lift);
        wxString liftString = LiftMap::liftString.at(lift);
        if (weight < MININUM_WEIGHT)
        {
            error += wxString::Format(wxT("Invalid %s weight: %.1f\n%s weight must be at least %i\n"), liftString, weight, liftString, MININUM_WEIGHT);
        }
        if (fmod(weight, MINIMUM_INCREASE) != 0)
        {
            error += wxString::Format(wxT("Invalid %s weight: %.1f\n%s weight must be multiple of %.1f\n"), liftString, weight, liftString, MINIMUM_INCREASE);
        }
    }
    return error;
}
