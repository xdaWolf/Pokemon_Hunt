#include "Subject.h"

#include <algorithm>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <chrono>
#include <windows.h> //include all necessary external files

Subject::Subject() // constructor
{
    std::cout << "Subject constructor" << std::endl;
}

Subject::~Subject() // destructor
{
}

void Subject::attach(Observer *pObserver)
{
    registeredObservers.push_back(pObserver); // add observer to list of registered observers
}

void Subject::detach(Observer *pObserver)
{
    registeredObservers.erase(std::remove_if(registeredObservers.begin(), registeredObservers.end(), [pObserver](Observer *obs)
                                             { return obs == pObserver; }),
                              registeredObservers.end()); // remove observer from list of registered observers
}

void Subject::notify(int pHealth, int pSpeed, int pCollected)
{
    for (auto observer : registeredObservers)
    {
        observer->refresh(pHealth, pSpeed, pCollected); // notify all registered observers
    }
}

size_t Subject::getRegisteredObserverCount() const
{
    return registeredObservers.size(); // return number of registered observers
}