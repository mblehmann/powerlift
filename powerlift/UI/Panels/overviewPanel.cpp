//
//  overviewPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/6/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "overviewPanel.hpp"

// constructor
OverviewPanel::OverviewPanel(wxFrame *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);

    competitionNameText = new wxStaticText(this, wxID_ANY, wxEmptyString);
    lifterTable = new CompetitorGridPanel(this);
    lifterSummaryPanel = new LifterSummaryPanel(this);
    lifterSummaryPanel->setStaticBoxLabel("Information");
    summaryPanel = new SummaryPanel(this);

    wxStaticBoxSizer *lifterBoxSizer = new wxStaticBoxSizer(new wxStaticBox(this, wxID_ANY, wxT("Lifter")), wxHORIZONTAL);
    lifterBoxSizer->Add(lifterSummaryPanel, 1, wxEXPAND);
    lifterBoxSizer->Add(summaryPanel, 1, wxEXPAND);
    
    verticalBox->Add(competitionNameText, 0, wxALIGN_CENTER | wxBOTTOM | wxTOP, 10);
    verticalBox->Add(lifterTable, 1, wxEXPAND);
    verticalBox->Add(lifterBoxSizer, 0, wxEXPAND);
    
    SetSizer(verticalBox);
    Layout();

}

OverviewPanel::~OverviewPanel()
{
    lifterTable->Destroy();
    lifterSummaryPanel->Destroy();
    summaryPanel->Destroy();
}

// setters
void OverviewPanel::setCompetitionName(wxString competitionName)
{
    competitionNameText->SetLabel(competitionName);
    Layout();
}

void OverviewPanel::setLifter(Lifter *lifter)
{
    lifterSummaryPanel->setLifter(lifter);
}

void OverviewPanel::setAttempt(Event *event, vector<double> wilks)
{
    summaryPanel->populateAttempts(event, wilks);
}

// operate on the table
void OverviewPanel::resetTable()
{
    lifterTable->resetTable();
}

void OverviewPanel::appendLifter(Lifter *lifter)
{
    lifterTable->appendLifter(lifter);
}

void OverviewPanel::appendLifter(Lifter *lifter, int index)
{
    lifterTable->appendLifter(lifter, index);
}

void OverviewPanel::populateTable(vector<Lifter*> lifters)
{
    lifterTable->populateTable(lifters);
}

// query the table
void OverviewPanel::selectCell(int row, int col)
{
    lifterTable->selectCell(row, col);
}

int OverviewPanel::getLifterID(int row)
{
    return lifterTable->getLifterID(row);
}

