#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/time.h>
#include<time.h>
#include<string.h>

struct timeval time_start;
struct timeval time_end;

typedef struct{
	int x, y;
	int **values;
}Matrix;

typedef struct{
	int index;
	Matrix matrix_a, matrix_b, matrix_c;
}thread_data;

void randomizeMatrixValues(Matrix matrix);
void readMatrixValues(char *file_name, Matrix matrix_a, Matrix matrix_b);
void printMatrix(Matrix matrix);
void* matrixCalculation(void *arg_data);

int main(int argc, char *argv[]){
	// Check arguments
	// Assumed argument format
	// ./main <x1> <y1> <x2> <y2> <matrix_1_file>
	// While the dimensions are necessary matrix file is optional
	int i;
	
	// Not enough arguments
	if((argc - 1) < 4){
		printf("Not enough arguments\n"
				"./main <x1> <y1> <x2> <y2> <matrix_file_path>\n");
		exit(-1);
	}
	else{
		int x1, y1, x2, y2;
		// Parse dimensions

		x1 = atoi(argv[2]);  // Column count of matrix A
		y1 = atoi(argv[1]);  // Row count of matrix A
		x2 = atoi(argv[4]);  // Column count of matrix B
		y2 = atoi(argv[3]);  // Row count of matrix B

		// Exceptions where dimensions arent possible for matrix multipication
		// 0 or smaller dimensions and if the product isnt defined 
		if( (x1 <= 0 || y1 <= 0 || x2 <= 0 || y2 <= 0) || (x1 != y2) ){
			printf("Dimensions aren't possible\n");
			exit(-1);
		}
		else{
			// Allocate memory for matrices
			int *matrix_a_values = malloc(sizeof(int) * x1 * y1),
				*matrix_b_values = malloc(sizeof(int) * x2 * y2),
				*matrix_c_values = malloc(sizeof(int) * x2 * y1);

            Matrix matrix_a, matrix_b, matrix_c;
            matrix_a.values = &matrix_a_values, matrix_a.x = x1, matrix_a.y = y1;
            matrix_b.values = &matrix_b_values, matrix_b.x = x2, matrix_b.y = y2;
            matrix_c.values = &matrix_c_values, matrix_c.x = x2, matrix_c.y = y1;

			// Check if matrix file is present
			if(argv[5] != NULL) {	
				// File args are available
				// Means there is no need for randomization

				readMatrixValues(argv[5], matrix_a, matrix_b);
			}
			else{
				// No file args are given
				// Will randomize matrix values
	
    			// Seed init for pseudo random number
			    srand(time(NULL));

				// Randomize values
				randomizeMatrixValues(matrix_a);
				randomizeMatrixValues(matrix_b);
			}

			// Matrices A and B
			printMatrix(matrix_a);	
			printMatrix(matrix_b);

			// A thread for each row of the result matrix
			int thread_count = y1;
			pthread_t thread_id[thread_count];	

			// Fill in thread argument data
			thread_data data;
			data.matrix_a = matrix_a;
			data.matrix_b = matrix_b;
			data.matrix_c = matrix_c;
			
			int i;
			int delta;
			int delta_sum;

			for(i = 0; i < thread_count; i++){
				data.index = i;
				// Start time reference
				gettimeofday(&time_start, NULL);
				
				// Multithreading ops
				pthread_create(&thread_id[i], NULL, matrixCalculation, (void*)&data);
				pthread_join(thread_id[i], NULL);

				// End time reference
				gettimeofday(&time_end, NULL);

				// Time difference in miliseconds
				delta = 1000000 * (time_end.tv_sec - time_start.tv_sec)
									+ (time_end.tv_usec - time_start.tv_usec);

				delta_sum += (int)delta;
				printf("Thread %d finished. Time: %d miliseconds.\n", i + 1, delta);
				
			}

			printf("\nResult Matrix\n");
			printMatrix(matrix_c);

			printf("Program finished. Time: %d miliseconds\n", delta_sum);
		}
	}
	
	return 0;
}

void randomizeMatrixValues(Matrix matrix){
	int i, j;

    for(i = 0; i < matrix.y; i++){
        for(j = 0; j < matrix.x; j++){
            *(*matrix.values + (i * matrix.x) + j) = (rand() % 6);
        }
    }
}

void readMatrixValues(char *file_name, Matrix matrix_a, Matrix matrix_b){

	FILE *fp = fopen(file_name, "r");

	if(fp == NULL){
		printf("Couldnt read file.\n");
		exit(-1);
	}
	else{
		int i = 0;
		size_t len = 0;
		ssize_t read;
		char * line = NULL;
		char *token;
		const char NUMBER_SEPARATOR[2] = " ";

		// Reading first matrix from the file

		while (i < matrix_a.y) {
			// Read line
			(read = getline(&line, &len, fp));
			int j = 0;
			// Split the line using NUMBER_SEPARATOR
			// First strtok is outside of the while loop because we need to check if token is NULL
			token = strtok(line, NUMBER_SEPARATOR);
			while( token != NULL ) {
				// Cast token to integer and set it to corresponding matrix value
				*(*matrix_a.values + (i * matrix_a.x) + j)  = atoi(token);
				token = strtok(NULL, NUMBER_SEPARATOR);
				j++;
			}
			i++;
    	}

		// Remove the space between matrices
		(read = getline(&line, &len, fp));

		// Read second matrix from the file
		i = 0;
		while (i < matrix_b.y) {
			(read = getline(&line, &len, fp));
			int j = 0;
			token = strtok(line, NUMBER_SEPARATOR);
			while( token != NULL ) {
				*(*matrix_b.values + (i * matrix_b.x) + j)  = atoi(token);
				token = strtok(NULL, NUMBER_SEPARATOR);
				j++;
			}
			i++;
    	}

		fclose(fp);
		if(line){
			free(line);
		}
	}
}

void printMatrix(Matrix matrix){
    int i, j;

    for(i = 0; i < matrix.y; i++){
		printf("[ ");
        for(j = 0; j < matrix.x;j++){
            printf("%d ", *(*matrix.values + (i * matrix.x) + j));
        }
        printf("]\n");
    }
	printf("\n");
}

void* matrixCalculation(void *arg_data){
	// Cast thread arguments to matrices
	thread_data *data = (thread_data*) arg_data;
    Matrix matrix_a = data->matrix_a,
            matrix_b = data->matrix_b,
            matrix_c = data->matrix_c;
	int i, j;

	for(i = 0; i < matrix_c.x; i++){
		int sum = 0;
		for(j = 0; j < matrix_a.x; j++){
			// Pointer arithmetic
			sum += *(*matrix_a.values + (data->index * matrix_a.x) + j) * *(*matrix_b.values + (j * matrix_b.x) + i);
        }
		// Set values of c matrix
		*(*matrix_c.values + (data->index * matrix_c.x) + i) = sum;
	}
}
