#include<stdio.h>
#include<conio.h>

int Mark[ 260 ], CharSet[ 260 ], Frq[ 520 ], Parant[ 520 ], CharCount;

int Heap[ 520 ], hn;

int MinFrq( int p, int q )
{
   if( Frq[ p ] < Frq[ q ] )	return 1;
   return 0;
}


void HeapInit( int n )
{
	int i;
	hn = n;
	for( i=0; i<=n; i++ )	Heap[ i ] = i;
}

void Adjust( int i )
{
	int p, c, ele = Heap[ i ];
	p = i, c = i*2;
	while( c <= hn ){
		if( c<hn && MinFrq( Heap[c+1], Heap[c] ) ) c++;
		if( MinFrq( Heap[c], ele ) ){
			Heap[ p ] = Heap[ c ];
			p = c;	c = p * 2;
		}else	break;
	}
	Heap[ p ] = ele;
}

int ExtractRoot( void )
{
	int ele = Heap[ 1 ];
	Heap[ 1 ] = Heap[ hn-- ];
	Adjust( 1 );
	return ele;
}

void Insert( int ele )
{
	int p, c;
	Heap[ ++hn ] = ele;
	c = hn;	p = hn/2;
	while( c > 0 ){
		if( MinFrq( ele, Heap[p] ) ){
			Heap[ c ] = Heap[ p ];
			c = p;	p = c / 2;
		}else break;
	}
	Heap[ c ] = ele;
}

void Read( char *FileName )
{
	int ch;
	FILE *fr = fopen( FileName, "rb" );
	CharCount = 0;
	for( ch=1; ch<=260; ch++ )
		Mark[ ch ] = 0;

	while( ( ch=fgetc(fr) ) != EOF ){
		if( Mark[ ch ] == 0 ){
			Mark[ ch ] = ++CharCount;
			Frq[ CharCount ] = 1;
			CharSet[ CharCount ] = ch;
		}else
			Frq[ Mark[ ch ] ]++;
	}
	fclose( fr );
	HeapInit( CharCount );
}
char Stack[ 260 ], Top;

void Push( int i )
{
	Stack[ ++Top ] = i;
}

int Pop( void )
{
	if( Top == 0 )	return -1;
	return Stack[ Top-- ];
}
void GenerateCode( void )
{
	int i, k;
	Top = 0;
	for( i=1; i<=CharCount; i++ ){
		k = Mark[ CharSet[ i ] ];
		while( k != Parant[ k ] ){
			k = Parant[ k ];
			if( k < 0 ){
				Push( 0 );
				k = -k;
			}else
				Push( 1 );
		}
		if( CharSet[ i ] == '\n' )
			printf("%5s(%2d) = ","\\n", Frq[ Mark[ CharSet[ i ] ] ] );
		else
			printf("%5c(%2d) = ", CharSet[ i ], Frq[ Mark[ CharSet[ i ] ] ] );
		while( (k = Pop( )) > -1 )	printf( "%d", k );
		printf( "\n" );
	}
}

void MakeTree( void )
{
	int min1, min2, nd = CharCount;
	while( hn > 1 ){
		min1 = ExtractRoot( );
		min2 = ExtractRoot( );
		Frq[ ++nd ] = Frq[ min1 ] + Frq[ min2 ];
		Insert( nd );
		Parant[ min1 ] = -nd;
		Parant[ min2 ] = nd;
	}
	Parant[ nd ] = nd;
}


void main( void )
{
	clrscr( );
	Read( "e:\\test1.txt" );
	MakeTree( );
	GenerateCode( );
}

