//
//  formPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/15/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "formPanel.hpp"

// constructor
FormPanel::FormPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    formSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxEmptyString), wxHORIZONTAL);
    
    SetSizer(formSizer);
}

// setters
void FormPanel::setLift(Lift lift)
{
    formSizer->GetStaticBox()->SetLabel(LiftMap::liftString.at(lift));
}

void FormPanel::populateForm(vector<Attempt*> attempts)
{
    resetForm();
    for (int i = 0; i < attempts.size(); i++)
    {
        wxStaticText *formText = new wxStaticText(this, wxID_ANY, wxString::Format(wxT("%.1f"), attempts[i]->getWeight()), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL);
        formText->SetBackgroundColour(ColorMap::liftColor.at(attempts[i]->getStatus()));
        formSizer->Add(formText, 1, wxEXPAND | wxALIGN_CENTER | wxALIGN_CENTER_VERTICAL);
    }
    Layout();
}

void FormPanel::resetForm()
{
    while (formSizer->GetItemCount() > 0)
    {
        formSizer->Hide((int) formSizer->GetItemCount()-1);
        formSizer->Remove((int) formSizer->GetItemCount()-1);
    }
    Layout();
}
