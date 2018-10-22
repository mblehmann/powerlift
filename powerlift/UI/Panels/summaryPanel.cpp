//
//  summaryPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/31/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "summaryPanel.hpp"

SummaryPanel::SummaryPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    wxStaticBoxSizer *inputBox = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Summary")), wxVERTICAL);

    wxGridBagSizer *inputGrid = new wxGridBagSizer(5, 5);
    
    inputGrid->Add(new wxStaticText(this, wxID_ANY, "Lift"), wxGBPosition(0, 0), wxDefaultSpan, wxALIGN_CENTER);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, "#1"), wxGBPosition(0, 1), wxDefaultSpan, wxALIGN_CENTER);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, "#2"), wxGBPosition(0, 2), wxDefaultSpan, wxALIGN_CENTER);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, "#3"), wxGBPosition(0, 3), wxDefaultSpan, wxALIGN_CENTER);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, "Best"), wxGBPosition(0, 4), wxDefaultSpan, wxALIGN_CENTER);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, "Wilks"), wxGBPosition(0, 5), wxDefaultSpan, wxALIGN_CENTER);
    
    inputGrid->Add(new wxStaticText(this, wxID_ANY, "Squat"), wxGBPosition(1, 0));
    inputGrid->Add(new wxStaticText(this, wxID_ANY, "Bench"), wxGBPosition(2, 0));
    inputGrid->Add(new wxStaticText(this, wxID_ANY, "Deadlift"), wxGBPosition(3, 0));
    inputGrid->Add(new wxStaticText(this, wxID_ANY, "Total"), wxGBPosition(4, 0));
    
    liftInput = new vector<wxStaticText*>();
    for (int i = 0; i < 9; i++)
    {
        liftInput->push_back(new wxStaticText(this, wxID_ANY, wxEmptyString));
        inputGrid->Add(liftInput->at(i), wxGBPosition(i/TRIES + 1, i % TRIES + 1), wxDefaultSpan, wxALIGN_CENTER);
    }
    
    liftBest = new vector<wxStaticText*>();
    for (int i = 0; i < 4; i++)
    {
        liftBest->push_back(new wxStaticText(this, wxID_ANY, wxEmptyString));
        inputGrid->Add(liftBest->at(i), wxGBPosition(i+1, 4), wxDefaultSpan, wxALIGN_CENTER);
    }
    
    liftWilks = new vector<wxStaticText*>();
    for (int i = 0; i < 4; i++)
    {
        liftWilks->push_back(new wxStaticText(this, wxID_ANY, wxEmptyString));
        inputGrid->Add(liftWilks->at(i), wxGBPosition(i+1, 5), wxDefaultSpan, wxALIGN_CENTER);
    }
    
    inputGrid->AddGrowableCol(1, 1);
    inputGrid->AddGrowableCol(2, 1);
    inputGrid->AddGrowableCol(3, 1);
    inputGrid->AddGrowableCol(4, 1);
    inputGrid->AddGrowableCol(5, 1);
    
    inputBox->Add(inputGrid, 1, wxEXPAND);
    
    SetSizer(inputBox);
    Layout();
}

void SummaryPanel::populateAttempts(Event *event, vector<double> wilks)
{
    for (Lift lift : lifts)
    {
        for (int i = 0; i < TRIES; i++)
        {
            int index = (lift*TRIES)+i;
            double weight = event->getAttemptWeight(lift, i);
            Status result = event->getAttemptStatus(lift, i);

            liftInput->at(index)->SetLabel(wxString::Format(wxT("%.1f"), weight));
            liftInput->at(index)->SetBackgroundColour(ColorMap::liftColor.at(result));
        }
        liftBest->at(lift)->SetLabel(wxString::Format(wxT("%.1f"), event->getLiftResult(lift)));
        liftWilks->at(lift)->SetLabel(wxString::Format(wxT("%.1f"), wilks[lift]));
    }

    liftBest->at(NUMBER_LIFTS)->SetLabel(wxString::Format(wxT("%.1f"), event->getTotalResult()));
    liftWilks->at(NUMBER_LIFTS)->SetLabel(wxString::Format(wxT("%.1f"), wilks[NUMBER_LIFTS]));
    Layout();
}

