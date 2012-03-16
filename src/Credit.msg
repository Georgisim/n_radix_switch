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

enum CreditTypes
{
   CR_ON = 1;
   CR_OFF = 2;
   CR_CREDIT = 3;
   CR_ACK = 3;   
   CR_NACK = 3;
};

packet Credit
{
    int VcId;
	int Credits;        
    // debug and verification
};

