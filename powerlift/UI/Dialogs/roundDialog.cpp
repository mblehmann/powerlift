//
//  roundDialog.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/31/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "roundDialog.hpp"
#include "powerliftFrame.hpp"

// constructor
RoundDialog::RoundDialog(wxFrame *parent, wxString title, wxSize size) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, size)
{
    competitorGridPanel = new CompetitorGridPanel(this);
    lifterSummaryPanel = new LifterSummaryPanel(this);
    lifterSummaryPanel->setStaticBoxLabel("Lifter");
    attemptPanel = new AttemptPanel(this);
    attemptPanel->setWeightEditable(false);
    timerPanel = new TimerPanel(this);
    nextLiftersPanel = new NextLiftersPanel(this);

    wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *infoBox = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *buttonBox = new wxBoxSizer(wxHORIZONTAL);

    roundText = new wxStaticText(this, wxID_ANY, wxEmptyString);

    roundButton = new wxButton(this, ID_BeginRound, wxT("Begin Round"));
    roundSummaryButton = new wxButton(this, ID_RoundSummary, wxT("View Round"));
    beginLiftButton = new wxButton(this, ID_BeginLift, wxT("Begin Lift"));
    finishLiftButton = new wxButton(this, ID_FinishLift, wxT("Finish Lift"));
    finishFlightButton = new wxButton(this, ID_FinishFlight, wxT("Finish Flight"));
    
    infoBox->Add(lifterSummaryPanel, 1, wxEXPAND);
    infoBox->Add(attemptPanel, 1, wxEXPAND);
    infoBox->Add(timerPanel, 1, wxEXPAND);
    infoBox->Add(nextLiftersPanel, 1, wxEXPAND);

    buttonBox->Add(roundButton, 1);
    buttonBox->Add(roundSummaryButton, 1, wxLEFT, 10);
    buttonBox->Add(beginLiftButton, 1, wxLEFT, 10);
    buttonBox->Add(finishLiftButton, 1, wxLEFT, 10);
    buttonBox->Add(finishFlightButton, 1, wxLEFT, 10);
    buttonBox->Add(new wxButton(this, wxID_OK, wxT("Close")), 1, wxLEFT, 10);

    verticalBox->Add(competitorGridPanel, 1, wxEXPAND);
    verticalBox->Add(roundText, 0, wxALIGN_CENTER | wxBOTTOM | wxTOP, 10);
    verticalBox->Add(infoBox, 0, wxEXPAND);
    verticalBox->Add(buttonBox, 0, wxALIGN_CENTER | wxBOTTOM | wxTOP, 10);
    
    SetSizer(verticalBox);
    Centre();
}

// setters
// begin the flight and initialize the data structures
void RoundDialog::setupFlight(Flight *flight)
{
    this->flight = flight;
    attemptPanel->setLift(flight->getCurrentLift());
    competitorGridPanel->populateTable(flight->getLifters());
    orderedLifters = flight->getOrderedLiftersInRound();

    roundText->SetLabel("Waiting to begin flight");
//    attemptPanel->setup(LiftMap::liftString.at(flight->getCurrentLift()));
    
    roundButton->SetLabel(wxString::Format(wxT("Begin Round #%i"), flight->getRound()+1));
    beginLiftButton->Disable();
    finishLiftButton->Disable();
    finishFlightButton->Disable();
}

// set the current lifter and the following one
void RoundDialog::setLifters()
{
    Lift lift = flight->getCurrentLift();
    int round = flight->getRound();
    
    lifterSummaryPanel->setLifter(orderedLifters[liftPos]);
    attemptPanel->populateAttempt(orderedLifters[liftPos]->getAttempt(lift, round));
    attemptPanel->populateForm(orderedLifters[liftPos]->getAttempts(lift));
    
    nextLiftersPanel->addLifters(orderedLifters, liftPos+1, lift, round);
    roundText->SetLabel(wxString::Format(wxT("Round %i - Lifter %i of %i"), flight->getRound()+1, liftPos+1, flight->getFlightSize()));
}

void RoundDialog::updateLifterTables()
{
    ((PowerliftFrame*) this->GetParent())->refreshCompetitorGrid();
    competitorGridPanel->populateTable(flight->getLifters());
}

// round control
// begin round
void RoundDialog::beginRound()
{
    orderedLifters = flight->getOrderedLiftersInRound();
    liftPos = 0;
    setLifters();

    roundButton->Disable();
    beginLiftButton->Enable();
}

void RoundDialog::endRound()
{
    lifterSummaryPanel->resetLifter();
    attemptPanel->reset();
    
    flight->advanceRound();
    wxMessageDialog(this, wxString::Format(wxT("Round %i concluded"), flight->getRound())).ShowModal();
    
    if (!isFlightOver())
    {
        roundText->SetLabel(wxString::Format(wxT("Round %i concluded - Waiting to begin next round"), flight->getRound()));
        roundButton->SetLabel(wxString::Format(wxT("Begin Round #%i"), flight->getRound()+1));
        roundButton->Enable();
        Layout();
    }
    else
    {
        roundText->SetLabel("All rounds concluded");
        roundSummaryButton->Disable();
        finishFlightButton->Enable();
        Layout();
    }
}

// checkers
bool RoundDialog::isFlightOver()
{
    return flight->getRound() == 3;
}

bool RoundDialog::isLastRound()
{
    return flight->getRound() == 2;
}

bool RoundDialog::isRoundOver()
{
    return liftPos == flight->getFlightSize();
}

// events
void RoundDialog::OnTimer(wxTimerEvent& event)
{
    timerPanel->tickTimer();
}

void RoundDialog::OnBeginRound(wxCommandEvent& event)
{
    wxString title = wxString::Format(wxT("Flight %i - %s - Round %i"), flight->getFlightNumber(), LiftMap::liftString.at(flight->getCurrentLift()), flight->getRound()+1);
    RoundSummaryDialog *roundSummaryDialog = new RoundSummaryDialog(this, title, wxSize(500, 500));
    roundSummaryDialog->setFlight(flight);
    roundSummaryDialog->setEditable(true);
    roundSummaryDialog->setConfirmed(false);
    roundSummaryDialog->populateLifters();
    roundSummaryDialog->ShowModal();
    if (roundSummaryDialog->getConfirmed())
        beginRound();
    else
        wxMessageDialog(this, "Please confirm the weights to begin the round").ShowModal();
    roundSummaryDialog->Destroy();

    Raise();
    SetFocus();
    Show();
}

void RoundDialog::OnViewRound(wxCommandEvent& event)
{
    wxString title = wxString::Format(wxT("Flight %i - %s - Round %i"), flight->getFlightNumber(), LiftMap::liftString.at(flight->getCurrentLift()), flight->getRound());
    RoundSummaryDialog *roundSummaryDialog = new RoundSummaryDialog(this, title, wxSize(500, 500));
    roundSummaryDialog->setFlight(flight);
    roundSummaryDialog->setEditable(false);
    roundSummaryDialog->setConfirmed(true);
    roundSummaryDialog->populateLifters();
    roundSummaryDialog->ShowModal();
    roundSummaryDialog->Destroy();
    
    Raise();
    SetFocus();
    Show();
}

void RoundDialog::OnBeginLift(wxCommandEvent& event)
{
    timerPanel->startTimer(LIFT_TIME);
    beginLiftButton->Disable();
    finishLiftButton->Enable();
}

void RoundDialog::OnFinishLift(wxCommandEvent& event)
{
    timerPanel->stopTimer();
    Lift lift = flight->getCurrentLift();
    int round = flight->getRound();

    double currentWeight = orderedLifters[liftPos]->getAttemptWeight(lift, round);
    Status result = attemptPanel->getResult();
    
    // update lifter
    orderedLifters[liftPos]->setLiftResult(lift, round, result);
    if (!isLastRound())
    {
        double nextWeight = result == GOOD ? currentWeight + MINIMUM_INCREASE : currentWeight;
        orderedLifters[liftPos]->setLiftWeight(lift, round+1, nextWeight);
    }
    
    // update competition
    ((PowerliftFrame*) this->GetParent())->refreshCompetitorGrid();
    competitorGridPanel->populateTable(flight->getLifters());
    finishLiftButton->Disable();
    
    // go to next
    liftPos++;
    if (!isRoundOver())
    {
        setLifters();
        beginLiftButton->Enable();
    }
    else
    {
        endRound();
    }
}

void RoundDialog::OnFinishFlight(wxCommandEvent& event)
{
    ((PowerliftFrame*) this->GetParent())->finishFlightLift();
}
