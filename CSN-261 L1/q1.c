#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int unusedrollno[10];
int rear=-1;

//! Creating node for linked list.
struct Node {

	int roll_no;
    char Name[50];
    char dob[20];
    char address[100];
    long long int phone_no;
    struct Node *prev;
    struct Node *next;   
};

struct Node* head=NULL;

//! To insert data from the file to the doubly linked list.
void insert(int roll_no, char Name[], char dob[], char address[], long long int phone_no){

	struct Node* new=(struct Node*)malloc(sizeof(struct Node*));

	new -> roll_no = roll_no;
	new -> phone_no = phone_no;
	strcpy(new -> dob, dob);
	strcpy(new -> Name, Name);
	strcpy(new -> address, address);

	if (head==NULL){
	new -> prev = new;
	new -> next = new;
	head = new;		
	}
	else if (new -> roll_no < head -> roll_no){
			new -> prev = head -> prev;
			new -> next = head;
			new -> prev -> next = new;
			head -> prev = new;
			head = head -> prev;
		}
		else if (head -> roll_no < new -> roll_no){
			struct Node* temp = head -> next;
			for (temp = head -> next ; temp != head ; temp = temp -> next){
				if (new -> roll_no < temp -> roll_no){
					new -> prev = temp -> prev;
					new -> next = temp;
					temp -> prev -> next = new;
					temp -> prev = new;
					break; 
				}
			}	
		}
		else {
			head -> prev -> next = new;
			new -> prev = head -> prev;
			new -> next = head;
			head -> prev = new;
		}
}

//! To search a roll number in the doubly linked list.
struct Node* SearchRollNo(int roll_no){
	struct Node* temp = head;
	if (temp -> roll_no == roll_no) return temp;
	else {
		for(temp = head -> next ; temp != head ; temp = temp -> next){
			if (temp -> roll_no == roll_no) return temp;
		}
		return NULL;
	}
}

//! to store the roll numbers deleted from the list.
void StoreUnusedRollNo(int roll_no){
	rear++;
	unusedrollno[rear]=roll_no;	
}

//! To delete a student from the list.
void Delete(int roll_no){
	if (head==NULL) printf("%s\n", "No element is present in the list. \n" );
	struct Node* temp= SearchRollNo(roll_no);
	if (temp == NULL) {
		printf("%s\n","This enrollment number is not prsesent in the list. \n" );
		return;
	}
	if (temp == head) {
		head -> prev -> next = temp -> next;
		temp -> next -> prev = temp -> prev;
		head = temp -> next;
		rear++;
		unusedrollno[rear] = temp -> roll_no; 
		free (temp);
		printf("Enrollment number %d deleted successfully. \n", roll_no );
	}
	else {
		head -> prev -> next = temp -> next;
		temp -> next -> prev = temp -> prev;
		rear++;
		unusedrollno[rear] = temp -> roll_no; 
		free(temp);
		printf("Enrollment number %d deleted successfully.\n", roll_no );
	}
}

//! To swap the data of two nodes.
void Swap_Nodes(struct Node* node1 , struct Node* node2){

	char Name[50], dob[20], address[100];
	int roll_no; long long int phone_no;
    strcpy(Name, node1->Name);
    strcpy(address, node1->address);
    strcpy(dob, node1->dob);
    phone_no = node1->phone_no;
    roll_no = node1->roll_no;

    strcpy(node1->Name, node2->Name);
    strcpy(node1->address, node2->address);
    strcpy(node1->dob, node2->dob);
    node1->phone_no = node2->phone_no;
    node1-> roll_no = node2->roll_no;

    strcpy(node2->Name, Name);
    strcpy(node2->address, address);
    strcpy(node2->dob, dob);
    node2->phone_no = phone_no;
    node2->roll_no = roll_no; 

}

//! To print the contents of the doubly linked list.
void Print_data(){

	struct Node* temp = (struct Node*)malloc(sizeof(struct Node*));
	temp = head;

	printf("Name : %s \n", temp->Name);
    printf("Enrollment no. : %d\n", temp->roll_no);
    printf("Date of Birth : %s \n", temp->dob);
    printf("Contact No. : %lld \n", temp -> phone_no );
    printf("Address : %s \n\n", temp -> address);

    for (temp = head -> next ; temp != head ; temp=temp -> next){
    	printf("Name : %s \n", temp->Name);
        printf("Enrollment no. : %d\n", temp->roll_no);
        printf("Date of Birth : %s \n", temp->dob);
        printf("Contact No. : %lld \n", temp -> phone_no );
        printf("Address : %s \n\n", temp -> address);
    }
}

//! To albhabetically sort the students on the basis of their name.
void sortByName(){

	struct Node* temp1;
    struct Node* temp2;

    if(head == NULL) 
    	printf("No element in the list !");
    temp1 = head;
    int roll_no1; int roll_no2;
    for(temp1 = head ; temp1 -> next != head ; temp1 = temp1 -> next)
    {
    	for(temp2 = temp1 -> next ; temp2 != head ; temp2 = temp2 -> next)
    	{
    		if(strcmp(temp1 -> Name , temp2 -> Name)>0)
    		{
    			Swap_Nodes(temp1,temp2);
    		}
    	}
    }
    printf(" Sorted successfully !\n");
}

//! To modify he contents of any node in the linked list.
void Modify( int roll_no, int instruction , char value[]){

   struct Node* temp = SearchRollNo(roll_no);

   if ( temp == NULL) 
   	{ 
   		printf("Enrollment number not found\n"); 
   		return; 
   	}
    
    if (instruction == 1) 
    	strcpy( temp -> Name , value);
    else if ( instruction == 2) 
    	strcpy( temp -> dob , value);
    else if ( instruction == 3) 
    	strcpy( temp -> address , value);
    else if ( instruction == 4) 
    	temp -> phone_no = atoll(value);
    else 
    	{
    		printf("Please insert valid instruction.\n");
    		return;
    	}

    printf("Given instruction is successfully Updated.\n");
}


int main() {


     int ROLL_NO = 101 ;
     int instruction;
     
    do
    {
     
        printf("%s", "Enter 1 to insert information from file \n");
        printf("%s", "Enter 2 to modify the information\n");
        printf("%s", "Enter 3 to delete some information\n");
        printf("%s", "Enter 4 to sort the students name alphabetically \n");
        printf("%s", "Enter 5 to print the list \n");
        printf("%s", "Enter 6 to exit the program...\n");

        scanf("%d", &instruction);
        int i = 1;

        switch(instruction) {
            case 1: {
                char Name[20], dob[20], address[200];
                long long int phone_no;
                
                char filename[31] = "StudentData.csv";
                char buff_string[1024];
        
                FILE *file = fopen(filename, "r");
                fgets(buff_string, sizeof(buff_string), file); 
                int num;
                printf("Enter the student number whose data you want to insert\n");
                scanf("%d",&num);
                	while( i<=num){
                    fgets(buff_string, sizeof(buff_string), file);
                    char *data = strtok(buff_string, ","); 
                    data = strtok(NULL, ",");
                    strcpy(Name, data);
                    data = strtok(NULL, ",");
                    strcpy(dob, data);
                    data = strtok(NULL, "\"");  
                    strcpy(address, data);
                    data = strtok(NULL, ",");
                    phone_no = atoll(data);
                    i++;
                    }
                    if(rear == -1) { 
                        insert(ROLL_NO, Name, dob, address, phone_no);
                        ROLL_NO++;
                    }
                    else {
                        int enroll = unusedrollno[0];
                        for(int a=0; a < rear ; a++){
                        	unusedrollno[a] = unusedrollno[a+1];
                        	rear--;
                        }
                        insert(enroll , Name, dob, address, phone_no);
                        

                    }
                printf("Information successfully inserted in the list !\n");
                break;
            }
            case 2 : 
            {
                char val[200];
                int roll_no, instruction;

                printf("%s\n", "Enter 1 to change the Name");
                printf("%s\n", "Enter 2 to change the Date of Birth");
                printf("%s\n", "Enter 3 to change the Address");
                printf("%s\n", "Enter 4 to change the Phone Number");
                scanf("%d", &instruction);

                printf("%s\n", "Enter Roll number: ");
                scanf("%d", &roll_no);
                
                printf("%s\n", "Enter new value: ");
                scanf("%s\n",val);
                Modify(roll_no, instruction, val);
                break;
            }

            case 3 : {
                int roll_no;
                printf("%s\n", "Enter Roll number: ");
                scanf("%d", &roll_no);
                StoreUnusedRollNo(roll_no);
                Delete(roll_no);
                break;
            }

            case 4 : {
                sortByName();
                break;
            }    

            case 5 : {
                Print_data();
                break;
            }

            case 6 : {
                return 0;
            }

            default: {
                printf("Please enter a valid instruction.\n");
            }
        }
    }
    while(instruction!=6);            
	return 0;
}









