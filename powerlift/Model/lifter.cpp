//
//  lifter.cpp
//  powerlifting
//
//  Created by Matheus Lehmann on 7/31/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "lifter.hpp"

// constructors
Lifter::Lifter()
{
    setName("");
    setTeam("");
    setGender("");
    setWeight(0);
    setRegistration("");
    setFlight(0);
    setLifterID(-1);
    setCheckedIn(false);
}

Lifter::Lifter(wxString name, wxString team, wxString gender, double weight, wxString registration, int flight, int lifterID)
{
    setName(name);
    setTeam(team);
    setGender(gender);
    setWeight(weight);
    setRegistration(registration);
    setFlight(flight);
    setLifterID(lifterID);
    setCheckedIn(false);
}

// setters
void Lifter::setName(wxString name)
{
    this->name = name;
}

void Lifter::setTeam(wxString team)
{
    this->team = team;
}

void Lifter::setGender(wxString gender)
{
    this->gender = gender;
}

void Lifter::setWeight(double weight)
{
    this->weight = weight;
}

void Lifter::setRegistration(wxString registration)
{
    this->registration = registration;
}

void Lifter::setFlight(int flight)
{
    this->flight = flight;
}

void Lifter::setCheckedIn(bool checkedIn)
{
    this->checkedIn = checkedIn;
}

void Lifter::setCategory(wxString data)
{
    category.deserialize(data);
}

void Lifter::setLifterID(int lifterID)
{
    this->lifterID = lifterID;
}

void Lifter::setEvent(wxString data)
{
    event.deserialize(data);
}

// getters
wxString Lifter::getName()
{
    return name;
}

wxString Lifter::getTeam()
{
    return team;
}

wxString Lifter::getGender()
{
    return gender;
}

double Lifter::getWeight()
{
    return weight;
}

wxString Lifter::getRegistration()
{
    return registration;
}

int Lifter::getFlight()
{
    return flight;
}

int Lifter::getLifterID()
{
    return lifterID;
}

bool Lifter::getCheckedIn()
{
    return checkedIn;
}

int Lifter::getCategoryIndex()
{
    return category.getIndex();
}

wxString Lifter::getCategoryDescription()
{
    return category.getDescription();
}

Event* Lifter::getEvent()
{
    return &event;
}

// Event
vector<Attempt*> Lifter::getAttempts(Lift lift)
{
    return event.getAttempts(lift);
}

Attempt* Lifter::getAttempt(Lift lift, int attempt)
{
    return event.getAttempt(lift, attempt);
}

double Lifter::getAttemptWeight(Lift lift, int attempt)
{
    return event.getAttemptWeight(lift, attempt);
}

Status Lifter::getAttemptStatus(Lift lift, int attempt)
{
    return event.getAttemptStatus(lift, attempt);
}

bool Lifter::isAttemptGood(Lift lift, int attempt)
{
    return event.isAttemptGood(lift, attempt);
}

// aggregators
int Lifter::getAttemptBest()
{
    return event.getAttemptBest();
}

double Lifter::getLiftResult(Lift lift)
{
    return event.getLiftResult(lift);
}

double Lifter::getTotalResult()
{
    return event.getTotalResult();
}

double Lifter::getWilksCoefficient()
{
    double weight = getWeight();
    if (gender.Cmp("Male"))
        return 500 / (maleWilks[0] + maleWilks[1]*weight + maleWilks[2]*pow(weight, 2) + maleWilks[3]*pow(weight, 3) + maleWilks[4]*pow(weight, 4) + maleWilks[5]*pow(weight, 5));
    else
        return 500 / (femaleWilks[0] + femaleWilks[1]*weight + femaleWilks[2]*pow(weight, 2) + femaleWilks[3]*pow(weight, 3) + femaleWilks[4]*pow(weight, 4) + femaleWilks[5]*pow(weight, 5));
}

double Lifter::getLiftWilks(Lift lift)
{
    return getLiftResult(lift) * getWilksCoefficient();
}

double Lifter::getTotalWilks()
{
    return getTotalResult() * getWilksCoefficient();
}

vector<double> Lifter::getWilks()
{
    vector<double> wilks;
    for (Lift lift : lifts)
    {
        wilks.push_back(getLiftWilks(lift));
    }
    wilks.push_back(getTotalWilks());
    return wilks;
}

// model
void Lifter::setFirstWeights(vector<double> firstWeights)
{
    for (Lift lift : lifts)
    {
        setLiftWeight(lift, 0, firstWeights[lift]);
    }
    setCheckedIn(true);
}

void Lifter::setLiftWeight(Lift lift, int attempt, double weight)
{
    event.setLiftWeight(lift, attempt, weight);
}

void Lifter::setLiftResult(Lift lift, int attempt, Status result)
{
    event.setLiftResult(lift, attempt, result);
}

// sorting
// true = higher
// false = lower
bool Lifter::compareWeight(Lifter *other, Lift lift, int attempt)
{
    for (int i = attempt; i >= 0; i--)
    {
        if (getAttemptWeight(lift, attempt) > other->getAttemptWeight(lift, attempt))
            return true;
        if (getAttemptWeight(lift, attempt) < other->getAttemptWeight(lift, attempt))
            return false;
    }
    return getLifterID() > other->getLifterID();
}

bool Lifter::comparePoints(Lifter *other)
{
    if (getTotalResult() > other->getTotalResult())
        return true;
    if (getTotalResult() < other->getTotalResult())
        return false;
    
    if (getWeight() < other->getWeight())
        return true;
    if (getWeight() > other->getWeight())
        return false;
    
    if (getAttemptBest() < other->getAttemptBest())
        return true;
    if (getAttemptBest() > other->getAttemptBest())
        return true;

    return getLifterID() < other->getLifterID();
}

bool Lifter::compareWilks(Lifter *other)
{
    if (getTotalWilks() > other->getTotalWilks())
        return true;
    if (getTotalWilks() < other->getTotalWilks())
        return false;
    
    if (getWeight() < other->getWeight())
        return true;
    if (getWeight() > other->getWeight())
        return false;
    
    if (getAttemptBest() < other->getAttemptBest())
        return true;
    if (getAttemptBest() > other->getAttemptBest())
        return true;
    
    return getLifterID() < other->getLifterID();
}

// serializations
wxString Lifter::serialize()
{
    wxString data;
    
    wxString name = getName();
    wxString team = getTeam();

    name.Replace(wxT(" "), wxT("_"));
    team.Replace(wxT(" "), wxT("_"));
    
    data = wxString::Format(wxT("%s%c%s%c%s%c%f%c%s%c%i%c%i%c%i%c%s%c%s"), name, LIFTER_DELIMITER, team, LIFTER_DELIMITER, gender, LIFTER_DELIMITER, weight, LIFTER_DELIMITER, registration, LIFTER_DELIMITER, flight, LIFTER_DELIMITER, lifterID, LIFTER_DELIMITER, checkedIn, LIFTER_DELIMITER, category.serialize(), LIFTER_DELIMITER, event.serialize());

    return data;
}

void Lifter::deserialize(wxString data)
{
    wxArrayString tokens = wxStringTokenize(data, LIFTER_DELIMITER);
    int index = 0;
    
    wxString name;
    wxString team;
    wxString gender;
    double weight;
    wxString registration;
    int flight;
    int lifterID;
    bool checkedIn;
    wxString category;
    wxString event;
    
    name = tokens[index];
    index++;
    
    team = tokens[index];
    index++;
    
    name.Replace(wxT("_"), wxT(" "));
    team.Replace(wxT("_"), wxT(" "));
    
    gender = tokens[index];
    index++;
    
    weight = wxAtof(tokens[index]);
    index++;
    
    registration = tokens[index];
    index++;
    
    flight = wxAtoi(tokens[index]);
    index++;
    
    lifterID = wxAtoi(tokens[index]);
    index++;
    
    checkedIn = wxAtoi(tokens[index]);
    index++;
    
    category = tokens[index];
    index++;
    
    event = tokens[index];
    index++;

    setName(name);
    setTeam(team);
    setGender(gender);
    setWeight(weight);
    setRegistration(registration);
    setFlight(flight);
    setLifterID(lifterID);
    setCheckedIn(checkedIn);
    setCategory(category);
    setEvent(event);
}
