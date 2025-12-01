#ifndef _PARSER_EXPORT_
#define _PARSER_EXPORT_

#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAX_MEXPR_LEN 512
#define MAX_STRING_SIZE 512

typedef struct lex_data {
  int token_code;
  int token_len;
  char *token_val;
} lex_data_t;

typedef struct stack {
  int top;
  lex_data_t data[MAX_MEXPR_LEN];
} stack_t;

extern "C" int yylex();

extern char lex_buffer[MAX_STRING_SIZE];
extern stack_t undo_stack;
extern char *lex_curr_token;
extern int lex_curr_token_len;
extern char *curr_ptr;
extern int cyylex();
extern void yyrewind(int n);
extern void parser_stack_reset();
extern void lex_set_scan_buffer(const char *buffer);
extern void RESTORE_CHECKPOINT(int check);

#define CHECKPOINT(check) check = undo_stack.top

#endif