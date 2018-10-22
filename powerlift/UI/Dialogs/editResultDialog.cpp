//
//  editResultDialog.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "editResultDialog.hpp"
#include "powerliftFrame.hpp"

// constructor
EditResultDialog::EditResultDialog(wxFrame *parent, wxString title, wxSize size) : EditLifterDialog(parent, title, size)
{
    editResultsPanel = new EditResultsPanel(this);
}

void EditResultDialog::setupDialog()
{
    wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);
    
    wxBoxSizer *panelBox = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *lifterBox = new wxBoxSizer(wxVERTICAL);
    
    lifterBox->Add(lifterPanel, 1, wxEXPAND | wxBOTTOM | wxTOP | wxRIGHT, 10);
    lifterBox->Add(editResultsPanel, 1, wxEXPAND | wxBOTTOM | wxRIGHT, 10);
    lifterBox->Add(new wxButton(this, ID_UpdateResults, wxT("Update")), 0, wxALIGN_CENTER);
    
    panelBox->Add(lifterListPanel, 1, wxEXPAND);
    panelBox->Add(lifterBox, 1, wxEXPAND);
    
    verticalBox->Add(panelBox, 1, wxEXPAND);
    verticalBox->Add(CreateButtonSizer(wxOK), 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    
    SetSizer(verticalBox);
    Centre();
}

// getters
double EditResultDialog::getWeight(Lift lift, int attempt)
{
    return editResultsPanel->getWeight(lift, attempt);
}

Status EditResultDialog::getResult(Lift lift, int attempt)
{
    return editResultsPanel->getResult(lift, attempt);
}

// validation
bool EditResultDialog::validateFields()
{
    if (!EditLifterDialog::validateFields())
        return false;
    for (Lift lift : lifts)
    {
        for (int i = 0; i < TRIES; i++)
        {
            if (getWeight(lift, i) < MININUM_WEIGHT || fmod(getWeight(lift, i), MINIMUM_INCREASE) != 0)
                return false;
            if (i > 0)
            {
                int increase = getResult(lift, i-1) == GOOD ? MINIMUM_INCREASE : 0;

                if (getWeight(lift, i) < getWeight(lift, i-1) + increase)
                    return false;
            }
        }
    }
    return true;
}

wxString EditResultDialog::getError()
{
    wxString error = EditLifterDialog::getError();
    for (Lift lift : lifts)
    {
        for (int i = 0; i < TRIES; i++)
        {
            if (getWeight(lift, i) < MININUM_WEIGHT)
            {
                error.Append(wxString::Format(wxT("Invalid weight for %s attempt %i: %.1f\nWeight must be at least %i\n"), LiftMap::liftString.at(lift), i+1, getWeight(lift, i), MININUM_WEIGHT));
            }
            if (fmod(getWeight(lift, i), MINIMUM_INCREASE) != 0)
            {
                error.Append(wxString::Format(wxT("Invalid weight for %s attempt %i: %.1f\nWeight must be multiple of %.1f\n"), LiftMap::liftString.at(lift), i+1, getWeight(lift, i), MINIMUM_INCREASE));
            }
            if (i > 0)
            {
                int increase = getResult(lift, i-1) == GOOD ? MINIMUM_INCREASE : 0;
                
                if (getWeight(lift, i) < getWeight(lift, i-1) + increase)
                {
                    error.Append(wxString::Format(wxT("Invalid weight for %s attempt %i: %.1f\nWeight must be at least %.1f\n"), LiftMap::liftString.at(lift), i+1, getWeight(lift, i), getWeight(lift, i-1)+increase));
                }
            }
        }
    }
    return error;
}

// events
void EditResultDialog::OnSelectLifter(wxCommandEvent& event)
{
    currentLifter = ((PowerliftFrame*) this->GetParent())->getLifter(getLifterID());
    lifterPanel->setLifter(currentLifter);
    editResultsPanel->populateAttempts(currentLifter->getEvent());
}

void EditResultDialog::OnUpdateResults(wxCommandEvent& event)
{
    if (validateFields())
    {
        updateLifter();
        
        currentLifter->setCheckedIn(true);
        for (Lift lift : lifts)
        {
            for (int i = 0; i < TRIES; i++)
            {
                currentLifter->setLiftWeight(lift, i, getWeight(lift, i));
                currentLifter->setLiftResult(lift, i, getResult(lift, i));
            }
        }
        populateLifterList(((PowerliftFrame*) this->GetParent())->getLifterList(false));
        ((PowerliftFrame*) this->GetParent())->refreshCompetitorGrid();
    }
    else
    {
        wxMessageDialog(this, getError()).ShowModal();
    }
}
