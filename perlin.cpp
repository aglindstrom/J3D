#include <cstdlib>
#include <cstdio>
#include <ctime>

double lerp(double, double, double);

int main(int argc, char** argv){

	int x=1, y=1;
	int t = 0; 
	double* r_base;

	for(int i = 1; i < argc-1; i++){
		switch(argv[i][1]){
			case 'x':
				x = atoi(argv[++i]);
				break;
			case 'y':
				y = atoi(argv[++i]);
				break;
			case 't':
				t = atof(argv[++i]);
				break;
			default:
				fprintf(stderr, "Usage: %s [-x | -y | -t]", argv[0]);
				return 1;
		}
	}

	srand(t == 0? time(NULL): t);
	
	r_base = (double*)malloc(sizeof(double)*x*y/4);
	
	for(int i = 0; i < x*y/4; i++){
		r_base[i] = rand()/(double)RAND_MAX);
	}

	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			printf("%0.4f\n", (double)lerp(r_base[(i/4)*(y/4) + j/4], r_base[(i/4)*(y/4) + j/4 + 1], (j%4)/3.0));
		}
	}
}

double lerp(double x, double y, double t){

	return (x*t) + (y*(1-t))
}
