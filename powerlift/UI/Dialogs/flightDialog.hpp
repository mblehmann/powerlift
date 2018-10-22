//
//  flightDialog.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/3/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef flightDialog_hpp
#define flightDialog_hpp

#include "definition.h"

#include "flightPanel.hpp"

using namespace std;

class FlightDialog : public wxDialog
{
    // attributes
    FlightPanel *flightPanel;
    wxStaticText *flightInformation;
    wxStaticText *statusInput;
    wxChoice *flightChoice;
    
public:
    // constructor
    FlightDialog(wxFrame *parent, wxString title, wxSize size);
    
    // setters
    void setNumberFlights(int numberFlights);
    void setConfirmed(bool isConfirmed);

    // events
    void OnSelectFlight(wxCommandEvent& event);
    void OnConfirmFlights(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

#endif /* flightDialog_hpp */
