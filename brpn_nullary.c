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
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "brpn_nullary.h"
#include "brpn_utility.h"

struct nullary_operator
{
   char name[10];
   nullary_operator_t func;
};

#define NUM_NULLARY_OPERATORS 3

static struct nullary_operator NullaryOperators[NUM_NULLARY_OPERATORS] =
{
   {
      "help",
      usage,
   },
   {
      "version",
      version,
   },
   {
      "quit",
      quit,
   },
};

nullary_operator_t nullary_operator_match(const char* string)
{
   int i;

   for (i = 0; i < NUM_NULLARY_OPERATORS; i++)
   {
      if (string_match(string, NullaryOperators[i].name))
      {
         return NullaryOperators[i].func;
      }
   }

   return NULL;
}

void usage(void)
{
   printf("Usage: brpn [flags]\n");
   printf("\n");
   printf("Flags:\n");
   printf("   -h --help .................... Print help\n");
   printf("   -v --version ................. Print version\n");
}

void version(void)
{
   printf("Version: brpn-0.0\n");
}

void quit(void)
{
   exit(0);
}

