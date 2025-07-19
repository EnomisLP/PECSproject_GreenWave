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

#include "first_queue.h"
#include "CarMessage_m.h"

Define_Module(First_queue);

void First_queue::initialize()
{
    //Fetching parameters from .ini file
    L = par("L");
    X = par("X");
    //Initializing parameters
    T_mean = 60;
    numberCars = 0;
    isGreen = false;
    isBusy = false;
    //Computing parameters
    int D = L/(X+1);
    double V_greenWave = 8.33;
    double C_greenWave = D/V_greenWave;
    maxNumberofCars = (D/4.5)*0.75; //assuming mean lenght of a car of 4.5 meters
    //maxNumberofCars = 100000000; // to use when adopting no stabilized simulator
    minNumberofCars = T_mean/C_greenWave;
    //Signals
    numberOfCarsInFirstQueueSig = registerSignal("numberOfCarsInFirstQueue");

}
//Function used to handle different types of messages
void First_queue::handleMessage(cMessage *msg)
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

//Function used to process cars
void First_queue::processNextCar()
{
    if (!TheQueue.isEmpty()) { //if the queue has car in
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
        //After processing a car, if the there are few cars in queue, sender can start sending cars
        if (TheQueue.getLength()<= minNumberofCars){
            cMessage *Go_ = new cMessage("Go");
            send(Go_,"outsen");
        }
        // Schedule the next processing step after C seconds if there are more cars
        cMessage *process_ = new cMessage("process");
        scheduleAt(simTime() + C, process_);
    }
    else{//if the queue is empty server goes in idle mode
        isBusy = false;
    }
}
//Function used to handle cars arriving in queue
void First_queue::handleCarMessage(cMessage *msg){
//if there are too much cars in queue, sending a message to the sender to stop sending them
    if (TheQueue.getLength()>= maxNumberofCars){
        cMessage *Stop_ = new cMessage("Stop");
        send(Stop_,"outsen");
        EV <<"Car in queue: " <<TheQueue.getLength() << "\n";
        delete msg;
    }
    //while if there are few cars in queue, sending a message to the sender to start sending them again
    else if(TheQueue.getLength()<= minNumberofCars){
        cMessage *Go_ = new cMessage("Go");
        send(Go_,"outsen");
        EV <<"Car in queue: " <<TheQueue.getLength() << "\n";
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
    //Case in which there are cars between min and max
    else{
        EV <<"Car in queue: " <<TheQueue.getLength() << "\n";
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

}
//function used to handle self process message
void First_queue::handleProcessMessage(cMessage *msg){
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
void First_queue::handleGreenMessage(cMessage *msg){
    //when the green message arrives isGreen become true
  isGreen = true;
  EV << "Light turned green\n";
  cMessage *checkqueue_ = new cMessage("checkqueue");
   scheduleAt(simTime(), checkqueue_);

  // Start processing cars if the queue is not empty and the server is not processing cars
  if (!TheQueue.isEmpty() && !isBusy) {
      processNextCar();
  }
}
//Function used to stop the process service
void First_queue::handleRedMessage(cMessage *msg){
  isGreen = false;
  EV << "Light turned red\n";

}
//Function used to register the number of cars in queue
void First_queue::handleNumberOfCarsInQueue(cMessage *msg){
    emit(numberOfCarsInFirstQueueSig,TheQueue.getLength());
}


