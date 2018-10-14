/**
 * Die class by igor.
 * Simulates the rolling of a 6-sided die.
 *
 * USAGE:
 *      Create a die by passing a 6-character string to
 * the constructor. Each side of the die (top, north,
 * east, west, south and bottom) will be assigned a character
 * from that string (in that order).
 *
 * roll( d ) rolls the die by 90 degrees in the given
 * direction d ('n', 'e', 'w' or 's').
 *
 * get( f ) returns the character on face f ('n', 'e',
 * 'w', 's' or 'b').
 *
 * TWEAKING:
 *      If you have lots of dice, you should replace the
 * string with an array of 6 characters and change the
 * constructor.
 *      If you wish to store the faces in a different order,
 * you only need to change the T, N, E, W, S and B macros.
 *
 * FIELD TESTING:
 *      Passed these problems on Valladolid: 10409
 *
 * This file is part of my library of algorithms found here:
 *      http://www.palmcommander.com:8081/tools/
 * LICENSE:
 *      http://www.palmcommander.com:8081/tools/LICENSE.html
 * Copyright (c) 2004
 * Last modified: August 3, 2004
 * Contact author:
 *      igor at cs.ubc.ca
 **/

#include <stdio.h>      // For testing only
#include <string>

using namespace std;

struct Die
{
#define T s[0]
#define N s[1]
#define E s[2]
#define W s[3]
#define S s[4]
#define B s[5]
#define CYC( a, b ) t = T; T = a; a = B; B = b; b = t; break;

    string s;

    Die( string ss ) : s( ss ) {}

    void roll( char d )
    {
        char t;
        switch( d )
        {
            case 'n': CYC( S, N );
            case 'e': CYC( W, E );
            case 'w': CYC( E, W );
            case 's': CYC( N, S );
        }
    }

    char get( char d )
    {
        switch( d )
        {
            case 't': return T;
            case 'n': return N;
            case 'e': return E;
            case 'w': return W;
            case 's': return S;
            case 'b': return B;
        }
        return 0;
    }

#undef T
#undef N
#undef E
#undef W
#undef S
#undef B
#undef CYC
};

//------------------- TESTING ------------------
int main()
{
    Die d( "124356" );
    d.roll( 's' );
    d.roll( 'e' );
    d.roll( 'n' );
    d.roll( 'w' );
    printf( "%c%c%c\n", d.get( 't' ), d.get( 'n' ), d.get( 'e' ) );
    return 0;
}

