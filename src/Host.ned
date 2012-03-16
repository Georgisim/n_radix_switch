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



simple Host
{
    parameters:
		int self_address;
		int n;
		int k;
		        
        string TrafficPattern = default("Uniform");
        volatile int PacketRate = default(exponential(100));
        volatile int PacketSize = default(16);
        int FlitSize = default(16);
        int CreditSize = default(4);
		volatile double sendIaTime @unit(s) = default(100ns);
		int PacketsToSend;
		
        //@display("p=,,m,$dim;i=device/cpu,black;b=40,40,rect,white,black,1");

    gates:
    //    inout stat_ctl;
        input in;
        output out;
        
        output out_credit;
        input in_credit;
        
}
