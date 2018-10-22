//
//  attemptPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/11/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "attemptPanel.hpp"

// constructor
AttemptPanel::AttemptPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);

    formPanel = new FormPanel(this);
    liftPanel = new LiftPanel(this);

    verticalBox->Add(formPanel, 1, wxEXPAND);
    verticalBox->Add(liftPanel, 2, wxEXPAND);
    
    SetSizer(verticalBox);
}

// setters
void AttemptPanel::setWeightEditable(bool editable)
{
    liftPanel->setEditable(editable);
}

void AttemptPanel::setLift(Lift lift)
{
    formPanel->setLift(lift);
    liftPanel->setLift(lift);
}

void AttemptPanel::reset()
{
    formPanel->resetForm();
    liftPanel->resetAttempt();
}

// filling
void AttemptPanel::populateAttempt(Attempt *attempt)
{
    liftPanel->setAttempt(attempt);
}

void AttemptPanel::populateForm(vector<Attempt*> attempts)
{
    formPanel->populateForm(attempts);
}

// getters
double AttemptPanel::getWeight()
{
    return liftPanel->getWeight();
}

Status AttemptPanel::getResult()
{
    return liftPanel->getResult();
}

