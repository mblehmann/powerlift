//
//  standingsFilterPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/15/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

// constructor
#include "standingsFilterPanel.hpp"

StandingsFilterPanel::StandingsFilterPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());

    wxFlexGridSizer *inputGrid = new wxFlexGridSizer(2, wxSize(5, 5));

    selectionText = new wxStaticText(this, wxID_ANY, wxEmptyString);
    filterInput = new wxChoice(this, ID_StandingsFilter, wxDefaultPosition, wxDefaultSize, WXSIZEOF(standingsFilters), standingsFilters);
    selectionInput = new wxChoice(this, ID_StandingsSelection, wxDefaultPosition, wxDefaultSize, wxArrayString());
    registrationInput = new wxChoice(this, ID_StandingsFilter, wxDefaultPosition, wxDefaultSize, WXSIZEOF(standingsRegistrations), standingsRegistrations);
    scoreInput = new wxChoice(this, ID_StandingsFilter, wxDefaultPosition, wxDefaultSize, WXSIZEOF(standingsScores), standingsScores);

    inputGrid->Add(new wxStaticText(this, wxID_ANY, "View standings per"));
    inputGrid->Add(filterInput);
    inputGrid->Add(selectionText);
    inputGrid->Add(selectionInput);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, "Registered in"));
    inputGrid->Add(registrationInput);
    inputGrid->Add(new wxStaticText(this, wxID_ANY, "Ranked by"));
    inputGrid->Add(scoreInput);
    
    SetSizer(inputGrid);
    Center();
    Layout();
}

// setters
void StandingsFilterPanel::setSelectionText(wxString text)
{
    selectionText->SetLabel(text);
    Layout();
}

void StandingsFilterPanel::setSelectionChoices(wxArrayString choices)
{
    selectionInput->Clear();
    selectionInput->Append(choices);
    Layout();
}

// getters
wxString StandingsFilterPanel::getFilter()
{
    return filterInput->GetString(filterInput->GetSelection());
}

wxString StandingsFilterPanel::getSelection()
{
    return selectionInput->GetString(selectionInput->GetSelection());
}

wxString StandingsFilterPanel::getRegistration()
{
    return registrationInput->GetString(registrationInput->GetSelection());
}

wxString StandingsFilterPanel::getScore()
{
    return scoreInput->GetString(scoreInput->GetSelection());
}
