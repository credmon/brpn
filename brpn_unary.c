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
#include "brpn_unary.h"
#include "brpn_utility.h"

struct unary_operator
{
   char name[10];
   char description[200];
   unary_operator_t func;
};

unary_operator_t unary_operator_match(const char* string);

/* unary */
static precision_t sin_local(precision_t a);
static precision_t cos_local(precision_t a);
static precision_t tan_local(precision_t a);
static precision_t asin_local(precision_t a);
static precision_t acos_local(precision_t a);
static precision_t atan_local(precision_t a);
static precision_t deg_local(precision_t a);
static precision_t rad_local(precision_t a);
static precision_t sin_frac(precision_t a, int iteration);
static precision_t degFtoC(precision_t a);
static precision_t degCtoF(precision_t a);

#define NUM_UNARY_OPERATORS 10

static struct unary_operator UnaryOperators[NUM_UNARY_OPERATORS] =
{
   {
      "sin",
      "Sine",
      sin_local,
   },
   {
      "cos",
      "Cosine",
      cos_local,
   },
   {
      "tan",
      "Tangent",
      tan_local,
   },
   {
      "asin",
      "Arcsine",
      asin_local,
   },
   {
      "acos",
      "Arccosine",
      acos_local,
   },
   {
      "atan",
      "Arctangent",
      atan_local,
   },
   {
      "deg",
      "Degrees",
      deg_local,
   },
   {
      "rad",
      "Radians",
      rad_local,
   },
   {
      "fc",
      "Fahrenheit to Celsius",
      degFtoC,
   },
   {
      "cf",
      "Celsius to Fahrenheit",
      degCtoF,
   }
};

unary_operator_t unary_operator_match(const char* string)
{
   int i;

   for (i = 0; i < NUM_UNARY_OPERATORS; i++)
   {
      if (string_match(string, UnaryOperators[i].name))
      {
         return UnaryOperators[i].func;
      }
   }

   return NULL;
}

void unary_operator_help(void)
{
   int i;

   printf("Unary Operators: [a] [operation]\n");

   for (i = 0; i < NUM_UNARY_OPERATORS; i++)
   {
      printf("%s\n", format_help_string('.',3,15, UnaryOperators[i].name, UnaryOperators[i].description));
   }
}

static precision_t sin_local(precision_t a)
{
   precision_t result = 0;

   result = (a/(1+((a*a)/sin_frac(a,2))));

   return result;
}

static precision_t cos_local(precision_t a)
{
   precision_t result = 0;

   result = sin_local(1.57-a);

   return result;
}

static precision_t tan_local(precision_t a)
{
   precision_t result = 0;
   result = sin_local(a)/cos_local(a);
   return result;
}

static precision_t asin_local(precision_t a)
{
   precision_t result = 0;
   return result;
}

static precision_t acos_local(precision_t a)
{
   precision_t result = 0;
   return result;
}

static precision_t atan_local(precision_t a)
{
   precision_t result = 0;
   return result;
}

static precision_t deg_local(precision_t a)
{
   precision_t result = (a*180)/(3.14159);
   return result;
}

static precision_t rad_local(precision_t a)
{
   precision_t result = (a*3.14159)/(180);
   return result;
}

static precision_t sin_frac(precision_t a, int iteration)
{
   if (iteration == 20) return 1;
   return (iteration*(iteration+1) - (a*a) + ((iteration*(iteration+1)*a*a)/(sin_frac(a,iteration+2))));
}

static precision_t degFtoC(precision_t a)
{
   precision_t result = 0;

   result = (a-32)*(0.5555555555);
   return result;
}

static precision_t degCtoF(precision_t a)
{
   precision_t result = 0;

   result = (a*1.8) + 32;
   return result;
}
