#include "mexpr_cpp_enums.h"
#include "parser_export.h"

// pow(x,2) + pow(y,2) = <CONSTANT>
parce_rc_t circle_eqn() {
  parse_init();

  int token_code = cyylex();
  if (token_code != MATH_CPP_POW) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_BRACKET_START) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_VARIABLE || strcmp(lex_curr_token, "x") != 0) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_COMMA) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_INT || strcmp(lex_curr_token, "2") != 0) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_BRACKET_END) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_PLUS) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_POW) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_BRACKET_START) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_VARIABLE || strcmp(lex_curr_token, "y") != 0) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_COMMA) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_INT || strcmp(lex_curr_token, "2") != 0) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_BRACKET_END) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_EQ) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_INT && token_code != MATH_CPP_DOUBLE) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != PARSER_EOL) {
    RETURN_PARSE_ERROR;
  }

  RETURN_PARSE_SUCCESS;
}

// pow(x,2)/pow(a,2) + pow(y,2)/pow(b,2) = 1
static bool ellipse_eqn() {
  int token_code = cyylex();
  if (token_code != MATH_CPP_POW) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_BRACKET_START) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_VARIABLE || strcmp(lex_curr_token, "x") != 0) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_COMMA) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_INT || strcmp(lex_curr_token, "2") != 0) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_BRACKET_END) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_DIV) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_POW) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_BRACKET_START) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_VARIABLE || strcmp(lex_curr_token, "a") != 0) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_COMMA) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_INT || strcmp(lex_curr_token, "2") != 0) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_BRACKET_END) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_PLUS) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_POW) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_BRACKET_START) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_VARIABLE || strcmp(lex_curr_token, "y") != 0) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_COMMA) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_INT || strcmp(lex_curr_token, "2") != 0) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_BRACKET_END) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_DIV) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_POW) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_BRACKET_START) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_VARIABLE || strcmp(lex_curr_token, "b") != 0) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_COMMA) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_INT || strcmp(lex_curr_token, "2") != 0) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_BRACKET_END) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_EQ) {
    RETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != MATH_CPP_INT || strcmp(lex_curr_token, "1") != 0) {
    yRETURN_PARSE_ERROR;
  }

  token_code = cyylex();
  if (token_code != PARSER_EOL) {
    RETURN_PARSE_ERROR;
  }

  RETURN_PARSE_SUCCESS;
}

void parse_equations() {
  if (circle_eqn() == RETURN_PARSE_SUCCESS) {
    printf("Equation of Circle\n");
  }

  if (ellipse_eqn() == RETURN_PARSE_SUCCESS) {
    printf("Equation of Ellipse\n");
  }
}
