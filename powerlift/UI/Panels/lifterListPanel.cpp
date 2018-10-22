//
//  lifterListPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/14/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "lifterListPanel.hpp"

// constructor
LifterListPanel::LifterListPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    selection = 0;
    
    SetSize(parent->GetClientSize());
    
    wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);
    
    listbox = new wxListBox(this, ID_LifterDetails, wxDefaultPosition, wxDefaultSize, 0, NULL);
    verticalBox->Add(listbox, 1, wxEXPAND | wxBOTTOM | wxTOP | wxLEFT | wxRIGHT, 10);
    
    SetSizer(verticalBox);
    Layout();
}

// accessors
void LifterListPanel::populateLifterList(wxArrayString lifters)
{
    listbox->Clear();
    for (int i = 0; i < lifters.size(); i++)
    {
        listbox->Insert(lifters[i], i);
    }
    if (lifters.size() > 0)
    {
        listbox->SetSelection(min(selection, (int) lifters.size()-1));
    }
}

int LifterListPanel::getLifterID()
{
    selection = listbox->GetSelection();
    wxString lifter = listbox->GetString(selection);
    wxArrayString tokens = wxStringTokenize(lifter, " ");
    return wxAtoi(tokens.Last());
}
