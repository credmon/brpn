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

typedef long double (*unary_operator_t)(long double);
typedef long double (*binary_operator_t)(long double,long double);
typedef long double precision_t;

struct unary_operator
{
   char name[10];
   unary_operator_t func;
};

struct binary_operator
{
   char name[10];
   binary_operator_t func;
};

void usage(int exit_code);
void version(void);
void get_input(int input_fd);
int operator_match(const char* string);
unary_operator_t unary_operator_match(const char* string);
binary_operator_t binary_operator_match(const char* string);
int string_match(const char* string1, const char* string2);
precision_t convert_string_to_double(const char* string);

precision_t sin_local(precision_t a);
precision_t cos_local(precision_t a);
precision_t tan_local(precision_t a);
precision_t asin_local(precision_t a);
precision_t acos_local(precision_t a);
precision_t atan_local(precision_t a);
precision_t deg_local(precision_t a);
precision_t rad_local(precision_t a);

precision_t add(precision_t a, precision_t b);
precision_t subtract(precision_t a, precision_t b);
precision_t multiply(precision_t a, precision_t b);
precision_t divide(precision_t a, precision_t b);
precision_t modulo(precision_t a, precision_t b);

#define NUM_UNARY_OPERATORS 8

struct unary_operator UnaryOperators[NUM_UNARY_OPERATORS] =
{
   {
      "sin",
      sin_local,
   },
   {
      "cos",
      cos_local,
   },
   {
      "tan",
      tan_local,
   },
   {
      "asin",
      asin_local,
   },
   {
      "acos",
      acos_local,
   },
   {
      "atan",
      atan_local,
   },
   {
      "deg",
      deg_local,
   },
   {
      "rad",
      rad_local,
   }
};

#define NUM_BINARY_OPERATORS 5

struct binary_operator BinaryOperators[NUM_BINARY_OPERATORS] =
{
   {
      "+",
      add,
   },
   {
      "-",
      subtract,
   },
   {
      "*",
      multiply,
   },
   {
      "/",
      divide,
   },
   {
      "%",
      modulo,
   }
};

int main(int argc, char** argv)
{
   struct option longopts[] =
   {
      {     "help",       no_argument, 0, 'h'},
      {  "version",       no_argument, 0, 'v'},
   };
   int longindex;
   int opt;

   while ((opt = getopt_long(argc, argv, "hv", longopts, &longindex)) != -1)
   {
      switch (opt)
      {
         case 'h':
            usage(0);
            break;
         case 'v':
            version();
            break;
         default:
            break;
      }
   }

   get_input(0);

   return 0;
}

void usage(int exit_code)
{
   printf("Usage: brpn [flags]\n");
   printf("\n");
   printf("Flags:\n");
   printf("   -h --help .................... Print help\n");
   printf("   -v --version ................. Print version\n");
 
   exit(exit_code);
}

void version(void)
{
   printf("Version: brpn-0.0\n");
   exit(0);
}

#define MAX_INPUT_ARRAY_LENGTH 256

void get_input(int input_fd)
{
   char input_array[MAX_INPUT_ARRAY_LENGTH];
   char input_array_cache[MAX_INPUT_ARRAY_LENGTH];
   ssize_t len;
   int i;
   int input_line_length = 0;
   precision_t accumulator[2];
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

               if ((UnaryFunc = unary_operator_match(input_array_cache)) != NULL)
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

int operator_match(const char* string)
{
   if (unary_operator_match(string) != NULL)
   {
      return 1;
   }

   if (binary_operator_match(string) != NULL)
   {
      return 1;
   }

   return 0;
}

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

int string_match(const char* string1, const char* string2)
{
   int i = 0;

   if (strlen(string1) != strlen(string2))
   {
      return 0;
   }

   while ((string1[i] != '\0') && (string2[i] != '\0'))
   {
      if (string1[i] != string2[i])
      {
         return 0;
      }
      i++;
   }
   return 1;
}

precision_t convert_string_to_double(const char* string)
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

precision_t add(precision_t a, precision_t b)
{
   precision_t result;
   result = a + b;
   return result;
}

precision_t subtract(precision_t a, precision_t b)
{
   precision_t result;
   result = a - b;
   return result;
}

precision_t multiply(precision_t a, precision_t b)
{
   precision_t result;
   result = a * b;
   return result;
}

precision_t divide(precision_t a, precision_t b)
{
   precision_t result;
   result = a / b;
   return result;
}

precision_t modulo(precision_t a, precision_t b)
{
   precision_t result = 0;
   /* result = a % b; */
   return result;
}

precision_t sin_frac(precision_t a, int iteration)
{
   if (iteration == 20) return 1;
   return (iteration*(iteration+1) - (a*a) + ((iteration*(iteration+1)*a*a)/(sin_frac(a,iteration+2))));
}

precision_t sin_local(precision_t a)
{
   precision_t result = 0;

   result = (a/(1+((a*a)/sin_frac(a,2))));

   return result;
}

precision_t cos_local(precision_t a)
{
   precision_t result = 0;

   result = sin_local(1.57-a);

   return result;
}

precision_t tan_local(precision_t a)
{
   precision_t result = 0;
   return result;
}

precision_t asin_local(precision_t a)
{
   precision_t result = 0;
   return result;
}

precision_t acos_local(precision_t a)
{
   precision_t result = 0;
   return result;
}

precision_t atan_local(precision_t a)
{
   precision_t result = 0;
   return result;
}

precision_t deg_local(precision_t a)
{
   precision_t result = (a*180)/(3.14159);
   return result;
}

precision_t rad_local(precision_t a)
{
   precision_t result = (a*3.14159)/(180);
   return result;
}

