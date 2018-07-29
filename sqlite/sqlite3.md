# SQLITE3


## intro

### installing

```shell
sudo apt install sqlite3
```

## details

### imoratnt things

1. sql tstatements terminate with semicolon. always place semicolon at the end of every statements
2. sqlite is a command line tool to create / edit / modify db.
3. sqlite database.db creates a databsae
4. some of the useful:

| command | description |
|---------|-------------|
| `.help` | display the help |
| `.tables` | display the tables in the db |
| `.schema items.db` | display the schema of the items.db file |
| `.output filename` | output the contents in the file filename |
| `.mode csv` | prints the contents in csv |

### creating tables

```shell
 $ sqlite3

 sqlite3> .help
```

1. creating elements / inserting elements into tables

```sql
CREATE TABLE tbl1(one varchar(20), two smallint);
```


the variable `one` is of type `varchar` and `two` is of type `smallint`.

2. listing the tables

```sql
.tables
```

3. display schema

```sql
.schema tbl1
```

4. inserting into table

```sql
insert into tbl1 values('dev', 28);
```

5. selecting the statements

```sql
select * from tbl1
```

6. querying the contents in the db

```sql
select one from tbl1 where two like 20;
```

or in caps form

```sql
SELECT one FROM tbl1 WHERE two LIKE 20;
```

7. writing the sqlite table in csv file

```sql
.headers on
.mode csv
.output devnaga.csv
select * from tbl1;
.quit
```

7. count number of elements in the table

```sql
SELECT COUNT(one) FROM tbl1;
```

the `one` is the cfirst column of the table `tbl1`

count all the elements with in the table

```sql
SELECT count(*) from tbl1;
```

1. count the number of tables in the db

```sql
select count (*) from sqlite_master;
```

9.  create simple message logging table..

```sql
CREATE TABLE simplemsg(ts TIMESTAMP, packetlen INTEGER(10), packet BLOB);
```

logging binary content into the above message interface

```sql
INSERT INTO simplemsg VALUES(CURRENT_TIMESTAMP, 10, X'01020304050607080910');
```

10. delete all elements in the table

```sql
DELETE from types;
```

11. delete specific element in the table

```sql
DELETE from tbl1 WHERE argument = 12
```

12. dump all the contents of the db

```sql
dump
```

14. dump a table

```sql
dump tbl1;
```

15. quit sqlite

```sql
.quit
```

16. attaching databases

```sql
 $sqlite3
 sqlite> ATTACH DATABASE "items.db" as "items";
 sqlite> ATTACH DATABASE "test.db" as "test";
 sqlite> .databases    # printing the databases available
```

### sqlite statements


### sqlite programming in C

1. include `sqlite3.h`
2. databse context is `sqlite3`.
3. types in sqlite:

| type  | description |
|-------|-------------|
| SQLITE3_TEXT | string |
| SQLITE_INTEGER | integer |
| SQLITE_FLOAT | float / double |
| SQLITE_BLOB | blob |

4. statements are part of `sqlite3_stmt`.

| name of the function | udescription |
|----------------------|--------------|
| `sqlite3_open` | open the sqlite database |
| `sqlite3_prepare_v2` | prepare the databse.. generate the bytecode of the command | 
| `sqlite3_step` | step through each statement? |
| `sqlite3_close` | close the sqlite database |
| `sqlite3_exec` | execute the sqlite3 statements |
| `sqlite3_column_count` | count number of columns |
| `sqlite3_column_type` | get column type |
| `sqlite3_column_text` |  returns the column text .. |
| `sqlite3_column_int` | returns the integer of the row .. |
| `sqlite3_column_double` | returns the double of the row .. |
| `sqlite3_column_blob` | get blob buf |
| `sqlite3_column_bytes` | get the length of the bytes |


5. sqlite print types


```c
#include <stdio.h>
#include <stdint.h>
#include <sqlite3.h>

int main(int argc, char **argv)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;

    sqlite3_open(argv[1], &db);
    if (!db) {
        return -1;
    }

    sqlite3_prepare_v2(db, "select * from types;", -1, &stmt, NULL);

    while (sqlite3_step(stmt) != SQLITE_DONE) {
        int i;
        int num_cols = sqlite3_column_count(stmt);

        for (i = 0; i < num_cols; i ++) {
            switch (sqlite3_column_type(stmt, i)) {
                case SQLITE3_TEXT:
                    fprintf(stderr, "%s, ", sqlite3_column_text(stmt, i));
                break;
                case SQLITE_INTEGER:
                    fprintf(stderr, "%d, ", sqlite3_column_int(stmt, i));
                break;
                case SQLITE_FLOAT:
                    fprintf(stderr, "%g, ", sqlite3_column_double(stmt, i));
                break;
                case SQLITE_BLOB: {
                    int blob_len;
                    const void *blob_buf;
                    const uint8_t *blob;

                    blob_buf = sqlite3_column_blob(stmt, i);
                    blob_len = sqlite3_column_bytes(stmt, i);

                    blob = blob_buf;

                    int j;

                    fprintf(stderr, "blob> ");
                    for (j = 0; j < blob_len; j ++) {
                        fprintf(stderr, "%02x ", blob[j]);
                    }
                    fprintf(stderr, "\n");
                }
                break;
                default:
                break;
            }
        }
        printf("\n");
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}
```

6. execute sqlite statements

```c
#include <stdio.h>
#include <sqlite3.h>

static int cb(void *unused, int argc, char **argv, char **colname)
{
    int i;

    for (i = 0; i < argc; i ++) {
        printf("%s = %s\n", colname[i], argv[i] ? argv[i]: "NULL");
    }

    printf("\n");
    return 0;
}

int main(int argc, char **argv)
{
    int ret;
    sqlite3 *db;
    char *errmsg = NULL;

    ret = sqlite3_open(argv[1], &db);

    if (!db) {
        return -1;
    }

    char *sql_statement = "SELECT * from simplemsg;";


    ret = sqlite3_exec(db, sql_statement, cb, 0, &errmsg);
    if (ret != SQLITE_OK) {
        return -1;
    }

    sqlite3_close(db);
    return 0;
}
```
