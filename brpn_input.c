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
#include <unistd.h>
#include "brpn_input.h"
#include "brpn_main.h"
#include "brpn_nullary.h"
#include "brpn_unary.h"
#include "brpn_binary.h"
#include "brpn_utility.h"

#define MAX_INPUT_ARRAY_LENGTH 256

static precision_t convert_string_to_double(const char* string);

void get_input(int input_fd)
{
   char input_array[MAX_INPUT_ARRAY_LENGTH];
   char input_array_cache[MAX_INPUT_ARRAY_LENGTH];
   ssize_t len;
   int i;
   int input_line_length = 0;
   precision_t accumulator[2];
   nullary_operator_t NullaryFunc;
   unary_operator_t UnaryFunc;
   binary_operator_t BinaryFunc;

   for (i = 0; i < 2; i++)
   {
      accumulator[i] = 0;
   }

   while((len = read(input_fd, input_array, MAX_INPUT_ARRAY_LENGTH*sizeof(char))) > 0)
   {
      for (i = 0; i < len; i++)
      {
         if ((input_array[i] == '\n') ||
             (input_array[i] == ' '))
         {
            if (input_line_length != 0)
            {
               input_array_cache[input_line_length] = '\0';
               if ((NullaryFunc = nullary_operator_match(input_array_cache)) != NULL)
               {
                  NullaryFunc();
               }
               else if ((UnaryFunc = unary_operator_match(input_array_cache)) != NULL)
               {
                  accumulator[0] = UnaryFunc(accumulator[0]);
                  printf("%Lf\n",accumulator[0]);
               }
               else if ((BinaryFunc = binary_operator_match(input_array_cache)) != NULL)
               {
                  accumulator[0] = BinaryFunc(accumulator[0],accumulator[1]);
                  printf("%Lf\n",accumulator[0]);
               }
               else
               {
                  accumulator[1] = accumulator[0];
                  accumulator[0] = convert_string_to_double(input_array_cache);
                  //printf("%lf %lf\n",accumulator[0], accumulator[1]);
               }
            }
            input_line_length = 0;
         }
         else
         {
            input_array_cache[input_line_length] = input_array[i];
            input_line_length++;
         }
      }
   }
}

static precision_t convert_string_to_double(const char* string)
{
    precision_t result = 0;
    int string_length = strlen(string);
    int i;
    char decimal_seen = 0;
    precision_t result_integer = 0;
    precision_t result_decimal = 0;

    for (i = 0; i < string_length; i++)
    {
       if (string[i] == '.')
       {
          decimal_seen = 1;
          break;
       }
       else if ((string[i] >= 0x30) && /* 0 - 9 */
                (string[i] <= 0x39))
       {
          result_integer = (result_integer*10) + ((precision_t) (string[i] - 0x30));
       }
    }

    if (decimal_seen)
    {
       for (i = string_length-1; i >= 0;  i--)
       {
          if (string[i] == '.')
          {
             break;
          }
          result_decimal = (result_decimal/10) + (((precision_t) (string[i] - 0x30))/10);
       }
    }

    result = result_integer + result_decimal;

    return result;
}

