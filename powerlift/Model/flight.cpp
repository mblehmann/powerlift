//
//  flight.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/3/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "flight.hpp"

// constructors
Flight::Flight()
{
    setFlightNumber(0);
    initializeLifts();
}

Flight::Flight(int flightNumber, vector<Lifter*> lifters)
{
    setFlightNumber(flightNumber);
    setLifters(lifters);
    initializeLifts();
}

// setters
void Flight::setFlightNumber(int flightNumber)
{
    this->flightNumber = flightNumber;
}

void Flight::setLifters(vector<Lifter*> lifters)
{
    this->lifters = lifters;
}

void Flight::setStatus(Lift lift, Competition status)
{
    this->status[lift] = status;
}

void Flight::setCurrentLift(Lift lift)
{
    this->currentLift = lift;
}

void Flight::initializeLifts()
{
    for (Lift lift : lifts)
        status[lift] = CREATED;
}

void Flight::resetRound()
{
    round = 0;
}

// getters
int Flight::getFlightNumber()
{
    return flightNumber;
}

vector<Lifter*> Flight::getLifters()
{
    return lifters;
}

Competition Flight::getStatus(Lift lift)
{
    return status[lift];
}

Lift Flight::getCurrentLift()
{
    return currentLift;
}

int Flight::getRound()
{
    return round;
}

int Flight::getFlightSize()
{
    return (int) lifters.size();
}

bool Flight::isRunning()
{
    for (map<Lift, Competition>::iterator it = status.begin(); it != status.end(); ++it)
    {
        if (it->second == RUNNING)
            return true;
    }
    return false;    
}

// model
void Flight::beginCompetition(Lift lift)
{
    setCurrentLift(lift);
    setStatus(lift, RUNNING);
    resetRound();
}

void Flight::finishCompetition()
{
    setStatus(currentLift, COMPLETED);
}

void Flight::advanceRound()
{
    round++;
}

vector<Lifter*> Flight::getOrderedLiftersInRound()
{
    vector<Lifter*> orderedLifters;
    
    for (int i = 0; i < lifters.size(); i++)
    {
        orderedLifters.push_back(lifters[i]);
    }
    
    for (int i = 0; i < orderedLifters.size()-1; i++)
    {
        for (int j = i+1; j < orderedLifters.size(); j++)
        {
            if (orderedLifters[i]->compareWeight(orderedLifters[j], currentLift, round))
            {
                Lifter *tmp = orderedLifters[i];
                orderedLifters[i] = orderedLifters[j];
                orderedLifters[j] = tmp;
            }
        }
    }
    
    return orderedLifters;
}

// serialization
wxString Flight::serialize()
{
    wxString data = wxString::Format(wxT("%i%c"), flightNumber, FLIGHT_DELIMITER);
    
    for (int i = 0; i < NUMBER_LIFTS; i++)
    {
        data.Append(wxString::Format(wxT("%i%c"), status[static_cast<Lift>(i)], FLIGHT_DELIMITER));
    }
    return data;
}

void Flight::deserialize(wxString data)
{
    wxArrayString tokens = wxStringTokenize(data, FLIGHT_DELIMITER);
    int index = 0;

    int flightNumber;
    Competition status;
    
    flightNumber = wxAtoi(tokens[index]);
    index++;
    
    setFlightNumber(flightNumber);

    for (int i = 0; i < NUMBER_LIFTS; i++)
    {
        status = static_cast<Competition>(wxAtoi(tokens[index]));
        index++;
        
        setStatus(static_cast<Lift>(i), static_cast<Competition>(status));
    }
}
