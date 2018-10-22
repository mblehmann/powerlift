//
//  event.cpp
//  powerlifting
//
//  Created by Matheus Lehmann on 7/31/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "event.hpp"

using namespace std;

// constructor
Event::Event()
{
    for (Lift lift : lifts)
    {
        event[lift] = vector<Attempt>();
        for (int i = 0; i < TRIES; i++)
        {
            event[lift].push_back(Attempt(lift, i));
        }
    }
}

// getters
vector<Attempt*> Event::getAttempts(Lift lift)
{
    vector<Attempt*> attempts;
    for (int i = 0; i < TRIES; i++)
    {
        attempts.push_back(getAttempt(lift, i));
    }
    return attempts;
}

Attempt* Event::getAttempt(Lift lift, int attempt)
{
    return &event[lift][attempt];
}

double Event::getAttemptWeight(Lift lift, int attempt)
{
    return event[lift][attempt].getWeight();
}

Status Event::getAttemptStatus(Lift lift, int attempt)
{
    return event[lift][attempt].getStatus();
}

// chekcers
bool Event::isAttemptGood(Lift lift, int attempt)
{
    return event[lift][attempt].isGood();
}

// aggregators
double Event::getLiftResult(Lift lift)
{
    double result = 0;
    for (Attempt attempt : event[lift]) {
        if (attempt.isGood()) result = max(result, attempt.getWeight());
    }
    return result;
}

int Event::getAttemptBest()
{
    for (int i = TRIES-1; i >= 0; i++)
    {
        if (isAttemptGood(DEADLIFT, i))
            return i;
    }
    return -1;
}

double Event::getTotalResult()
{
    double result = 0;
    for (Lift lift : lifts)
    {
        result += getLiftResult(lift);
    }
    return result;
}

// setters
void Event::setLiftWeight(Lift lift, int attempt, double weight)
{
    event[lift][attempt].setWeight(weight);
}

void Event::setLiftResult(Lift lift, int attempt, Status result)
{
    event[lift][attempt].setStatus(result);
}

// serialization
wxString Event::serialize()
{
    wxString data = "";
    for (Lift lift : lifts)
    {
        for (Attempt attempt : event[lift])
        {
            data.Append(wxString::Format(wxT("%s%c"), attempt.serialize() + EVENT_DELIMITER));
        }
    }
    return data;
}

void Event::deserialize(wxString data)
{
    wxArrayString tokens = wxStringTokenize(data, EVENT_DELIMITER);
    int index = 0;
    
    for (Lift lift : lifts)
    {
        for (int i = 0; i < event[lift].size(); i++)
        {
            event[lift][i].deserialize(tokens[index]);
            index++;
        }
    }
}
