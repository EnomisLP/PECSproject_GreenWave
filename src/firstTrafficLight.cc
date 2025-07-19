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

#include "firstTrafficLight.h"

Define_Module(FirstTrafficLight);
//Same as the TrafficLight module but it is initialized as the first one
void FirstTrafficLight::initialize(){
    P = par("P");
    cMessage *green = new cMessage("green");
    scheduleAt(simTime().dbl(),green);
}

void FirstTrafficLight::handleMessage(cMessage *msg)
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
void FirstTrafficLight::handleRedLight(cMessage *msg){
    EV <<"The light is Red\n";
    send(msg,"checklight");
    cMessage *green = new cMessage("green");

    scheduleAt(simTime().dbl() + P/2, green);
}
void FirstTrafficLight::handleGreenLight(cMessage *msg){
    EV <<"The light is Green\n";
    send(msg,"checklight");
    cMessage *red = new cMessage("red");
    scheduleAt(simTime().dbl() + P/2, red);
}
