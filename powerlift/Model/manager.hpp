//
//  manager.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/6/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef manager_hpp
#define manager_hpp

#include "lifter.hpp"

class Manager
{
    // attributes
    wxString name;
    wxString description;
    int numberFlights;
    int lifterID;
    
    map<int, Lifter> lifters;
    vector<Category> categories;
    
    // setters
    void setLifterID(int lifterID);
    
public:
    // constructors
    Manager();
    Manager(wxString name, wxString descriptions, int numberFlights);
    
    // setters
    void setName(wxString name);
    void setDescription(wxString description);
    void setNumberFlights(int numberFlights);
    void setupCategories();

    // getters
    wxString getName();
    wxString getDescription();
    int getNumberFlights();
    Category* getCategory(wxString gender, double weight);
    int getCategoryIndex(wxString description);
    
    // add lifters
    Lifter* AddLifter(wxString name, wxString team, wxString gender, double weight, wxString registration, int flight);
    void AddLifter(int mapID, wxString lifter);
    
    // lifter list
    vector<Lifter*> getLifters(bool checkedIn, wxString registration);
    vector<Lifter*> getLiftersAtGender(wxString gender, bool checkedIn, wxString registration);
    vector<Lifter*> getLiftersAtFlight(int flight, bool checkedIn, wxString registration);
    vector<Lifter*> getLiftersAtCategory(int index, bool checkedIn, wxString registration);
    vector<Lifter*> getLiftersAtTeam(wxString team, bool checkedIn, wxString registration);
    
    // lifters
    wxArrayString getLifterNameID(bool isCheckIn);
    Lifter* getLifter(int lifterID);

    // results
    wxArrayString getSelections(Filter filter);
    wxArrayString getAllCategories();
    wxArrayString getAllFlights();
    wxArrayString getAllTeams();
    wxArrayString getAllGenders();
    vector<Lifter*> getRankedLifters(Filter filter, wxString selection, wxString registration, wxString score);
    vector<Lifter*> sortByPoints(vector<Lifter*> *lifters);
    vector<Lifter*> sortByWilks(vector<Lifter*> *lifters);

    // overall statistics
    int getMaximumFlightSize();
    int getRegisteredLifters();
    int getCheckedInLifters();
    
    // serialization
    wxString serialize();
    void deserialize(wxString data);
};

#endif /* manager_hpp */
