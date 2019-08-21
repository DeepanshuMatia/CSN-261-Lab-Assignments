/**
* @file MAT.c
* @brief To represent any region in its quadtree form.
* @author Deepanshu Matia
* @Date 7/8/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


int n ;   //! order of the input array.
int I =0;int I2=0;  //! indexes used in the recursion tree.
int ** arr1;   //! input array
int ** arr2;   //! output array.

//! to print the quad tree in node form. 
void printtree(int s, int i, int j)
{
   bool x = true;
   int num = arr1[i][j];
    for(int p = i ; p < s+i; p++)
    for(int q = j ; q < s+j;q++)
    {
        if(arr1[p][q] != num)
            x = false;
      }

   if (x){
       int bit = arr1[i][j];
       I2 = I2+1;    
       int l = log2(n/s);
       printf("%d             %d              %d\n",I2,bit,l);
       return;
    }
    printtree(s/2, i, j );
    printtree(s/2, i, j+s/2 );
    printtree(s/2, i+s/2, j );
    printtree(s/2, i+s/2, j+s/2 );
}

//! to print the output  maximal array.
void outputarray(int s, int i, int j)
{  
   bool x = true;
   int num = arr1[i][j];
    for(int p = i ; p < s+i; p++)
    for(int q = j ; q < s+j;q++)
    {
        if(arr1[p][q] != num)
            x = false;
      }

   if (x){
       I = I+1;    
       for (int p = i;p < i+s ;p++)
          for (int q = j; q < j+s;q++)
              arr2[p][q] = I;
       return;
    }
    outputarray(s/2, i, j );
    outputarray(s/2, i, j+s/2 );
    outputarray(s/2, i+s/2, j );
    outputarray(s/2, i+s/2, j+s/2 );
}

//! method to find the order of the input array.
int size(FILE *input){
    int t = 0;
    while(getc(input) != '\n')
        t++;
    t = (t-1) /2;
    return t;
  }


//! Main function.
int main(){

    FILE * input = fopen ("L2_P2_inputsample.txt","r");
    int x = size(input);
    fclose(input);
    n = pow(2,ceil(log2(x)));
    arr1 = (int **)malloc(n*sizeof(int*));
    for (int i =0;i<n;i++){
    	arr1[i] = (int *)malloc(n*sizeof(int));
    }
    arr2 = (int **)malloc(n*sizeof(int*));
    for (int i =0;i<n;i++){
    	arr2[i] = (int *)malloc(n*sizeof(int));
    }
    for (int i=0;i<n;i++)
    	for (int j=0;j<n;j++)
    		arr1[i][j] = 0;
    FILE * input2 = fopen ("L2_P2_inputsample.txt","r");
    for (int i= n-x-1;i<n;i++)
    	for (int j=n-x-1;j<n;j++)
    		{
    			if (j!= n-1)
    				fscanf(input2,"%d",&arr1[i][j]);
    			else 
    				fscanf(input2,"%d\n",&arr1[i][j]);
    		}
    fclose(input2);
        outputarray(n, 0, 0);
        
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<n;j++)
                printf("%d ",arr2[i][j]); 
            printf("\n");
        }
        
        printf("%s      %s      %s\n","Leafnode", "Bitvalue","Level ");
        printtree(n, 0, 0);

    return 0;
}


