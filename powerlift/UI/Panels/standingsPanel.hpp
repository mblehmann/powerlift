//
//  standingsPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/10/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef standingsPanel_hpp
#define standingsPanel_hpp

#include "lifter.hpp"

class StandingsPanel : public wxPanel
{
    wxFlexGridSizer *lifterRanking;
    
public:
    StandingsPanel(wxWindow *parent);
    
    void resetRanking();
    void populateRanking(vector<Lifter*> lifters);
};

#endif /* standingsPanel_hpp */
