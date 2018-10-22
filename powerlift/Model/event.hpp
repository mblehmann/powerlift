//
//  event.hpp
//  powerlifting
//
//  Created by Matheus Lehmann on 7/31/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef event_hpp
#define event_hpp

#include "attempt.hpp"

using namespace std;

class Event
{
    // attributes
    map<Lift, vector<Attempt> > event;
    
public:
    // constructor
    Event();
    
    // getters
    vector<Attempt*> getAttempts(Lift lift);
    Attempt* getAttempt(Lift lift, int attempt);    
    double getAttemptWeight(Lift lift, int attempt);
    Status getAttemptStatus(Lift lift, int attempt);
    
    // checkers
    bool isAttemptGood(Lift lift, int attempt);
    
    // aggregators
    double getLiftResult(Lift lift);
    int getAttemptBest();
    double getTotalResult();

    // setters
    void setLiftWeight(Lift lift, int attempt, double weight);
    void setLiftResult(Lift lift, int attempt, Status result);
    
    // serialization
    wxString serialize();
    void deserialize(wxString data);
};

#endif /* event_hpp */
