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
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "brpn_usage.h"
#include "brpn_nullary.h"

int check_commandline_args(int argc, char** argv)
{
   struct option longopts[] =
   {
      {     "help",       no_argument, 0, 'h'},
      {  "version",       no_argument, 0, 'v'},
   };
   int longindex;
   int opt;
   int rc = 0;
   int do_break = 0;

   while ((opt = getopt_long(argc, argv, "hv", longopts, &longindex)) != -1)
   {
      switch (opt)
      {
         case 'h':
            usage();
            rc = -1;
            break;
         case 'v':
            version();
            rc = -1;
            break;

         /* parse command line args as standard data? */
         default:
            break;
      }

      if (do_break)
      {
         break;
      }
   }

   return rc;
}

void usage(void)
{
   printf("Usage: brpn [flags]\n");
   printf("\n");
   printf("Flags:\n");
   printf("   -h --help .................... Print help\n");
   printf("   -v --version ................. Print version\n");
}
