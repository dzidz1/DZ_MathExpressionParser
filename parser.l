%{
#include "mexpr_cpp_enums.h"
#include "parser_export.h"


extern void parse_equations();
extern parse_rc_t A();
extern parse_rc_t C();
stack_t undo_stack = {-1, {0, 0, 0}}; // top = -1 when stack is empty
char lex_buffer[MAX_STRING_SIZE];
char *curr_ptr = lex_buffer;
char *lex_curr_token = NULL;
int lex_curr_token_len = 0;

static void lex_push(lex_data_t lex_data) {
    assert(undo_stack.top < MAX_MEXPR_LEN - 1);
    undo_stack.data[++undo_stack.top] = lex_data;
    lex_curr_token = (char *)lex_data.token_val;
    lex_curr_token_len = lex_data.token_len;
}

static lex_data_t lex_pop() {
    assert(undo_stack.top > -1);
    lex_data_t peek = undo_stack.data[undo_stack.top];
    undo_stack.top--;

    if(undo_stack.top > -1) {
        lex_data_t *stack_top = &undo_stack.data[undo_stack.top];
        lex_curr_token = stack_top->token_val;
        lex_curr_token_len = stack_top->token_len;
    } else {
        lex_curr_token = NULL;
        lex_curr_token_len = 0;
    }

    return peek;
}

void parser_stack_reset() {
    for(int i = 0; i < undo_stack.top; i++) {
        lex_data_t *lex_data = &undo_stack.data[i];
        lex_data->token_code = 0;
        lex_data->token_len = 0;
        if(lex_data->token_val) {
            free(lex_data->token_val);
            lex_data->token_val = NULL;
        }
    }

    undo_stack.top = -1;
    curr_ptr = lex_buffer;
    lex_curr_token = NULL;
    lex_curr_token_len = 0;
}

void lex_set_scan_buffer(const char *buffer) {
    yy_scan_string(buffer);
}


static void process_white_space(int n) {
    lex_data_t lex_data;
    lex_data.token_code = PARSER_WHITE_SPACE;
    lex_data.token_len = n;
    lex_data.token_val = NULL;
    lex_push(lex_data);
    curr_ptr += n;
}


int cyylex() {
    int token_code = yylex();

    lex_data_t lex_data;
    lex_data.token_code = token_code;
    lex_data.token_len = yyleng;
    lex_data.token_val = (char *)malloc(yyleng + 1);
    assert(lex_data.token_val != NULL);
    memcpy(lex_data.token_val, yytext, yyleng);
    lex_data.token_val[yyleng] = '\0';

    lex_push(lex_data);
    curr_ptr += yyleng;
    
    return token_code;
}

/* argument n represents the number of non-space tokens that should be removed */
void yyrewind(int n) {
    if(n <= 0 || curr_ptr == lex_buffer) return;
    int data_len = 0;
    lex_data_t lex_data;
    while(n > 0) {
        lex_data = lex_pop();
        data_len += lex_data.token_len;
        if(lex_data.token_code == PARSER_WHITE_SPACE) continue;
        n--;
        lex_data.token_code = 0;
        lex_data.token_len = 0;
    }
    curr_ptr -= data_len;
    yy_scan_string(curr_ptr);
}

void RESTORE_CHECKPOINT(int check) {
    while(undo_stack.top > check) {
        lex_data_t lex_data = lex_pop();
        curr_ptr -= lex_data.token_len;

        if(lex_data.token_val) {
            free(lex_data.token_val);
            lex_data.token_val = NULL;
        }
    }

    yy_scan_string(curr_ptr);
}

%}



/* Definitions */
DIGIT    [0-9]
INTEGER  {DIGIT}+
DOUBLE   {DIGIT}+\.{DIGIT}+
LETTER   [a-zA-Z_]
IDENT    {LETTER}({LETTER}|{DIGIT})*

%%

[ ]              { process_white_space(1); }

[ \t]+          { process_white_space(yyleng); }

"\n"            { return PARSER_EOL; }

"("             { return MATH_CPP_BRACKET_START; }
")"             { return MATH_CPP_BRACKET_END; }
","             { return MATH_CPP_COMMA; }

"<="            { return MATH_CPP_LESS_THAN_EQ; }
">="            { return MATH_CPP_GREATER_THAN_EQ; }
"!="            { return MATH_CPP_NEQ; }
"<"             { return MATH_CPP_LESS_THAN; }
">"             { return MATH_CPP_GREATER_THAN; }
"="             { return MATH_CPP_EQ; }

"and"           { return MATH_CPP_AND; }
"or"            { return MATH_CPP_OR; }

"sqrt"          { return MATH_CPP_SQRT; }
"sqr"           { return MATH_CPP_SQR; }
"mmax"          { return MATH_CPP_MAX; }
"mmin"          { return MATH_CPP_MIN; }
"sin"           { return MATH_CPP_SIN; }
"cos"           { return MATH_CPP_COS; }
"pow"           { return MATH_CPP_POW; }

"*"             { return MATH_CPP_MUL; }
"/"             { return MATH_CPP_DIV; }
"%"             { return MATH_CPP_MOD; }
"+"             { return MATH_CPP_PLUS; }
"-"             { return MATH_CPP_MINUS; }

{INTEGER}       { return MATH_CPP_INT; }
{DOUBLE}        { return MATH_CPP_DOUBLE; }
{IDENT}         { return MATH_CPP_VARIABLE; }

.               { printf("Unrecognized character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

int main(int argc, char **argv) {
    while(1) {
        printf("Input->   ");
    
        if(fgets(lex_buffer, sizeof(lex_buffer), stdin) == NULL) {
            break;
        }

        if(lex_buffer[0] == '\n') {
            continue;
        }

        lex_set_scan_buffer(lex_buffer);

        
        //parse_rc_t err = A();
        parse_rc_t err = C();
        if(err == PARSE_ERR) {
            printf("rejected\n");
        } else {
            printf("accepted\n");
        }

        printf("parsed string: \n");
        for(int i = 0; i < undo_stack.top; i++) {
            lex_data_t *lex_data = (lex_data_t *)&undo_stack.data[i];
            printf("%s", lex_data->token_val);
        }

        parser_stack_reset();
        printf("\n");
    }

    return 0;
}