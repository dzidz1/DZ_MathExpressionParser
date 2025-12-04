#ifndef _PARSER_EXPORT_
#define _PARSER_EXPORT_

#include <assert.h>
#include <stdio.h>
#include <string.h>

typedef enum parse_rc { PARSE_ERR, PARSE_SUCCESS } parse_rc_t;

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

#define RETURN_PARSE_ERROR                                                     \
  {                                                                            \
    RESTORE_CHECKPOINT(_lchkp);                                                \
    return PARSE_ERR;                                                          \
  }

#define RETURN_PARSE_SUCCESS return PARSE_SUCCESS

#define parse_init()                                                           \
  int token_code = 0;                                                          \
  int _lchkp = undo_stack.top;                                                 \
  parse_rc_t err = PARSE_SUCCESS

#define PARSER_LOG_ERR(token_obtained, expected_token)                         \
  printf("%s(%d) : Token Obtained = %d (%s) , expected token = %d\n",          \
         __FUNCTION__, __LINE__, token_obtained, lex_curr_token,               \
         expected_token)

#endif