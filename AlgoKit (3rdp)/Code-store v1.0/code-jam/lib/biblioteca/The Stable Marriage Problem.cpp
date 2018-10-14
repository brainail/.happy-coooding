#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

char gosta [260][260];
char caso [260];
int pos [260];
char homens [50];
char mulheres[50];
char temp [100];
int n;

void read () {
	scanf ("%d", &n);
	
	for (int i = 0; i < n; i++) {
		scanf ("%s", temp);
		homens[i] = temp[0];
	}
	for (int i = 0; i < n; i++) {
		scanf ("%s", temp);
		mulheres[i] = temp[0];
	}
	for (int i = 0; i < (n<<1); i++) {
		scanf ("%s", temp);
		strcpy (gosta[temp[0]], temp+2);
	}
	memset (pos, -1, sizeof (pos));
	memset (caso, 0, sizeof (caso));
}

int p = 1;
void process () {

	char atual, outro, mulher;
	for (int i = 0; i < n; i++) {
		atual = homens [i];
		mulher = gosta[atual][++pos[atual]];
		
		while (outro = caso[ mulher ]) {
			for (int j = 0; j < n; j++) {
				if (gosta[mulher][j] == atual) {
					caso [mulher] = atual;
					atual = outro;	
					break;
				} else if (gosta[mulher][j] == outro) break;
			}			
			mulher = gosta[atual][++pos[atual]];
		}
		caso [mulher] = atual;
	}
	
	for (int i = 0; i < n; i++) {
		atual = homens [i];
		mulher = gosta[atual][pos[atual]];
		printf ("%c %c\n", atual, mulher);
	}	
}
