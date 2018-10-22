//
//  editLifterDialog.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/13/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "editLifterDialog.hpp"
#include "powerliftFrame.hpp"

// constructor
EditLifterDialog::EditLifterDialog(wxFrame *parent, wxString title, wxSize size) : AddLifterDialog(parent, title, size)
{
    lifterListPanel = new LifterListPanel(this);
    currentLifter = NULL;
}

void EditLifterDialog::setupDialog()
{
    wxBoxSizer *verticalBox = new wxBoxSizer(wxVERTICAL);
    
    wxBoxSizer *panelBox = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *lifterBox = new wxBoxSizer(wxVERTICAL);
    
    int spacer = 290;
    lifterBox->Add(lifterPanel, 1, wxEXPAND | wxBOTTOM | wxTOP | wxRIGHT, 10);
    lifterBox->Add(new wxButton(this, ID_UpdateLifter, wxT("Update")), 0, wxALIGN_CENTER | wxBOTTOM, 10);
    lifterBox->AddSpacer(spacer);
    
    panelBox->Add(lifterListPanel, 1, wxEXPAND);
    panelBox->Add(lifterBox, 1, wxEXPAND);
    
    verticalBox->Add(panelBox, 1, wxEXPAND);
    verticalBox->Add(CreateButtonSizer(wxOK), 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);
    
    SetSizer(verticalBox);
    Centre();
    Layout();
}

// accessor
void EditLifterDialog::populateLifterList(wxArrayString lifterList)
{
    lifterListPanel->populateLifterList(lifterList);
    
    if (lifterList.size() > 0)
    {
        wxCommandEvent *event = new wxCommandEvent();
        OnSelectLifter(*event);
        delete event;
    }
}

int EditLifterDialog::getLifterID()
{
    return lifterListPanel->getLifterID();
}

void EditLifterDialog::updateLifter()
{
    currentLifter->setName(lifterPanel->getName());
    currentLifter->setTeam(lifterPanel->getTeam());
    currentLifter->setGender(lifterPanel->getGender());
    currentLifter->setWeight(lifterPanel->getWeight());
    currentLifter->setRegistration(lifterPanel->getRegistration());
    currentLifter->setFlight(lifterPanel->getFlight());
    
    Category* category = ((PowerliftFrame*) this->GetParent())->getCategory(currentLifter->getGender(), currentLifter->getWeight());
    currentLifter->setCategory(category->serialize());
}

// events
void EditLifterDialog::OnSelectLifter(wxCommandEvent& event)
{
    currentLifter = ((PowerliftFrame*) this->GetParent())->getLifter(getLifterID());
    lifterPanel->setLifter(currentLifter);
}

void EditLifterDialog::OnUpdateLifter(wxCommandEvent& event)
{
    if (validateFields())
    {
        updateLifter();
        populateLifterList(((PowerliftFrame*) this->GetParent())->getLifterList(false));
        ((PowerliftFrame*) this->GetParent())->updateLifter();
    }
    else
    {
        wxMessageDialog(this, getError()).ShowModal();
    }
}

// validation
bool EditLifterDialog::validateFields()
{
    return AddLifterDialog::validateFields() && currentLifter != NULL;
}

wxString EditLifterDialog::getError()
{
    wxString error = AddLifterDialog::getError();
    if (currentLifter == NULL)
    {
        error += "No lifter selected. Please select one lifter in the list\n";
    }
    return error;
}
