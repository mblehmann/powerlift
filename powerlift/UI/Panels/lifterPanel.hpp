//
//  lifterPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef lifterPanel_hpp
#define lifterPanel_hpp

#include "lifter.hpp"

class LifterPanel : public wxPanel
{
    // attributes
    wxTextCtrl *nameInput;
    wxTextCtrl *teamInput;
    wxChoice *genderChoice;
    wxTextCtrl *weightInput;
    wxChoice *registrationChoice;
    wxChoice *flightChoice;
    
    // setters
    void setName(wxString name);
    void setTeam(wxString team);
    void setGender(wxString gender);
    void setWeight(double weight);
    void setRegistration(wxString registration);
    void setFlight(int flight);
    
public:
    // constructor
    LifterPanel(wxWindow *parent);

    // initialization
    void setNumberFlights(int numberFlights);
    void setLifter(Lifter *lifter);

    // getters
    wxString getName();
    wxString getTeam();
    wxString getGender();
    double getWeight();
    wxString getRegistration();
    int getFlight();
};

#endif /* lifterPanel_hpp */
