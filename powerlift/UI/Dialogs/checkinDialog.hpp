//
//  checkinDialog.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef checkinDialog_hpp
#define checkinDialog_hpp

#include "editLifterDialog.hpp"
#include "checkinFilterPanel.hpp"
#include "firstWeightsPanel.hpp"

using namespace std;

class CheckinDialog : public EditLifterDialog
{
protected:
    // attributes
    CheckinFilterPanel *checkinFilterPanel;
    FirstWeightsPanel *firstWeightsPanel;
 
    // events
    virtual void OnSelectLifter(wxCommandEvent& event);
    void OnCheckInLifter(wxCommandEvent& event);
    void OnCheckInFilter(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();

public:
    // constructor
    CheckinDialog(wxFrame *parent, wxString title, wxSize size);
    
    void setupDialog();
    
    // getters
    double getWeight(Lift lift);
//    double getSquatWeight();
//    double getBenchWeight();
//    double getDeadliftWeight();
    
    // accessors
    void updateLifterSummary();

    // validation
    bool validateFields();
    wxString getError();
};

#endif /* checkinDialog_hpp */
