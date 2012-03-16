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

enum ControlTypes
{
    CTL_NONE = 0;
	CTL_REQ_VC = 1;
	CTL_RELEASE_VC = 2;
	CTL_REQ_SW = 3;
	CTL_GRANT = 4;
	CTL_BUFFER_CREDIT = 5;
};

packet Control
{
    int VcId;
    int Port;
	int Credits;        
    // debug and verification
};

