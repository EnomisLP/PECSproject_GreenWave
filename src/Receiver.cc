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

#include "Receiver.h"
#include "CarMessage_m.h"

Define_Module(Receiver);

void Receiver::initialize(){
    //Initialization of parameters
    waitingTime = 0.0;
    noStopCar = 0;
    ResponseTime = 0.0;
    numberOfCars = 0;
    //Signals
    numberOfCarsSig = registerSignal("numberOfCars");
    waitingTimeSig = registerSignal("waitingTime");
    ResponseTimeSig = registerSignal("ResponseTime");
    noStopCarSig = registerSignal("noStopCar");

}//Function used to handle different types of messages
void Receiver::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(),"car") == 0){
    printMessage(msg);
    SignalnumberOfCarsProcess();
    SignalWaitingTimeProcess(msg);
    SignalResponseTimeProcess(msg);
    SignalnoStopCarProcess(msg);

    }
    else {
        throw cRuntimeError("Unrecognized message type. Abort.");
    }
    delete msg;

}
//Function used to print car informations
void Receiver:: printMessage(cMessage *msg){
    EV <<"The car ID: "<<check_and_cast<CarMessage *>(msg) -> getID()<<
    " is deleted at " << simTime() << "seconds. The car passed "
    << check_and_cast<CarMessage *>(msg) -> getWaitingTime()<<
    " seconds in queue. Details \n isStopped: "
    <<check_and_cast<CarMessage *>(msg) -> isStopped()<<"\n";
}
//Function used to register Waiting times of cars
 void Receiver:: SignalWaitingTimeProcess(cMessage * msg){
     waitingTime = check_and_cast<CarMessage *>(msg)->getWaitingTime();
     EV << "Total time in queue: " << waitingTime << "\n";

     if (waitingTimeSig == -1) {
         throw cRuntimeError("Signal 'waitingTime' is not registered correctly!");
     }
     else{
         emit(waitingTimeSig, waitingTime);
     }
 }
 //Function used to register Response times of the system
 void Receiver::SignalResponseTimeProcess(cMessage * msg){
     ResponseTime = (simTime().dbl() - check_and_cast<CarMessage * >(msg) -> getArrivalRoadTime());
     EV <<"Time to cross the road: "<<ResponseTime<< "\n";
     if (ResponseTime == -1) {
          throw cRuntimeError("Signal 'ResponseTime' is not registered correctly!");
      }
     else{
         emit(ResponseTimeSig,ResponseTime);
     }
 }
//Function used to register the number of cars in green wave
 void Receiver:: SignalnoStopCarProcess(cMessage * msg){
     if(check_and_cast<CarMessage *>(msg) -> isStopped()== 0){
     noStopCar++;
     emit(noStopCarSig,noStopCar);
     }
 }
//Function used to register the number of cars in the system
 void Receiver :: SignalnumberOfCarsProcess(){
     numberOfCars++;
     emit(numberOfCarsSig,numberOfCars);
 }



