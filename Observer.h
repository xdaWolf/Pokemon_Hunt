#pragma once

#include <string>

#ifndef OBSERVER_H_
#define OBSERVER_H_

/*
    Observer class: Observer class for the observer pattern. Defines refresh method.
*/

class Observer
{
private:
public:
    virtual void refresh(int pHealth, int pSpeed, int pCollected); // parameters used for player
};

#endif