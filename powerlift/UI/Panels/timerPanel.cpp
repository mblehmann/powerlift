//
//  timerPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/17/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "timerPanel.hpp"

// constructor
TimerPanel::TimerPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    wxStaticBoxSizer *timerBoxSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Timer")), wxVERTICAL);
    
    timerText = new wxStaticText(this, wxID_ANY, wxEmptyString);
    timerText->SetFont(wxFont(120, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD));

    timer = new wxTimer(GetParent(), ID_Timer);
    timeoutSound = new wxSound("JapaneseTemple.wav");

    timerBoxSizer->Add(timerText, 0, wxALIGN_CENTER, 10);
    
    SetSizer(timerBoxSizer);
}

// setters
void TimerPanel::setTimer(int time)
{
    currentTime = time;
}

void TimerPanel::startTimer()
{
    timerText->SetLabel(wxString::Format(wxT("%i"), currentTime));
    timerText->SetForegroundColour("Black");
    Layout();
    timer->Start(1000);
}

// accessors
void TimerPanel::startTimer(int time)
{
    setTimer(time);
    startTimer();
}

void TimerPanel::tickTimer()
{
    currentTime--;
    timerText->SetLabel(wxString::Format(wxT("%i"), currentTime));
    Layout();
    
    if (currentTime == LIFT_WARNING)
        timerText->SetForegroundColour("Red");

    if (currentTime == 0)
    {
        timeoutSound->Play();
        stopTimer();
    }
}

void TimerPanel::stopTimer()
{
    timer->Stop();
}
