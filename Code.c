#include<stdio.h>
#include<stdlib.h>
struct list{
    int coefficient;
    int exponent;
    struct list *next;
};
typedef struct list node;
node *start=NULL;

node *getnode(){
    node *newnode;
    newnode=(node*)malloc(sizeof(node));
    printf("Enter coefficient:");
    scanf("%d",&newnode->coefficient);
    printf("Enter exponent:");
    scanf("%d",&newnode->exponent);
    newnode->next=NULL;
    return newnode;
}
//Function for create a list to simplify
node *getnodesimplify(node *ptrexist){
    node *newnode;
    newnode=(node*)malloc(sizeof(node));
    newnode->coefficient=ptrexist->coefficient;
    newnode->exponent=ptrexist->exponent;
    newnode->next=NULL;
    return newnode;
}
//Function for create a list to multiply
node *getnodemultiply(node *ptr1,node *ptr2){
    node *newnode;
    newnode=(node*)malloc(sizeof(node));
    newnode->coefficient=(ptr1->coefficient)*(ptr2->coefficient);
    newnode->exponent=(ptr1->exponent)+(ptr2->exponent);
    newnode->next=NULL;
    return newnode;
}
node *createlist(int n,node *start){
    int i;
    node *newnode;
    node *temp;

    for(i=0;i<n;i++){
        newnode=getnode();
        if(start==NULL){
            start=newnode;
        }else{
            temp=start;
            while(temp->next!=NULL)
                temp=temp->next;
            temp->next=newnode;
        }
    }
    return start;
}
void display(node *start){
    node *ptr;
    ptr=start;
    while(ptr!=NULL){
        printf("coefficient is: %d\n",ptr->coefficient);
        printf("exponent is: %d\n",ptr->exponent);
        ptr=ptr->next;
    }
}

//Simplify function
node *simplify(node *start){
    node *newstart,*ptrexist,*ptr,*newnode;
    ptrexist=start;
    newstart=getnodesimplify(ptrexist);
    do{
        ptrexist=ptrexist->next;
        ptr=newstart;
        do{
            if(ptrexist->exponent==ptr->exponent){
                ptr->coefficient=(ptr->coefficient)+(ptrexist->coefficient);
                break;
            }else if(ptr->next==NULL){
                newnode=getnodesimplify(ptrexist);
                ptr->next=newnode;
                break;
            }else{
                ptr=ptr->next;
            }
        }while(ptr!=NULL);
    }while(ptrexist->next!=NULL);
    return newstart;
}
//Addition function
node *addition(node *start1,node *start2){
    node *ptr,*addition;
    ptr=start1;
    while(ptr->next!=NULL)
        ptr=ptr->next;
    ptr->next=start2;
    addition=simplify(start1);
    return addition;
}
//Multiplication function
node *multiplication(node *start1,node *start2,int n,int m){
    node *ptr1=start1,*ptr2,*newnode,*start3=NULL,*temp,*simpleststart;
    int i,j;
    for(i=0;i<n;i++){
        ptr2=start2;
        for(j=0;j<m;j++){
            newnode=getnodemultiply(ptr1,ptr2);
            if(start3==NULL){
                start3=newnode;
            }else{
                temp=start3;
                while(temp->next!=NULL)
                    temp=temp->next;
                temp->next=newnode;
            }
            ptr2=ptr2->next;
        }
        ptr1=ptr1->next;
    }
    if(start3->next!=NULL){
        simpleststart=simplify(start3);
        return simpleststart;
    }
    else
        return start3;
}
int main(){
    int n,m;
    node *ptr1,*ptr2,*add,*mul;
    //Take details about the first polynomial.
    printf("**********Details about first polynomial***********\n\nHow many terms in the first polynomial? :");
    scanf("%d",&n);
    printf("Please enter coefficients and exponents:\n");
    ptr1=createlist(n,start);

    //Take details about second polynomial.
    printf("**********Details about second polynomial**********\n\nHow many terms in the second polynomial? :");
    scanf("%d",&m);
    printf("Please enter coefficients and exponents:\n");
    ptr2=createlist(m,start);

    printf(".........after addition........\n");
    add=addition(ptr1,ptr2);
    display(add);
    printf(".........after multiplication........\n");
    mul=multiplication(ptr1,ptr2,n,m);
    display(mul);
    return 0;
}
