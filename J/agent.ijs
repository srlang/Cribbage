NB. agent.ijs -- part of the J implementation of the cribbage scorer.
NB. Agent to determine which cards to keep or throw given a cribbage hand.
NB. Copyright (C) 2012      Sean R. Lang
NB.
NB. This program is free software: you can redistribute it and/or modify
NB. if under the terms of the GNU General Public License as published by
NB. the Free Software Foundation, either version 3 of the License, or 
NB. (at your option) any later version.
NB.
NB. This program is distributed in the hope that it will be useful,
NB. but WITHOUT ANY WARRANTY; without even the implied warranty of 
NB. MERCHANTIBILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
NB. GNU General Public License for more details.
NB.
NB. You should have received a copy of the GNU General Public License
NB. along with this program. If not, see <http://www.gnu.org/licenses/>.



NB. NOTE: This program doesn't need to do an enumeration of every hand
NB. at the beginning. A smart way of doing this would be to make the 
NB. enumeration happen for each hand given and if it's not in the larger
NB. table, then it's safe to add.
