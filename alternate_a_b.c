#include "mexpr_cpp_enums.h"
#include "parser_export.h"

// A->aB
// B->bA|b|ba

parse_rc_t A();
parse_rc_t B();

// A->aB
parse_rc_t A() {
  parse_init();

  token_code = cyylex();
  if (token_code != MATH_CPP_VARIABLE || strcmp(lex_curr_token, "a") != 0) {
    RETURN_PARSE_ERROR;
  }

  err = B();
  if (err == PARSE_ERR)
    RETURN_PARSE_ERROR;

  return PARSE_SUCCESS;
}

parse_rc_t B() {
  parse_init();

  do {
    // B->bA
    token_code = cyylex();

    if (token_code != MATH_CPP_VARIABLE || strcmp(lex_curr_token, "b") != 0) {
      yyrewind(1);
      break;
    }

    err = A();
    if (err == PARSE_ERR) {
      yyrewind(1);
      break;
    }

    RETURN_PARSE_SUCCESS;
  } while (0);

  do {
    // B->b
    token_code = cyylex();

    if (token_code != MATH_CPP_VARIABLE || strcmp(lex_curr_token, "b") != 0) {
      yyrewind(1);
      break;
    }

    RETURN_PARSE_SUCCESS;
  } while (0);

  do {
    // B->ba
    token_code = cyylex();

    if (token_code != MATH_CPP_VARIABLE || strcmp(lex_curr_token, "b")) {
      yyrewind(1);
      break;
    }

    token_code = cyylex();

    if (token_code != MATH_CPP_VARIABLE || strcmp(lex_curr_token, "a")) {
      yyrewind(2);
      break;
    }

    RETURN_PARSE_SUCCESS;
  } while (0);

  RETURN_PARSE_ERROR;
}
