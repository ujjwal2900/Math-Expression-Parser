#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ParserExport.h"
#include "MExprcppEnums.h"

parse_rc_t A();
static parse_rc_t B();

//Implemented the below grammar, which accepts strings consisting of alternate a's and b's
//B-> bA|b|ba

parse_rc_t B()
{
    parse_init();

    //B->bA
    do{

        token_code= cyylex();

        if(token_code != MATH_CPP_VARIABLE){
            yyrewind(1);
            break;
        }

        if(strcmp(lex_curr_token, "b")!=0){
            yyrewind(1);
            break;
        }

        err = A();

        if(err == PARSE_ERR){
            yyrewind(1);
            break;
        }
        
        RETURN_PARSE_SUCCESS;   
    }while(0);

    //B->b
    do{

        token_code = cyylex();

        if(token_code != MATH_CPP_VARIABLE){
            yyrewind(1);
            break;
        }

        if(strcmp(lex_curr_token, "b") != 0){
            yyrewind(1);
            break;
        }

        RETURN_PARSE_SUCCESS;
    }while(0);

    //B-> ba
    do{

        token_code = cyylex();

        if(token_code != MATH_CPP_VARIABLE){
            yyrewind(1);
            break;
        }
        if(strcmp(lex_curr_token, "b") != 0){
            yyrewind(1);
            break;
        }

        token_code = cyylex();

        if(token_code != MATH_CPP_VARIABLE){
            yyrewind(2);
            break;
        }
        if(strcmp(lex_curr_token, "a") != 0){
            yyrewind(2);
            break;
        }

        RETURN_PARSE_SUCCESS;
        
    }while(0);

    RETURN_PARSE_ERROR;
}

//A-> aB
parse_rc_t A()
{
    parse_init();

    token_code = cyylex();

    if(token_code != MATH_CPP_VARIABLE)
    {
        RETURN_PARSE_ERROR; 
    }

    if(strcmp(lex_curr_token,"a") != 0){

        RETURN_PARSE_ERROR;
    }

    err = B();
    
    if(err == PARSE_ERR)
        RETURN_PARSE_ERROR;
    
    RETURN_PARSE_SUCCESS;
}