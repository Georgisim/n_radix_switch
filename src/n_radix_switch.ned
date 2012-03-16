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


network n_radix_switch
{
    parameters:
        int n @prompt("n") = default(2);
		int nvcs =  default(1);
    submodules:

        host[n]: Host {
            parameters:
                self_address = index;
                k = n;
                n = 1;
                @display("i=device/cpu;is=s");
        }

        switch[1]: Switch {
            parameters:
                self_address = 0;
                k = n;
                n = 1;
                nports = n;
                nvcs = nvcs;
                @display("p=,,m,$k,,;i=abstract/switch");
        }

    connections:
        // host <--> switch connections 
        for i=0..n-1 {
            host[i].out --> host_to_switch_data_channel --> switch[0].in[i];
            host[i].in <-- host_to_switch_data_channel <-- switch[0].out[i];

            host[i].out_credit --> host_to_switch_data_channel --> switch[0].in_credit[i];
            host[i].in_credit <--  host_to_switch_data_channel <-- switch[0].out_credit[i];
        }
}
