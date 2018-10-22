//
//  PowerliftApp.cpp
//  powerlift
//
//  Created by Matheus Lehmann on 8/6/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#include "powerliftApp.hpp"
#include "powerliftFrame.hpp"

bool PowerliftApp::OnInit()
{
    PowerliftFrame *powerliftFrame = new PowerliftFrame(wxT("Powerlift Competition Manager"), wxPoint(50, 50), wxSize(1060, 640));
    powerliftFrame->Show(true);
    return true;
}
