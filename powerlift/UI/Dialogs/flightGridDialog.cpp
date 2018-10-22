//
//  flightGridDialog.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/5/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "flightGridDialog.hpp"
#include "powerliftFrame.hpp"

// constructor
FlightGridDialog::FlightGridDialog(wxFrame *parent, wxString title, wxSize size) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, size)
{
    flightGridPanel = new FlightGridPanel(this);

    wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);
    
    competitionInformation = new wxStaticText(this, wxID_ANY, wxEmptyString);
    
    verticalBox->Add(competitionInformation, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    verticalBox->Add(flightGridPanel, 1, wxEXPAND);
    verticalBox->Add(CreateButtonSizer(wxCLOSE), 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    
    SetSizer(verticalBox);
    Centre();
    Layout();
}

// accessors
void FlightGridDialog::setFlights(vector<Flight*> flights)
{
    flightGridPanel->setFlights(flights);
    currentFlight = -1;
    currentLift = SQUAT;
    setInformation();
}

void FlightGridDialog::endFlight()
{
    currentFlight = -1;
    setInformation();
}

void FlightGridDialog::setInformation()
{
    if (currentFlight < 0)
    {
        competitionInformation->SetLabel("Start Flight");
        flightGridPanel->setRunning(false);
    }
    else
    {
        competitionInformation->SetLabel(wxString::Format(wxT("Currently competing %s for Flight %i"), LiftMap::liftString.at(currentLift), currentFlight));
        flightGridPanel->setRunning(true);
    }
    flightGridPanel->update();
    Layout();
}

// events
void FlightGridDialog::OnStartFlight(wxCommandEvent& event)
{
    wxString data = ((wxStringClientData*)((wxButton*) event.GetEventObject())->GetClientData())->GetData();
    wxArrayString tokens = wxStringTokenize(data, " ");
    
    currentFlight = wxAtoi(tokens[0]);
    currentLift = static_cast<Lift>(wxAtoi(tokens[1]));
    
    ((PowerliftFrame*) this->GetParent())->beginFlightLift(currentFlight, currentLift);
    setInformation();
}
