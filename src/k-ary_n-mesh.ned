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


network k_ary_n_mesh
{
    parameters:
        int k @prompt("k") = default(4);
        int n @prompt("n") = default(2);
		int nvcs =  default(1);
    submodules:

        host[k ^ n]: Host {
            parameters:
                self_address = index;
                k = k;
                n = n;
                @display("i=device/cpu;is=s");
        }

        switch[k ^ n]: Switch {
            parameters:
                self_address = index;
                k = k;
                n = n;
                nports = 2 * n + 1;
                nvcs = nvcs;
				//@display("p=,,m,;i=abstract/switch");
                @display("p=,,m,$k,,;i=abstract/switch");
        }

    connections:
        // host <--> switch connections 
        for i=0..k ^ n-1 {
            host[i].out --> host_to_switch_data_channel --> switch[i].in[2 * n];
            host[i].in <-- host_to_switch_data_channel <-- switch[i].out[2 * n];

            host[i].out_credit --> host_to_switch_data_channel --> switch[i].in_credit[2 * n];
            host[i].in_credit <--  host_to_switch_data_channel <-- switch[i].out_credit[2 * n];
        }


        for i=0..k ^ n-1, for j=0..n-1 {
            switch[i].out[j+n] --> switch_to_switch_data_channel --> switch[i + k ^ j ].in[j+n] if ((i / k ^ j ) % k != k - 1);
            switch[i].out[j] --> switch_to_switch_data_channel -->  switch[i - k ^ j ].in[j] if ((i / k ^ j ) % k != 0);

            switch[i].in_credit[j+n] <-- switch_to_switch_ctl_channel <-- switch[i + k ^ j ].out_credit[j+n] if ((i / k ^ j ) % k != k - 1);
            switch[i].in_credit[j] <-- switch_to_switch_ctl_channel <--  switch[i - k ^ j ].out_credit[j] if ((i / k ^ j ) % k != 0);
            
            // wraparound cannels
            switch[i].out[j+n] --> switch_to_switch_data_channel --> switch[i - (k-1) * k ^ j ].in[j+n] if ((i / k ^ j ) % k == k - 1);
            switch[i].out[j] --> switch_to_switch_data_channel -->  switch[i + (k-1) * k ^ j ].in[j] if ((i / k ^ j ) % k == 0);

            switch[i].in_credit[j+n] <-- switch_to_switch_ctl_channel <-- switch[i - (k-1) * k ^ j ].out_credit[j+n] if ((i / k ^ j ) % k == k - 1);
            switch[i].in_credit[j] <-- switch_to_switch_ctl_channel <--  switch[i + (k-1) * k ^ j ].out_credit[j] if ((i / k ^ j ) % k == 0);
        }
}
