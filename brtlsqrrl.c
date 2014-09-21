/* 
 * Brutal squirrel v0.4
 * Converter to hex digits and back
 * Copyright (C) 2007-2011 Kurashov Artem Konstantinovich
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdio.h>
#include <string.h>

char hexdigitz[] =
  { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd',
  'e', 'f'
};

int
decdigit (int x)
{
  if ((x < 48 || x > 102) || (x > 57 && x < 97))
    return 0;
  if (x < 97)
    return x - 48;
  else
    return x - 87;
}

int main (int argc, char **argv)
{
  int i, c[2], p[2], mode = 0, mode2 = 0, flag10 = 0;
  for (i = 1; i < argc; i++)
    {
      if (!strcmp (argv[i], "-c"))
	mode = 1;
      if (!strcmp (argv[i], "-d"))
	mode = 0;
      if (!strcmp (argv[i], "-t"))
	mode2 = 1;
      if (!strcmp (argv[i], "-b"))
	mode2 = 0;
      if (!strcmp (argv[i], "-h") || !strcmp (argv[i], "--help"))
	{
	  printf
	    ("Options:\n-c - compile binary file\n-d - decompile to hex digits\n-t - text (void newline symbol before EOF)\n-b - binary (default)\n-h/--help - help\n");
	  return 0;
	}
    }
  for (;;)
    {
      if ((c[0] = getchar ()) == EOF)
	break;
      if (mode)
	if ((c[1] = getchar ()) == EOF)
	  c[1] = 0;
      switch (mode)
	{
	case 0:
	  if (mode2)
	    {
	      if (flag10)
		{
		  flag10 = 0;
		  putchar ('0');
		  putchar ('a');
		}
	      if (c[0] == 10 && !flag10)
		{
		  flag10 = 1;
		  continue;
		}
	    }
	  p[1] = hexdigitz[c[0] % 16];
	  p[0] = hexdigitz[c[0] >> 4];
	  putchar (p[0]);
	  putchar (p[1]);
	  break;
	case 1:
	  p[0] = decdigit (c[0]) * 16 + decdigit (c[1]);
	  putchar (p[0]);
	}
    }
  return 0;
}
