Minimalist terminal calendar and ics/ical viewer (chronical)
============================================================

DESCRIPTION
-----------

`chronical` uses the ncurses C library to draw a very simplistic, very minimal calendar, coupled to a notepad for each day.


INSTALLATION:
-------------

    $ make

That's it- creates `chronical` in the same directory.

Invoke with

    $ chronical [OPTION] [DATE]

With no option, chronical will open the graphical calendar view.  


USAGE
-----

Tab - Switch between calendar and notepad windows.

q - Quit.

h - Help.  A menu will pop up with available commands

### Calendar window

Left and Right - Navigate between days.

Up and Down - Navigate between weeks.

Shift Left and Right - Navigate between months.

Shift Up and Down - Navigate between years.

FEATURES
--------

- Guarantees correct days of the week for the dates between years 2000 and 2099 inclusive.  
- Speedy navigation and simple, sleek design.  


CONTRIBUTING
------------

1. Fork this repo, make some changes and submit a pull request.
2. Open a new issue of some improvements you would like to see happen (<https://github.com/Gnumech/zcal/issues/new>).


COPYLEFT
--------

Copyleft (C) 2017 Shaun Marshall

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
