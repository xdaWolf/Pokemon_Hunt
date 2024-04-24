#pragma once

#include "Observer.h"
#include <vector>

#ifndef SUBJECT_H_
#define SUBJECT_H_

/*
    Subject class: Subject class for the observer pattern. Defines attach, detach and notify method.
*/

class Subject
{
private:
    // VARIABLES
    std::vector<Observer *> registeredObservers;

public:
    // METHODS
    Subject();
    ~Subject();
    virtual void detach(Observer *pObserver);
    virtual void attach(Observer *pObserver);
    virtual void notify(int pHealth, int pSpeed, int pCollected);
    size_t getRegisteredObserverCount() const;
};

#endif