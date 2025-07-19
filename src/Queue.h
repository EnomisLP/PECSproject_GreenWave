//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __MYTEST_Queue_H_
#define __MYTEST_Queue_H_

#include <omnetpp.h>
#include "CarMessage_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Queue : public cSimpleModule
{
public:
    simsignal_t numberOfCarsInQueueSig;
    cQueue TheQueue;
    bool isGreen;
    bool isBusy;
    int numberCars;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void handleCarMessage(cMessage *msg);
    virtual void handleProcessMessage(cMessage *msg);
    virtual void handleGreenMessage(cMessage *msg);
    virtual void handleRedMessage(cMessage *msg);
    virtual void processNextCar();
    virtual void handleNumberOfCarsInQueue(cMessage *msg);
};

#endif
