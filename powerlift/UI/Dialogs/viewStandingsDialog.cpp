//
//  viewStandingsDialog.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "viewStandingsDialog.hpp"
#include "powerliftFrame.hpp"

// constructor
ViewStandingsDialog::ViewStandingsDialog(wxFrame *parent, wxString title, wxSize size) : wxDialog(parent, wxID_ANY, title, wxDefaultPosition, size)
{
    standingsFilterPanel = new StandingsFilterPanel(this);
    standingsPanel = new StandingsPanel(this);
    
    wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);
    verticalBox->Add(standingsFilterPanel, 0, wxALIGN_CENTER | wxBOTTOM | wxTOP, 10);
    verticalBox->Add(standingsPanel, 1, wxEXPAND | wxBOTTOM | wxLEFT | wxRIGHT, 10);
    
    SetSizer(verticalBox);
    Centre();
    Layout();
    
    wxCommandEvent *event = new wxCommandEvent();
    OnStandingsFilter(*event);
    delete event;
}

// events
void ViewStandingsDialog::OnStandingsFilter(wxCommandEvent& event)
{
    wxString filter = standingsFilterPanel->getFilter();
    wxArrayString selections = ((PowerliftFrame*) this->GetParent())->getSelections(FilterMap::filterString.at(filter));
    
    standingsFilterPanel->setSelectionText(filter);
    standingsFilterPanel->setSelectionChoices(selections);
    
    OnPopulateLifters(event);
}

void ViewStandingsDialog::OnPopulateLifters(wxCommandEvent& event)
{
    wxString filter = standingsFilterPanel->getFilter();
    wxString selection = standingsFilterPanel->getSelection();
    wxString registration = standingsFilterPanel->getRegistration();
    wxString score = standingsFilterPanel->getScore();

    vector<Lifter*> lifters = ((PowerliftFrame*) this->GetParent())->getRankedLifters(FilterMap::filterString.at(filter), selection, registration, score);
    
    standingsPanel->populateRanking(lifters);
    Layout();
}
