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

#include "Sender.h"
#include "CarMessage_m.h"
#include "TrafficLight.h"

Define_Module(Sender);

void Sender::initialize()
{
    //Recalling parameters from .ini file
    L = par("L");
    X = par("X");
    P  = par("P");
    //Parameters initialization
    isFull = false;
    V_greenWave = 8.33;
    counter = 0;
    //Computing other parameters
    D = L/(X+1);
    C_greenWave = D/V_greenWave;
    //Signals initialization
    ArrivalTimeSig = registerSignal("ArrivalTime");
    //Self message to start sending cars after all trafficLights are
    //Initialized and the first one become green
    cMessage *event_ = new cMessage("event");
    scheduleAt(simTime().dbl() + ((P/2)*(X+1)), event_);
}
//Function that handles different types of messages
void Sender::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(), "event") == 0){
        handleEventMessage(msg);


    }
    else if(strcmp(msg->getName(), "Stop") == 0){
        handleStopMessage(msg);
        delete msg;

    }
    else if (strcmp(msg->getName(), "Go") == 0){
        handleGoMessage(msg);
        delete msg;
    }
    else {
        throw cRuntimeError("Unrecognized message type. Abort.");
    }
}
//Function to handle "event" messages:
//used to send cars every T seconds according to the value of boolean "isFull"
void Sender::handleEventMessage(cMessage *msg){
    if(isFull){
        delete msg;
        cMessage *event_ = new cMessage("event");
        double T = exponential(86.5617,1); //To have a mean of 60
        //double T = exponential(43.28085,1); //To have a mean of 30
        scheduleAt(simTime().dbl() + T, event_);
    }
    else {
        CarMessage * car = CreateCar();
        send(car,"out");
        EV <<"Sending car with ID: "<< car->getID()<<" with speed: " << car->getV()<<
            " from the sender\n";
        counter++;
        cMessage *event_ = new cMessage("event");
        double T = exponential(86.5617,1);
        //double T = exponential(43.28085,1);
        scheduleAt(simTime().dbl() + T, event_);
        emit(ArrivalTimeSig,T);
    }
}
//Function used to create cars with specific parameters
CarMessage* Sender::CreateCar(){
    double V = uniform(4,12,0);
    double C = D/V;
    CarMessage *car = new CarMessage("car");
    car->setID(counter);
    car->setV(V_greenWave);
    car->setC(C_greenWave);
    car->setDepartureTime(simTime().dbl());
    car ->setArrivalRoadTime(simTime().dbl());
    return car;
}
//Function used to handle "Stop" message from the first intersection
void Sender:: handleStopMessage(cMessage * msg){

    isFull = true;
}
//Function used to handle "Go" message from the first intersection
void Sender::handleGoMessage(cMessage *msg){

    isFull = false;
}

