//
//  liftPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "liftPanel.hpp"

// constructor
LiftPanel::LiftPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());

    attemptBoxSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxEmptyString), wxVERTICAL);
    liftGridSizer = new wxFlexGridSizer(2, wxSize(5, 5));
    
    liftGridSizer->AddGrowableCol(1, 1);
    attemptBoxSizer->Add(liftGridSizer, 1, wxEXPAND);
    
    SetSizer(attemptBoxSizer);
}

// setters
void LiftPanel::setEditable(bool editable)
{
    this->editable = editable;
}

void LiftPanel::setLift(Lift lift)
{
    attemptBoxSizer->GetStaticBox()->SetLabel(wxString::Format(wxT("%s #%i"), LiftMap::liftString.at(lift), 1));
}

void LiftPanel::setAttempt(Attempt *attempt)
{
    resetAttempt();
    attemptBoxSizer->GetStaticBox()->SetLabel(wxString::Format(wxT("%s #%i"), LiftMap::liftString.at(attempt->getLift()), attempt->getAttempt()+1));
    
    liftGridSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Lift")));
    liftGridSizer->Add(new wxStaticText(this, wxID_ANY, LiftMap::liftString.at(attempt->getLift())), 1, wxEXPAND);
    liftGridSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Attempt")));
    liftGridSizer->Add(new wxStaticText(this, wxID_ANY, wxString::Format(wxT("%i"), attempt->getAttempt()+1)), 1, wxEXPAND);

    if (editable)
    {
        weightInput = new wxTextCtrl(this, wxID_ANY, wxString::Format(wxT("%.1f"), attempt->getWeight()));
        resultInput = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, WXSIZEOF(liftStatus), liftStatus);
    }
    else
    {
        weightInput = new wxStaticText(this, wxID_ANY, wxString::Format(wxT("%.1f"), attempt->getWeight()));
        resultInput = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, WXSIZEOF(liftResults), liftResults);
    }
    liftGridSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Weight")));
    liftGridSizer->Add(weightInput, 1, wxEXPAND);
    liftGridSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Result")));
    liftGridSizer->Add(resultInput, 1, wxEXPAND);
    
    int resultSelection = resultInput->FindString(ResultStringMap::resultString.at(attempt->getStatus()));
    resultSelection != wxNOT_FOUND ? resultInput->SetSelection(resultSelection) : resultInput->SetSelection(0);   
    Layout();
}

void LiftPanel::resetAttempt()
{
    while (liftGridSizer->GetItemCount() > 0)
    {
        liftGridSizer->Hide((int) liftGridSizer->GetItemCount()-1);
        liftGridSizer->Remove((int) liftGridSizer->GetItemCount()-1);
    }
    Layout();
}

// getters
double LiftPanel::getWeight()
{
    double weight;
    if (editable)
        ((wxTextCtrl*) weightInput)->GetValue().ToDouble(&weight);
    else
        ((wxStaticText*) weightInput)->GetLabel().ToDouble(&weight);
    return weight;
}

Status LiftPanel::getResult()
{
    return ResultMap::resultString.at(resultInput->GetString(resultInput->GetSelection()));
}


