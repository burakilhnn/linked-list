#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct node
{
    char* data;
    int count;
    struct node *next;
};

void print_list(struct node* a)
{
    while(a!=NULL)
    {
        printf("%s : %d\n",a->data, a->count);
        a = a->next;
    }
}

void insertToEnd(struct node *a, char* item, int cot)
{
    while(a->next!=NULL)
    {
        a = a->next;
    }
    a->next = (struct node*)malloc(sizeof(struct node));
    a->next->data = item;
    a->next->count = cot;
    a->next->next = NULL;
}

void insertToList(struct node *a, char* item, int cot)
{
    struct node* temp;
    struct node* iter = a;
    while(iter->next->count >= cot)
    {
        iter = iter->next;
    }
    temp = (struct node*)malloc(sizeof(struct node));
    temp->data = item;
    temp->count = cot;
    temp->next = iter->next;
    iter->next = temp;
}

struct node* delete_item(struct node* a, char* item)
{
    struct node* temp;
    struct node* iter = a;
    if( strcmp(a->data, item) == 0)
    {
        temp = a;
        a= a->next;
        free(temp);
        return a;
    }
    while(iter->next !=NULL && strcmp(iter->next->data, item)!= 0)
    {
        iter = iter->next;
    }
    temp = iter->next;
    iter->next = iter->next->next;
    free(temp);
    return a;
}

int compare_words(char* firstWord, char* secondWord)
{
    int result = strcasecmp(firstWord,secondWord);
    if(result == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int count_words(char* item)
{
    FILE *myFile = fopen("text.txt", "r");
    if(myFile == NULL)
    {
        printf("The file does not exist.");
        exit(1);
    }
    char* word;
    int count = 0;
    while(!feof(myFile))
    {
        word = malloc(sizeof(char)*20);
        fscanf(myFile,"%s",word);
        if(strcasecmp(word,item) == 0)
        {
            count++;
        }
    }
    fclose(myFile);
    return count;
}

struct node* insert_sequential(struct node* a, char* item, int cot)
{
    struct node* temp;
    struct node* iter = a;
    struct node* last = a;
    if(a == NULL)
    {
        a = (struct node*)malloc(sizeof(struct node));
        a->data = item;
        a->count = cot;
        a->next = NULL;
        return a;
    }
    if(a->count < cot)
    {
        temp = (struct node*)malloc(sizeof(struct node));
        temp->data = item;
        temp->count = cot;
        temp->next = a;
        return temp;
    }

    while(last->next != NULL)
    {
        last = last->next;
    }
    if(last->count >= cot)
    {
        insertToEnd(a,item,cot);
    }
    else
    {
        insertToList(a,item,cot);
    }
    return a;
}

int main()
{
    struct node* root;
    root = NULL;
    FILE *myFile = fopen("text.txt", "r");
    if(myFile == NULL)
    {
        printf("The file does not exist.");
        exit(1);
    }
    char* word;
    int is_in_list, repeat, compare;
    struct node* iter = root;
    while(!feof(myFile))
    {
        is_in_list = 0;
        word = malloc(sizeof(char)*20);
        fscanf(myFile,"%s",word);
        while(iter != NULL)
        {
            compare = compare_words(word,iter->data);
            if( compare == 1 )
            {
                is_in_list = 1;
                break;
            }
            iter = iter->next;
        }
        if(is_in_list == 0)
        {
            repeat = count_words(word);
            root = insert_sequential(root, word, repeat);
        }
        iter = root;
    }
    fclose(myFile);
    print_list(root);
    return 0;
}
