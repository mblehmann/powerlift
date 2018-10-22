//
//  standingsFilterPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/15/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef standingsFilterPanel_hpp
#define standingsFilterPanel_hpp

#include "definition.h"

class StandingsFilterPanel : public wxPanel
{
    // attributes
    wxChoice *filterInput;
    wxChoice *selectionInput;
    wxChoice *registrationInput;
    wxChoice *scoreInput;

    wxStaticText *selectionText;
    
public:
    // constructor
    StandingsFilterPanel(wxWindow *parent);
    
    // setters
    void setSelectionText(wxString text);
    void setSelectionChoices(wxArrayString choices);
    
    // getters
    wxString getFilter();
    wxString getSelection();
    wxString getRegistration();
    wxString getScore();
};

#endif /* standingsFilterPanel_hpp */
