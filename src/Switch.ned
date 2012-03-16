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

simple inCtl
{
    parameters:
        int nports;
        int nvcs;
        int CreditSize = default(4);
    gates:
        // control  
        output out_credit;
        input buffer;
}

simple outCtl
{
    parameters:
        int nports;
        int nvcs;
		double SwitchClock @unit(s) = default(16ns);    
    gates:
        // control
        input in_credit[nports];

        input from_buffer[nports];
        output buffer[nports];

}

simple inRegister
{
    parameters:
        @display("i=block/routing,black");
        int n;
        int k;
        int self_address;
        string RoutingAlgorithm = default("DOR");

        int nvcs;
    gates:
        input in;
        output out;

        // control
}



simple Buffer
{
    parameters:
        @display("i=block/queue,black;t=0 flits");
        int BufferLength = default(16);
        int RTtreshold = default(1);
        double SwitchClock @unit(s) = default(16ns); 
        int nvcs;
    gates:
        input in;
        output out;

        // control
        output in_ctl;

        output out_ctl;
        input form_out_ctl;
}

simple Mux
{
    parameters:
        int nports;
    gates:
        input in;
        output out[nports];

        // control
}

simple outPort
{
    parameters:
        int nports;
        int port_index;

    gates:
        input in[nports];
        output out @loose;

}


//
// TODO auto-generated module
//
module Switch
{
    parameters:
        int nports;
        int nvcs;

        int self_address;
        int n;
        int k;

        //@display("p=,,m,$dim;i=abstract/router2;bgb=437,264;bgl=2");

        @display("bgb=600,839;bgl=2");
    gates:
        // data lanes
        input in[nports] @loose;
        output out[nports] @loose;

        // control lanes
        input in_credit[nports] @loose;
        output out_credit[nports] @loose;


    submodules:
        reg[nports]: inRegister {
            n = n;
            k = k;
            nvcs = nvcs;
            self_address = self_address;
            @display("p=45,40,c,150;i=block/departure");
        }
        buffer[nports]: Buffer {
            nvcs = nvcs;
            @display("p=248,40,c,150;b=100,40");
        }
        mux[nports]: Mux {
            nports = nports;
            @display("p=373,40,c,150;i=abstract/dispatcher");
        }
        port[nports]: outPort {
            nports = nports;
            port_index = index;
            @display("p=525,40,c,150;i=block/join");
        }
        out_ctl: outCtl {
            nports = nports;
            nvcs = nvcs;

            @display("p=525,792;i=block/dispatch");
        }
        in_ctl[nports]: inCtl {
            nports = nports;
            nvcs = nvcs;
            @display("p=129,94,c,150;i=block/dispatch");
        }
    connections:
        for i=0..nports-1 {
            in[i] --> { @display("m=w"); } --> reg[i].in;
            reg[i].out --> buffer[i].in;
            buffer[i].out --> mux[i].in;
            port[i].out --> { @display("m=e"); } --> out[i];

            out_ctl.buffer[i] --> { @display("ls=#0080FF"); } --> buffer[i].form_out_ctl;
            out_ctl.from_buffer[i] <-- { @display("ls=#0080FF"); } <-- buffer[i].out_ctl;
            in_ctl[i].buffer <-- { @display("ls=#0080FF"); } <-- buffer[i].in_ctl;

            out_credit[i] <-- { @display("m=w;ls=#0080FF"); } <-- in_ctl[i].out_credit;
            in_credit[i] --> { @display("m=e;ls=#0080FF"); } --> out_ctl.in_credit[i];
        }

        for i=0..nports-1, for j=0..nports-1 {
            mux[i].out[j] --> port[j].in[i];
        }

}

