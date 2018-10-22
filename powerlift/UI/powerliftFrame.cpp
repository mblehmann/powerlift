//
//  powerliftFrame.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/6/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "powerliftFrame.hpp"

// constructor
PowerliftFrame::PowerliftFrame(const wxString& title, const wxPoint& pos, const wxSize& size) : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    createMenuBar();
    setCompetitionStatus(NONE);
}

// menu
void PowerliftFrame::createMenuBar()
{
    menuBar = new wxMenuBar;

    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_NewCompetition, "&New Competition", "Create a new competition");
    menuFile->Append(ID_EditCompetition, "&Edit Competition", "Edit the competition");
    menuFile->Append(ID_CloseCompetition, "&Close Competition", "Close the competition");
    menuFile->AppendSeparator();
    menuFile->Append(ID_SaveCompetition, "&Save Competition", "Save the competition");
    menuFile->Append(ID_LoadCompetition, "&Load Competition", "Load a competition");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT, "&Exit", "Exit the program");
    menuBar->Append(menuFile, "&File");
    
    wxMenu *menuEdit = new wxMenu;
    menuEdit->Append(ID_AddLifter, "&Add Lifter", "Add a lifter to the competition");
    menuEdit->Append(ID_EditLifter, "&Edit Lifter", "Edit the lifters in the competition");
    menuEdit->AppendSeparator();
    menuEdit->Append(ID_Checkin, "&Check-in", "Check-in the lifters to the competition");
    menuEdit->Append(ID_ViewFlights, "&View Flights", "View the list of lifters in each flight");
    menuEdit->AppendSeparator();
    menuEdit->Append(ID_StartCompetition, "&Start Competition", "Start the competition");
    menuBar->Append(menuEdit, "&Edit");
    
    wxMenu *menuCompetition = new wxMenu;
    menuCompetition->Append(ID_ViewCompetition, "&View Competition", "View the competition flights and lifts");
    menuCompetition->Append(ID_ViewRound, "&View Round", "View the current round running in the competition");
    menuEdit->AppendSeparator();
    menuCompetition->Append(ID_EditResult, "&Edit Result", "Edit the results of the competition");
    menuBar->Append(menuCompetition, "&Competition");
    
    wxMenu *menuResults = new wxMenu;
    menuResults->Append(ID_ViewStandings, "&View Standings", "View the standings of the competition");
    menuBar->Append(menuResults, "&Results");
    
    SetMenuBar(menuBar);
}

void PowerliftFrame::configureMenu(Competition competitionStatus)
{
    switch (competitionStatus)
    {
        case NONE:
            enableMenu(menuBar->GetMenu(0));
            menuBar->GetMenu(0)->FindItem(ID_EditCompetition)->Enable(false);
            menuBar->GetMenu(0)->FindItem(ID_CloseCompetition)->Enable(false);
            menuBar->GetMenu(0)->FindItem(ID_SaveCompetition)->Enable(false);
            disableMenu(menuBar->GetMenu(1));
            disableMenu(menuBar->GetMenu(2));
            disableMenu(menuBar->GetMenu(3));
            break;
        case CREATED:
            enableMenu(menuBar->GetMenu(0));
            enableMenu(menuBar->GetMenu(1));
            menuBar->GetMenu(1)->FindItem(ID_StartCompetition)->Enable(false);
            disableMenu(menuBar->GetMenu(2));
            disableMenu(menuBar->GetMenu(3));
            break;
        case CONFIRMED:
            enableMenu(menuBar->GetMenu(0));
            enableMenu(menuBar->GetMenu(1));
            disableMenu(menuBar->GetMenu(2));
            disableMenu(menuBar->GetMenu(3));
            break;
        case RUNNING:
            enableMenu(menuBar->GetMenu(0));
            disableMenu(menuBar->GetMenu(1));
            enableMenu(menuBar->GetMenu(2));
            enableMenu(menuBar->GetMenu(3));
            break;
        case COMPLETED:
            enableMenu(menuBar->GetMenu(0));
            disableMenu(menuBar->GetMenu(1));
            disableMenu(menuBar->GetMenu(2));
            enableMenu(menuBar->GetMenu(3));
            break;
        default: break;
    }
}

void PowerliftFrame::enableMenu(wxMenu *menu)
{
    wxMenuItemList list = menu->GetMenuItems();

    for (int i = 0; i < list.size(); i++)
        list[i]->Enable(true);
}

void PowerliftFrame::disableMenu(wxMenu *menu)
{
    wxMenuItemList list = menu->GetMenuItems();
    
    for (int i = 0; i < list.size(); i++)
        list[i]->Enable(false);
}

// file
void PowerliftFrame::OnNewCompetition(wxCommandEvent& event)
{
    CompetitionDialog *competitionDialog = new CompetitionDialog(this, "Create new competition", wxSize(500, 300));
    competitionDialog->setDefaultCompetition();
    while (true)
    {
        if (competitionDialog->ShowModal() == wxID_OK)
        {
            if (competitionDialog->validateFields())
            {
                wxString name = competitionDialog->getName();
                wxString description = competitionDialog->getDescription();
                int numberFlights = competitionDialog->getNumberFlights();

                // if a competition exists, close it before
                if (isCompetitionCreated())
                    OnCloseCompetition(event);

                createCompetition(name, description, numberFlights);
                break;
            }
            else
            {
                wxMessageDialog(this, competitionDialog->getError()).ShowModal();
            }
            
        }
        else
        {
            break;
        }
    }
    competitionDialog->Destroy();
}

void PowerliftFrame::OnEditCompetition(wxCommandEvent& event)
{
    CompetitionDialog *competitionDialog = new CompetitionDialog(this, "Edit the competition", wxSize(500, 300));
    competitionDialog->setCompetition(manager);
    while (true)
    {
        if (competitionDialog->ShowModal() == wxID_OK)
        {
            if (competitionDialog->validateFields())
            {
                wxString name = competitionDialog->getName();
                wxString description = competitionDialog->getDescription();
                int numberFlights = competitionDialog->getNumberFlights();

                manager->setName(name);
                manager->setDescription(description);
                manager->setNumberFlights(numberFlights);
                
                break;
            }
            else
            {
                wxMessageDialog(this, competitionDialog->getError()).ShowModal();
            }
        }
        else
        {
            break;
        }
    }
    competitionDialog->Destroy();
}

void PowerliftFrame::OnCloseCompetition(wxCommandEvent& event)
{
    delete manager;
    delete overviewPanel;
    if (flights != NULL)
        delete flights;
    if (flightGridDialog != NULL)
        delete flightGridDialog;
    if (roundDialog != NULL)
        delete roundDialog;
    setCompetitionStatus(NONE);
}

void PowerliftFrame::OnSaveCompetition(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, "Save the tournament", "", "", "*", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
    
    wxTextFile file(saveFileDialog.GetPath());
    file.Open();
    file.AddLine(serialize());
    file.Close();
}

void PowerliftFrame::OnLoadCompetition(wxCommandEvent& event)
{
    wxFileDialog openFileDialog(this, "Open a tournament", "", "", "*", wxFD_OPEN|wxFD_FILE_MUST_EXIST);
    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    wxString data;
    wxTextFile file(openFileDialog.GetPath());
    file.Open();
    data = file.GetFirstLine();
    file.Close();

    if (isCompetitionCreated())
        OnCloseCompetition(event);

    deserialize(data);
}

// edit 
void PowerliftFrame::OnAddLifter(wxCommandEvent& event)
{
    AddLifterDialog *addLifterDialog = new AddLifterDialog(this, "Add new lifter", wxSize(360, 260));
    addLifterDialog->setNumberFlights(manager->getNumberFlights());
    addLifterDialog->setupDialog();
    
    while (true)
    {
        if (addLifterDialog->ShowModal() == wxID_OK)
        {
            if (addLifterDialog->validateFields())
            {
                wxString name = addLifterDialog->getName();
                wxString team = addLifterDialog->getTeam();
                wxString gender = addLifterDialog->getGender();
                double weight = addLifterDialog->getWeight();
                wxString registration = addLifterDialog->getRegistration();
                int flight = addLifterDialog->getFlight();
                Lifter *lifter = manager->AddLifter(name, team, gender, weight, registration, flight);
                overviewPanel->appendLifter(lifter);
                break;
            }
            else
            {
                wxMessageDialog(this, addLifterDialog->getError()).ShowModal();
            }
        }
        else
        {
            break;
        }
    }
    addLifterDialog->Destroy();
}

void PowerliftFrame::OnEditLifter(wxCommandEvent& event)
{
    EditLifterDialog *editLifterDialog = new EditLifterDialog(this, "Edit lifters", wxSize(600, 600));
    editLifterDialog->setNumberFlights(manager->getNumberFlights());
    editLifterDialog->setupDialog();
    editLifterDialog->populateLifterList(getLifterList(false));
    editLifterDialog->ShowModal();
    editLifterDialog->Destroy();
}

void PowerliftFrame::OnCheckin(wxCommandEvent& event)
{
    CheckinDialog *checkinDialog = new CheckinDialog(this, "Check-in lifters", wxSize(600, 600));
    checkinDialog->setNumberFlights(manager->getNumberFlights());
    checkinDialog->setupDialog();
    checkinDialog->populateLifterList(getLifterList(false));
    checkinDialog->ShowModal();    
    checkinDialog->Destroy();
}

void PowerliftFrame::OnViewFlights(wxCommandEvent& event)
{
    FlightDialog *flightDialog = new FlightDialog(this, "Flights Overview", wxSize(600, 600));
    flightDialog->setNumberFlights(manager->getNumberFlights());
    flightDialog->setConfirmed(isCompetitionConfirmed());
    flightDialog->ShowModal();
    flightDialog->Destroy();
}

void PowerliftFrame::OnStartCompetition(wxCommandEvent& event)
{
    createFlights();
    flightGridDialog = new FlightGridDialog(this, "Competition Overview", wxSize(600, 600));
    flightGridDialog->setFlights(getFlights());
    wxMessageDialog(this, getSummary()).ShowModal();
}

// competition
void PowerliftFrame::OnViewCompetition(wxCommandEvent& event)
{
    flightGridDialog->SetFocus();
    flightGridDialog->Raise();
    flightGridDialog->Show();
}

void PowerliftFrame::OnViewRound(wxCommandEvent& event)
{
    if (isFlightRunning())
    {
        flightGridDialog->Raise();
        flightGridDialog->Show();
        roundDialog->SetFocus();
        roundDialog->Raise();
        roundDialog->Show();
    }
    else
    {
        wxMessageDialog(this, "No flight current running").ShowModal();
    }
}

void PowerliftFrame::OnEditResult(wxCommandEvent& event)
{
    EditResultDialog *editResultDialog = new EditResultDialog(this, "Edit Results", wxSize(900, 760));
    editResultDialog->setNumberFlights(manager->getNumberFlights());
    editResultDialog->setupDialog();
    editResultDialog->populateLifterList(getLifterList(false));
    editResultDialog->ShowModal();
    editResultDialog->Destroy();
}

// results
void PowerliftFrame::OnViewStandings(wxCommandEvent& event)
{
    ViewStandingsDialog *viewStandingsDialog = new ViewStandingsDialog(this, "Standings", wxSize(600, 600));
    viewStandingsDialog->ShowModal();
    viewStandingsDialog->Destroy();
}

void PowerliftFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

// grid
void PowerliftFrame::OnClick(wxGridEvent& event)
{
    overviewPanel->selectCell(event.GetRow(), 0);
}

void PowerliftFrame::OnSelectCell(wxGridEvent& event)
{
    int lifterID = overviewPanel->getLifterID(event.GetRow());
    Lifter *lifter = getLifter(lifterID);
    if (lifter != NULL)
    {
        overviewPanel->setLifter(lifter);
        overviewPanel->setAttempt(lifter->getEvent(), lifter->getWilks());
    }
}

// setup
void PowerliftFrame::setCompetitionStatus(Competition competitionStatus)
{
    this->competitionStatus = competitionStatus;
    configureMenu(competitionStatus);
}

void PowerliftFrame::loadFlight(int index, wxString data)
{
    flights->at(index).deserialize(data);
}

// getting (list of) lifters
wxArrayString PowerliftFrame::getLifterList(bool isCheckin)
{
    return manager->getLifterNameID(isCheckin);
}

vector<Lifter*> PowerliftFrame::getLiftersAtFlight(int flight, int checkedIn)
{
    return manager->getLiftersAtFlight(flight, checkedIn, "All");
}

Lifter* PowerliftFrame::getLifter(int lifterID)
{
    return manager->getLifter(lifterID);
}

// statistics
int PowerliftFrame::getRegisteredLifters()
{
    return manager->getRegisteredLifters();
}

int PowerliftFrame::getCheckedInLifters()
{
    return manager->getCheckedInLifters();
}

wxString PowerliftFrame::getSummary()
{
    wxString summary = "Competition Started!\n";
    for (map<int, Flight>::iterator it = flights->begin(); it != flights->end(); ++it)
    {
        summary.Append(wxString::Format(wxT("Flight %i with %i lifters\n"), it->first, it->second.getFlightSize()));
    }
    return summary;
}

// flights
vector<Flight*> PowerliftFrame::getFlights()
{
    vector<Flight*> flightsVector;
    for (map<int, Flight>::iterator it = flights->begin(); it != flights->end(); ++it)
    {
        flightsVector.push_back(&(it->second));
    }
    return flightsVector;
}

wxString PowerliftFrame::getFlightStatus()
{
    wxString flightStatus;
    
    if (isFlightRunning())
    {
        flightStatus = wxString::Format(wxT("%i%c"), (int) flights->size(), FRAME_DELIMITER);
        for (int i = 0; i < flights->size(); i++)
            flightStatus.Append(wxString::Format(wxT("%s%c"), flights->at(i).serialize(), FRAME_DELIMITER));
    }
    else
    {
        flightStatus = wxString::Format(wxT("%i%c"), 0, FRAME_DELIMITER);
    }
    return flightStatus;
}

// category
Category* PowerliftFrame::getCategory(wxString gender, double weight)
{
    return manager->getCategory(gender, weight);
}

// standings
wxArrayString PowerliftFrame::getSelections(Filter filter)
{
    return manager->getSelections(filter);
}

vector<Lifter*> PowerliftFrame::getRankedLifters(Filter filter, wxString selection, wxString registration, wxString score)
{
    return manager->getRankedLifters(filter, selection, registration, score);
}

// checking status of the competitions
bool PowerliftFrame::isCompetitionCreated()
{
    return competitionStatus != NONE;
}

bool PowerliftFrame::isCompetitionConfirmed()
{
    return competitionStatus == CONFIRMED;
}

bool PowerliftFrame::isFlightRunning()
{
    return currentFlight != NULL;
}

// control of the competition
void PowerliftFrame::updateLifter()
{
    refreshCompetitorGrid();
    setCompetitionStatus(CREATED);
}

void PowerliftFrame::confirmFlights()
{
    setCompetitionStatus(CONFIRMED);
}

void PowerliftFrame::beginFlightLift(int flight, Lift lift)
{
    if (!isFlightRunning())
    {
        currentFlight = &flights->at(flight);
        currentFlight->beginCompetition(lift);
        flightGridDialog->Raise();
        flightGridDialog->Show();
        
        roundDialog = new RoundDialog(this, wxString::Format(wxT("Flight %i - %s"), flight, LiftMap::liftString.at(currentFlight->getCurrentLift())), wxSize(1060, 640));
        roundDialog->setupFlight(currentFlight);
        roundDialog->Show();
    }
    else
    {
        flightGridDialog->Raise();
        flightGridDialog->Show();
        roundDialog->SetFocus();
        roundDialog->Raise();
        roundDialog->Show();
    }
}

void PowerliftFrame::refreshCompetitorGrid()
{
    overviewPanel->populateTable(manager->getLifters(false, "All"));
}

void PowerliftFrame::finishFlightLift()
{
    currentFlight->finishCompetition();
    flightGridDialog->endFlight();
    delete roundDialog;
    currentFlight = NULL;
}

// initialization
void PowerliftFrame::loadCompetition(wxString data)
{
    manager = new Manager();
    manager->deserialize(data);

    overviewPanel = new OverviewPanel(this);
    overviewPanel->SetFocus();
    overviewPanel->setCompetitionName(manager->getName());
    refreshCompetitorGrid();
    
    flights = NULL;
    currentFlight = NULL;
    flightGridDialog = NULL;
    roundDialog = NULL;
}

void PowerliftFrame::createCompetition(wxString name, wxString description, int numberFlights)
{
    manager = new Manager(name, description, numberFlights);

    overviewPanel = new OverviewPanel(this);
    overviewPanel->SetFocus();
    overviewPanel->setCompetitionName(name);
    
    flights = NULL;
    currentFlight = NULL;
    flightGridDialog = NULL;
    roundDialog = NULL;
    
    setCompetitionStatus(CREATED);
}

void PowerliftFrame::createFlights()
{
    int numberFlights = manager->getNumberFlights();
    
    flights = new map<int, Flight>();
    for (int i = 0; i < numberFlights; i++)
    {
        vector<Lifter*> lifters = manager->getLiftersAtFlight(i+1, true, "All");
        if (lifters.size() > 0)
        {
            Flight newFlight(i+1, lifters);
            flights->insert(pair<int, Flight>(i+1, newFlight));
        }
    }
    setCompetitionStatus(RUNNING);
}

// serialization
wxString PowerliftFrame::serialize()
{
    wxString data;
    
    data = wxString::Format(wxT("%i%c%s%s"), competitionStatus, FRAME_DELIMITER, getFlightStatus(), manager->serialize());

    return data;
}

void PowerliftFrame::deserialize(wxString data)
{
    wxArrayString tokens = wxStringTokenize(data, FRAME_DELIMITER);
    int index = 0;

    Competition competitionStatus;
    int numberFlights;
    vector<wxString> flightStatus;
    wxString manager;
    
    competitionStatus = static_cast<Competition>(wxAtoi(tokens[index]));
    index++;

    numberFlights = wxAtoi(tokens[index]);
    index++;
    
    for (int i = 0; i < numberFlights; i++)
    {
        flightStatus.push_back(tokens[index]);
        index++;
    }
    
    manager = tokens[index];
    
    loadCompetition(manager);
    
    switch(competitionStatus)
    {
        case NONE:
        case CREATED:
        case CONFIRMED: break;
        case RUNNING:
        case COMPLETED:
            wxCommandEvent *event = new wxCommandEvent();
            OnStartCompetition(*event);
            flightGridDialog->endFlight();
            delete event;
            break;
    }
    
    setCompetitionStatus(competitionStatus);
    for (int i = 0; i < numberFlights; i++)
        loadFlight(i, flightStatus[i]);

}
