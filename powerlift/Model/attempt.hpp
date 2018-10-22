//
//  attempt.hpp
//  powerlifting
//
//  Created by Matheus Lehmann on 7/31/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef attempt_hpp
#define attempt_hpp

#include "definition.h"

using namespace std;

class Attempt
{
    // attributes
    Lift lift;
    int attempt;
    double weight;
    Status status;
    
    // setters
    void setLift(Lift lift);
    void setAttempt(int attempt);
    
public:
    // constructor
    Attempt(Lift lift, int attempt);
    
    // setters
    void setWeight(double weight);
    void setStatus(Status status);

    // getters
    Lift getLift();
    int getAttempt();
    double getWeight();
    Status getStatus();    
    
    // checkers
    bool isReady();
    bool isDone();
    bool isGood();
    
    // serialization
    wxString serialize();
    void deserialize(wxString data);
};

#endif /* attempt_hpp */
