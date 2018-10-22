//
//  timerPanel.hpp
//  powerlift
//
//  Created by Matheus Lehmann on 9/17/18.
//  Copyright © 2018 Matheus Lehmann. All rights reserved.
//

#ifndef timerPanel_hpp
#define timerPanel_hpp

#include "definition.h"

class TimerPanel : public wxPanel
{
    // attributes
    wxSound *timeoutSound;
    wxStaticText *timerText;
    wxTimer *timer;
    int currentTime;

    // setters
    void setTimer(int time);
    void startTimer();

public:
    // constructor
    TimerPanel(wxWindow *parent);

    // accessors
    void startTimer(int time);
    void tickTimer();
    void stopTimer();
};

#endif /* timerPanel_hpp */
