/***********************************************************************/
/* Student Name: Panagiotis Goulas, Student ID: 886001                 */
/* Assignment 1: Subject: Algorithms and Data Structures - Comp20003   */
/* Time and Date Submitted: 7/9/2018                                   */

/*                        Programming is Fun                           */
/***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

/* debuger from 
https://github.com/ChuanyuanLiu/SchoolStuff/blob/master/Algorithms/recipes.md
which is from Design of Algorithms
*/
#define DEBUG 0
#if DEBUG
#define DUMPINT(x) printf("line %3d: %s = %d\n", __LINE__, #x, x)
#else
#define DUMPINT(x)
#endif

#if DEBUG
#define DUMPSTR(x) printf("line %3d: %s = |%s|\n", __LINE__, #x, x)
#else
#define DUMPSTR(x)
#endif

/* Constansts */
#define MAXLENGTHSTR 512
#define MAXCHAR      128
#define ONE            1
#define NOMAXELEMENTS 15

#define ID             0
#define NAME           1
#define SEX            2
#define AGE            3
#define HEIGHT         4
#define WEIGHT         5
#define TEAM           6
#define NOC            7
#define GAMES          8
#define YEAR           9
#define SEASON        10
#define CITY          11
#define SPORT         12
#define EVENT         13
#define MEDAL         14

/***********************  Structs ***************************************/
typedef struct node node_t;

/* inspired and used material from Grady's workshop No 4 youtube and LMS code*/

struct node
{
    char data[NOMAXELEMENTS][MAXCHAR];
    node_t *left;
    node_t *right;
    char title[MAXCHAR];
};

/***********************  Function Prototypes ***************************/
void print_data(char data[NOMAXELEMENTS][MAXCHAR], FILE *write_file);

/* print the data once it is found */
void print_data(char data[NOMAXELEMENTS][MAXCHAR], FILE *write_file)
{
    fprintf(write_file,
        "%s --> ID: %s Sex: %s || Age: %s || Height: %s ||"
        "Weight: %s || Team: %s || NOC: %s || Games: %s || Year: %s || Season:"
        "%s || City: %s || Sport: %s || Event: %s ||"
        "Medal: %s ||\n",
        data[NAME],data[ID],data[SEX],data[AGE],data[HEIGHT],data[WEIGHT],
        data[TEAM], data[NOC], data[GAMES], data[YEAR],data[SEASON],
        data[CITY],data[SPORT],data[EVENT],data[MEDAL]);
}

/* Malloc space for a 'node' struct */
node_t *create_node()
{
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    if (new_node == NULL)
    {
        fprintf(stderr, "Out of memory!!! (create_node)\n");
        exit(1);
    }

    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/* Free the space for a 'node' struct */
void freeNode(node_t *node)
{
    if (node->left) {
        freeNode(node->left);
    }
    if (node->right) {
        freeNode(node->right);
    }
    free(node);
}

/* 
    The function you are to write. Takes a parent pointer (null for the root),
    and returns the tree with the child in the right position. Returns the
    item in a new tree with null left/right pointers.
*/
node_t *bstInsert(node_t *parent, node_t *newNode)
{
    /* Write this function */
    node_t **insertLocation = &parent;
    /* keep looking for the place to insert */
    while (*insertLocation)
    {
        int result = strcmp(newNode->title, ((*insertLocation)->title));
        if (result > 0)
        {
            insertLocation = &(((*insertLocation)->right));
        }
        else
        {
            insertLocation = &(((*insertLocation)->left));
        }
    }
    *insertLocation = newNode;
    return parent;
}

/* search */
node_t *bstSearch(node_t *parent, char input[MAXCHAR], FILE *write_file)
{
    /* Write this function. */
    node_t **insertLocation = &parent;
    int not_found = 1;
    int no_comparis = 0;

    /* keep looking for the place to insert */
    while (*insertLocation)
    {
        DUMPSTR((*insertLocation)->title);
        DUMPSTR(input);

        int result = strcmp(input, ((*insertLocation)->title));
        DUMPINT(result);
        no_comparis += 1;
        if (result > 0)
        {
            insertLocation = &(((*insertLocation)->right));
        }
        else if (result < 0)
        {
            insertLocation = &(((*insertLocation)->left));
        }
        else
        {
            not_found = 0;
            print_data((*insertLocation)->data, write_file);
            insertLocation = &(((*insertLocation)->left));
        }
    }
    /* if not print NOTFOUND */
    if (not_found)
    {
        fprintf(write_file, "%s -- > NOTFOUND\n", input);
    }

    printf("%s -- > %d\n", input, no_comparis);
    return parent;
}

int main(int argc, char *argv[])
{
    char str[MAXLENGTHSTR];
    /* open file assert if you can read it and use fgets and strcpy and*/
    /* strtok to get the required input from the csv                   */
    /*  from https://www.tutorialspoint.com/cprogramming/c_file_io.htm */
    FILE *newfile;
    newfile = fopen(argv[ONE], "r");
    assert(newfile);
    char *token;

    node_t *root = NULL;

    /* FROM TUTORIALS POINT.COM */
    /* https://www.youtube.com/watch?v=WKUYJ8jTca4 */
    while (fgets(str, MAXLENGTHSTR, newfile) != NULL)
    {
        node_t *node = create_node();
        int count = 0;

        /* get the first token */
        token = strtok(str, ",");

        /* walk through other tokens */
        while ((token != NULL) & (count != NOMAXELEMENTS))
        {
            strcpy(node->data[count], token);
            if (count == MEDAL)
            {
                if (node->data[count][strlen(token) - 1] == '\n')
                {
                    node->data[count][strlen(token) - 1] = '\0';
                }
            }
            if (count == NAME)
            {
                strcpy(node->title, token);
            }
            token = strtok(NULL, ",");
            count += 1;
        }

        /* insert the node */
        root = bstInsert(root, node);
    }

    /* open file */
    FILE *write_file;
    write_file = fopen(argv[2], "w");
    assert(write_file);

    /* search */
    char input[MAXCHAR];
    while (fgets(input, MAXCHAR, stdin) != NULL)
    {
        if (input[strlen(input) - 1] == '\n') {
        input[strlen(input) - 1] = '\0';
        }
        bstSearch(root, input, write_file);
    }

    return 0;
    /* All Done!!                                     */
    /* I hope it works like a charm !!                */
}
/*                        Programming is Fun                           */
