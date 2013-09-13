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
#include <string.h>
#include "brpn_utility.h"

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

#define HELP_BUFFER_LENGTH 250

char* format_help_string(char pad_char, int string1_indent_column, int string2_indent_column, const char* string1, const char* string2)
{
   static char buffer[HELP_BUFFER_LENGTH];
   int len1, len2;
   int buffer_index, string_index;

   // 
   memset(buffer, 0, sizeof(char)*HELP_BUFFER_LENGTH);
   len1 = strlen(string1);
   len2 = strlen(string2);
   
   for (buffer_index = 0; buffer_index < string1_indent_column; buffer_index++)
   {
      buffer[buffer_index] = ' ';
   }

   for (string_index = 0; (string_index < len1) && (buffer_index < HELP_BUFFER_LENGTH) && (buffer_index < string2_indent_column); string_index++, buffer_index++)
   {
      buffer[buffer_index] = string1[string_index];
   }

   if (buffer_index != (string2_indent_column))
   {
      buffer[buffer_index++] = ' ';
   }

   for (; buffer_index < (string2_indent_column - 1); buffer_index++)
   {
      buffer[buffer_index] = '.';
   }

   if (buffer_index == (string2_indent_column - 1))
   {
      buffer[buffer_index++] = ' ';
   }

   for (string_index = 0; (string_index < len2) && (buffer_index < HELP_BUFFER_LENGTH); string_index++, buffer_index++)
   {
      buffer[buffer_index] = string2[string_index];
   }

   return buffer;
}
