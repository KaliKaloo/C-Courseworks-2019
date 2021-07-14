#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct node{
    int data;                
    struct node *next; 
}node;

typedef struct list{ //list of children a node has
    int numchild;         //number of children in list
    node *firstChild;      //first node in list of children
}list;

typedef struct Network{
    int nodeNum;         //number of vertices
    list *arrayOflist;     //array of the list of children
}Network;

node* makeNode(int m);
Network *makeNetwork(int n);
void addLink(Network*n, int source, int desti);
int maxNode(char a[]);
int uniqueNodes(char a[]);
void printNetwork(Network*n);
double averageChild(Network *n);
void freeNetwork(Network* n);
void checkuniqueNodes();
void build ();
void test();

//MAIN---------------------------------------------------

int main(int n, char *argv[n]){
    if (n==1){
        test ();
        return 0;
    }
    else if (n>2){
      printf("Please input like this: ./network 1-2,1-3,2-4\n");
      return 1;
      }
    int length = strlen(argv[1]);
    int numnode = uniqueNodes( argv[1]);
    int max = maxNode(argv[1]);

    Network* net = makeNetwork(numnode);
    for(int i=0; i<length-1;i++){
        if (argv[1][i] == '-'){
            int source = atoi(&argv[1][i-1]);
            int desti = atoi(&argv[1][i+1]);
            addLink(net, source, desti);
        }
        else if ((argv[1][i-1]=='.') && (argv[1][i+1]=='.')){
            int source = atoi(&argv[1][i]);
            int desti = source;
            addLink(net, source, desti);
        }
    }
    printf("\nDirected network\n");
    printf("> Nodes and their children:");
    printNetwork(net);
    printf("  %d:\n",max);
    printf("\n> Number of nodes: %d\n", net->nodeNum);
    printf("\n> Node with max value is: %d\n", max);
    double averageAmountChild = averageChild(net);
    printf("\n> Average number of children: %f\n\n", averageAmountChild);
    freeNetwork(net);
    return 0;
}


//FUNCTIONS----------------------------------------------

node* makeNode(int data){
    node *newNode = malloc(sizeof(node));
    newNode->data = data;
    newNode->next = NULL;
    
    return newNode;}

Network *makeNetwork(int n){
    Network* network = malloc(sizeof(Network));
    network->nodeNum = n;
    network->arrayOflist = (list*)malloc(sizeof(list)*n);

    for(int i = 0; i < n; i++){
        network->arrayOflist[i].numchild = 0; //number of children is 0 at first
        network->arrayOflist[i].firstChild = NULL;} //firstChild node in all list is NULL
    return network;
}

void addLink(Network*n, int source, int desti){
    node* newNode = makeNode(desti);
    newNode->next = n->arrayOflist[source].firstChild;
    n->arrayOflist[source].firstChild = newNode;  //the firstChild child in the list of children for source is desti(newnode)
    n->arrayOflist[source].numchild = (n->arrayOflist[source].numchild) +1; //increase num of children for source by 1
}

int maxNode(char a[]){
    int length = strlen(a);

    char first = a[0];
    int max = first -'0';
    for(int i =0; i<=length; i++){
        if (a[i] !='-' || a[i]!=',' || a[i]!='\0'){
            int point = a[i]-'0';
            if (max < point){
                max = point;}
            }
        }
    return max;}

int uniqueNodes(char a[]){
    int n = strlen(a);
    int nodeNum = 1; 

    for (int i = 1; i < n; i++) { 
        if((a[i]!= '-') && (a[i]!=',')){
        int p = 0; 
        for (p = 0; p < i; p++) 
            if ((a[p]!= '-') && (a[p]!=',') && (a[i] == a[p])) //for each character, compare it with the other characters
                break; 
        if (i == p) 
            nodeNum++; }
    } 
    return nodeNum; 
} 

void printNetwork(Network*n){
    int k = n->nodeNum;
    for (int i = 1; i < (k); i++){
        node* hold = n->arrayOflist[i].firstChild; //hold points to first node in the list of children for node i
        printf("\n  ");
        printf("%d: ", i);
        while (hold){
            printf("%d,", hold->data);
            hold = hold->next;
        }}printf("\n");
}

double averageChild(Network *n){
    double sum = 0;
    for (int i=0; i<n->nodeNum; i++){;
        sum = sum + (n->arrayOflist[i].numchild);
    }
    double average = sum/(n->nodeNum);
    return average;
}

void freeNetwork(Network* n){
    if(n){
        if(n->arrayOflist){
            for (int i = 0; i < (n->nodeNum); i++){ 
                node* hold = n->arrayOflist[i].firstChild; //holds first child in list
                while (hold){
                    node* temp = hold;  //temporarily hold first child in list
                    hold = hold->next; //holds next child in list
                    free(temp);}} //frees previous child
            free(n->arrayOflist);}
        free(n);}
}



//TEST----------------------------------------------------

void whichLine(int line, bool x) {
  if (x){
    return;}
  else{  
  printf("The test on line %d fails.\n", line);}
  exit(1);
}

void checkUniqueNodes(){
    whichLine(__LINE__, uniqueNodes("1") == 1);
    whichLine(__LINE__, uniqueNodes("1-2,1-3,1-4") == 4);
    whichLine(__LINE__, uniqueNodes("1,2,3") == 3);
    whichLine(__LINE__, uniqueNodes("1,----2") == 2);
}

void build (){
    int n=5;
    Network *p = makeNetwork(n);
    whichLine(__LINE__, p->nodeNum == n);
    addLink(p, 1 , 2);
    whichLine(__LINE__, p->arrayOflist[1].numchild == 1);
    addLink(p, 1 , 3);
    whichLine(__LINE__, p->arrayOflist[1].numchild == 2);
    whichLine(__LINE__, p->arrayOflist[1].firstChild->data == 3);

    addLink(p, 2 , 3);
    whichLine(__LINE__, p->arrayOflist[2].numchild == 1);
    addLink(p, 2 , 4);
    whichLine(__LINE__, p->arrayOflist[2].numchild == 2);
    whichLine(__LINE__, p->arrayOflist[1].firstChild->data == 3);

}

void test(){
  checkUniqueNodes();
  build();
  printf("All tests passed \n");
}
