//
//  lifterListPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/14/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef lifterListPanel_hpp
#define lifterListPanel_hpp

#include "definition.h"

using namespace std;

class LifterListPanel : public wxPanel
{
    // attributes
    int selection;
    wxListBox *listbox;
    
public:
    // constructor
    LifterListPanel(wxWindow *parent);
    
    // accessors
    void populateLifterList(wxArrayString lifters);
    int getLifterID();
};

#endif /* lifterListPanel_hpp */
