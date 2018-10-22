//
//  flightPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/3/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef flightPanel_hpp
#define flightPanel_hpp

#include "lifter.hpp"

class FlightPanel : public wxPanel
{
    // attributes
    wxFlexGridSizer *flightGridSizer;
    
public:
    // constructor
    FlightPanel(wxWindow *parent);
    
    // accessors
    void resetList();
    int populateLifters(vector<Lifter*> lifters);
};

#endif /* flightPanel_hpp */
