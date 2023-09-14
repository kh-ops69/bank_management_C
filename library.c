#include "library.h"

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

void hello(void) {
    printf("Hello, World!\n");
}

int callback(void *, int, char **, char **);


int callback(void *NotUsed, int argc, char **argv,
             char **azColName) {

    NotUsed = 0;

    for (int i = 0; i < argc; i++) {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

    return 0;
}