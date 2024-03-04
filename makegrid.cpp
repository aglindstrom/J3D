#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <cstring>

void parse_args(int, char**, int*, int*, double*);

int main(int argc, char** argv){

	int i, x, y, faces;
	double theta = 0.0;
	double u, v;
	char buff[100];
	double* z;
	
	parse_args(argc, argv, &x, &y, &theta);

	z = (double*)malloc(sizeof(double)*x*y);
	
	fprintf(stderr, "loading...\n");
	
	for(i = 0, fgets(buff, 100, stdin); i < x*y && !feof(stdin) && buff != nullptr; i++, fgets(buff, 100, stdin)){
		z[i] = atof(buff);
	}

	faces = (2*(x-1))*(y-1);
	
	printf("%d %d\n", faces, x*y);

	for(int i = 0; i < (x-1)*y; i++){
		
		printf("%d %d %d ", i, i+1, i+y);
		printf("%d %d %d \n", i+1, i+y, i+y+1);
		
		if((i+2)%(y) == 0){
			i++;
		}
		
	}
	
	printf("\n");

	srand(time(NULL));

	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			printf("%0.2f %0.2f %0.2f\n", (double)(i), (double)(j), z[i*y + j]);
		}
	}
}

void parse_args(int argc, char** argv, int* x, int* y, double* theta){
	
	*x = 0;
	*y = 0;
	*theta = 0.0;

	for(int i = 1; i < argc; i++){
			if(argv[i][1] == 't'){
				*theta = atof(argv[++i])*3.14159/180;
			}else if(argv[i][1] == 'x'){
				*x = atoi(argv[++i]);
			}else if(argv[i][1] == 'y'){
				*y = atoi(argv[++i]);
			}else{
				fprintf(stderr, "Usage: %s [-x|-y|-t]", argv[0]);
			}
	}

	if(*y == 0) *y = *x;

}
