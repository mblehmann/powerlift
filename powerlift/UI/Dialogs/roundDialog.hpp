//
//  roundDialog.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/31/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef roundDialog_hpp
#define roundDialog_hpp

#include "flight.hpp"

#include "competitorGridPanel.hpp"
#include "lifterSummaryPanel.hpp"
#include "attemptPanel.hpp"
#include "timerPanel.hpp"
#include "nextLiftersPanel.hpp"
#include "roundSummaryDialog.hpp"

using namespace std;

class RoundDialog : public wxDialog
{
    // attributes
    Flight *flight;
    vector<Lifter*> orderedLifters;
    int liftPos;
    
    // GUI
    CompetitorGridPanel *competitorGridPanel;
    LifterSummaryPanel *lifterSummaryPanel;
    AttemptPanel *attemptPanel;
    TimerPanel *timerPanel;
    NextLiftersPanel *nextLiftersPanel;

    wxStaticText *roundText;
    wxButton *roundButton;
    wxButton *roundSummaryButton;
    wxButton *beginLiftButton;
    wxButton *finishLiftButton;
    wxButton *finishFlightButton;
    
public:
    // constructor
    RoundDialog(wxFrame *parent, wxString title, wxSize size);

    // setters
    void setupFlight(Flight *flight);
    void setLifters();
    void updateLifterTables();
    
    // round control
    void beginRound();
    void endRound();

    // checkers
    bool isFlightOver();
    bool isLastRound();
    bool isRoundOver();
    
    // events
    void OnTimer(wxTimerEvent& event);
    void OnBeginRound(wxCommandEvent& event);
    void OnViewRound(wxCommandEvent& event);
    void OnBeginLift(wxCommandEvent& event);
    void OnFinishLift(wxCommandEvent& event);
    void OnFinishFlight(wxCommandEvent& event);
    wxDECLARE_EVENT_TABLE();
};

#endif /* roundDialog_hpp */
