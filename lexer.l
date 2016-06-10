%{
#include <stdio.h>
#include "node.h"
#include "parser.h"
#define SAVE_TOKEN yylval.string = strdup(yytext);
#define TOKEN(t) (yylval.token = t)
%}

%option noyywrap

%%

[ \t\n]                           ; // ignore whitespace
"fn"                    return TOKEN(TFN);
[\@a-zA-Z_][a-zA-Z0-9_]*          SAVE_TOKEN; return IDENT;
[\!\=\+\-\|\/\#\$\%\^\&\*]+       SAVE_TOKEN; return IDENT;
[0-9]+\.[0-9]*          SAVE_TOKEN; return DOUBLE;
[0-9]+                  SAVE_TOKEN; return INT;
"("                     return TOKEN(LPAR);
")"                     return TOKEN(RPAR);
"{"                     return TOKEN(LBRC);
"}"                     return TOKEN(RBRC);
"["                     return TOKEN(LSQU);
"]"                     return TOKEN(RSQU);
"."                     return TOKEN(DOT);
","                     return TOKEN(COM);
.                       puts("Unknown token!"); yyterminate();

%%
