//
//  flightPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/3/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "flightPanel.hpp"

// constructor
FlightPanel::FlightPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    flightGridSizer = new wxFlexGridSizer(FLIGHT_COLUMNS, wxSize(5, 5));

    for (wxString label : flightLabels)
        flightGridSizer->Add(new wxStaticText(this, wxID_ANY, label), 1, wxALIGN_CENTER);
    
    flightGridSizer->AddGrowableCol(0, 1);
    flightGridSizer->AddGrowableCol(1, 1);
    flightGridSizer->AddGrowableCol(2, 1);
    
    SetSizer(flightGridSizer);
}

// accessor
void FlightPanel::resetList()
{
    while (flightGridSizer->GetItemCount() > FLIGHT_COLUMNS)
    {
        flightGridSizer->Hide((int) flightGridSizer->GetItemCount()-1);
        flightGridSizer->Remove((int) flightGridSizer->GetItemCount()-1);
    }
}

int FlightPanel::populateLifters(vector<Lifter*> lifters)
{
    int checkedIn = 0;
    
    resetList();
    for (int i = 0; i < lifters.size(); i++)
    {
        flightGridSizer->Add(new wxStaticText(this, wxID_ANY, lifters.at(i)->getName()), 0, wxALIGN_CENTER);
        flightGridSizer->Add(new wxStaticText(this, wxID_ANY, lifters.at(i)->getTeam()), 0, wxALIGN_CENTER);
        flightGridSizer->Add(new wxStaticText(this, wxID_ANY, lifters.at(i)->getCategoryDescription()), 0, wxALIGN_CENTER);
        if (lifters.at(i)->getCheckedIn())
        {
            flightGridSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Yes")), 0, wxALIGN_CENTER);
            checkedIn++;
        }
        else
        {
            flightGridSizer->Add(new wxStaticText(this, wxID_ANY, wxT("No")), 0, wxALIGN_CENTER);
        }
    }

    Layout();
    return checkedIn;
}
