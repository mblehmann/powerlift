//
//  nextLiftersPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/31/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "nextLiftersPanel.hpp"

// constructor
NextLiftersPanel::NextLiftersPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    wxStaticBoxSizer *nextLiftersBoxSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Next Lifters")), wxVERTICAL);
    nextLiftersGrid = new wxFlexGridSizer(NEXT_LIFTERS_COLS, wxSize(5, 5));

    nextLiftersGrid->AddGrowableCol(0, 1);
    nextLiftersBoxSizer->Add(nextLiftersGrid, 1, wxEXPAND);
    
    SetSizer(nextLiftersBoxSizer);
}

// accessors
void NextLiftersPanel::resetList()
{
    while (nextLiftersGrid->GetItemCount() > 0)
    {
        nextLiftersGrid->Hide((int) nextLiftersGrid->GetItemCount()-1);
        nextLiftersGrid->Remove((int) nextLiftersGrid->GetItemCount()-1);
    }
}

void NextLiftersPanel::addLifters(vector<Lifter*> lifters, int index, Lift lift, int attempt)
{
    resetList();
    for (int i = 0; i < NEXT_LIFTERS_ROWS; i++)
    {
        if (index+i >= lifters.size())
            break;
        nextLiftersGrid->Add(new wxStaticText(this, wxID_ANY, lifters[index+i]->getName()));
        nextLiftersGrid->Add(new wxStaticText(this, wxID_ANY, wxString::Format(wxT("%.1f"), lifters[index+i]->getAttemptWeight(lift, attempt))));
    }
    Layout();
}
