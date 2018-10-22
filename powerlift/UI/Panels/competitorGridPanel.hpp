//
//  competitorGridPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/5/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef competitorGridPanel_hpp
#define competitorGridPanel_hpp

#include "lifter.hpp"

class CompetitorGridPanel : public wxPanel
{
    wxGrid *lifterTable;

public:
    // constructor
    CompetitorGridPanel(wxWindow *parent);
    ~CompetitorGridPanel();
    
    // operate
    void resetTable();
    void appendLifter(Lifter *lifter);
    void appendLifter(Lifter *lifter, int index);
    void populateTable(vector<Lifter*> lifters);
    
    // query
    void selectCell(int row, int col);
    int getLifterID(int row);
};
    
#endif /* competitorGridPanel_hpp */
