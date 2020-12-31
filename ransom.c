#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);


//struct of a node
typedef struct node
{
    char *data;
    int counter;
    struct node *next;
} node_t;

//struct of a list
struct list
{
    node_t *head;
    node_t *tail;
};

//create new node and insert one word to the data.
node_t *create_node(char *data)
{
    node_t *node1 = malloc(sizeof(node_t));
    node1->next = NULL;
    node1->data = NULL;
    if (node1==NULL)
    {
    return NULL;
    }
    node1->data = data;
    node1->counter = 1;
    return node1;
}

//create new list and put head node in its head.
struct list *create_new_list(node_t *head)
{
struct list *list1=malloc(sizeof(*list1));
    list1->head = NULL;
    list1->tail = NULL;
if (list1==NULL)
    {
    return NULL;
    }
list1->head=head;
list1->tail=head;
return list1;
}

//add new word to the list. if the word exists +1 to the counter of 
//the word's node. else -> create a new node in the tail of list.
bool append_list(struct list* list1, char *word)
{

		node_t *temp_node;
        temp_node = list1->head;
        bool found = false;
        char *temp_data;
        
        //checks if the word exists in the list already.
        while((temp_node) && !found)
        {
           
        temp_data=temp_node->data;
            if(!(strcmp(temp_data,word)))
            {
                (temp_node->counter)++;
                
                
                found = true;
            }
            else
            {
            temp_node=temp_node->next;
            }
            }
        //if the word isn't in the list, enter and add a new node to the list.
        if(!found)
        { 
            node_t *node1 = create_node(word);
            if (node1==NULL)
            {
                return false;
            }
            list1->tail->next = node1;
            list1->tail = node1;
        }
  return true;      
}

//free all mallocs strting the head of the list.
void free_all(node_t *list_head)
{
    while(list_head)
    {
        node_t *temp = list_head;
        list_head = list_head->next;
        free(temp);
    }
}


//building a list out of the words in the array.
struct list *build_list(int count,char **word_arr)
{
	bool ok = true;
    node_t *node1=create_node(word_arr[0]);
	if (node1==NULL)
	{
	   return NULL;
	}
	
    struct list *list1=create_new_list(node1);
    if (list1==NULL)
    {
        return NULL;
    }
    for(int i=1; i<count;i++)
    {
        ok = append_list(list1, (word_arr[i]));
    }
    if(ok)
    {
        return list1;
    }else
    {
        return NULL;
    }
}

//return true if word is in magazine_words otherwise return false.
bool find_word(node_t *word,struct list *magazine_words){
	
    node_t *temp_magazine = magazine_words->head;
    //checking all the nodes in magazine_words;
    while((temp_magazine))
    {
        if(!strcmp(temp_magazine->data, word->data)){
        	int magazine_counter=temp_magazine->counter;
        	int word_counter=word->counter;
        	
            if(magazine_counter>=word_counter)
            {
                return true;
            }else
            {
            
                return false;
            }
        }
        else
        {
            temp_magazine = temp_magazine->next;
        }
    }
    
    return false;
}


//return true if all the word in note_words is in magazine_words
//otherwise return false.
bool can_write_note(struct list *magazine_words,struct list *note_words)
{
	if (note_words==NULL)
    {
		return false;
    }
	if(note_words->head == NULL)
    {
        return false;
    }	
    node_t *temp_note = note_words->head;
    bool can_write = true; //turn to false if one ofthe words can't be writen
    //in the note


    //enter if we didnt reach to the end of the list and all the words so far
    //can be writen in the note/
    while((temp_note!=NULL) && can_write)
    {
        can_write = find_word(temp_note, magazine_words);
        temp_note=temp_note->next;
    }
    
    return can_write;
}

// Complete the checkMagazine function below.
void checkMagazine(int magazine_count, char **magazine, int note_count,
 char **note)
    {
    struct list *magazine_words = build_list(magazine_count, magazine);
    if(magazine_words == NULL)
    {
        return;
    }
    struct list *note_words = build_list(note_count, note);
    if(note_words == NULL)
    {
        free_all(magazine_words->head);
        return;
    }
    bool answer = can_write_note(magazine_words, note_words);
    if(answer)
    {
        printf("Yes");
    }else
    {
       printf("No");
    }
    free_all(magazine_words->head);
    free_all(note_words->head);
    free(magazine_words);
    free(note_words);
}

int main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;
 checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
