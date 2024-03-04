#include <cmath>
#include <cstdio>


int main(int argc, char** argv){

	int x=1, y=1;
	double t = 0.0, s = 1.0, z=0.0; 

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
			case 's':
				s = atof(argv[++i]);
				break;
			default:
				fprintf(stderr, "Usage: %s [-x | -y | -t]", argv[0]);
				return 1;
		}
	}

	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			z = sqrt(i*i + j*j)/sqrt(x*x + y*y);
			printf("%0.4f\n", sin(((double)(z*360.0*s)*3.14159/180.0)+t));
		}
	}
}
