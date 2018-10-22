//
//  definition.h
//  powerlifting
//
//  Created by Matheus Lehmann on 7/31/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef definition_h
#define definition_h

#include <stdio.h>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <float.h>

#include "wx/wxprec.h"
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/tokenzr.h"
#include "wx/wfstream.h"
#include "wx/valnum.h"
#include "wx/textfile.h"
#include "wx/grid.h"
#include "wx/gbsizer.h"
#include "wx/sound.h"
#include "wx/statline.h"

using namespace std;

// basic definitions
#define TRIES 3
#define NUMBER_LIFTS 3
#define MININUM_WEIGHT 25
#define MINIMUM_INCREASE 2.5
#define LIFT_TIME 60
#define LIFT_WARNING 10
#define NEXT_LIFTERS_ROWS 7
#define NEXT_LIFTERS_COLS 2

#define MIN_FLIGHTS 1
#define MAX_FLIGHTS 5
#define GRID_COLUMNS 13
#define FLIGHT_COLUMNS 4
#define ROUND_COLUMNS 4
#define STANDINGS_FILTERS 4
#define STANDINGS_SCORES 2
#define STANDINGS_REGISTRATIONS 3
#define STANDINGS_LABELS 8

#define MIN_LIFT_WEIGHT 30
#define NUM_RESULTS 3

#define INVALID_VALUE -1

#define ATTEMPT_DELIMITER '#'
#define EVENT_DELIMITER '$'
#define LIFTER_DELIMITER '%'
#define MANAGER_DELIMITER '&'
#define FLIGHT_DELIMITER '@'
#define CATEGORY_DELIMITER '!'
#define FRAME_DELIMITER '*'

// enumerations
typedef enum {
    SQUAT,
    BENCH,
    DEADLIFT,
} Lift;

typedef enum {
    NONE,
    CREATED,
    CONFIRMED,
    RUNNING,
    COMPLETED,
} Competition;

typedef enum {
    UNDEFINED,
    READY,
    GOOD,
    FAIL,
    PASS,
} Status;

typedef enum {
    CATEGORY,
    FLIGHT,
    TEAM,
    GENDER,
} Filter;

typedef enum
{
    ID_Useless,
    
    ID_NewCompetition,
    ID_EditCompetition,
    ID_CloseCompetition,
    ID_SaveCompetition,
    ID_LoadCompetition,

    ID_AddLifter,
    ID_EditLifter,
    ID_LifterDetails,
    ID_UpdateLifter,
    ID_Checkin,
    ID_CheckinLifter,
    ID_CheckinFilter,

    ID_StartCompetition,
    ID_ViewFlights,
    ID_SelectFlight,
    ID_ConfirmFlights,

    ID_ViewCompetition,
    ID_StartFlight,
    ID_ViewRound,
    
    ID_Timer,
    ID_BeginRound,
    ID_RoundSummary,
    ID_BeginLift,
    ID_FinishLift,
    ID_FinishFlight,

    ID_EditResult,
    ID_UpdateResults,
    
    ID_ViewStandings,
    ID_StandingsFilter,
    ID_StandingsSelection,
    ID_StandingsScore,
    
    ID_ChangeRoundWeight,
    ID_ConfirmRound,
    ID_UnconfirmRound,
} Events;

// data structures
const Lift lifts[] = {SQUAT, BENCH, DEADLIFT};

const double maleWilks[] = {-216.0475144, 16.2606339, -0.002388645, -0.00113732, 7.01863E-06, -1.291E-08};
const double femaleWilks[] = {594.31747775582, -27.23842536447, 0.82112226871, -0.00930733913, 4.731582E-05, -9.054E-08};

struct LiftMap {
    static map<Lift, wxString> create_map()
    {
        map<Lift, wxString> m;
        m[SQUAT] = "Squat";
        m[BENCH] = "Bench";
        m[DEADLIFT] = "Deadlift";
        return m;
    }
    static const map<Lift, wxString> liftString;
};

const wxString genders[] = {wxT("Male"), wxT("Female")};
const wxString registrations[] = {wxT("Open"), wxT("Interbox")};

struct ColorMap {
    static map<Status, wxString> create_map()
    {
        map<Status, wxString> m;
        m[GOOD] = "Green";
        m[PASS] = "Yellow";
        m[FAIL] = "Red";
        m[READY] = "White";
        m[UNDEFINED] = wxEmptyString;
        return m;
    }
    static const map<Status, wxString> liftColor;
};

const wxString gridLabels[] = {"ID", "Name", "Squat #1", "Squat #2", "Squat #3", "Bench #1", "Bench #2", "Bench #3", "Deadlift #1", "Deadlift #2", "Deadlift #3", "Total", "Points"};

const wxString flightLabels[] = {"Name", "Team", "Category", "Checked-In"};
const wxString roundLabels[] = {"Order", "Lifter", "Lifter ID", "Attempt Weight"};

const wxString liftResults[] = {wxT("Good"), wxT("Pass"), wxT("Fail")};
const wxString liftStatus[] = {wxT("Ready"), wxT("Good"), wxT("Pass"), wxT("Fail")};
const wxString standingsFilters[] = {wxT("Category"), wxT("Flight"), wxT("Team"), wxT("Gender")};
const wxString standingsScores[] = {wxT("Points"), wxT("Wilks")};
const wxString standingsRegistrations[] = {wxT("All"), wxT("Open"), wxT("Interbox")};
const wxString standingsLabels[] = {"Rank", "Name", "Team", "Flight", "Category", "Registration", "Score", "Wilks"};

struct ResultMap {
    static map<wxString, Status> create_map()
    {
        map<wxString, Status> m;
        m["Good"] = GOOD;
        m["Pass"] = PASS;
        m["Fail"] = FAIL;
        m["Ready"] = READY;
        return m;
    }
    static const map<wxString, Status> resultString;
};

struct ResultStringMap {
    static map<Status, wxString> create_map()
    {
        map<Status, wxString> m;
        m[GOOD] = "Good";
        m[PASS] = "Pass";
        m[FAIL] = "Fail";
        m[READY] = "Ready";
        m[UNDEFINED] = "Undefined";
        return m;
    }
    static const map<Status, wxString> resultString;
};

struct FilterMap {
    static map<wxString, Filter> create_map()
    {
        map<wxString, Filter> m;
        m["Category"] = CATEGORY;
        m["Flight"] = FLIGHT;
        m["Team"] = TEAM;
        m["Gender"] = GENDER;
        return m;
    }
    static const map<wxString, Filter> filterString;
};

#endif /* definition_h */
