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

package pecsproject.simulations;
import pecsproject.Intersection;
import pecsproject.Sender;
import pecsproject.TrafficLight;
import pecsproject.Queue;
import pecsproject.Receiver;
import pecsproject.First_queue;
import pecsproject.First_intersection;
network Road
{
    parameters:
        @display("bgb=331.2,324.48");
        int X = default(5);
        int L = default(1);
        @statistic[numberOfCarsStat](source="numberOfCars"; record=count; );
        @statistic[waitingTimeStat](source="waitingTime"; record=vector,max,min; );
        @statistic[noStopCarStat](source="noStopCar"; record= count; );
        @statistic[ResponseTimeStat](source="ResponseTime"; record=vector,max,min; );
        @statistic[numberOfCarsInQueueStat0](source="numberOfCarsInQueue0"; record=vector,count);
        @statistic[numberOfCarsInQueueStat1](source="numberOfCarsInQueue1"; record=vector,count);
        @statistic[numberOfCarsInQueueStat2](source="numberOfCarsInQueue2"; record=vector,count);
        @statistic[numberOfCarsInQueueStat3](source="numberOfCarsInQueue3"; record=vector,count);
        @statistic[numberOfCarsInQueueStat4](source="numberOfCarsInQueue4"; record=vector,count);
       	@statistic[ServiceRateStat](source="ServiceRate"; record=vector);
       	@statistic[ArrivalRateStat](source="ArrivalRate"; record=vector);
       	@statistic[UtilizzationStat](source="Utilizzation"; record=vector);
        @statistic[numberOfCarsInFirstQueueStat](source="numberOfCarsInFirstQueue";record=vector);
        @statistic[ArrivalTimeStat](source="ArrivalTime";record=vector);
    submodules:
        intef: First_intersection {
            @display("p=104,196");
        }
        inte[X]: Intersection {
            @display("p=143,135");
        }
        sen: Sender {
            @display("p=71.04,263.04");
        }
        rec: Receiver {
            @display("p=191.04001,31.68");
        }

    connections:
        sen.out --> intef.in;
        intef.outsen --> sen.inque;
        intef.out --> inte[0].in;
        for i=0..X-2,if X>1 {
            inte[i].out --> inte[i+1].in;

        }
        inte[X-1].out --> rec.in;
}

