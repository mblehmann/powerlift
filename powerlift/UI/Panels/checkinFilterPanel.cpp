//
//  checkinFilterPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/13/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "checkinFilterPanel.hpp"

// constructor
CheckinFilterPanel::CheckinFilterPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);
    
    checkedInFilter = new wxCheckBox(this, ID_CheckinFilter, wxT("Unchecked-in only?"));
    checkedInFilter->SetValue(false);
    
    wxFlexGridSizer *summaryGrid = new wxFlexGridSizer(2, wxSize(5, 5));
    
    registeredLifters = new wxStaticText(this, wxID_ANY, wxEmptyString);
    checkedInLifters = new wxStaticText(this, wxID_ANY, wxEmptyString);
    percentageLifters = new wxStaticText(this, wxID_ANY, wxEmptyString);
    
    summaryGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Registered Lifters")));
    summaryGrid->Add(registeredLifters);
    summaryGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Checked-in Lifters")));
    summaryGrid->Add(checkedInLifters);
    summaryGrid->Add(new wxStaticText(this, wxID_ANY, wxT("Checked-in Percentage")));
    summaryGrid->Add(percentageLifters);
    
    summaryGrid->AddGrowableCol(1, 1);
    
    verticalBox->Add(checkedInFilter, 0, wxALIGN_CENTER);
    verticalBox->Add(summaryGrid, 0, wxALIGN_CENTER | wxBOTTOM | wxTOP | wxLEFT | wxRIGHT, 10);
    
    SetSizer(verticalBox);
    Layout();
}

// accessors
void CheckinFilterPanel::updateLifterSummary(int registered, int checkedIn)
{
    registeredLifters->SetLabel(wxString::Format(wxT("%i"), registered));
    checkedInLifters->SetLabel(wxString::Format(wxT("%i"), checkedIn));
    percentageLifters->SetLabel(wxString::Format(wxT("%.1f"), ((double) checkedIn / (double) registered) * 100));
    Layout();
}

bool CheckinFilterPanel::getCheckedInFilter()
{
    return checkedInFilter->GetValue();
}
