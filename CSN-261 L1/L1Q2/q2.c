#include <stdio.h>
#include <stdlib.h>

int front=-1;
int rear=-1;
int size=0;
int *dequeue;

//! Initialising the deque.
void create_dequeue(int data){
	size=1;
	dequeue=(int*)malloc(sizeof(size*sizeof(int)));
	front=0;
	rear=0;
	dequeue[0]=data;
}
//! Insert an element in the deque from the front.
void insert_front(){
	int data;
	printf("%s\n","Insert the number to be added" );
	scanf("%d", &data);
	if (size==0) {
		create_dequeue(data);
		return;
	}
	if (rear==size-1){
		size*=2;
		dequeue=(int*)realloc(dequeue, sizeof(size*sizeof(int)));
	}
		int i=rear;
		while(i>=0){
			dequeue[i+1]=dequeue[i];
			i--;
		}
		dequeue[front]=data;
		rear++;
}

//! Insert an element in the deque from the rear.
void insert_rear(){
	int data;
	printf("%s\n","Insert the number to be added" );
	scanf("%d", &data);
	if (size==0) {
		create_dequeue(data);
	}
	if (rear==size-1){
		size*=2;
		dequeue=(int*)realloc(dequeue, sizeof(size*sizeof(int)));
	}
	rear++;
	dequeue[rear]=data;
}

//! Delete the front element of the deque.
void delete_front(){
	for(int i=0;i<rear;i++){
		dequeue[i]=dequeue[i+1];
	}
	rear--;
	if(rear+1==size/2){
		size=size/2;
		dequeue=(int*)realloc(dequeue, sizeof(size*sizeof(int)));
	}
}

//! Delete the rear element of the deque.
void delete_rear(){
	dequeue[rear]=0;
	rear--;
	if(rear+1==size/2){
		size=size/2;
		dequeue=(int*)realloc(dequeue, sizeof(size*sizeof(int)));
	}
}

//! Print the size and contents of the deque.
void print(){
	for(int i=0;i<=rear;i++){
        printf("%d ", dequeue[i]);
    }
    printf("The size of the deque is %d bytes.", size*4 );
    putchar('\n');

}

int main(){
	int instruction;
	do {
		printf("%s\n", "1-Insert in Front" );
	printf("%s\n", "2-Insert in Rear" );
	printf("%s\n", "3-Delete from front" );
	printf("%s\n", "4-Delete from Rear");
	printf("%s\n", "5-Print the dequeue");
	printf("%s\n", "6-End the Program");
	scanf("%d", &instruction);
	switch(instruction){
		case 1: insert_front();
		break;
		case 2: insert_rear();
		break;
		case 3: delete_front();
		break;
		case 4: delete_rear();
		break;
		case 5: print();
		break;

		case 6: break;
		default : printf("%s\n", "Please enter a valid input.");
	}
}
	while(instruction!=6);
	return 0;
}































