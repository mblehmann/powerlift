//
//  category.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/20/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "category.hpp"

// constructors
Category::Category()
{
    setIndex(-1);
    setGender("");
    setMinWeight(-1);
    setMaxWeight(-1);
    setDescription("");
}

Category::Category(int index, wxString gender, double minWeight, double maxWeight)
{
    setIndex(index);
    setGender(gender);
    setMinWeight(minWeight);
    setMaxWeight(maxWeight);
    buildDescription();
}

// setters
void Category::setIndex(int index)
{
    this->index = index;
}

void Category::setGender(wxString gender)
{
    this->gender = gender;
}

void Category::setMinWeight(double minWeight)
{
    this->minWeight = minWeight;
}

void Category::setMaxWeight(double maxWeight)
{
    this->maxWeight = maxWeight;
}

void Category::setDescription(wxString description)
{
    this->description = description;
}

// getters
int Category::getIndex()
{
    return index;
}

wxString Category::getGender()
{
    return gender;
}

double Category::getMinWeight()
{
    return minWeight;
}

double Category::getMaxWeight()
{
    return maxWeight;
}

wxString Category::getDescription()
{
    return description;
}

// checkers
void Category::buildDescription()
{
    if (maxWeight == DBL_MAX)
    {
        description = wxString::Format("%s %i+", gender, (int) minWeight);
    }
    else
    {
        description = wxString::Format("%s %i", gender, (int) maxWeight);
    }
}

bool Category::isOnTheCategoy(wxString gender, double weight)
{
    return this->gender.Cmp(gender) == 0 && weight >= minWeight && weight <= maxWeight;
}

// serialization
wxString Category::serialize()
{
    wxString data;
    
    wxString category = getDescription();
    category.Replace(wxT(" "), wxT("_"));
    
    data = wxString::Format(wxT("%i%c%s%c%f%c%f%c%s"), index, CATEGORY_DELIMITER, gender, CATEGORY_DELIMITER, minWeight, CATEGORY_DELIMITER, maxWeight, CATEGORY_DELIMITER, category);
    
    return data;
}

void Category::deserialize(wxString data)
{
    wxArrayString tokens = wxStringTokenize(data, CATEGORY_DELIMITER);
    int index = 0;
    
    int categoryIndex;
    wxString gender;
    double minWeight;
    double maxWeight;
    wxString category;

    categoryIndex = wxAtoi(tokens[index]);
    index++;
    
    gender = tokens[index];
    index++;
    
    minWeight = wxAtof(tokens[index]);
    index++;
    
    maxWeight = wxAtof(tokens[index]);
    index++;
    
    category = tokens[index];
    category.Replace(wxT("_"), wxT(" "));

    setIndex(categoryIndex);
    setGender(gender);
    setMinWeight(minWeight);
    setMaxWeight(maxWeight);
    setDescription(category);
}
