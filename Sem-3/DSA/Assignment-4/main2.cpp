#include <iostream>
using namespace std;

#define size 7

typedef struct node_1
{
  int member;
  node_1 *next_child = NULL;

} node_1;

typedef struct node_2
{
  int vertex;
  node_2 *next = NULL;
  node_1 *next_child = NULL;

} node_2;

typedef struct graph
{
  node_2 *vertices = NULL;
  int len;
} graph;

typedef struct in_deg_ar
{
  int a[size]={0};
  int len=0;
} in_deg_ar;

typedef struct stack
{
  int arr[size] = {0};
  int len=0;
} stack;

// Functions declaration
// void create_Empty_Queue(queue *q);
// void enqueue(queue *q, int x);
// int dequeue(queue *q);
// void print_queue(queue *q);
void create_vertex(graph &g, int v);

void remove_vertex(graph &g, int x, in_deg_ar &arr);

void add_directedEdge(graph &g, int a, int b);
void in_degree(graph g, in_deg_ar &arr);
void sort(graph g, stack q, in_deg_ar a);
void display_graph(graph &g);


void push(int i,stack &q)
{
  q.arr[q.len]=i;
  q.len++;
}

void print_q(stack q)
{
  for(int i=0;i<q.len;i++)
  {
    cout<<q.arr[i]<<"  ";
  }
  cout<<endl;
}

int main()
{

  graph G;
  G.len = 7;

  int i;
  in_deg_ar ina;
  ina.len = size;

  for (i = 0; i < G.len; i++)
  {
    create_vertex(G, i);
  }

  add_directedEdge(G, 0, 5);
  add_directedEdge(G, 0, 4);
  add_directedEdge(G, 0, 3);
  add_directedEdge(G, 3, 2);
  add_directedEdge(G, 4, 2);
  add_directedEdge(G, 1, 2);
  add_directedEdge(G, 5, 3);
  add_directedEdge(G, 6, 0);

  display_graph(G);

  in_degree(G, ina);

  cout << endl
       << "Indegree: ";
  for (int j = 0; j < size; ++j)
  {
    cout << ina.a[j] << " ";
  }
  cout << endl;

  // remove_vertex(G, 1, ina);
  // display_graph(G);

  // in_degree(G, ina);
  // cout << endl
  //      << "Indegree: ";
  // for (int j = 0; j < size; ++j)
  // {
  //   cout << j<<"-"<<ina.a[j] << " ";
  //   cout<<endl;
  // }
  // cout << endl;

  // cout << endl;
  // sort(G, in_deg_arr ina);

  // cout << endl;
  // for (int j = 0; j < G.len; ++j)
  // {
  //   cout << in_deg_ar;r[j] << " ";
  // }

  stack q;

  cout<<endl;

  sort(G,q,ina);


}


void create_vertex(graph &g, int v)
{
  node_2 *new_ver = new node_2;
  new_ver->vertex = v;
  new_ver->next_child = NULL;
  new_ver->next = g.vertices;

  g.vertices = new_ver;
}

// We assumed that only vertex with indegree 0
// is being removed
void remove_vertex(graph &g, int x, in_deg_ar &arr)
{
  node_2 *temp = g.vertices;

  if (temp->vertex == x)
    g.vertices = temp->next;

  else
  {
    while (temp->next != NULL)
    {
      if (temp->next->vertex == x)
      {
        
        temp->next = temp->next->next;
        break;
      }
      temp = temp->next;
    }
  }
  
  arr.a[x] = -1;
  g.len--;
}


void add_directedEdge(graph &g, int a, int b)
{

  node_2 *temp = g.vertices;
  while (temp->vertex != a)
    temp = temp->next;

  node_1 *new_mem = new node_1;
  new_mem->member = b;
  new_mem->next_child = temp->next_child;
  temp->next_child = new_mem;
}


void in_degree(graph g, in_deg_ar &arr)

{
  int i;
  for(i=0; i<size; i++)
  {
    if(arr.a[i] != -1)
      arr.a[i] = 0;
  }
  node_2* temp = g.vertices;
  while (temp!= NULL)
  {
    node_1 *x = temp->next_child;

    while (x != NULL)
    {
      arr.a[x->member]++;
      x = x->next_child;
    }
    temp = temp->next;
  }
}


void sort(graph g, stack q, in_deg_ar a)
{
  in_deg_ar temp = a;
  graph G = g;
  stack c = q;

  for(int i=0; i<a.len; i++)
  {
    g=G;
    a=temp;
    q=c;
    if(a.a[i]==0)
    { 
      remove_vertex(g,i,a);
      push(i,q);
      //display_graph(g);
      in_degree(g, a);
      cout << endl << "Indegree: ";
       for (int j = 0; j < size; ++j)
      {
        cout << j<<"-"<<a.a[j] << " ";
        cout<<endl;
       }
      cout << endl;

      print_q(q);
      
      
      if(q.len < size)
      {
       sort(g,q,a);
      }

      else
      {
       print_q(q);
      }
    } 
  }   
}     
      

void display_graph(graph &g)
{
  cout << " Vertex  ->  Directed Edge " << endl;

  node_2 *temp1 = g.vertices;
  while (temp1 != NULL)
  {
    cout << "   " << temp1->vertex << " -> ";
    node_1 *temp2 = temp1->next_child;

    while (temp2 != NULL)
    {
      cout << temp2->member << " , ";
      temp2 = temp2->next_child;
    }

    cout << endl;
    temp1 = temp1->next;
  }
}
