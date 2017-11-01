#include <stdio.h>
#include <stdlib.h>
int const COUNT = 50;   //数列总数
int const MAX_SIZE = 1000;//数值的最大值

typedef struct
{
    int data;
    struct Node *next;
} Node;

void free_node(Node *node)
{
    if(node == NULL)
        return 0 ;
    if(node->next == NULL)
        free(node);
    else
        free_node(node->next);
}

//核心段
int get_maximum_length(int data[],int start,int pre_number, Node *result_node)
{
    int length1,length2 ;
    length1=length2 = 0;
    if(start >= COUNT)
    {
        return 0;
    }
    if(data[start] > pre_number)
    {
        Node new_node1,new_node2;
        new_node1.next = NULL;
        new_node2.next = NULL;
        length1 = get_maximum_length(data,start+1,data[start],&new_node1)+1;
        length2 = get_maximum_length(data,start+1,pre_number,&new_node2);
        if(length1>length2)//添加当前选取的值进入备份
        {
            Node *add_node = malloc(sizeof(Node));
            add_node->data = data[start];
            add_node->next = new_node1.next;
            result_node->next = add_node;
            free_node(new_node2.next);
            return length1;
        }
        else
        {
            result_node->next = new_node2.next;
            free_node(new_node1.next);
            return length2;
        }
    }
    else
        return get_maximum_length(data,start+1,pre_number,result_node);
}

void print_data(int data[], int size)
{
    for(int i = 0; i<size; i++)
    {
        printf(" %d",data[i]);
    }
    printf("\n");

}

void print_node(Node *node)
{
    while(node != NULL)
    {
        printf(" %d",node->data);
        node = node->next;
    }
}

int main()
{
    int data[COUNT];
    for(int i = 0; i < COUNT ; i++)
    {
        data[i] = rand()%MAX_SIZE;
    }
    print_data(data,COUNT);

    Node result_node ;
    int size = get_maximum_length(data,0,-1,&result_node);
    printf("size = %d\n",size);
    print_node(result_node.next);
    free_node(result_node.next);
    return 0;
}
