/**
* @file transpose.c
* @brief The program encrypts a text file using a given encryption key
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
    if (argc != 5) {
        printf("%s\n", "Please enter correct number of arguments." );
        return 0;
    }

	int n, a, b;
	n = atoi(argv[1]);
	a = atoi(argv[2]);
	b = atoi(argv[3]);

    if (n < 1){
        printf("%s\n", "Encryption is not possible for this value of n.");
        return 0;
    }

    int x = findSize(argv[4]);

    //! Finding the length of the string to make it a multiple of n.
    int length; 
    if ( x % n == 0) length = x;
    else {
    	length = x + n - x%n;
    }

    char str[length];

    //! Entering the file data into the character array.
    FILE *fp = fopen(argv[4], "r");
    if (fp == NULL){
        printf("%s\n", "Please enter a valid filename.");
        return 0;
    }
    for (int k =0 ; k < length; k++){
        str[k] = fgetc(fp);
    }
    fclose(fp);
    
    //! Creating a new string that contains the encrypted code.
    char str2[length];
    for (int j=0; j < length/n ;j++ ){
    for (int i = 0; i < length; i++)
    {
    	str2[i + n*j] = str[(a*i+b)%n + n*j];
    }
}

    //! Creating an output file with the encrypted code. 
    FILE* fptr;
    fptr = fopen("outputfile.txt", "w");
    for (int i=0;i<length;i++)
    fprintf(fptr,"%c",str2[i]);
    fclose(fptr);
    return 0;
}

