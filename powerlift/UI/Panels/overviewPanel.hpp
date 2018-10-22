//
//  overviewPanel_hpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/6/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef overviewPanel_hpp
#define overviewPanel_hpp

#include "lifter.hpp"
#include "competitorGridPanel.hpp"
#include "lifterSummaryPanel.hpp"
#include "summaryPanel.hpp"

class OverviewPanel : public wxPanel
{
    // attributes
    wxStaticText *competitionNameText;
    CompetitorGridPanel *lifterTable;
    LifterSummaryPanel *lifterSummaryPanel;
    SummaryPanel *summaryPanel;
        
public:
    // constructor
    OverviewPanel(wxFrame *parent);
    ~OverviewPanel();
    
    // setters
    void setCompetitionName(wxString competitionName);
    void setLifter(Lifter *lifter);
    void setAttempt(Event *event, vector<double> wilks);
    
    // operate on the table
    void resetTable();
    void appendLifter(Lifter *lifter);
    void appendLifter(Lifter *lifter, int index);
    void populateTable(vector<Lifter*> lifters);

    // query the table
    void selectCell(int row, int col);
    int getLifterID(int row);
};

#endif /* overviewPanel_hpp */
