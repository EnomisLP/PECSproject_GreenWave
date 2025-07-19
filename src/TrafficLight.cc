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

#include "TrafficLight.h"

Define_Module(TrafficLight);

void TrafficLight::initialize()
{
    //Fetching parameters from .ini file and indexes from parent module Intersection
    int L = par("L");
    int X = par("X");
    P = par("P");
    cModule *parent = getParentModule();
    int parentIndex = parent->getIndex();
    //Computing parameters
    double D = L/(X+1);
    double V = 8.33;
    double C = D/V;
    double Offset = ((parentIndex+1) * C)-0.1; // a shift of 0.1 is added to avoid loss time for the syncronization
    //Syncronization of the traffic lights
    cMessage *green = new cMessage("green");
    //scheduleAt(simTime().dbl() + (Offset/2) ,green); //No working system conditions
    //scheduleAt(simTime().dbl() ,green); //No working system conditions
    scheduleAt(simTime().dbl() + Offset ,green); //Working System conditions

}
//Function used to handle different types of messages
void TrafficLight::handleMessage(cMessage *msg)
{
    if(strcmp(msg->getName(),"green") == 0){
        handleGreenLight(msg);
    }

    else if(strcmp(msg->getName(),"red") == 0){
        handleRedLight(msg);
        }
    else {
        throw cRuntimeError("Unrecognized message type. Abort.");
    }
}
//Function used send a green message after receiving a red one
void TrafficLight::handleRedLight(cMessage *msg){
    EV <<"The light is Red\n";
    send(msg,"checklight");
    cMessage *green = new cMessage("green");

    scheduleAt(simTime().dbl() + P/2, green);
}
//Function used send a red message after receiving a green one
void TrafficLight::handleGreenLight(cMessage *msg){
    EV <<"The light is Green\n";
    send(msg,"checklight");
    cMessage *red = new cMessage("red");

    scheduleAt(simTime().dbl() + P/2, red);
}
