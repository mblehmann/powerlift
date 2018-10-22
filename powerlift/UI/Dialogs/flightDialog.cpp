//
//  flightDialog.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/3/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "flightDialog.hpp"
#include "powerliftFrame.hpp"

// constructor
FlightDialog::FlightDialog(wxFrame *parent, wxString title, wxSize size) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, size)
{
    flightPanel = new FlightPanel(this);

    wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);
    wxGridSizer *flightBox = new wxGridSizer(2, wxSize(5, 5));
    wxBoxSizer *buttonBox = new wxBoxSizer(wxHORIZONTAL);

    flightInformation = new wxStaticText(this, wxID_ANY, wxEmptyString);
    flightChoice = new wxChoice(this, ID_SelectFlight);
    statusInput = new wxStaticText(this, wxID_ANY, wxEmptyString);
    
    flightBox->Add(new wxStaticText(this, wxID_ANY, wxT("Flight")), 0, wxALIGN_CENTER);
    flightBox->Add(flightChoice, 0, wxALIGN_CENTER | wxLEFT, 10);

    buttonBox->Add(new wxButton(this, ID_ConfirmFlights, wxT("Confirm")), 0, wxALIGN_CENTER);
    buttonBox->Add(new wxButton(this, wxID_OK, wxT("OK")), 0, wxALIGN_CENTER | wxLEFT, 10);

    verticalBox->Add(flightInformation, 0, wxALIGN_CENTER | wxBOTTOM | wxTOP, 10);
    verticalBox->Add(flightPanel, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
    verticalBox->Add(flightBox, 0, wxALIGN_CENTER | wxBOTTOM | wxTOP, 10);
    verticalBox->Add(statusInput, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    verticalBox->Add(buttonBox, 0, wxALIGN_CENTER | wxBOTTOM, 10);
    
    SetSizer(verticalBox);
    Centre();
    Layout();
}

// setters
void FlightDialog::setNumberFlights(int numberFlights)
{
    flightChoice->Clear();
    wxArrayString flights;
    for (int i = 0; i < numberFlights; i++)
        flights.Add(wxString::Format(wxT("%i"), i+1));
    flightChoice->Append(flights);
    
    flightChoice->SetSelection(0);
    wxCommandEvent *event = new wxCommandEvent();
    OnSelectFlight(*event);
    delete event;
}

void FlightDialog::setConfirmed(bool isConfirmed)
{
    isConfirmed ? statusInput->SetLabel("Confirmed") : statusInput->SetLabel("Unconfirmed");
    Layout();
}

// events
void FlightDialog::OnSelectFlight(wxCommandEvent& event)
{
    int selectedFlight = wxAtoi(flightChoice->GetString(flightChoice->GetSelection()));
    vector<Lifter*> lifters = ((PowerliftFrame*) this->GetParent())->getLiftersAtFlight(selectedFlight, false);
 
    int checkedIn = flightPanel->populateLifters(lifters);
    flightInformation->SetLabel(wxString::Format(wxT("Flight #%i (%i Lifters; %i Checked-In)"), selectedFlight, (int) lifters.size(), checkedIn));
    Layout();
}

void FlightDialog::OnConfirmFlights(wxCommandEvent& event)
{
    statusInput->SetLabel("Confirmed");
    ((PowerliftFrame*) this->GetParent())->confirmFlights();
    Layout();
}
