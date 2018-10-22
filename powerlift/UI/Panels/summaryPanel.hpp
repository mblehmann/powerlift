//
//  summaryPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/31/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef summaryPanel_hpp
#define summaryPanel_hpp

#include "event.hpp"

class SummaryPanel : public wxPanel
{
    vector<wxStaticText*> *liftInput;
    vector<wxStaticText*> *liftBest;
    vector<wxStaticText*> *liftWilks;
    
public:
    SummaryPanel(wxWindow *parent);
    void populateAttempts(Event *event, vector<double> wilks);
};

#endif /* summaryPanel_hpp */
