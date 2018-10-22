//
//  formPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 10/15/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef formPanel_hpp
#define formPanel_hpp

#include "attempt.hpp"

class FormPanel : public wxPanel
{
    wxStaticBoxSizer *formSizer;

public:
    // constructor
    FormPanel(wxWindow *parent);
    
    // setters
    void setLift(Lift lift);
    void populateForm(vector<Attempt*> attempts);
    void resetForm();
};

#endif /* formPanel_hpp */
