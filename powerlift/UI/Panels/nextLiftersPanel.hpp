//
//  nextLiftersPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/31/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef nextLiftersPanel_hpp
#define nextLiftersPanel_hpp

#include "lifter.hpp"

class NextLiftersPanel : public wxPanel
{
    // attributes
    wxFlexGridSizer *nextLiftersGrid;
    
public:
    // constructor
    NextLiftersPanel(wxWindow *parent);
    
    // accessors
    void resetList();
    void addLifters(vector<Lifter*> lifters, int index, Lift lift, int attempt);
};

#endif /* nextLiftersPanel_hpp */
