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

#ifndef __MYTEST_Receiver_H_
#define __MYTEST_Receiver_H_

#include <omnetpp.h>
#include "CarMessage_m.h"

using namespace omnetpp;

/**
 * TODO - Generated class
 */
class Receiver : public cSimpleModule
{
private:
    simsignal_t waitingTimeSig;
    simsignal_t noStopCarSig;
    simsignal_t ResponseTimeSig;
    simsignal_t numberOfCarsSig;
    double waitingTime = 0.0;
    int noStopCar;
    double ResponseTime = 0.0;
    int numberOfCars = 0;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void printMessage(cMessage *msg);
    virtual void SignalWaitingTimeProcess(cMessage * msg);
    virtual void SignalResponseTimeProcess(cMessage * msg);
    virtual void SignalnoStopCarProcess(cMessage * msg);
    virtual void SignalnumberOfCarsProcess();

};

#endif
