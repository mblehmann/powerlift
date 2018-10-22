//
//  category.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/20/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef category_hpp
#define category_hpp

#include "definition.h"

using namespace std;

class Category
{
    // attributes
    int index;
    wxString gender;
    double minWeight;
    double maxWeight;
    wxString description;
    
public:
    // constructors
    Category();
    Category(int index, wxString gender, double minWeight, double maxWeight);

    // setters
    void setIndex(int index);
    void setGender(wxString gender);
    void setMinWeight(double minWeight);
    void setMaxWeight(double maxWeight);
    void setDescription(wxString description);
    
    // getters
    int getIndex();
    wxString getGender();
    double getMinWeight();
    double getMaxWeight();
    wxString getDescription();

    // checkers
    void buildDescription();
    bool isOnTheCategoy(wxString gender, double weight);
    
    // serialization
    wxString serialize();
    void deserialize(wxString data);
};

#endif /* category_hpp */
