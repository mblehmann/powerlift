//
//  roundSummaryDialog.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/24/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "roundSummaryDialog.hpp"
#include "roundDialog.hpp"

// constructor
RoundSummaryDialog::RoundSummaryDialog(wxDialog *parent, wxString title, wxSize size) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, size)
{
    roundPanel = new RoundPanel(this);

    wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);
    buttonBox = new wxBoxSizer(wxHORIZONTAL);
    
    statusInput = new wxStaticText(this, wxID_ANY, wxEmptyString);
    
    buttonBox->Add(new wxButton(this, wxID_OK, wxT("Begin")), 1);

    verticalBox->Add(roundPanel, 1, wxEXPAND | wxBOTTOM | wxTOP | wxRIGHT | wxLEFT, 10);
    verticalBox->Add(statusInput, 0, wxALIGN_CENTER | wxBOTTOM | wxTOP, 10);
    verticalBox->Add(buttonBox, 0, wxALIGN_CENTER | wxBOTTOM | wxTOP | wxRIGHT | wxLEFT, 10);
    
    SetSizer(verticalBox);
    Centre();
}

// setters
void RoundSummaryDialog::setFlight(Flight *flight)
{
    this->flight = flight;
}

void RoundSummaryDialog::setEditable(bool editable)
{
    this->editable = editable;
    roundPanel->setEditable(editable);
    
    if (editable)
    {
        buttonBox->Prepend(new wxButton(this, ID_UnconfirmRound, wxT("Unconfirm")), 1, wxRIGHT, 10);
        buttonBox->Prepend(new wxButton(this, ID_ConfirmRound, wxT("Confirm")), 1, wxRIGHT, 10);
    }
}

void RoundSummaryDialog::setConfirmed(bool confirmed)
{
    confirmed ? statusInput->SetLabel("Confirmed") : statusInput->SetLabel("Unconfirmed");
    Layout();
}

// accessors
void RoundSummaryDialog::populateLifters()
{
    roundPanel->populateLifters(flight->getOrderedLiftersInRound(), flight->getCurrentLift(), flight->getRound());
}

void RoundSummaryDialog::updateWeights()
{
    for (Lifter *lifter : flight->getLifters())
    {
        lifter->setLiftWeight(flight->getCurrentLift(), flight->getRound(), getRoundWeight(lifter->getLifterID()));
    }
    populateLifters();
}

// getters
bool RoundSummaryDialog::getConfirmed()
{
    return statusInput->GetLabel().Cmp("Confirmed") == 0;
}

double RoundSummaryDialog::getRoundWeight(int lifterID)
{
    return roundPanel->getRoundWeight(lifterID);
}

// events
void RoundSummaryDialog::OnUnconfirmFlights(wxCommandEvent& event)
{
    setConfirmed(false);
}

void RoundSummaryDialog::OnConfirmFlights(wxCommandEvent& event)
{
    if (validateFields())
    {
        setConfirmed(true);
        updateWeights();
        ((RoundDialog*) this->GetParent())->updateLifterTables();
    }
    else
    {
        wxMessageDialog(this, getError()).ShowModal();
    }
}

// validators
bool RoundSummaryDialog::validateFields()
{
    Lift lift = flight->getCurrentLift();
    int round = flight->getRound();
    
    for (Lifter *lifter : flight->getLifters())
    {
        double roundWeight = getRoundWeight(lifter->getLifterID());
        double previousWeight;
        if (round == 0)
            previousWeight = MININUM_WEIGHT;
        else
            previousWeight = lifter->isAttemptGood(lift, round-1) ? lifter->getAttemptWeight(lift, round-1) + MINIMUM_INCREASE : lifter->getAttemptWeight(lift, round-1);
        
        if (roundWeight < previousWeight || fmod(roundWeight, MINIMUM_INCREASE) != 0)
            return false;
    }
    return true;
}

wxString RoundSummaryDialog::getError()
{
    wxString error = wxEmptyString;
    Lift lift = flight->getCurrentLift();
    int round = flight->getRound();
    
    for (Lifter *lifter : flight->getOrderedLiftersInRound())
    {
        double roundWeight = getRoundWeight(lifter->getLifterID());
        double previousWeight;
        if (round == 0)
            previousWeight = MININUM_WEIGHT;
        else
            previousWeight = lifter->isAttemptGood(lift, round-1) ? lifter->getAttemptWeight(lift, round-1) + MINIMUM_INCREASE : lifter->getAttemptWeight(lift, round-1);
        
        if (roundWeight < previousWeight)
            error.Append(wxString::Format(wxT("Next weight of %s must be at least %.1f\n"), lifter->getName(), previousWeight));
        if (fmod(roundWeight, MINIMUM_INCREASE) != 0)
             error.Append(wxString::Format(wxT("Next weight of %s must be multiple of %.1f\n"), lifter->getName(), MINIMUM_INCREASE));
    }
    return error;
}
