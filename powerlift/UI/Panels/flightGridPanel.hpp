//
//  flightGridPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/5/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef flightGridPanel_hpp
#define flightGridPanel_hpp

#include "flight.hpp"

#include "liftGridPanel.hpp"

class FlightGridPanel : public wxPanel
{
    // attributes
    map<Lift, LiftGridPanel*> *liftGridPanels;
    vector<Flight*> flights;
    bool running;
    
public:
    // constructor
    FlightGridPanel(wxWindow *parent);
    
    // setters
    void setFlights(vector<Flight*> flights);
    void setRunning(bool running);

    // accessors
    void update();
    void updateButtonStatus(int flightIndex, Lift lift);
};

#endif /* flightGridPanel_hpp */
