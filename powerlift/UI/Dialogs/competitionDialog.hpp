//
//  competitionDialog.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef competitionDialog_hpp
#define competitionDialog_hpp

#include "manager.hpp"
#include "competitionPanel.hpp"

using namespace std;

class CompetitionDialog : public wxDialog
{
    // attributes
    CompetitionPanel *competitionPanel;
    
    // setters
    void setName(wxString name);
    void setNumberFlights(int numberFlights);
    void setDescription(wxString description);
    
public:
    // constructor
    CompetitionDialog(wxFrame *parent, wxString title, wxSize size);
    
    // set competition
    void setDefaultCompetition();
    void setCompetition(Manager *manager);
    
    // getters
    wxString getName();
    int getNumberFlights();
    wxString getDescription();

    // validation
    bool validateFields();
    wxString getError();
};

#endif /* competitionDialog_hpp */
