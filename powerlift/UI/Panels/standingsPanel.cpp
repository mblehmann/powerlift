//
//  standingsPanel.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "standingsPanel.hpp"

StandingsPanel::StandingsPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE)
{
    SetSize(parent->GetClientSize());
    
    lifterRanking = new wxFlexGridSizer(STANDINGS_LABELS, wxSize(5, 5));
    
    for (wxString label : standingsLabels)
        lifterRanking->Add(new wxStaticText(this, wxID_ANY, label), 0, wxALIGN_CENTER);

    lifterRanking->AddGrowableCol(1, 1);
    lifterRanking->AddGrowableCol(2, 1);
    lifterRanking->AddGrowableCol(4, 1);
    
    SetSizer(lifterRanking);
}

void StandingsPanel::resetRanking()
{
    while (lifterRanking->GetItemCount() > STANDINGS_LABELS)
    {
        lifterRanking->Hide((int) lifterRanking->GetItemCount()-1);
        lifterRanking->Remove((int) lifterRanking->GetItemCount()-1);
    }
    Layout();
}

void StandingsPanel::populateRanking(vector<Lifter*> lifters)
{
    resetRanking();
    for (int i = 0; i < lifters.size(); i++)
    {
        Lifter *current = lifters[i];
        lifterRanking->Add(new wxStaticText(this, wxID_ANY, wxString::Format(wxT("%i"), i+1)), 0, wxALIGN_CENTER);
        lifterRanking->Add(new wxStaticText(this, wxID_ANY, current->getName()), 0, wxALIGN_CENTER);
        lifterRanking->Add(new wxStaticText(this, wxID_ANY, current->getTeam()), 0, wxALIGN_CENTER);
        lifterRanking->Add(new wxStaticText(this, wxID_ANY, wxString::Format(wxT("%i"), current->getFlight())), 0, wxALIGN_CENTER);
        lifterRanking->Add(new wxStaticText(this, wxID_ANY, current->getCategoryDescription()), 0, wxALIGN_CENTER);
        lifterRanking->Add(new wxStaticText(this, wxID_ANY, current->getRegistration()), 0, wxALIGN_CENTER);
        lifterRanking->Add(new wxStaticText(this, wxID_ANY, wxString::Format(wxT("%.1f"), current->getTotalResult())), 0, wxALIGN_CENTER);
        lifterRanking->Add(new wxStaticText(this, wxID_ANY, wxString::Format(wxT("%.1f"), current->getTotalWilks())), 0, wxALIGN_CENTER);
    }
    Layout();
}
