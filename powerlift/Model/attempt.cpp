//
//  attempt.cpp
//  powerlifting
//
//  Created by Matheus Lehmann on 7/31/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "attempt.hpp"

// constructor
Attempt::Attempt(Lift lift, int attempt)
{
    setLift(lift);
    setAttempt(attempt);
    weight = 0;
}

// setters
void Attempt::setLift(Lift lift)
{
    this->lift = lift;
    setStatus(UNDEFINED);
}

void Attempt::setAttempt(int attempt)
{
    this->attempt = attempt;
}

void Attempt::setWeight(double weight)
{
    this->weight = weight;
    setStatus(READY);
}

void Attempt::setStatus(Status status)
{
    this->status = status;
}

// getters
Lift Attempt::getLift()
{
    return lift;
}

int Attempt::getAttempt()
{
    return attempt;
}

double Attempt::getWeight()
{
    return weight;
}

Status Attempt::getStatus()
{
    return status;
}

// checkers
bool Attempt::isReady()
{
    return getStatus() == READY;
}

bool Attempt::isDone()
{
    return getStatus() == GOOD || getStatus() == FAIL || getStatus() == PASS;
}

bool Attempt::isGood()
{
    return getStatus() == GOOD;
}

// serialization
wxString Attempt::serialize()
{
    wxString data = wxString::Format(wxT("%i%c%i%c%f%c%i"), lift, ATTEMPT_DELIMITER, attempt, ATTEMPT_DELIMITER, weight, ATTEMPT_DELIMITER, status);
    
    return data;
}

void Attempt::deserialize(wxString data)
{
    wxArrayString tokens = wxStringTokenize(data, ATTEMPT_DELIMITER);
    int index = 0;
    
    Lift lift;
    int attempt;
    double weight;
    Status status;
    
    lift = static_cast<Lift>(wxAtoi(tokens[index]));
    index++;
    
    attempt = wxAtoi(tokens[index]);
    index++;
    
    weight = wxAtof(tokens[index]);
    index++;
    
    status = static_cast<Status>(wxAtoi(tokens[index]));
    
    setLift(lift);
    setAttempt(attempt);
    setWeight(weight);
    setStatus(status);
}
        
        
