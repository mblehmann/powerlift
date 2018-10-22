//
//  editResultDialog.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef editResultDialog_hpp
#define editResultDialog_hpp

#include "editLifterDialog.hpp"
#include "editResultsPanel.hpp"

using namespace std;

class EditResultDialog : public EditLifterDialog
{
    // attributes
    EditResultsPanel *editResultsPanel;
    
public:
    // constructor
    EditResultDialog(wxFrame *parent, wxString title, wxSize size);
    
    void setupDialog();
    
    // getters
    double getWeight(Lift lift, int attempt);
    Status getResult(Lift lift, int attempt);
    
    // validation
    bool validateFields();
    wxString getError();
    
    // events
    virtual void OnSelectLifter(wxCommandEvent& event);
    void OnUpdateResults(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

#endif /* editResultDialog_hpp */
