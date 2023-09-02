#include "library.h"

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void hello(void) {
    printf("Hello, World!\n");
}

int callback(void *, int, char **, char **);

int main(void) {

    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("test.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "DROP TABLE IF EXISTS Cars;"
                "CREATE TABLE Cars(Id INT, Name TEXT, Price INT);"
                "INSERT INTO Cars VALUES(1, 'Audi', 52642);"
                "INSERT INTO Cars VALUES(2, 'Mercedes', 57127);"
                "INSERT INTO Cars VALUES(3, 'Skoda', 9000);"
                "INSERT INTO Cars VALUES(4, 'Volvo', 29000);"
                "INSERT INTO Cars VALUES(5, 'Bentley', 350000);"
                "INSERT INTO Cars VALUES(6, 'Citroen', 21000);"
                "INSERT INTO Cars VALUES(7, 'Hummer', 41400);"
                "INSERT INTO Cars VALUES(8, 'Volkswagen', 21600);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    int last_id = sqlite3_last_insert_rowid(db);
    printf("The last Id of the inserted row is %d\n", last_id);

    char *sql1 = "SELECT * FROM Cars";
    rc = sqlite3_exec(db, sql1, callback, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    char *sql2 = "SELECT Id, Name FROM Cars WHERE Id = ?";

    sqlite3_stmt *res;
    rc = sqlite3_prepare_v2(db, sql2, -1, &res, 0);

    if (rc == SQLITE_OK) {

        sqlite3_bind_int(res, 1, 5);// represents res, 1(default arg), and the id which we want to receive material from
    } else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    if (step == SQLITE_ROW) {

        printf("%s: ", sqlite3_column_text(res, 0));
        printf("%s\n", sqlite3_column_text(res, 1));

    }

    sqlite3_finalize(res);

    sqlite3_close(db);

    return 0;
}

int callback(void *NotUsed, int argc, char **argv,
             char **azColName) {

    NotUsed = 0;

    for (int i = 0; i < argc; i++) {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

    return 0;
}