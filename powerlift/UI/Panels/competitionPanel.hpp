//
//  competitorPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/4/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef competitorPanel_hpp
#define competitorPanel_hpp

#include "definition.h"

using namespace std;

class CompetitionPanel : public wxPanel
{
    // attributes
    wxTextCtrl *nameInput;
    wxTextCtrl *numberFlightsInput;
    wxTextCtrl *descriptionInput;
    
public:
    // constructor
    CompetitionPanel(wxWindow *parent);
    
    // setters
    void setName(wxString name);
    void setNumberFlights(int numberFlights);
    void setDescription(wxString description);

    // getters
    wxString getName();
    int getNumberFlights();
    wxString getDescription();
};

#endif /* competitorPanel_hpp */
