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

//
// TODO generated message class
//
message CarMessage {
    int ID = 0;
    double V = 0.0;
    double C  = 0;
    double arrivalTime = 0; //To register the time a car arrive in a queue
    double departureTime = 0; // To register the time a car depart from a queue
    double waitingTime = 0;
    bool isStopped = true;
    double arrivalRoadTime = 0;// To register the time a car arrives in the road
}
