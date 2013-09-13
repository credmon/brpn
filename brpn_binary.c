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
#include "brpn_main.h"
#include "brpn_binary.h"
#include "brpn_utility.h"

struct binary_operator
{
   char name[10];
   char description[200];
   binary_operator_t func;
};

/* binary */
static precision_t add(precision_t a, precision_t b);
static precision_t subtract(precision_t a, precision_t b);
static precision_t multiply(precision_t a, precision_t b);
static precision_t divide(precision_t a, precision_t b);
static precision_t modulo(precision_t a, precision_t b);

#define NUM_BINARY_OPERATORS 5

static struct binary_operator BinaryOperators[NUM_BINARY_OPERATORS] =
{
   {
      "+",
      "Add",
      add,
   },
   {
      "-",
      "Subtract",
      subtract,
   },
   {
      "*",
      "Multiply",
      multiply,
   },
   {
      "/",
      "Divide",
      divide,
   },
   {
      "%",
      "Modulo",
      modulo,
   },
};

binary_operator_t binary_operator_match(const char* string)
{
   int i;

   for (i = 0; i < NUM_BINARY_OPERATORS; i++)
   {
      if (string_match(string, BinaryOperators[i].name))
      {
         return BinaryOperators[i].func;
      }
   }

   return NULL;
}

void binary_operator_help(void)
{
   int i;

   printf("Binary Operators: [a] [b] [operation]\n");

   for (i = 0; i < NUM_BINARY_OPERATORS; i++)
   {
      printf("%s\n", format_help_string('.',3,15, BinaryOperators[i].name, BinaryOperators[i].description));
   }
}

static precision_t add(precision_t a, precision_t b)
{
   precision_t result;
   result = b + a;
   return result;
}

static precision_t subtract(precision_t a, precision_t b)
{
   precision_t result;
   result = b - a;
   return result;
}

static precision_t multiply(precision_t a, precision_t b)
{
   precision_t result;
   result = b * a;
   return result;
}

static precision_t divide(precision_t a, precision_t b)
{
   precision_t result;
   result = b / a;
   return result;
}

static precision_t modulo(precision_t a, precision_t b)
{
   precision_t result = 0;
   /* result = a % b; */
   return result;
}

