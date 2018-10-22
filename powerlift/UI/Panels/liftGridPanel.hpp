//
//  liftGridPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/13/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef liftGridPanel_hpp
#define liftGridPanel_hpp

#include "flight.hpp"

class LiftGridPanel : public wxPanel
{
    // attributes
    Lift lift;
    vector<wxButton*> *flightButtons;
    
public:
    // constructor
    LiftGridPanel(wxWindow *parent);
    
    // setters
    void setLift(Lift lift);
    void setFlights(vector<Flight*> flights);
    
    // accessors
    void setButtonLabel(int index, wxString label);
    void enableButton(int index);
    void disableButton(int index);
};

#endif /* liftGridPanel_hpp */
