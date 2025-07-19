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

#include "Queue.h"
#include "CarMessage_m.h"
Define_Module(Queue);

void Queue::initialize()
{
    //Fetching parent indexes and setting parameters
    cModule *parent = getParentModule();
    int parentIndex = parent->getIndex();
    isGreen = false;
    isBusy = false;
    numberCars = 0;
    // Construct a unique signal name for each intersection
    numberOfCarsInQueueSig = registerSignal(("numberOfCarsInQueue" + std::to_string(parentIndex)).c_str());

}
//Function used to handle different types of messages
void Queue::handleMessage(cMessage *msg)
{


    if (strcmp(msg->getName(), "car") == 0) {
        handleCarMessage(msg);
    }


    else if (strcmp(msg->getName(), "process") == 0) {
        handleProcessMessage(msg);
    }


    else if (strcmp(msg->getName(), "green") == 0) {
        handleGreenMessage(msg);
        delete msg;
    }


    else if (strcmp(msg->getName(), "red") == 0) {
     handleRedMessage(msg);
     delete msg;
    }
    else if(strcmp(msg->getName(), "checkqueue") == 0){
        handleNumberOfCarsInQueue(msg);
        delete msg;
    }
    else{
        throw cRuntimeError("Unrecognized message type. Abort.");
    }
}

//Function used to process the cars
void Queue::processNextCar()
{
    if (!TheQueue.isEmpty()) { //if the queue has car in queue
        isBusy = true;//server goes busy mode
        CarMessage *car = check_and_cast<CarMessage *>(TheQueue.pop());
        //popping a car from the queue
        car ->setDepartureTime(simTime().dbl());
        double a = car -> getArrivalTime();
        double d = car -> getDepartureTime();
        double del = car -> getWaitingTime();
        car ->setWaitingTime(del+(d - a));
        //setting cars parameters
        if(car->getWaitingTime()== 0){
            car->setIsStopped(false);
        }
        else{
            car->setIsStopped(true);
        }
        //setting isStopped parameter with the waitingTime in queue
        EV << "Sending Car " << car-> getID() << " to cross at " << car -> getDepartureTime() <<
                " seconds after passing "<< car -> getWaitingTime()<< " seconds in queue. Details:\n"
                        "Speed: "<<car -> getV() << "\n Is Stopped: "<<car -> isStopped() << "\n";
        double C = car->getC();
        sendDelayed(car,C, "out");
        // Schedule the next processing step after C seconds if there are more cars
        cMessage *process_ = new cMessage("process");
        scheduleAt(simTime() + C, process_);
    }
    else{//if the queue is empty server goes in idle mode
        isBusy = false;
    }
}
//Function used to handle cars arriving in the queue
void Queue::handleCarMessage(cMessage *msg){
    check_and_cast<CarMessage *>(msg) -> setArrivalTime(simTime().dbl());
    numberCars++;
    EV << "Car "<< check_and_cast<CarMessage *>(msg) -> getID()<<" has arrived at "
            <<check_and_cast<CarMessage *>(msg) -> getArrivalTime()<<
            " and is added to the queue\n";
    TheQueue.insert(msg);
    //once a car arrive, setting the arrival time to the simulation time and inserting it in the queue
    if (isGreen && !isBusy) {
        EV << "Light is green, sending car immediately\n";
        processNextCar();
        // If the light is green and no car is currently being processed, process the car immediately
    }
}
//Function used to handle self message for processing
void Queue::handleProcessMessage(cMessage *msg){
    //when a process message arrives
    if (isGreen && !TheQueue.isEmpty()) {//if the light is green and there are cars in the queue
       processNextCar();
    }
    else {
        //if the light is red or there aren't cars in queue
        EV << "Cannot process: either the queue is empty or the light is red\n";
        isBusy = false; //servers goes idle and delete the process message
        delete msg;
    }

}
//Function used to start the process service
void Queue::handleGreenMessage(cMessage *msg){
    //when the green message arrives isGreen become true
  isGreen = true;
  EV << "Light turned green\n";
  //Sending a self message to check how many cars are in queue
  cMessage *checkqueue_ = new cMessage("checkqueue");
  scheduleAt(simTime(), checkqueue_);
  // Start processing cars if the queue is not empty and the server is not processing cars
  if (!TheQueue.isEmpty() && !isBusy) {
      processNextCar();

  }
}
//Function used to stop process service
void Queue::handleRedMessage(cMessage *msg){
  isGreen = false;
  EV << "Light turned red\n";

}
//Function used to register number of cars in Queue
void Queue::handleNumberOfCarsInQueue(cMessage *msg){
    emit(numberOfCarsInQueueSig,TheQueue.getLength());
}
