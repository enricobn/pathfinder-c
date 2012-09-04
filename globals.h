#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef GLOBALS_H_
#define GLOBALS_H_

typedef enum {FALSE, TRUE} boolean;

#define ERROR(...) fprintf(stderr, __VA_ARGS__)

#define NEW_STRUCT_POINTER(STRUCT) (struct STRUCT *) malloc(sizeof(struct STRUCT))

//#define NEW(VAR) (__typeof__( VAR )) malloc(sizeof(__typeof__( VAR )));
#define NEW(TYPE) (TYPE) malloc(sizeof(TYPE));

#endif