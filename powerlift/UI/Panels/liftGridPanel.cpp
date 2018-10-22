//
//  liftGridPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/13/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "liftGridPanel.hpp"

// constructor
LiftGridPanel::LiftGridPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    wxStaticBoxSizer *liftSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxEmptyString), wxHORIZONTAL);
    
    SetSizer(liftSizer);
}

// setters
void LiftGridPanel::setLift(Lift lift)
{
    this->lift = lift;
    ((wxStaticBoxSizer*) GetSizer())->GetStaticBox()->SetLabel(LiftMap::liftString.at(lift));
}

void LiftGridPanel::setFlights(vector<Flight*> flights)
{
    flightButtons = new vector<wxButton*>;
    for (int i = 0; i < flights.size(); i++)
    {
        int flightNumber = flights[i]->getFlightNumber();
        wxButton *button = new wxButton(this, ID_StartFlight, wxString::Format(wxT("Flight %i\nReady"), flightNumber));
        button->SetClientData(new wxStringClientData(wxString::Format(wxT("%i %i"), flightNumber, lift)));
        
        flightButtons->push_back(button);
        GetSizer()->Add(flightButtons->at(i), 1, wxEXPAND);
    }
    Layout();
}

// accessors
void LiftGridPanel::setButtonLabel(int index, wxString label)
{
    flightButtons->at(index)->SetLabel(label);
    Layout();
}

void LiftGridPanel::enableButton(int index)
{
    flightButtons->at(index)->Enable();
    Layout();
}

void LiftGridPanel::disableButton(int index)
{
    flightButtons->at(index)->Disable();
    Layout();
}
