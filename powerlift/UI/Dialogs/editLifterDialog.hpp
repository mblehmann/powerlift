//
//  editLifterDialog.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/13/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef editLifterDialog_hpp
#define editLifterDialog_hpp

#include "addLifterDialog.hpp"
#include "lifterListPanel.hpp"

using namespace std;

class EditLifterDialog : public AddLifterDialog
{
protected:
    // attributes
    LifterListPanel *lifterListPanel;
    Lifter *currentLifter;
    
    // events
    virtual void OnSelectLifter(wxCommandEvent& event);
    void OnUpdateLifter(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
    
public:
    // constructor
    EditLifterDialog(wxFrame *parent, wxString title, wxSize size);
    
    void setupDialog();
    
    // accessors
    void populateLifterList(wxArrayString lifterList);
    int getLifterID();    
    void updateLifter();
    
    // validation
    bool validateFields();
    wxString getError();
};

#endif /* editLifterDialog_hpp */
