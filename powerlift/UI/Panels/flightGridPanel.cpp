//
//  flightGridPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/5/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "flightGridPanel.hpp"

// constructor
FlightGridPanel::FlightGridPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());

    wxBoxSizer *competitionBox = new wxBoxSizer(wxVERTICAL);
    
    liftGridPanels = new map<Lift, LiftGridPanel*>;
    for (Lift lift : lifts)
    {
        liftGridPanels->insert(pair<Lift, LiftGridPanel*>(lift, new LiftGridPanel(this)));
        liftGridPanels->at(lift)->setLift(lift);
        competitionBox->Add(liftGridPanels->at(lift), 1, wxEXPAND);
    }
    
    SetSizer(competitionBox);
}

// setters
void FlightGridPanel::setFlights(vector<Flight*> flights)
{
    this->flights = flights;
    
    for (Lift lift : lifts)
    {
        liftGridPanels->at(lift)->setFlights(flights);
    }
    
    Layout();
}

void FlightGridPanel::setRunning(bool running)
{
    this->running = running;
}

// accessors
void FlightGridPanel::update()
{
    for (Lift lift : lifts)
    {
        for (int i = 0; i < flights.size(); i++)
        {
            updateButtonStatus(i, lift);
        }
    }
}

void FlightGridPanel::updateButtonStatus(int flightIndex, Lift lift)
{
    wxString message;
    bool enable = true;
    Competition status = flights[flightIndex]->getStatus(lift);
    int flightNumber = flights[flightIndex]->getFlightNumber();

    switch (status)
    {
        case CREATED:
            message = wxString::Format(wxT("Start\nFlight %i\nReady"), flightNumber);
            if (running)
                enable = false;
            break;
        case COMPLETED:
            message = wxString::Format(wxT("Flight %i\nCompleted"), flightNumber);
            enable = false;
            break;
        default:
            message = wxString::Format(wxT("View\nFlight %i\nRunning"), flightNumber);
            break;
    }
    
    liftGridPanels->at(lift)->setButtonLabel(flightIndex, message);
    enable ? liftGridPanels->at(lift)->enableButton(flightIndex) : liftGridPanels->at(lift)->disableButton(flightIndex);
}


