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

package pecsproject;
//package org.omnetpp.queueing;
//import org.omnetpp.queueing.Sink;
//
// TODO auto-generated module
//
module Intersection
{
    parameters:
        @display("bgb=206,227");
    gates:
        input in;
        output out;
       
        
        
    submodules:
        que: Queue {
            @display("p=78,66");
        }
        light: TrafficLight {
            @display("p=87,156");
        }
    connections:
        in --> que.in;
        light.checklight --> que.inc;
        que.out --> out;
        
       
        
}
