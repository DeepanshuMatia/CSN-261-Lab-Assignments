/**
* @file comparefiles.c
* @brief The program compares whether the input file and the decrypted file are the same.
* @author Deepanshu Matia
* @Date 7/8/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//! method to find the size of the file
int findSize(char file_name[]) 
{  
    FILE* fp = fopen(file_name, "r"); 
  
   
    if (fp == NULL) { 
        printf("File Not Found!\n"); 
        return -1; 
    } 
  
    fseek(fp, 0L, SEEK_END); 
  
    // calculating the size of the file 
    int res = ftell(fp); 
  
    // closing the file 
    fclose(fp); 
  
    return res; 
} 

//! Main function
int main(int argc, char *argv[])
{	

	FILE *f1 = fopen(argv[1], "r");

	int length = findSize(argv[1]);

    char str[length];
    char str2[length];

    //! Storing the data of the input file in the string.
	for (int i = 0; i < length; i++ ){
		str [i] = fgetc(f1);
	}
	fclose(f1);

		//! Storing the data of the decrypted file in the string.
		FILE *f2 = fopen(argv[2], "r");
		for (int j=0; j<length; j++){
			str2[j] = fgetc(f2);
		}
		fclose(f2);

		//! Comparing the data of the files and printing the answer.
		for (int a = 0; a<length ; a++){
			if (str[a] != str2[a]){
				printf("%s\n", "The files do not match." );
				return 0;
			}
		}
		printf("%s\n", "The files match successfully!");
		return 0;
}































