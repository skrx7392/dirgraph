#include <iostream>
#include <stddef.h>

using namespace std;

class Graph {
private:
    bool** adjacencyMatrix;
    int vertexCount;

public:
    Graph(int vertexCount) {
        this->vertexCount = vertexCount;
        adjacencyMatrix = new bool *[vertexCount];
        for (int i=0; i<vertexCount; i++){
            adjacencyMatrix[i] = new bool [vertexCount];
            for (int j=0; j<vertexCount; j++){
                adjacencyMatrix[i][j] = false;
            }
        }
    }

    ~Graph() {
        for (int i=0; i<vertexCount; i++)
            delete[] adjacencyMatrix[i];
        delete[] adjacencyMatrix;
    }

    void addEdge(int, int);
    void removeEdge(int, int);
    bool isEdge(int, int);
    enum vertexState {White, Gray, Black};
    void DFS();
    void runDFS(int u, vertexState state[]);
    void BFS();
};

class queue_class{
public:
    int rear,front,a[10];

    queue_class()   // Constructor method
    {
        rear=0;
        front=0;
    }
    void insert(int s) // Function to add the elements to the queue
    {  if(rear==8)
        cout<<"queue is full";
       else
       { a[rear]=s;
        rear=rear+1;
       }
     }
    int remove()    //Function to remove elements from the queue
    {
        if(front==rear)
           return -1;
        else
          return a[front++];
   }
};

void Graph::addEdge(int i, int j) {
    if (i>=0 && i<vertexCount && j>=0 && j<vertexCount) {
        adjacencyMatrix[i][j] = true;
        //adjacencyMatrix[j][i] = true;
    }
}

void Graph::removeEdge (int i, int j) {
    if (i>=0 && i<vertexCount && j>=0 && j<vertexCount) {
        adjacencyMatrix[i][j] = false;
        //adjacencyMatrix[j][i] = false;
    }
}

bool Graph::isEdge (int i, int j) {
    if (i>=0 && i<vertexCount && j>=0 && j<vertexCount) {
        return adjacencyMatrix[i][j];
    }
    else
        return false;
}

void Graph::DFS(){
    vertexState *state = new vertexState[vertexCount];
    for (int c=0; c<vertexCount; c++) {
        state[c] = White;
    }
    runDFS(0, state);
    for(int counter=0; counter<vertexCount; counter++){
       if(state[counter]==White){
            runDFS(counter, state);
       }
    }
    delete [] state;
}

void Graph::runDFS(int u, vertexState state[]){
    state[u] = Gray;
    char ordering[8];
    ordering[0]='x';
    ordering[1]='s';
    ordering[2]='w';
    ordering[3]='y';
    ordering[4]='v';
    ordering[5]='t';
    ordering[6]='z';
    ordering[7]='u';
    cout << ordering[u] << " ";
    for (int v=0; v<vertexCount; v++){
        if (isEdge(u,v) && state[v] == White)
            runDFS(v, state);
    }
    state[u] = Black;
}

void Graph::BFS()
{
    int visitedNode[10]={0,0,0,0,0,0,0,0,0,0},i,node,j,k=0;
    queue_class bfsQueue;
    visitedNode[0]=1;
    bfsQueue.insert(0);
    node=bfsQueue.remove();
    while(node!=-1){
        cout<<node<<" ";
        for(i=node,j=0;j<8;j++)
        {
            if(isEdge(i,j)==1 & visitedNode[j]==0)
            {
                bfsQueue.insert(j);
                visitedNode[j]=1;
            }
        }
        node=bfsQueue.remove();
 }
}

int main() {

    Graph myGraph(8);

    myGraph.addEdge(0,1);
    myGraph.addEdge(0,3);
    myGraph.addEdge(0,4);
    myGraph.addEdge(1,2);
    myGraph.addEdge(1,4);
    myGraph.addEdge(2,0);
    myGraph.addEdge(3,4);
    myGraph.addEdge(3,5);
    myGraph.addEdge(4,2);
    myGraph.addEdge(5,4);
    myGraph.addEdge(6,3);
    myGraph.addEdge(6,5);
    myGraph.addEdge(6,7);
    myGraph.addEdge(7,4);

    int a, b;
    for(a=0; a<=7; a++){
        cout<<endl;
        for(b=0; b<=7; b++){
            cout << " " << myGraph.isEdge(a,b);
        }
    }
    cout << endl << endl;
    cout << "DFS of the tree is: ";
    myGraph.DFS();
    cout << endl << endl;
    cout << "BFS of the tree is: ";
    myGraph.BFS();
    cout << endl;
    return 0;
}

