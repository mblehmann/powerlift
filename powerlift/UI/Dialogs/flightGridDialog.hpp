//
//  flightGridDialog.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/5/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef flightGridDialog_hpp
#define flightGridDialog_hpp

#include "flight.hpp"
#include "flightGridPanel.hpp"

using namespace std;

class FlightGridDialog : public wxDialog
{
    // attributes
    int currentFlight;
    Lift currentLift;
    wxStaticText *competitionInformation;
    FlightGridPanel *flightGridPanel;
    
public:
    // constructor
    FlightGridDialog(wxFrame *parent, wxString title, wxSize size);

    // accessors
    void setFlights(vector<Flight*> flights);
    void endFlight();
    void setInformation();
    
    // events
    void OnStartFlight(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

#endif /* flightGridDialog_hpp */
