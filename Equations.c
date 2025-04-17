#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "ParserExport.h"
#include "MExprcppEnums.h"


// x^2 + y^2 = r^2
//pow(x,2)+pow(y,2)=<CONSTANT>
parse_rc_t circle_eqn(){

    parse_init();

    token_code = cyylex();

    if(token_code != MATH_CPP_POW){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_BRACKET_START){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_VARIABLE){

        RETURN_PARSE_ERROR;
    }

    if(strcmp(lex_curr_token, "x")!=0){
        
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_COMMA){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_INT){

        RETURN_PARSE_ERROR;
    }

    if(strcmp(lex_curr_token, "2")!=0){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_BRACKET_END){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_PLUS){

        RETURN_PARSE_ERROR;
    }

    ////pow(x,2)+pow(y,2)=<CONSTANT>
    token_code = cyylex();

    if(token_code != MATH_CPP_POW){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_BRACKET_START){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_VARIABLE){

        RETURN_PARSE_ERROR;
    }

    if(strcmp(lex_curr_token, "y")!=0)    {

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_COMMA){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_INT){

        RETURN_PARSE_ERROR;
    }

    if(strcmp(lex_curr_token, "2")!=0){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_BRACKET_END){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_EQ){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_INT && 
            token_code != MATH_CPP_DOUBLE){

        RETURN_PARSE_ERROR;
    }

    RETURN_PARSE_SUCCESS;

}

// x^2/a^2 + y^2/b^2 = 1
//pow(x,2)/pow(a,2)+pow(y,2)/pow(b,2)=1
parse_rc_t ellipse_eqn(){

    parse_init();

    token_code = cyylex();

    if(token_code != MATH_CPP_POW){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_BRACKET_START){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_VARIABLE){

        RETURN_PARSE_ERROR;
    }

    if(strcmp(lex_curr_token, "x")!=0){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_COMMA){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_INT){

        RETURN_PARSE_ERROR;
    }

    if(strcmp(lex_curr_token, "2")!=0){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_BRACKET_END){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_DIV){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_POW){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_BRACKET_START){

        printf("hel0");
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_VARIABLE){

        printf("hel1");
        RETURN_PARSE_ERROR;
    }

    if(strcmp(lex_curr_token,"a")!=0){

        printf("hell2");
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_COMMA){

        printf("hell2");
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_INT){

        printf("hel3");
        RETURN_PARSE_ERROR;
    }

    if(strcmp(lex_curr_token, "2")!=0){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_BRACKET_END){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_PLUS){

        RETURN_PARSE_ERROR;
    }

    ////pow(x,2)/pow(a,2)+pow(y,2)/pow(b,2)=1
    token_code = cyylex();
    if(token_code != MATH_CPP_POW){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_BRACKET_START){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_VARIABLE){

        RETURN_PARSE_ERROR;
    }

    if(strcmp(lex_curr_token, "y")!=0){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_COMMA){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_INT){

        RETURN_PARSE_ERROR;
    }

    if(strcmp(lex_curr_token, "2")!=0){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_BRACKET_END){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_DIV){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_POW){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_BRACKET_START){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_VARIABLE){

        RETURN_PARSE_ERROR;
    }

    if(strcmp(lex_curr_token,"b")!=0){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_COMMA){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_INT){

        RETURN_PARSE_ERROR;
    }

    if(strcmp(lex_curr_token, "2")!=0){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_BRACKET_END){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_EQ){

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if(token_code != MATH_CPP_INT){

        RETURN_PARSE_ERROR;
    }

    if(strcmp(lex_curr_token, "1")!=0){

        RETURN_PARSE_ERROR;
    }
    
    RETURN_PARSE_SUCCESS;
}

void Parse_Equations(){

    /*
    parse_rc_t rc = circle_eqn();

    if(rc == PARSE_SUCCESS){
        printf("Eqn of Circle\n");
    }
    */
    parse_rc_t rc = ellipse_eqn();

    if(rc == PARSE_SUCCESS){
        printf("Eqn of Ellipse\n");
    }
}