/*
 *
 *
 *
 */

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cfloat>


// consider refactoring to mesh class that contains all verts, 
// indices, num_verts, num_faces, mins, and maxes
typedef struct vert3d{
   
   double coords[3];
   double depth;

}vertex;

void mv_multiply(double**, double*, double*, int, int);
void transform_by(double**, double*, double*, int, int);
void load_mesh(vertex**, int**, int*, int*);
void make_poly(vertex*, int*, const char*, double, double, double);
void parse_args(int, char**, double*, double*, double*);

int main(int argc, char** argv){

   double alpha = 0, beta = 0, gamma = 0;

   parse_args(argc, argv, &alpha, &beta, &gamma);

   /* ROTATION MATRIX*/
   double rot_matrix[9] = {cos(beta)*cos(gamma), sin(alpha)*sin(beta)*cos(gamma)-cos(alpha)*sin(gamma), cos(alpha)*sin(beta)*cos(gamma)+sin(alpha)*sin(gamma), cos(beta)*sin(gamma), sin(alpha)*sin(beta)*sin(gamma) + cos(alpha)*cos(gamma), cos(alpha)*sin(beta)*sin(gamma)-sin(alpha)*cos(gamma), -sin(beta), sin(alpha)*cos(beta), cos(alpha)*cos(beta)};
   
   double d_min = DBL_MAX, x_min = DBL_MAX, y_min = DBL_MAX, d_max = DBL_MIN, x_max = DBL_MIN, y_max = DBL_MIN, x_size = 0.0, y_size = 0.0;
   double z;
   int i = 0, j = 0;
   int num_faces, num_verts;
   
   int* indices;
   vertex* mesh;

   double* intermediate = (double*)malloc(sizeof(double)*3);
   vertex* result; 
   
   load_mesh(&mesh, &indices, &num_faces, &num_verts);
   result = (vertex*)malloc(sizeof(vertex)*num_verts);
   
   for(i = 0; i < num_verts; i++){

      intermediate[0] = 0;
      intermediate[1] = 0;
      intermediate[2] = 0;
      
      mv_multiply(&intermediate, rot_matrix, mesh[i].coords, 3, 3);
      
      result[i].coords[0] = intermediate[0];
      result[i].coords[1] = intermediate[1];
      result[i].coords[2] = intermediate[2];
      result[i].depth = mesh[i].depth;

      if(intermediate[0] > x_max){ x_max = intermediate[0]; }
      if(intermediate[0] < x_min){ x_min = intermediate[0]; }
      if(intermediate[1] > y_max){ y_max = intermediate[1]; }
      if(intermediate[1] < y_min){ y_min = intermediate[1]; }

      if(result[i].depth < d_min){ d_min = result[i].depth; }
      if(result[i].depth > d_max){ d_max = result[i].depth; }
   }

   

   // find the aspect ratio
   x_size = x_max - x_min;
   y_size = y_max - y_min;
   
   if(x_size < y_size){
      x_size = x_size/y_size;
      y_size = 1;
   }else{
      y_size = y_size/x_size;
      x_size = 1;
   }

   fprintf(stderr,"aspect x: %0.2f y: %0.2f\n", y_size, x_size);
   
   
   // print the jgraph file
   printf("newgraph\n");
   printf("xaxis nodraw size %0.2f\nyaxis nodraw size %0.2f\n", 8.5*x_size, 8.5*y_size);
   
   for(i = num_faces*3-3, j = num_faces-1; j != -1; i-=3, j--){
      z = mesh[indices[i]].depth/d_max;
      make_poly(result, indices+i, "solid", mesh[indices[i]].coords[2], z, z);
   }
   
   printf("\n");

   return 0;
}

/*
 * mv_multiply multiplies a matrix times a vector and sets the result in a reference to a result vector
 * @param:
 *    result: the result of the multiplication
 *    matrix: the matrix to multiply
 *    vector: the vector to multiply
 *     width: the width of the matrix
 *    height: the height of the matrix
 *
 */
void mv_multiply(double* result[], double* matrix, double* vector, int width, int height){

   for(int i = 0; i < width; i++){                       // multiply the matrix by the vector like this
      for(int j = 0; j != height; j++){                  // [m00 * v0 + m01 * v1 + ... + m0w * vh]
         (*result)[i] += matrix[i*height+j] * vector[j]; // [m10 * v0 + m11 * v1 + ... + m1w * vh]
      }                                                  // [...                              ...] 
   }                                                     // [mh0 * v0 + mh1 * v1 + ... + mhw + vh]
}

/*
 * make_poly makes a jgraph curve polygon from 3 vertices with colors r,g,b
 * and prints it to stdout
 *    
 * @param:
 *    points: a pointer to a list of vertices
 *   indices: a pointer to the start of a list of 3 indices
 *  linetype: specifies the outline of the polygon
 *         r: red color channel
 *         g: green color channel
 *         b: blue color channel
 */
void make_poly(vertex* points, int* indices, const char* linetype, double r, double g, double b){

   printf("newcurve poly marktype none "); // start jgraph polygon
   printf("linetype %s ", linetype);       // set linetype
   printf("color %f %f %f", r, g, b);      // set colors
   printf("\n pts");                       // start points
                                           //
   for(int i = 0; i < 3; i++){             // print 3 points for the face to stdout
      printf(" %0.2f %0.2f ", points[indices[i]].coords[0], points[indices[i]].coords[1]);
   }

   printf("\n");
}



/*
 * load_mesh loads a file with a custom format from stdin
 * (consider revising to .obj format)
 * 
 * file format: 
 *    num_faces num_verts
 *    indices: new line delimited 6 per line
 *    vertices: new line delimited 3 coords per line
 *
 * @out_params: 
 *       mesh: list to be filled with vertices 
 *    indices: list to be filled with indices 
 *  num_faces: number of faces in the file (num_faces*3 is the number of indices)
 *  num_verts: number of vertices in the file
 */
void load_mesh(vertex** mesh, int** indices, int* num_faces, int* num_verts){

   int buff_size = 512;                                // use an input buffer size of 512 for now
   char* buff = (char*)malloc(sizeof(char)*buff_size); // allocate input buffer to buff_size
   int i = 0, j = 0;
   
   scanf("%d %d", num_faces, num_verts); // load the number of faces and verts from the head
   fgets(buff, buff_size, stdin);        // consume the rest of the first line
   
   fprintf(stderr, "%d %d\n", *num_faces, *num_verts);
   
   *indices = (int*)malloc(sizeof(int)*(*num_faces)*3);  // allocate the correct number
   *mesh = (vertex*)malloc(sizeof(vertex)*(*num_verts)); // of faces and verts

   for(;i < (*num_faces)*3;){
      
      fgets(buff, buff_size, stdin); // get a line of face indices
      
      (*indices)[i++] = atoi(strtok(buff, " "));   // load 6 indices at a time
      (*indices)[i++] = atoi(strtok(NULL, " "));   // could be a for loop but 
      (*indices)[i++] = atoi(strtok(NULL, " "));   // this felt like a good 
      (*indices)[i++] = atoi(strtok(NULL, " "));   // idea at the time
      (*indices)[i++] = atoi(strtok(NULL, " "));   //
      (*indices)[i++] = atoi(strtok(NULL, " \n")); //
   }

   
   fgets(buff, buff_size, stdin); // remove new line between indices and vertices
   
   fgets(buff, buff_size, stdin); // get first vertex

   for(;j < (*num_verts); j++){
      
      (*mesh)[j].coords[0] = atof(strtok(buff, " "));    // load 3 vertex coordinates
      (*mesh)[j].coords[1] = atof(strtok(NULL, " "));    //
      (*mesh)[j].coords[2] = atof(strtok(NULL, "\n"));   //
      
      /* calculate the depth of each vertex */
      (*mesh)[j].depth = sqrt((*mesh)[j].coords[0]*(*mesh)[j].coords[0] + (*mesh)[j].coords[1]*(*mesh)[j].coords[1] + (*mesh)[j].coords[2]*(*mesh)[j].coords[2]);
      fgets(buff, buff_size, stdin);
   
   }
   
   for(i=0; i < (*num_faces)*3; i+=3){
      // maybe calculate the normal here
      // do that by taking the cross product of the edges connectecd to
      // this vert on this face (sa maybe do it after the fact? needed for lighting)
   
   }

   free(buff);

   return;
}

/*
 * parse_args parses the command line arguments for j3D 
 *    
 *    usable arguments:
 *       -x: x axis angle
 *       -y: y axis angle
 *       -z: z axis angle 
 *       -d: convert degrees input to radians
 *
 * @params:
 *    argc: number of command line args
 *    argv: command line args
 *   alpha: x axis angle
 *    beta: y axis angle
 *   gamma: z axis angle
 */
void parse_args(int argc, char** argv, double* alpha, double* beta, double* gamma){
   
   bool deg = false;

   for(int i = 1; i < argc; i++){
      if(argv[i][1] == 'x'){       // load x angle
         *alpha = atof(argv[++i]);
      }else if(argv[i][1] == 'y'){ // load y angle
         *beta = atof(argv[++i]);
      }else if(argv[i][1] == 'z'){ // load z angle
         *gamma = atof(argv[++i]);
      }else if(argv[i][1] == 'd'){ // set conversion
         deg = true;
      }else{                     // if an incorrect option is used print usage
         fprintf(stderr, "usage: %s [-x | -y | -z | -d] < [file]", argv[0]);
      }
   }

   if(deg == true){                    // convert from degrees to radians
      *alpha = (*alpha)*3.14159/180;
      *beta = (*beta)*3.14159/180;
      *gamma = (*gamma)*3.14159/180;
   }
}
