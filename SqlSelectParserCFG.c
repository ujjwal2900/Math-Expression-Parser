#include <string.h>
#include "ParserExport.h"
#include "MExprcppEnums.h"

/*
CFG:
Q-> select COLS from TAB
COLS-> COL|COL, COLS
COL-> <variable>
TAB-> <variable>
*/

static parse_rc_t TAB();
static parse_rc_t COL();
static parse_rc_t COLS();
extern parse_rc_t Q();


//TAB-> <variable>
parse_rc_t TAB()
{
    parse_init();

    token_code = cyylex();

    if(token_code != MATH_CPP_VARIABLE){

        RETURN_PARSE_ERROR;
    }

    RETURN_PARSE_SUCCESS;
}

//TABS-> TAB | TAB, TABS
parse_rc_t TABS()
{
    parse_init();
    int initial_chkp;
    CHECKPOINT(initial_chkp);
    do{
        err = TAB();

        if(err == PARSE_ERR) break;

        token_code = cyylex();

        if(token_code != MATH_CPP_COMMA)    
        {
            yyrewind(2);
            break;
        }

        err = TABS();

        if(err == PARSE_ERR)
            break;
        
        RETURN_PARSE_SUCCESS;
        
    }while(0);

    //RESTORE_CHKP(initial_chkp);
    do{

        err = TAB();

        if(err == PARSE_ERR)    
            break;
        
        RETURN_PARSE_SUCCESS;

    }while(0);

    RETURN_PARSE_ERROR;
}


//COL-> <variable>
parse_rc_t COL()
{
    parse_init();

    token_code = cyylex();

    if(token_code != MATH_CPP_VARIABLE){

        RETURN_PARSE_ERROR;
    }

    RETURN_PARSE_SUCCESS;
}

// COLS->COL|COL,COLS
parse_rc_t COLS()
{
    parse_init();
    int initial_chkp;
    CHECKPOINT(initial_chkp);
    do{
        err = COL();

        if(err == PARSE_ERR) break;

        token_code = cyylex();

        if(token_code != MATH_CPP_COMMA)    
        {
            yyrewind(2);
            break;
        }

        err = COLS();

        if(err == PARSE_ERR)
            break;
        
        RETURN_PARSE_SUCCESS;
        
    }while(0);

    //RESTORE_CHKP(initial_chkp);
    do{

        err = COL();

        if(err == PARSE_ERR)    
            break;
        
        RETURN_PARSE_SUCCESS;

    }while(0);

    RETURN_PARSE_ERROR;
}


parse_rc_t Q()
{
    parse_init();

    do{
        token_code = cyylex();

        if(token_code != MATH_CPP_VARIABLE){

            RETURN_PARSE_ERROR;
        }

        if(strcmp(lex_curr_token, "select")!=0){

            RETURN_PARSE_ERROR;
        }

        err = COLS();

        if(err == PARSE_ERR)
            RETURN_PARSE_ERROR;
    }while(0);

    do{

        token_code = cyylex();

        if(token_code != MATH_CPP_VARIABLE){

            RETURN_PARSE_ERROR;
        }

        if(strcmp(lex_curr_token, "from")!=0){

            RETURN_PARSE_ERROR;
        }

        err= TABS();

        if(err = PARSE_ERR)
            RETURN_PARSE_ERROR;
        
    }while(0);
    
    token_code = cyylex();
    if(token_code != PARSER_EOL)
        RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}

