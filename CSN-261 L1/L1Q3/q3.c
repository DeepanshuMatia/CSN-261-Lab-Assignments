#include <stdio.h>
#include <stdlib.h>

//! Read pixel data from the file and store it in a 2 D array.
int** read_color_data (char* file_name) {	                        
	int** color_array = (int**)malloc(953*sizeof(int*));            
    for(int i = 0; i<953; i++){
    	color_array[i] = (int*)malloc(1268*sizeof(int));              
    }
	FILE* color_file = fopen(file_name, "r");

	for (int i = 0; i < 953; i++)
		for (int j = 0; j < 1268; j++){
			if (j != 1267)
				fscanf(color_file, "%d,", &color_array[i][j]);        
			else
				fscanf(color_file, "%d\n", &color_array[i][j]);

		}

	fclose(color_file);
	return color_array;
}

//! Create an output file by reading pixel data from the 2D array.
void write_pixel_data (char *file, int** color_info) {
	FILE* color_array;
	color_array = fopen(file, "w");

	for (int i = 0; i < 953; i++)
		for (int j = 0; j < 1268; j++){
			if (j != 1267 )
				fprintf(color_array, "%d,", color_info[i][j] );
			else 
				fprintf(color_array, "%d\n", color_info[i][j] );
		}
		fclose(color_array);
}

int** Red;
int** Green;
int** Blue;

//! Remove all Red shades.
void remove_red(){
for(int i = 0; i<953; i++)
	for(int j = 0; j<1268; j++){
        if((Red[i][j] > Green[i][j]) && (Red[i][j] > Blue[i][j]))
        	Red[i][j] = 0;
	}
}

//! Remove all Green shades.
void remove_green(){
for(int i = 0; i<953; i++)
	for(int j = 0; j<1268; j++){
        if((Green[i][j] > Red[i][j]) && (Green[i][j] > Blue[i][j]))
        	Green[i][j] = 0;
        }
	}

//! Remove all Blue shades.
void remove_blue(){
for(int i = 0; i<953; i++)
	for(int j = 0; j<1268; j++){
        if((Blue[i][j] > Green[i][j]) && (Blue[i][j] > Red[i][j]))
        	Blue[i][j] = 0;
        }
	}

//!  Preserve any red shades in the image, but remove all green and blue.
void red_only(){
	remove_blue();
	remove_green();
	remove_blue();
}	

//! Preserve any green shades in the image, but remove all red and blue.
void green_only(){
	remove_blue();
	remove_red();
	remove_blue();
}

//! Preserve any blue shades in the image, but remove all red and green.
void blue_only(){
	remove_red();
	remove_green();
	remove_red();
}

//! displays the current pixel (RED, GREEN and BLUE) values of the input image at the point with coordinates (x, y), 
//!where x and y are the row and column numbers in that image file, respectively.
void get_pixel(){
	int x,y;
	printf("%s\n", "Enter the coordinates of the pixel." );
	scanf("%d", &x);
	scanf("%d", &y);
	printf("Red=%d\n", Red[x-1][y-1] );
	printf("Green=%d\n", Green[x-1][y-1]);
	printf("Blue=%d\n", Blue[x-1][y-1]);
}

int main(){
	Red=read_color_data("Q3_ip_Red.dat");
	Green=read_color_data("Q3_ip_Green.dat");
	Blue=read_color_data("Q3_ip_Blue.dat");
	int instruction;
	do{
	printf("%s\n","1. Remove all red shades." );
	printf("%s\n","2. Remov all green shades." );
	printf("%s\n","3. Remove all blue shades." );
	printf("%s\n","4. Red only." );
	printf("%s\n","5. Green only." );
	printf("%s\n","6. Blue only." );
	printf("%s\n","7. Get color values for a pixel." );
	printf("%s\n","8. End the program." );
	scanf("%d", &instruction);

	switch(instruction){
		case 1: remove_red();
		write_pixel_data("Q3_op_red.dat", Red);
		write_pixel_data("Q3_op_green.dat", Green);
		write_pixel_data("Q3_op_blue.dat", Blue);
		break;
		case 2: remove_green();
		write_pixel_data("Q3_op_red.dat", Red);
		write_pixel_data("Q3_op_green.dat", Green);
		write_pixel_data("Q3_op_blue.dat", Blue);
		break;
		case 3: remove_blue();
		write_pixel_data("Q3_op_red.dat", Red);
		write_pixel_data("Q3_op_green.dat", Green);
		write_pixel_data("Q3_op_blue.dat", Blue);
		break;
		case 4: red_only();
		write_pixel_data("Q3_op_red.dat", Red);
		write_pixel_data("Q3_op_green.dat", Green);
		write_pixel_data("Q3_op_blue.dat", Blue);
		break;
		case 5: green_only();
		write_pixel_data("Q3_op_red.dat", Red);
		write_pixel_data("Q3_op_green.dat", Green);
		write_pixel_data("Q3_op_blue.dat", Blue);
		break;
		case 6: blue_only();
		write_pixel_data("Q3_op_red.dat", Red);
		write_pixel_data("Q3_op_green.dat", Green);
		write_pixel_data("Q3_op_blue.dat", Blue);
		break;
		case 7: get_pixel();
		break;
		case 8: break;
		default: printf("%s\n", "Please enter a valid input.");
	}
}
	while (instruction!=8);
}



























