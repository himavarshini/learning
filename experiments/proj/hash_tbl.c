#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct list {
    char *str;
    int hashindx;
    struct list *next;
};

struct hashtbl {
    int size;
    struct list **list;
};

struct hashtbl *table;

void create_hash_tbl(int size)
{
    table = calloc(1, sizeof(*table));

    table->list = calloc(size, sizeof(*(table->list)));

    table->size = size;
}

unsigned int hash(char *str)
{
    unsigned int hashval = 0;

    // hashval = *str + (hashval * 31)
    for (; *str; str++)
        hashval = *str + (hashval << 5) - hashval;

    return hashval % table->size;
}

struct list *lookup_string(char *str)
{
    unsigned int hashindx = hash(str);
    struct list *list;

    for (list = table->list[hashindx]; list; list = list->next) {
         if (strcmp(str, list->str) == 0)
             return list;
    }

    return NULL;
}

int add_string(char *str)
{
    unsigned int hashindx = hash(str);
    struct list *new;
    
    new = lookup_string(str);
    if (new)
        return -1;

    new = calloc(1, sizeof(struct list));
    new->str = strdup(str);
    new->hashindx = hashindx;
    printf("adding before %p %d\n", table->list[hashindx], hashindx);
    new->next = table->list[hashindx]; //
    table->list[hashindx] = new;

    return 0;
}

void display_list()
{
    struct list *printer;
    int i;

    for (i = 0; i < table->size; i++) {
         printer = table->list[i];

         while (printer != NULL) {
              printf("string hash : %s %d\n", printer->str, printer->hashindx);
              printer = printer->next;
         }
    }

}

int main()
{
    int size = 100;

    create_hash_tbl(size);

    add_string("devendra");
    add_string("dndra");
    add_string("dendra");
    add_string("deendra");
    add_string("devendra");
    add_string("deve32432ndra");
    add_string("devendrkfasdkfa");
    add_string("devendrewgweaga");
    add_string("devendaeewvwvra");
    add_string("devendvvewwara");
    add_string("devendvvwwara");
    add_string("devendveae3wgwra");
    add_string("defafvendra");
    add_string("devendra");
    add_string("deveffdsfdsandra");
    add_string("devendrfsfsddaa");
    add_string("devfsadfsdendra");
    add_string("devefasvdsndra");
    add_string("devvxcendra");
    add_string("naga");
    add_string("ine");
    add_string("31131");
    add_string("314234243");
    add_string("2148431431");
    add_string("431431413");

    display_list();

    struct list *t;

    t = lookup_string("devendra");
    if (t)
        printf("ptr %p string %s hash %d\n", t, t->str, t->hashindx);
    t = lookup_string("naga");
    if (t)
        printf("ptr %p string %s hash %d\n", t, t->str, t->hashindx);
    t = lookup_string("ine");
    if (t)
        printf("ptr %p string %s hash %d\n", t, t->str, t->hashindx);
    t = lookup_string("31131");
    if (t)
        printf("ptr %p string %s hash %d\n", t, t->str, t->hashindx);
    t = lookup_string("314234243");
    if (t)
        printf("ptr %p string %s hash %d\n", t, t->str, t->hashindx);
    t = lookup_string("devendran");
    if (t)
        printf("ptr %p string %s hash %d\n", t, t->str, t->hashindx);
    t = lookup_string("2148431431");
    if (t)
        printf("ptr %p string %s hash %d\n", t, t->str, t->hashindx);

    return 0;
}

