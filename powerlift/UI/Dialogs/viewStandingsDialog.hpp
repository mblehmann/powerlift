//
//  viewStandingsDialog.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef viewStandingsDialog_hpp
#define viewStandingsDialog_hpp

#include "standingsPanel.hpp"
#include "standingsFilterPanel.hpp"

using namespace std;

class ViewStandingsDialog : public wxDialog
{
    // attributes
    StandingsFilterPanel *standingsFilterPanel;
    StandingsPanel *standingsPanel;
    
public:
    // constructor
    ViewStandingsDialog(wxFrame *parent, wxString title, wxSize size);
    
    // events
    void OnStandingsFilter(wxCommandEvent& event);
    void OnPopulateLifters(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

#endif /* viewStandingsDialog_hpp */
