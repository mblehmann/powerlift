//
//  main.cpp
//  powerlifting
//
//  Created by Matheus Lehmann on 7/31/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "definition.h"

#include "powerliftApp.hpp"
#include "powerliftFrame.hpp"
#include "editLifterDialog.hpp"
#include "checkinDialog.hpp"
#include "flightDialog.hpp"
#include "flightGridDialog.hpp"
#include "roundDialog.hpp"
#include "editResultDialog.hpp"

const map<Lift, wxString> LiftMap::liftString = LiftMap::create_map();
const map<Status, wxString> ColorMap::liftColor = ColorMap::create_map();
const map<wxString, Status> ResultMap::resultString = ResultMap::create_map();
const map<Status, wxString> ResultStringMap::resultString = ResultStringMap::create_map();
const map<wxString, Filter> FilterMap::filterString = FilterMap::create_map();

wxBEGIN_EVENT_TABLE(PowerliftFrame, wxFrame)
EVT_MENU(ID_NewCompetition,     PowerliftFrame::OnNewCompetition)
EVT_MENU(ID_EditCompetition,    PowerliftFrame::OnEditCompetition)
EVT_MENU(ID_CloseCompetition,   PowerliftFrame::OnCloseCompetition)
EVT_MENU(ID_SaveCompetition,    PowerliftFrame::OnSaveCompetition)
EVT_MENU(ID_LoadCompetition,    PowerliftFrame::OnLoadCompetition)

EVT_MENU(ID_AddLifter,          PowerliftFrame::OnAddLifter)
EVT_MENU(ID_EditLifter,         PowerliftFrame::OnEditLifter)
EVT_MENU(ID_Checkin,            PowerliftFrame::OnCheckin)
EVT_MENU(ID_ViewFlights,        PowerliftFrame::OnViewFlights)
EVT_MENU(ID_StartCompetition,   PowerliftFrame::OnStartCompetition)

EVT_MENU(ID_ViewCompetition,    PowerliftFrame::OnViewCompetition)
EVT_MENU(ID_ViewRound,          PowerliftFrame::OnViewRound)
EVT_MENU(ID_EditResult,         PowerliftFrame::OnEditResult)

EVT_MENU(ID_ViewStandings,      PowerliftFrame::OnViewStandings)

EVT_MENU(wxID_EXIT,             PowerliftFrame::OnExit)
EVT_GRID_CELL_LEFT_CLICK(       PowerliftFrame::OnClick)
EVT_GRID_SELECT_CELL(           PowerliftFrame::OnSelectCell)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(EditLifterDialog, wxDialog)
EVT_LISTBOX(ID_LifterDetails,   EditLifterDialog::OnSelectLifter)
EVT_BUTTON(ID_UpdateLifter,     EditLifterDialog::OnUpdateLifter)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(CheckinDialog, wxDialog)
EVT_LISTBOX(ID_LifterDetails,   CheckinDialog::OnSelectLifter)
EVT_BUTTON(ID_CheckinLifter,    CheckinDialog::OnCheckInLifter)
EVT_CHECKBOX(ID_CheckinFilter,  CheckinDialog::OnCheckInFilter)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(FlightDialog, wxDialog)
EVT_CHOICE(ID_SelectFlight,    FlightDialog::OnSelectFlight)
EVT_BUTTON(ID_ConfirmFlights,  FlightDialog::OnConfirmFlights)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(FlightGridDialog, wxDialog)
EVT_BUTTON(ID_StartFlight,   FlightGridDialog::OnStartFlight)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(RoundDialog, wxDialog)
EVT_TIMER(ID_Timer,          RoundDialog::OnTimer)
EVT_BUTTON(ID_BeginRound,    RoundDialog::OnBeginRound)
EVT_BUTTON(ID_RoundSummary,  RoundDialog::OnViewRound)
EVT_BUTTON(ID_BeginLift,     RoundDialog::OnBeginLift)
EVT_BUTTON(ID_FinishLift,    RoundDialog::OnFinishLift)
EVT_BUTTON(ID_FinishFlight,  RoundDialog::OnFinishFlight)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(RoundSummaryDialog, wxDialog)
EVT_BUTTON(ID_ConfirmRound,     RoundSummaryDialog::OnConfirmFlights)
EVT_TEXT(ID_ChangeRoundWeight,  RoundSummaryDialog::OnUnconfirmFlights)
EVT_BUTTON(ID_UnconfirmRound,   RoundSummaryDialog::OnUnconfirmFlights)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(EditResultDialog, wxDialog)
EVT_BUTTON(ID_UpdateResults,    EditResultDialog::OnUpdateResults)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(ViewStandingsDialog, wxDialog)
EVT_CHOICE(ID_StandingsFilter,     ViewStandingsDialog::OnStandingsFilter)
EVT_CHOICE(ID_StandingsSelection,  ViewStandingsDialog::OnPopulateLifters)
EVT_RADIOBOX(ID_StandingsScore,    ViewStandingsDialog::OnPopulateLifters)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(PowerliftApp);
