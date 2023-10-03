#include <iostream>
#include <algorithm>
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
  int len = 0;
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

void create_vertex(graph &g, int v);

void remove_vertex(graph &g, int x, in_deg_ar &arr);
void permute(graph& g);

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

  add_directedEdge(G, 5, 0);
  add_directedEdge(G, 4, 0);
  add_directedEdge(G, 3, 0);
  add_directedEdge(G, 2, 3);
  add_directedEdge(G, 2, 4);
  add_directedEdge(G, 2, 1);
  add_directedEdge(G, 3, 5);
  add_directedEdge(G, 0, 6);

  display_graph(G);

  permute(G);

	return 0;
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
	if(g.vertices == NULL){
		return;
	}
  node_2 *temp = g.vertices;
  if (temp->vertex == x)
    g.vertices = temp->next;

  else
  {
    while (temp->next != NULL)
    {
      if (temp->next->vertex == x)
      {
		auto temp2 = temp->next->next_child;
		while(temp2!=NULL)
		{
			arr.a[temp2->member]--;
			temp2=temp2->next_child;
		}
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

int find(int arr[7], int key){
	for(int i=0; i<7; ++i){
		if(arr[i] == key)
			return i;
	}
	return -1;
}

void permute(graph& g){
  int array[7] = {0, 1, 2, 3, 4, 5, 6};

  do{
	  bool in_lexocological_order = true;
	  for(int i = 0; i<7; ++i){
      int task = array[i];
      node_2 *temp = g.vertices;

      bool all_prerequisites_done = true;
      while (temp != NULL)
      {
        if (temp->vertex == task)
        {
          auto temp2 = temp->next_child;
          while(temp2!=NULL)
          {
            int task_prerequisite = temp2->member;
            if(find(array, task_prerequisite) > i){
              all_prerequisites_done = false;
              break;
            }
            temp2=temp2->next_child;
          }
          break;
        }
        temp = temp->next;
      }
      if(all_prerequisites_done == false){
        in_lexocological_order = false;
        break;
      }
	  }
	  if(in_lexocological_order){
		  for(int i = 0; i<7; ++i){
			  cout << array[i] << ", ";
		  }
		  cout<<endl;
	  }
  }while(next_permutation(array, array+7));

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
