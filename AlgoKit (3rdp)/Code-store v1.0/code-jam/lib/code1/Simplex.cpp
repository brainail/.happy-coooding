#include<stdio.h>

double c[20];
double a[20][20];

int n, m;
void getInput(){
	printf("Number of variables: ");
	scanf("%d", &n);
	printf("Number of equations: ");
	scanf("%d", &m);
	printf("Enter c vector:");
	for(int i = 0; i < n; i++){
		scanf("%lf", &c[i]);
	}
	printf("Enter the A.b matrix:");
	for(i = 0; i < m; i++){
		for(int j = 0; j < n+1; j++){
			scanf("%lf", &a[i+1][j]);
		}
/*		if(a[i+1][0] < 0){
			for(j = 0; j < n+1; j++){
				 a[i+1][j] = -a[i+1][j];
			}
		}*/
		for(j = n+1; j < n+m+1; j++){
			if(j-n-1 == i){
				a[i+1][j] = 1;
			}else
				a[i+1][j] = 0;
		}
	}
	for(int j = 0; j < n+m; j++){
		if(j >= n){
			a[0][j+1] = 0;
		}else
			a[0][j+1] = c[j];
	}
	a[0][0] = 0;
}

void simplex(){
	int opt = 0;
	int unbounded = 0;
	int pivot, index;
	int Basic[20];
	double min, mult;

	for(int i = 0; i < m; i++){
		Basic[i] = n+i;
	}
	while(!(opt || unbounded)){
		opt = 1;
		min = 0.0;
		for(int i = 0; i < n; i++){
			if(a[0][i+1] < 0.0){
				opt = 0;
				if(min > a[0][i+1]){
					min = a[0][i+1];
					index = i+1;
				}
			}
		}
		if(opt) continue;
		unbounded = 1;
		min = 10e10;
		for(i = 0; i < m; i++){
			if(a[i+1][index]>0.0){
				unbounded = 0;
				if(a[i+1][0]/a[i+1][index] < min){
					min = a[i+1][0]/a[i+1][index];
					pivot = i+1;
				}
			}
		}
		if(unbounded) continue;
		Basic[pivot-1] = index-1;
		double tem = a[pivot][index];
		for(i = 0; i <= n+m; i++){
			a[pivot][i] /= tem;
		}
		for(i = 0; i <= m; i++){
			if(i != pivot){
				mult = -a[i][index]/a[pivot][index];
				for(int j = 0; j <= n+m; j++){
					a[i][j] += a[pivot][j]*mult;
				}
			}
		}
	}
	if(opt){
		printf("%.3lf\n", a[0][0]);
	}
}

int main(){
	freopen("simplex.in", "rt", stdin);
	getInput();
	simplex();
	return 0;
}
