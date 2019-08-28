/**
* @file l3q2.c
* @brief This program finds the triplets according to the given question.
* @author Deepanshu Matia
* @Date 21/8/2019
*/

#include <stdio.h>
#include <stdlib.h>


struct Node { 
    int data; 
    struct Node* next; 
}; 

//* To print the input array of numbers.
void print_list(struct Node* head) {
     struct Node* current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

//* Main function.
int main(){
     
    struct Node* Head =NULL;
    int n;
    printf("Enter the numbers of integers!");
    scanf("%d",&n);
    printf("Enter the %d integers in order!",n);
    int dp[n]; 

    //* To give input in the linear list.
    for (int i=0;i<n;i++){
    	struct Node * temp = Head;
    	if ( temp == NULL)
    	{
    		struct Node * first_node  = (struct Node*)malloc(sizeof(struct Node));
    		scanf("%d",&(first_node -> data));
    		Head = first_node;
    		first_node ->next = NULL;
    	}
    	else {
    		while(temp -> next!=NULL){
                 temp = temp ->next;
    		}
    		temp ->next =(struct Node*)malloc(sizeof(struct Node));
    		int x;
    		scanf("%d",&(temp ->next->data));
    		temp ->next->next = NULL;
    	}
    }
    
    printf("This is the given list of numbers \n");
    print_list(Head);
    printf("These are the triplets ( i,j,k ) which follows the given condition!\n");
    struct Node * temp  = Head;
    if(Head != NULL){
         dp [0] = Head ->data;
         temp = temp ->next;
         for (int i=1;i<n;i++){
    	      dp[i] = dp [i-1]^(temp ->data);
    	      temp = temp ->next;
         }
    }

    //* To print all the triplets following the conditions.
    for (int j=1;j<n;j++){
        for (int k=j;k<n;k++){
            if (dp[j-1] == (dp[j-1]^dp[k]))
            {
                printf("( %d, %d, %d )\n",(1),(j+1),(k+1));
            }
        }
    }

    for (int i=1;i<n-1;i++)
        for (int j=i+1;j<n;j++)
            for (int k=j;k<n;k++){
                if ((dp[j-1]^dp[i-1]) == (dp[j-1]^dp[k]))
                {
                    printf("( %d, %d, %d )\n",(i+1),(j+1),(k+1));
                }
            }
	return 0;
}










