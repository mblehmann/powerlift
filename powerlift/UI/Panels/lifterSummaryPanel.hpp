//
//  lifterSummaryPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/9/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef lifterSummaryPanel_hpp
#define lifterSummaryPanel_hpp

#include "lifter.hpp"

class LifterSummaryPanel : public wxPanel
{
    // attributes
    wxStaticText *lifterNameText;
    wxStaticText *lifterTeamText;
    wxStaticText *lifterGenderText;
    wxStaticText *lifterWeightText;
    wxStaticText *lifterCategoryText;
    wxStaticText *lifterRegistrationText;
    wxStaticText *lifterFlightText;
    
    // setters
    void setName(wxString name);
    void setTeam(wxString team);
    void setGender(wxString gender);
    void setWeight(double weight);
    void setCategory(wxString category);
    void setRegistration(wxString registration);
    void setFlight(int flight);
    
public:
    // constructor
    LifterSummaryPanel(wxWindow *parent);

    // configuration
    void setStaticBoxLabel(wxString label);
    void setLifter(Lifter *lifter);
    void resetLifter();
};

#endif /* lifterSummaryPanel_hpp */
