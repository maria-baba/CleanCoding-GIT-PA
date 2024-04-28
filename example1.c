/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/
/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa
#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
}NODE;
typedef struct graph
{
    int value;
    int *vis;
    struct Node **adjacency_list;
}GPH;

NODE *create_node(int value)
{
    NODE *new_node = (NODE *)malloc(sizeof(NODE));

    new_node->data = value;
    new_node->next = NULL;

    return new_node;
}
void add_edge(GPH *graph, int src, int dest)
{
    NODE *new_node = create_node(dest);
    new_node->next = graph->adjacency_list[src];
    graph->adjacency_list[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_list[dest];
    graph->adjacency_list[dest] = new_node;
}
GPH *create_graph(int value)
{
    GPH *graph = (GPH *)malloc(sizeof(GPH));
    graph->value = value;
    graph->adjacency_list = malloc(sizeof(NODE *) * value);
    graph->vis = calloc(value,sizeof(int));

    for (int i = 0; i < value; i++)
    {
        graph->adjacency_list[i] = NULL;
        graph->vis[i] = 0;
    }
    return graph;
}
void DFS(GPH *graph, int v_nr)
{
    NODE *adj_list = graph->adjacency_list[v_nr];
    NODE *aux = adj_list;
    graph->vis[v_nr] = 1;
    printf("%d ", v_nr);
    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (graph->vis[con_ver] == 0)
        {
            DFS(graph, con_ver);
        }
    aux = aux->next;
    }
}
void insert_edges(GPH *graph, int edg_nr, int nrv)
{
    int src;
    int dest;
    printf("Adauga %d munchii (de la 0 la %d)\n", edg_nr, nrv - 1);
    for (int i = 0; i < edg_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(graph, src, dest);
    }
}
int is_path(GPH *graph, int start_node, int end_node)// 0 sau 1 daca poate fi sau nu ajuns
{
    DFS(graph, start_node);
    if(graph->vis[start_node] == 1 && graph->vis[end_node] == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int main()
{
    int number_of_vertices;
    int edge_nr;
    int start_node;
    int end_node;

    printf("Cate noduri are graful?\n");
    scanf("%d", &number_of_vertices);

    printf("Cate muchii are graful?\n");
    scanf("%d", &edge_nr);

    GPH *graph = create_graph(number_of_vertices);

    insert_edges(graph, edge_nr, number_of_vertices);

    printf("Introduceti nodul de start: ");
    scanf("%d", &start_node);

    printf("Introduceti nodul de destinatie: ");
    scanf("%d", &end_node);

    printf("Parcurgerea cu DFS:\n");
    int path = is_path(graph, start_node, end_node);
    if(path)
        printf("\nExista drum intre nodul %d si %d", start_node, end_node);
    else
        printf("\nNu exista drum intre nodul %d si %d", start_node, end_node);
}