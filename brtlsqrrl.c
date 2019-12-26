/*
 * Brutal squirrel v0.6
 * Converter to hex digits and back
 * Copyright (c) 2007-2018 Artem Kurashov
 * under GNU GPLv3
 */

#include <stdio.h>
#include <string.h>

char
hexdigitz (int x)
{
    if (x < 10) return 48 + x;
    else return x + 87;
}


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
            puts("Options:");
            puts("-c - compile binary file");
            puts("-d - decompile to hex digits");
            puts("-t - text (void newline symbol before EOF)");
            puts("-b - binary (default)");
            puts("-h/--help - help");
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
            p[1] = hexdigitz(c[0] % 16);
            p[0] = hexdigitz(c[0] >> 4);
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
