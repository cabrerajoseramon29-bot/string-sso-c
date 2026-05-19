#include <stddef.h>
#include <stdio.h>
#include "cli.h"
#include "../core/vector/vector.h"
#include "../core/string/string_sso.h"
#include "../logic/filters.h"
#include "../logic/sort.h"

/* prototipos internos */
static void getNum(const char *msg, size_t *num){
    int c;
    printf("%s\n", msg);

    while (scanf("%zu", num) != 1) {
        printf("Error. You must enter a number..\n> ");
        while((c = getchar()) != '\n' && c != EOF);
    }
    while((c = getchar()) != '\n' && c != EOF);
}

static size_t readDim(void){
    size_t num;
    getNum("Enter the number of elements the vector will contain.:", &num);
    return num;
}

static size_t readLon(void){
    size_t num;
    getNum("Enter the length (number of characters) of the words to search for.:", &num);
    return num;
}

static String *readPrefix(void){
    String *prefix = string_create();
    if(!prefix){
        string_destroy(prefix);
        return NULL;
    }
    printf("Enter the prefix to search for.:\n");
    
    string_read(prefix);
    return prefix;
}

static void print(Vector *v){
    size_t n = vector_size(v);

    if (n > 0) {
        printf("%zu word(s) found.:\n",n);
    }else{
        printf("No results found..\n");
        return;
    }
    for (size_t i = 0; i < n; i++) {
        String **ptr = vector_get(v, i);
        String *s = *ptr;

        printf("%zu- %s\n",i+1, string_c_str(s));
    }
}

static void release(Vector *v){
    size_t n = vector_size(v);

    for (size_t i = 0; i < n; i++) {
        String **ptr = vector_get(v, i);
        String *s = *ptr;

        string_destroy(s);
    }
    vector_destroy(v);
}

static void menu(Vector *list){
    size_t option = 0;
    
    while (1) {
        getNum("\nEnter the desired option.:\n"
            "1- Filter by size\n2- Filter by length\n3- Filter by prefix\n4- Exit", &option);
    
        switch (option) {
            case 1:{
                Vector *filtered = filter_by_length(list);
                insertion_sort_strings(filtered);
                print(filtered);
                vector_destroy(filtered);
                break;               
            }
            case 2:{
                size_t len = readLon();
                Vector *filtered = filter_by_exact_length(list, len);
                insertion_sort_strings(filtered);
                print(filtered);
                vector_destroy(filtered);
                break;
            }
            case 3:{
                String *prefix = readPrefix();
                Vector *filtered = filter_by_prefix(list, prefix);
                insertion_sort_strings(filtered);
                print(filtered);
                string_destroy(prefix);
                vector_destroy(filtered);
                break;
            }
            case 4:{
                printf("Leaving ...\n");
                return;
            }
            default:{
                printf("Error. A valid option must be entered..\n");
            }
        }
    }
    
}


/* ================= ENTRY ================= */

void cli_run(void) {
    size_t dim = readDim();
    Vector *list = create_list(dim);
    if(!list){
        fprintf(stderr, "Error creating the list.\n");
        return;
    }

    menu(list);

    release(list);
}
