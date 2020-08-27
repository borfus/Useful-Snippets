#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXTOKENLEN 64
#define MAXTOKENS 100
#define pop stack[top--]
#define push(s) stack[++top] = s

struct token {
    char type;
    char string[MAXTOKENLEN];   
};

int top = -1;
struct token stack[MAXTOKENS];
struct token this;

enum type {
    TYPE, QUALIFIER, IDENTIFIER
};

// UTILITY
enum type classify_string() {
    char *s = this.string;
    if (strcmp(s, "const") == 0) {
        strcpy(s, "read-only");
        return QUALIFIER;
    }
    if (strcmp(s, "volatile") == 0) { return QUALIFIER; }
    if (strcmp(s, "void") == 0) { return TYPE; }
    if (strcmp(s, "char") == 0) { return TYPE; }
    if (strcmp(s, "signed") == 0) { return TYPE; }
    if (strcmp(s, "unsigned") == 0) { return TYPE; }
    if (strcmp(s, "short") == 0) { return TYPE; }
    if (strcmp(s, "int") == 0) { return TYPE; }
    if (strcmp(s, "long") == 0) { return TYPE; }
    if (strcmp(s, "float") == 0) { return TYPE; }
    if (strcmp(s, "double") == 0) { return TYPE; }
    if (strcmp(s, "struct") == 0) { return TYPE; }
    if (strcmp(s, "union") == 0) { return TYPE; }
    if (strcmp(s, "enum") == 0) { return TYPE; }
    return IDENTIFIER;
}

void gettoken() {
    char *p = this.string;

    while ((*p = getchar()) == ' '); // read past spaces

    if (isalnum(*p)) {
        while (isalnum(*++p=getchar()));
        ungetc(*p, stdin);
        *p = '\0';
        this.type = classify_string();
        return;
    }

    if (*p == '*') {
        strcpy(this.string, "pointer to");
        this.type = '*';
        return;
    }
    this.string[1] = '\0';
    this.type = *p;
    return;
}

void read_to_first_identifier() {
    gettoken();
    while (this.type != IDENTIFIER) {
        push(this);
        gettoken();
    }
    printf("%s is ", this.string);
    gettoken();
}

// PARSING

void deal_with_arrays() {
    while (this.type == '[') {
        printf("array ");
        gettoken();
        if (isdigit(this.string[0])) {
            printf("0..%d ", atoi(this.string) - 1);
            gettoken();
        }
        gettoken();
        printf("of ");
    }
}

void deal_with_function_args() {
    while (this.type != ')') {
        gettoken();
    }
    gettoken();
    printf("function returning ");
}

void deal_with_pointers() {
    while (stack[top].type == '*') {
        printf("%s ", pop.string);
    }
}

void deal_with_declarator() {
    switch (this.type) {
        case '[':
            deal_with_arrays();
            break;
        case '(':
            deal_with_function_args();
    }

    deal_with_pointers();

    while (top >= 0) {
        if (stack[top].type == '(') {
            pop;
            gettoken();
            deal_with_declarator();
        } else {
            printf("%s ", pop.string);
        }
    }
}

int main() {
    read_to_first_identifier();
    deal_with_declarator();
    printf("\n");
    return 0;
}

