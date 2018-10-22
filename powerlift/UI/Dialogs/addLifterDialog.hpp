//
//  addLifterDialog.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/7/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef addLifterDialog_hpp
#define addLifterDialog_hpp

#include "lifterPanel.hpp"

using namespace std;

class AddLifterDialog : public wxDialog
{
protected:
    // attribute
    LifterPanel *lifterPanel;
    
public:
    // constructor
    AddLifterDialog(wxFrame *parent, wxString title, wxSize size);
    
    void setupDialog();
    
    // configuration
    void setNumberFlights(int numberFlights);

    // getters
    wxString getName();
    wxString getTeam();
    wxString getGender();
    double getWeight();
    wxString getRegistration();
    int getFlight();
    
    // validation
    bool validateFields();
    wxString getError();
};

#endif /* addLifterDialog_hpp */
