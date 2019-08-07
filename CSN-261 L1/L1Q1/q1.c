#include <stdio.h>
#include <stdlib.h> 
#include <string.h> 

int unusedRollNumber[50];
int left=-1;
int right=-1;
int intitalRollNumber=101;
 
 struct Student{
     int rollNumber;
     char name[50];
     char dob[10];
     char address[100];
     long phoneNumber;
     struct Student *next;
     struct Student *prev;
 };

 struct Student *head = NULL;

struct Student* find(int rollnumber){
       struct Student *temp=(struct Student*)malloc(sizeof(struct Student));
       temp=head;
       if(head==NULL){
           return NULL;
       }
       if(head->rollNumber==rollnumber){
           return head;
       }
       temp=temp->next;
           while(temp!=head){
             if(temp->rollNumber==rollnumber){
                 return temp;
             }
             temp=temp->next;
           }
           return NULL;
       
 }

void insertIntoQueue(int number){
      if(left==-1){
          left++;
          right++;
          unusedRollNumber[right]=number;
          return;
      }
      right++;
      unusedRollNumber[right]=number;
      return;

}

void delete(int number){
    struct Student *temp=find(number);
    if (temp==NULL){
          printf("%s\n","Invalid Roll Number");
          return;
    }
    struct Student *piche=temp->prev;
    struct Student *aage=temp->next;

    if(temp==head){
        piche->next=aage;
    aage->prev=piche;
    head=aage;
    }
else{
    piche->next=aage;
    aage->prev=piche;
}
    insertIntoQueue(number); // inserts the number into queue as an unused roll number; 
    free(temp);
    return;

}
 void modify(int rollNumber,int id,long number,char stringVal[]){
     struct Student *temp=find(rollNumber);
     if(temp==NULL){
         printf("%s\n","Student not found");
         return; 
     }
      switch (id)
      {
      case 1:{
         strcpy(temp->name,stringVal);
         break;
      }
      case 2:{
          strcpy(temp->dob,stringVal);
          break;
      }
      case 3:{
          strcpy(temp->address,stringVal);
           break;
      }
      case 4:{
          temp->phoneNumber=number;
          break;
      }
      default:
      printf("%s","Invalid input");
          break;
      }

 }

 void insertIntoList(int rollnumber,char Name[],char Dob[],char Address[],long phonenumber){
     struct Student *temp = (struct Student*)malloc(sizeof(struct Student));

     temp->rollNumber=rollnumber;
     strcpy(temp->name,Name);
     strcpy(temp->dob,Dob);
     strcpy(temp->address,Address);
     temp->phoneNumber=phonenumber;

     if(head==NULL){
         temp->next=temp;
         temp->prev=temp;
         head=temp;
     }
     else{
         struct Student *last=head->prev;
         last->next=temp;
         temp->prev=last;
         temp->next=head;
         head->prev=temp;
     }
 }
 void print(){
     struct Student* temp = (struct Student*)malloc(sizeof(struct Student));
    temp = head;    
    int a = 1;
    while(temp != head || a) {
        a = 0;
        printf("%s\n", temp->name);
        printf("%d\n", temp->rollNumber);
        printf("%s\n\n", temp->dob);
        temp = temp->next;
    }
 }

 void swap(struct Student *n1,struct Student *n2){
         int rollnum;
         char n[50];
         char a[100];
         char d[10];
         long phonenum;
        
         rollnum=n1->rollNumber;
         strcpy(n,n1->name);
         strcpy(d,n1->dob);
         strcpy(a,n1->address);
         phonenum=n1->phoneNumber;

         n1->rollNumber=n2->rollNumber;
         strcpy(n1->name,n2->name);
         strcpy(n1->dob,n2->dob);
         strcpy(n1->address,n2->address);
         n1->phoneNumber=n2->phoneNumber;

         n2->rollNumber=rollnum;
         strcpy(n2->name,n);
         strcpy(n2->dob,d);
         strcpy(n2->address,a);
         n2->phoneNumber=phonenum;
 }

 void sortByRoll(){

     struct Student *temp1=head;
     struct Student *temp2=NULL;

     int a=1,b=1;
    
    if(head==NULL){
        printf("%s","No nodes present");
        return;
    }
     while(temp1!=head || a){
         a=0;
         temp2=temp1->next;
         while(temp2!=head || b){
             b=0;
             if(temp1->rollNumber>temp2->rollNumber){
                 swap(temp1,temp2);
             }
             temp2=temp2->next;
         }
         temp1=temp1->next;
     }
 }

 void sort(){
     struct Student *temp1=head;
     struct Student *temp2=NULL;

     int a=1,b=1;

     if(head==NULL){
        printf("%s","No nodes present");
        return;
    }
    while(temp1!=head || a){
         a=0;
         temp2=temp1->next;
         while(temp2!=head || b){
             b=0;
             if(strcmp(temp1->name,temp2->name)>0){
                 swap(temp1,temp2);
             }
             temp2=temp2->next;
         }
         temp1=temp1->next;
     }
    
 }

int main(){
    int choice;
    int i = 1;
    int count=0;

    while(10){
        printf("%s\n","Menu. Please choose option");
        printf("%s\n","1.Insert Student Data(read from file)");
        printf("%s\n","2.Delete Student Data");
        printf("%s\n","3.Sort");
        printf("%s\n","4.Modify Student Data");
        printf("%s\n","5.Print Data");
        printf("%s\n","6.Exit");
        
        scanf("%d",&choice);

        switch(choice){
            case 1:{
            //read from file starts
            count++;
             char Name[50],Dob[10],Address[100];
             long phoneNumber;
             
             char filename[31] = "StudentData.csv";
                char buff[1024];
        
                FILE *fp = fopen(filename, "r");
                for(int i=0;i<count;i++){
                fgets(buff, sizeof(buff), fp); 
                }
                    fgets(buff, sizeof(buff), fp);
                    char *token = strtok(buff, ","); 
                    token = strtok(NULL, ",");
                    strcpy(Name, token);
                    token = strtok(NULL, ",");
                    strcpy(Dob, token);
                    token = strtok(NULL, ",");  
                    strcpy(Address, token);
                    token = strtok(NULL, ",");
                    phoneNumber = atol(token);

                    if(right == -1) { 
                        insertIntoList(intitalRollNumber, Name, Dob, Address, phoneNumber);
                        intitalRollNumber++;
                    }
                    else {
                        int rno = unusedRollNumber[right];
                        unusedRollNumber[right] = 0;
                        insertIntoList(rno , Name, Dob, Address, phoneNumber);
                        right--;
                        sortByRoll();
                    }
                printf("%s", "Successfully Inserted!\n");
                break;
    
        }
           case 2:{
               int number;
               printf("%s\n","Enter roll number to delete");
               scanf("%d",&number);
               delete(number);
               break;
           }
           case 3:{
                sort();
                break;
           }
           case 4:{
           int id;
           long number;
           int rollNumber;
           char stringVal[100];
           printf("%s","Enter Roll Number");
           scanf("%d",&rollNumber);
             printf("%s\n","Choose the field you want to change");
             printf("%s\n","1.Name");
             printf("%s\n","2.Date of Birth");
             printf("%s\n","3.Address");
             printf("%s\n","4.Phone Number");
             scanf("%d",&id);
             printf("%s\n","Enter the value to replace with");
             if(id==4){
                 scanf("%ld",&number);
                 
             }
             else{
                 scanf("%s",stringVal);
             }
             modify(rollNumber,id,number,stringVal);
             sortByRoll();
             break;
           }
           case 5:{
               print();
               break;
           }
           case 6:{
               return 0;
           }
    }
}
}