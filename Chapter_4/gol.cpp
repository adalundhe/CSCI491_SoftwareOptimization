#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char cell;

/* w%64 == 0 */
#define w 128
#define h 128
#define fix_x(x) ( (((x)/(w/8))%8) | (((x)%w)*8) )
#define pos(y,x) ( y*w + fix_x(x) )

extern cell *map;
extern void clearMap();
extern void nextGen();

/* horribly dirty */
static char buf[w+1]= {0};
static int ch;
static int getcell(FILE *fIn){
static char *p= buf;
	if( !*p ){
		if( feof(fIn) ){
			ch= -1;
			return ch;
		}else{
			char *q;
			for(q= buf, *q= 0
			; !feof(fIn) && q<buf+w &&
				(ch=fgetc(fIn)) != -1 && ch != '\n'
			; *q++= ch);
			*q= 0;
			if( q == buf ){
				*q++= ' ';
				*q= 0;
			}
			if( ch != '\n' )
				while( !feof(fIn) &&
					(ch=fgetc(fIn)) != -1 && ch != '\n' );

			if( p != buf ){
				p= buf;
				ch= '\n';
				return ch;
			}
		}
	}

	ch= *p++;
	if( ch!=' ' && ch!='@' ) ch= -1;
	if( buf+w <= p ) p=buf, *p=0;
	return ch;
}

static void putMap(){
	int x,y;
	for(y=0; y<22 /*h*/
	; puts(""), ++y)
		for(x=0; x<64 /*w*/
		; putchar( map[pos(y,x)]? '@': ' ' ), ++x);
}

int main(int argc, char *argv[]){
	int cyc= 1, steps= 4, i,j;
	int x,y;
	FILE *fIn= stdin;

	if( 1<argc ){
		fIn= fopen(argv[1],"r");
		if( !fIn ) fIn= stdin;

		if( 2<argc ){
			steps= atoi(argv[2]);
			if( steps<=0 ) steps= 4;
		}
		/* gens per 1 cyc */
		if( 3<argc ){
			cyc= atoi(argv[3]);
			if( cyc<=0 ) cyc= 1;
		}
	}

	clearMap();

	for(y=0; y<h; ++y)
		for(x=0; x<w && getcell(fIn) && ch != '\n'; ++x)
			map[pos(y,x)]= ch == '@';

	if( fIn != stdin ) fclose(fIn);

	for(i=0; i<steps; ++i){
		putMap();
		puts("----");
		for(j=0; j<cyc; ++j) nextGen();
	}
	putMap();

	return 0;
}
