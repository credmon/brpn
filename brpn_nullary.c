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
#include "brpn_binary.h"
#include "brpn_nullary.h"
#include "brpn_unary.h"
#include "brpn_utility.h"

struct nullary_operator
{
   char name[10];
   char description[200];
   nullary_operator_t func;
};

static void help(void);

#define NUM_NULLARY_OPERATORS 3

static struct nullary_operator NullaryOperators[NUM_NULLARY_OPERATORS] =
{
   {
      "help",
      "Print help dialog.",
      help,
   },
   {
      "version",
      "Print program version.",
      version,
   },
   {
      "quit",
      "Exit program.",
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

void nullary_operator_help(void)
{
   int i;

   printf("Nullary Operators: [operation]\n");

   for (i = 0; i < NUM_NULLARY_OPERATORS; i++)
   {
      printf("%s\n", format_help_string('.',3,15, NullaryOperators[i].name, NullaryOperators[i].description));
   }
}

static void help(void)
{
   printf("\n");
   nullary_operator_help();
   printf("\n");
   binary_operator_help();
   printf("\n");
   unary_operator_help();
   printf("\n");
}


void version(void)
{
   printf("Version: brpn-0.0\n");
}

void quit(void)
{
   exit(0);
}

