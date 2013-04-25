NB. enumerate.ijs -- part of the J implementation of the cribbage scorer.
NB. Used to enumerate all possible hands and store them into a file
NB. that can later be used for probabilistic calculations or what-have-you.
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



NB. ====================================================================
NB. Cribbage Enumerator Script
NB.
NB. This script exists to enumerate all possible hands in a game of
NB. cribbage. It will also have a verb to write out these enumerations
NB. so that repeat calculations are not necessary.
NB. 
NB. Because of the nature of this scripts birth (i.e. I want to find
NB. a specific-valued hand; also because extra credit project is to 
NB. use probabilistic models to determine best four cards to keep), 
NB. a hand's score will also be calculated and stored with the 
NB. enumeration.
NB. ====================================================================



NB. We need the scoring verbs to store a score with the enumerations.
require 'scorer.ijs'




