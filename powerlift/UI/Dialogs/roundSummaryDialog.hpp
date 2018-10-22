//
//  roundSummaryDialog.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/24/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef roundSummaryDialog_hpp
#define roundSummaryDialog_hpp

#include "flight.hpp"
#include "roundPanel.hpp"

using namespace std;

class RoundSummaryDialog : public wxDialog
{
    // attributes
    Flight *flight;
    bool editable;
    
    // GUI
    RoundPanel *roundPanel;
    wxStaticText *statusInput;
    wxBoxSizer *buttonBox;

    // events
    void OnConfirmFlights(wxCommandEvent& event);
    void OnUnconfirmFlights(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
public:
    // constructor
    RoundSummaryDialog(wxDialog *parent, wxString title, wxSize size);

    // setters
    void setFlight(Flight *flight);
    void setEditable(bool editable);
    void setConfirmed(bool confirmed);
    
    // accessors
    void populateLifters();
    void updateWeights();
    
    // getters
    bool getConfirmed();
    double getRoundWeight(int lifterID);

    // validators
    bool validateFields();
    wxString getError();
};

#endif /* roundSummaryDialog_hpp */
