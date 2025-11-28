%{
#include "mexpr_cpp_enums.h"
#include <stdio.h>
#include <string.h>

extern "C" int yylex();
extern char lex_buffer[512];


char lex_buffer[512];
%}



/* Definitions */
DIGIT    [0-9]
INTEGER  {DIGIT}+
DOUBLE   {DIGIT}+\.{DIGIT}+
LETTER   [a-zA-Z_]
IDENT    {LETTER}({LETTER}|{DIGIT})*

%%

[ \t]+          { /* Skip whitespace */ }

"\n"            { return PARSER_EOL; }

"("             { return MATH_CPP_BRACKET_START; }
")"             { return MATH_CPP_BRACKET_END; }
","             { return MATH_CPP_COMMA; }

"<="            { return MATH_CPP_LESS_THAN_EQ; }
">="            { return MATH_CPP_GREATER_THAN_EQ; }
"!="            { return MATH_CPP_NEQ; }
"<"             { return MATH_CPP_LESS_THAN; }
">"             { return MATH_CPP_GREATER_THAN; }
"=="            { return MATH_CPP_EQ; }

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
        
        yy_scan_string(lex_buffer);

        int token_code;
        while((token_code = yylex()) != PARSER_EOL) {
            printf("token code = %d, token = %s, token_len = %d\n", 
                   token_code, yytext, yyleng);
        }
        printf("\n");
    }

    return 0;
}