#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sqlite3.h>

struct simple_types {
    int8_t onebyte;
    int16_t twobytes;
    int32_t fourbytes;
    char string[20];
    double double_val;
    float float_val;
    bool cond;
};

struct simple_types types[] = {
    {1, 10, 20, "Hello", 1.44, 4.11, true},
    {1, 11, 20, "Hello", 1.44, 4.11, true},
    {1, 12, 20, "Hello", 1.44, 4.11, true},
    {1, 13, 20, "Hello", 1.44, 4.11, true},
    {1, 14, 20, "Hello", 1.44, 4.11, true},
    {1, 15, 20, "Hello", 1.44, 4.11, true},
    {1, 10, 21, "Hello", 1.44, 4.11, true},
    {1, 10, 22, "Hello", 1.44, 4.11, true},
    {1, 10, 23, "Hello", 1.44, 4.11, true},
    {1, 10, 25, "Hello", 1.44, 4.11, true},
    {1, 10, 26, "Hello", 1.44, 4.11, true},
    {1, 10, 27, "Hello", 1.44, 4.11, true},
    {1, 10, 28, "Hello", 1.44, 4.11, true},
    {1, 10, 29, "Hello", 1.44, 4.11, true},
    {1, 20, 20, "Hello", 1.44, 4.11, true},
    {1, 21, 20, "Hello", 1.44, 4.11, true},
    {1, 22, 20, "Hello", 1.44, 4.11, true},
    {1, 23, 20, "Hello", 1.44, 4.11, true},
    {1, 24, 20, "Hello", 1.44, 4.11, true},
    {1, 25, 20, "Hello", 1.44, 4.11, true},
    {1, 26, 20, "Hello", 1.44, 4.11, true},
    {1, 27, 20, "Hello", 1.44, 4.11, true},
    {1, 10, 11, "Hello", 1.44, 4.11, true},
    {1, 10, 21, "Hello", 1.44, 4.11, true},
    {1, 10, 22, "Hello", 1.44, 4.11, true},
    {1, 10, 23, "Hello", 1.44, 4.11, true},
    {1, 10, 24, "Hello", 1.44, 4.11, true},
    {1, 10, 25, "Hello", 1.44, 4.11, true},
    {1, 10, 26, "Hello", 1.44, 4.11, true},
};

static sqlite3 *db;

static int insert_elements()
{
    // selecting and insertion
    int ret;
    char *select_stmt = "SELECT * FROM types;";

    ret =sqlite3_exec(db, select_stmt, NULL, 0, NULL);
    if (ret != SQLITE_OK) {
        printf("failed to exec %d --> \n", ret);
        return -1;
    }

    char buf[2048];
    int i;

    for (i = 0; i < sizeof(types) / sizeof(types[0]); i ++) {
        memset(buf, 0, sizeof(buf));

        sprintf(buf, "INSERT INTO types values(%d, %d, %d, \"%s\", %f, %f, %d);",
                            types[i].onebyte, types[i].twobytes, types[i].fourbytes,
                            types[i].string, types[i].double_val, types[i].float_val,
                            types[i].cond);
        fprintf(stderr, "buf is %s\n", buf);
        ret = sqlite3_exec(db, buf, NULL, 0, NULL);
        if (ret != SQLITE_OK) {
            printf("failed to exec %d\n", ret);
            return -1;
        }
    }

    return 0;
}

static int attach_databases()
{
    int ret;
    char *attach_db_stmt_items[] = {
        "ATTACH DATABASE \"items.db\" as \"items\";",
        "ATTACH DATABASE \"test.db\" as \"test\";",
    };
    int i;

    for (i = 0; i < sizeof(attach_db_stmt_items) / sizeof(attach_db_stmt_items[0]); i ++) {
        ret = sqlite3_exec(db, attach_db_stmt_items[i], NULL, 0, NULL);
        if (ret != SQLITE_OK) {
            printf("failed to exec %d\n", ret);
            return -1;
        }
    }

    printf("successfully attached\n");
    return 0;
}

static int delete_elements(int element_val)
{
    int ret;
    char *delete_stmt = "DELETE FROM types WHERE int16 = ";
    char exec_buf[2048];

    memset(exec_buf, 0, sizeof(exec_buf));

    sprintf(exec_buf, "%s %d", delete_stmt, element_val);

    printf("exec buf is %s\n", exec_buf);

    ret = sqlite3_exec(db, exec_buf, NULL, 0, NULL);
    if (ret != SQLITE_OK) {
        printf("failed to exec %d\n", ret);
        return -1;
    }

    return 0;
}

int main(int argc, char **argv)
{
    sqlite3_open(argv[1], &db);
    if (!db) {
        fprintf(stderr, "failed to open db %s\n", argv[1]);
        return -1;
    }

    if (!strcmp(argv[2], "insert")) {
        insert_elements();
    } else if (!strcmp(argv[2], "attach")) {
        attach_databases();
    } else if (!strcmp(argv[2], "delete")) {
        delete_elements(atoi(argv[3]));
    }

    return 0;
}
