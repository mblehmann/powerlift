//
//  powerliftFrame.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/6/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef powerliftFrame_hpp
#define powerliftFrame_hpp

#include "manager.hpp"
#include "flight.hpp"

#include "overviewPanel.hpp"
#include "competitionDialog.hpp"
#include "checkinDialog.hpp"
#include "flightDialog.hpp"
#include "flightGridDialog.hpp"
#include "roundDialog.hpp"
#include "editResultDialog.hpp"
#include "viewStandingsDialog.hpp"

using namespace std;

class PowerliftFrame : public wxFrame
{
    // attributes
    Manager *manager;
    Competition competitionStatus;
    map<int, Flight> *flights;
    Flight* currentFlight;

    // GUI
    wxMenuBar *menuBar;
    OverviewPanel *overviewPanel;
    FlightGridDialog *flightGridDialog;
    RoundDialog *roundDialog;
    
    // menu
    void createMenuBar();
    void configureMenu(Competition competitionStatus);
    void enableMenu(wxMenu *menu);
    void disableMenu(wxMenu *menu);
    
    // file
    void OnNewCompetition(wxCommandEvent& event);
    void OnEditCompetition(wxCommandEvent& event);
    void OnCloseCompetition(wxCommandEvent& event);
    void OnSaveCompetition(wxCommandEvent& event);
    void OnLoadCompetition(wxCommandEvent& event);
    
    // edit
    void OnAddLifter(wxCommandEvent& event);
    void OnEditLifter(wxCommandEvent& event);
    void OnCheckin(wxCommandEvent& event);
    void OnViewFlights(wxCommandEvent& event);
    void OnStartCompetition(wxCommandEvent& event);
    
    // competition
    void OnViewCompetition(wxCommandEvent& event);
    void OnViewRound(wxCommandEvent& event);
    void OnEditResult(wxCommandEvent& event);

    // results
    void OnViewStandings(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
 
    // grid
    void OnClick(wxGridEvent& event);
    void OnSelectCell(wxGridEvent& event);
    wxDECLARE_EVENT_TABLE();
    
    // initialization
    void loadCompetition(wxString data);
    void createCompetition(wxString name, wxString description, int numberFlights);
    void createFlights();
    
    // serialization
    wxString serialize();
    void deserialize(wxString data);
    
public:
    // constructor
    PowerliftFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

    // setup
    void setCompetitionStatus(Competition competitionStatus);
    void loadFlight(int index, wxString data);
    
    // getting (list of) lifters
    wxArrayString getLifterList(bool isCheckin);
    vector<Lifter*> getLiftersAtFlight(int flight, int checkedIn);
    Lifter* getLifter(int lifterID);

    // statistics
    int getRegisteredLifters();
    int getCheckedInLifters();
    wxString getSummary();

    // flights
    vector<Flight*> getFlights();
    wxString getFlightStatus();
    
    // category
    Category* getCategory(wxString gender, double weight);
    
    // standings
    wxArrayString getSelections(Filter filter);
    vector<Lifter*> getRankedLifters(Filter filter, wxString selection, wxString registration, wxString score);
    
    // checking status of the competitions
    bool isCompetitionCreated();
    bool isCompetitionConfirmed();
    bool isFlightRunning();
    
    // control of the competition
    void updateLifter();
    void confirmFlights();
    void beginFlightLift(int flight, Lift lift);
    void refreshCompetitorGrid();
    void finishFlightLift();
};

#endif /* powerliftFrame_hpp */
