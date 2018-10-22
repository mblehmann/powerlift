//
//  flight.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/3/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef flight_hpp
#define flight_hpp

#include "lifter.hpp"

using namespace std;

class Flight
{
    // attributes
    int flightNumber;
    vector<Lifter*> lifters;
    map<Lift, Competition> status;

    Lift currentLift;
    int round;

public:
    // constructor
    Flight();
    Flight(int flightNumber, vector<Lifter*> lifters);
    
    // setters
    void setFlightNumber(int flightNumber);
    void setLifters(vector<Lifter*> lifters);
    void setStatus(Lift lift, Competition status);
    void setCurrentLift(Lift lift);
    
    void initializeLifts();
    void resetRound();

    // getters
    int getFlightNumber();
    vector<Lifter*> getLifters();
    Competition getStatus(Lift lift);
    
    Lift getCurrentLift();
    int getRound();
    int getFlightSize();
    bool isRunning();
    
    // model
    void beginCompetition(Lift lift);
    void finishCompetition();
    void advanceRound();
    vector<Lifter*> getOrderedLiftersInRound();
    
    // serialization
    wxString serialize();
    void deserialize(wxString data);
};

#endif /* flight_hpp */
