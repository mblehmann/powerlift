//
//  manager.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/6/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "manager.hpp"

// constructors
Manager::Manager()
{
    setName("");
    setDescription("");
    setNumberFlights(0);
    setLifterID(0);
    setupCategories();
}

Manager::Manager(wxString name, wxString description, int numberFlights)
{
    setName(name);
    setDescription(description);
    setNumberFlights(numberFlights);
    setLifterID(0);
    setupCategories();
}

// setters
void Manager::setName(wxString name)
{
    this->name = name;
}

void Manager::setDescription(wxString description)
{
    this->description = description;
}

void Manager::setNumberFlights(int numberFlights)
{
    this->numberFlights = numberFlights;
}

void Manager::setLifterID(int lifterID)
{
    this->lifterID = lifterID;
}

void Manager::setupCategories()
{
    double maleWeights[] = {0, 59, 66, 74, 83, 93, 105, 120, DBL_MAX};
    int maleCategories = 8;
    double femaleWeights[] = {0, 47, 52, 57, 63, 72, 84, DBL_MAX};
    int femaleCategories = 7;
    
    int index = 0;
    
    for (int i = 0; i < maleCategories; i++)
    {
        Category current(index, "Male", maleWeights[i]+0.01, maleWeights[i+1]);
        categories.push_back(current);
        index++;
    }
    
    for (int i = 0; i < femaleCategories; i++)
    {
        Category current(index, "Female", femaleWeights[i]+0.01, femaleWeights[i+1]);
        categories.push_back(current);
        index++;
    }
}

// getters
wxString Manager::getName()
{
    return name;
}

wxString Manager::getDescription()
{
    return description;
}

int Manager::getNumberFlights()
{
    return numberFlights;
}

Category* Manager::getCategory(wxString gender, double weight)
{
    for (int i = 0; i < categories.size(); i++)
    {
        if (categories[i].isOnTheCategoy(gender, weight))
            return &categories[i];
    }
    return NULL;
}

int Manager::getCategoryIndex(wxString description)
{
    for (int i = 0; i < categories.size(); i++)
    {
        if (categories[i].getDescription().Cmp(description) == 0)
            return categories[i].getIndex();
    }
    return -1;
}

// add lifters
Lifter* Manager::AddLifter(wxString name, wxString team, wxString gender, double weight, wxString registration, int flight)
{
    Lifter athlete(name, team, gender, weight, registration, flight, lifterID);
    Category* athleteCategory = getCategory(gender, weight);
    athlete.setCategory(athleteCategory->serialize());
    lifters.insert(pair<int, Lifter>(lifterID, athlete));
    lifterID++;
    return getLifter(lifterID-1);
}

void Manager::AddLifter(int mapID, wxString lifter)
{
    Lifter athlete;
    athlete.deserialize(lifter);
    lifters.insert(pair<int, Lifter>(mapID, athlete));
}

// lifter list
vector<Lifter*> Manager::getLifters(bool checkedIn, wxString registration)
{
    vector<Lifter*> liftersVector;
    for (map<int, Lifter>::iterator it = lifters.begin(); it != lifters.end(); ++it)
    {
        if ((it->second.getCheckedIn() || !checkedIn) && (it->second.getRegistration().Cmp(registration) == 0 || registration.Cmp("All") == 0))
            liftersVector.push_back(&it->second);
    }
    return liftersVector;
}

vector<Lifter*> Manager::getLiftersAtGender(wxString gender, bool checkedIn, wxString registration)
{
    vector<Lifter*> liftersVector;
    for (map<int, Lifter>::iterator it = lifters.begin(); it != lifters.end(); ++it)
    {
        if (it->second.getGender().compare(gender) == 0 && (it->second.getCheckedIn() || !checkedIn) && (it->second.getRegistration().Cmp(registration) == 0 || registration.Cmp("All") == 0))
            liftersVector.push_back(&it->second);
    }
    return liftersVector;
}

vector<Lifter*> Manager::getLiftersAtFlight(int flight, bool checkedIn, wxString registration)
{
    vector<Lifter*> liftersVector;
    for (map<int, Lifter>::iterator it = lifters.begin(); it != lifters.end(); ++it)
    {
        if (it->second.getFlight() == flight && (it->second.getCheckedIn() || !checkedIn) && (it->second.getRegistration().Cmp(registration) == 0 || registration.Cmp("All") == 0))
            liftersVector.push_back(&it->second);
    }
    return liftersVector;
}

vector<Lifter*> Manager::getLiftersAtCategory(int index, bool checkedIn, wxString registration)
{
    vector<Lifter*> liftersVector;
    for (map<int, Lifter>::iterator it = lifters.begin(); it != lifters.end(); ++it)
    {
        if (it->second.getCategoryIndex() == index && (it->second.getCheckedIn() || !checkedIn) && (it->second.getRegistration().Cmp(registration) == 0 || registration.Cmp("All") == 0))
            liftersVector.push_back(&it->second);
    }
    return liftersVector;
}

vector<Lifter*> Manager::getLiftersAtTeam(wxString team, bool checkedIn, wxString registration)
{
    vector<Lifter*> liftersVector;
    for (map<int, Lifter>::iterator it = lifters.begin(); it != lifters.end(); ++it)
    {
        if (it->second.getTeam().compare(team) == 0 && (it->second.getCheckedIn() || !checkedIn) && (it->second.getRegistration().Cmp(registration) == 0 || registration.Cmp("All") == 0))
            liftersVector.push_back(&it->second);
    }
    return liftersVector;
}

// lifters
wxArrayString Manager::getLifterNameID(bool isCheckIn)
{
    wxArrayString liftersNameID;
    for (map<int, Lifter>::iterator it = lifters.begin(); it != lifters.end(); ++it)
    {
        if (!it->second.getCheckedIn() || !isCheckIn)
            liftersNameID.Add(wxString::Format(wxT("%s %i"), it->second.getName(), it->second.getLifterID()));
    }
    liftersNameID.Sort();
    return liftersNameID;
}

Lifter* Manager::getLifter(int lifterID)
{
    return &lifters[lifterID];
}

// results
wxArrayString Manager::getSelections(Filter filter)
{
    wxArrayString selections;
    switch (filter)
    {
        case CATEGORY:
            selections = getAllCategories();
            break;
        case FLIGHT:
            selections = getAllFlights();
            break;
        case TEAM:
            selections = getAllTeams();
            break;
        case GENDER:
            selections = getAllGenders();
            break;
    }
    return selections;
}

wxArrayString Manager::getAllCategories()
{
    wxArrayString categoriesList;
    for (int i = 0; i < categories.size(); i++)
    {
        if (getLiftersAtCategory(categories[i].getIndex(), false, "All").size() > 0)
            categoriesList.Add(categories[i].getDescription());
    }
    return categoriesList;
}

wxArrayString Manager::getAllFlights()
{
    wxArrayString flightsList;
    for (int i = 0; i < numberFlights; i++)
    {
        flightsList.Add(wxString::Format(wxT("%i"), i+1));
    }
    return flightsList;
}

wxArrayString Manager::getAllTeams()
{
    wxArrayString teamsList;
    set<wxString> teamsSet;
    for (map<int, Lifter>::iterator it = lifters.begin(); it != lifters.end(); ++it)
    {
        wxString team = it->second.getTeam();
        if (teamsSet.count(team) == 0)
        {
            teamsList.Add(team);
            teamsSet.insert(team);
        }
    }
    teamsList.Sort();
    return teamsList;
}

wxArrayString Manager::getAllGenders()
{
    wxArrayString gendersList;
    gendersList.Add("All");
    gendersList.Add("Male");
    gendersList.Add("Female");
    return gendersList;
}

vector<Lifter*> Manager::getRankedLifters(Filter filter, wxString selection, wxString registration, wxString score)
{
    vector<Lifter*> lifters;
    switch (filter)
    {
        case CATEGORY:
            lifters = getLiftersAtCategory(getCategoryIndex(selection), false, registration);
            break;
        case FLIGHT:
            lifters = getLiftersAtFlight(wxAtoi(selection), false, registration);
            break;
        case TEAM:
            lifters = getLiftersAtTeam(selection.ToStdString(), false, registration);
            break;
        case GENDER:
            if (selection.Cmp("All") == 0)
                lifters = getLifters(false, registration);
            else
                lifters = getLiftersAtGender(selection.ToStdString(), false, registration);
            break;
    }
    
    if (lifters.size() > 0)
    {
        if (score.Cmp("Points") == 0)
            lifters = sortByPoints(&lifters);
        else
            lifters = sortByWilks(&lifters);
    }
    
    return lifters;
}

vector<Lifter*> Manager::sortByPoints(vector<Lifter*> *lifters)
{
    for (int i = 0; i < lifters->size()-1; i++)
    {
        for (int j = i+1; j < lifters->size(); j++)
        {
            if (!lifters->at(i)->comparePoints(lifters->at(j)))
            {
                Lifter *tmp = lifters->at(i);
                lifters->at(i) = lifters->at(j);
                lifters->at(j) = tmp;
            }
        }
    }
    return *lifters;
}

vector<Lifter*> Manager::sortByWilks(vector<Lifter*> *lifters)
{
    for (int i = 0; i < lifters->size()-1; i++)
    {
        for (int j = i+1; j < lifters->size(); j++)
        {
            if (!lifters->at(i)->compareWilks(lifters->at(j)))
            {
                Lifter *tmp = lifters->at(i);
                lifters->at(i) = lifters->at(j);
                lifters->at(j) = tmp;
            }
        }
    }
    return *lifters;
}

// overall statistics
int Manager::getMaximumFlightSize()
{
    vector<int> size(numberFlights);
    int maxSize = 0;
    for (map<int, Lifter>::iterator it = lifters.begin(); it != lifters.end(); ++it)
    {
        size[it->second.getFlight()-1]++;
    }
    for (int i = 0; i < numberFlights; i++)
    {
        maxSize = max(maxSize, size[i]);
    }
    return maxSize;
}

int Manager::getRegisteredLifters()
{
    return (int) lifters.size();
}

int Manager::getCheckedInLifters()
{
    int checkedIn = 0;
    for (map<int, Lifter>::iterator it = lifters.begin(); it != lifters.end(); ++it)
    {
        if (it->second.getCheckedIn())
            checkedIn++;
    }
    return checkedIn;
}

// serialization
wxString Manager::serialize()
{
    wxString data;
    
    wxString name = getName();
    wxString description = getDescription();
    
    name.Replace(wxT(" "), wxT("_"));
    description.Replace(wxT(" "), wxT("_"));

    data = wxString::Format(wxT("%s%c%s%c%i%c%i%c"), name, MANAGER_DELIMITER, description, MANAGER_DELIMITER, numberFlights, MANAGER_DELIMITER, lifterID, MANAGER_DELIMITER);
    
    for (map<int, Lifter>::iterator it = lifters.begin(); it != lifters.end(); ++it)
    {
        data.Append(wxString::Format(wxT("%i%c%s%c"), it->first, MANAGER_DELIMITER, (it->second).serialize(), MANAGER_DELIMITER));
    }
    
    return data;
}

void Manager::deserialize(wxString data)
{
    wxArrayString tokens = wxStringTokenize(data, MANAGER_DELIMITER);
    int index = 0;
    
    wxString name;
    wxString description;
    int numberFlights;
    int lifterID;
    
    int mapID;
    wxString lifter;

    name = tokens[index];
    index++;
    
    description = tokens[index];
    index++;
    
    name.Replace(wxT("_"), wxT(" "));
    description.Replace(wxT("_"), wxT(" "));
    
    numberFlights = wxAtoi(tokens[index]);
    index++;
    
    lifterID = wxAtoi(tokens[index]);
    index++;

    setName(name);
    setDescription(description);
    setNumberFlights(numberFlights);
    setLifterID(lifterID);
    
    while (index < tokens.size())
    {
        mapID = wxAtoi(tokens[index]);
        index++;
        
        lifter = tokens[index];
        index++;
        
        AddLifter(mapID, lifter);
    }
}
