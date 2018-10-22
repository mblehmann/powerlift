//
//  competitorGridPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/5/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "competitorGridPanel.hpp"

// constructor
CompetitorGridPanel::CompetitorGridPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    
    lifterTable = new wxGrid(this, wxID_ANY);
    lifterTable->CreateGrid(0, GRID_COLUMNS);
    int col = 0;
    for (wxString label : gridLabels)
    {
        lifterTable->SetColLabelValue(col, label);
        col++;
    }
    
    lifterTable->HideRowLabels();
    lifterTable->EnableEditing(false);
    
    sizer->Add(lifterTable, 1, wxEXPAND);
    
    SetSizer(sizer);
}

CompetitorGridPanel::~CompetitorGridPanel()
{
    lifterTable->Destroy();
}

// operate
void CompetitorGridPanel::resetTable()
{
    if (lifterTable->GetNumberRows() > 0)
    {
        lifterTable->DeleteRows(0, lifterTable->GetNumberRows());
    }
}

void CompetitorGridPanel::appendLifter(Lifter *lifter)
{
    lifterTable->AppendRows();
    appendLifter(lifter, lifterTable->GetNumberRows()-1);
}

void CompetitorGridPanel::appendLifter(Lifter *lifter, int index)
{
    lifterTable->SetCellValue(index, 0, wxString::Format(wxT("%i"), lifter->getLifterID()));
    lifterTable->SetCellValue(index, 1, lifter->getName());
    
    for (Lift lift : lifts)
    {
        for (int i = 0; i < TRIES; i++)
        {
            int colIndex = (lift*TRIES)+i+2;
            lifterTable->SetCellValue(index, colIndex, wxString::Format(wxT("%.1f"), lifter->getAttemptWeight(lift, i)));
            lifterTable->SetCellBackgroundColour(index, colIndex, ColorMap::liftColor.at(lifter->getAttemptStatus(lift, i)));
        }
    }
    
    lifterTable->SetCellValue(index, 11, wxString::Format(wxT("%.1f"), lifter->getTotalResult()));
    lifterTable->SetCellValue(index, 12, wxString::Format(wxT("%.1f"), lifter->getTotalWilks()));
}

void CompetitorGridPanel::populateTable(vector<Lifter*> lifters)
{
    if (lifters.size() > 0)
    {
        this->resetTable();
        lifterTable->AppendRows((int) lifters.size());
        for (int i = 0; i < lifters.size(); i++)
        {
            appendLifter(lifters[i], i);
        }
    }
}

// query
void CompetitorGridPanel::selectCell(int row, int col)
{
    lifterTable->GoToCell(row, col);
}

int CompetitorGridPanel::getLifterID(int row)
{
    return wxAtoi(lifterTable->GetCellValue(row, 0));
}

