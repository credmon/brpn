/*
    This is brpn, a rpn calculator.

    Copyright (C) 2012 Christopher Redmon.

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

*/
#ifndef BRPN_NULLARY_H
#define BRPN_NULLARY_H

typedef void (*nullary_operator_t)(void);

extern nullary_operator_t nullary_operator_match(const char* string);

extern void usage(void);
extern void version(void);
extern void quit(void);

#endif
