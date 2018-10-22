//
//  lifter.hpp
//  powerlifting
//
//  Created by Matheus Lehmann on 7/31/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef lifter_hpp
#define lifter_hpp

#include "event.hpp"
#include "category.hpp"

using namespace std;

class Lifter
{
    // attributes
    wxString name;
    wxString team;
    wxString gender;
    double weight;
    wxString registration;
    int flight;
    int lifterID;
    bool checkedIn;
    
    // data structure
    Category category;
    Event event;

    // setters
    void setLifterID(int lifterID);
    void setEvent(wxString data);
    
public:
    // constructors
    Lifter();
    Lifter(wxString name, wxString team, wxString gender, double weight, wxString registration, int flight, int lifterID);
    
    // setters
    void setName(wxString name);
    void setTeam(wxString team);
    void setGender(wxString gender);
    void setWeight(double weight);
    void setRegistration(wxString registration);
    void setFlight(int flight);
    void setCheckedIn(bool checkedIn);
    void setCategory(wxString data);
    
    // getters
    wxString getName();
    wxString getTeam();
    wxString getGender();
    double getWeight();
    wxString getRegistration();
    int getFlight();
    int getLifterID();
    bool getCheckedIn();
    
    int getCategoryIndex();
    wxString getCategoryDescription();
    Event* getEvent();
    
    // Event
    vector<Attempt*> getAttempts(Lift lift);
    Attempt* getAttempt(Lift lift, int attempt);
    double getAttemptWeight(Lift lift, int attempt);
    Status getAttemptStatus(Lift lift, int attempt);
    bool isAttemptGood(Lift lift, int attempt);
    
    // aggregators
    int getAttemptBest();
    double getLiftResult(Lift lift);
    double getTotalResult();
    double getWilksCoefficient();
    double getLiftWilks(Lift lift);
    double getTotalWilks();
    vector<double> getWilks();

    // model
    void setFirstWeights(vector<double> firstWeights);
    void setLiftWeight(Lift lift, int attempt, double weight);
    void setLiftResult(Lift lift, int attempt, Status result);

    // sorting
    bool compareWeight(Lifter *other, Lift lift, int attempt);
    bool comparePoints(Lifter *other);
    bool compareWilks(Lifter *other);

    // serialization
    wxString serialize();
    void deserialize(wxString data);
};

#endif /* lifter_hpp */
