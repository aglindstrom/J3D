#include <cstdlib>
#include <cstdio>
#include <ctime>

int main(int argc, char** argv){

	int x=1, y=1;
	int t = 0; 

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

	for(int i = 0; i < x; i++){
		for(int j = 0; j < y; j++){
			printf("%0.4f\n", (double)rand()/(double)RAND_MAX);
		}
	}
}
