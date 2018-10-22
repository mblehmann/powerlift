//
//  checkinFilterPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/13/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef checkinFilterPanel_hpp
#define checkinFilterPanel_hpp

#include "definition.h"

using namespace std;

class CheckinFilterPanel : public wxPanel
{
    // attributes
    wxCheckBox *checkedInFilter;
    wxStaticText *registeredLifters;
    wxStaticText *checkedInLifters;
    wxStaticText *percentageLifters;
    
public:
    // constructor
    CheckinFilterPanel(wxWindow *parent);
    
    // accessors
    void updateLifterSummary(int registered, int checkedIn);
    bool getCheckedInFilter();
};

#endif /* checkinFilterPanel_hpp */
