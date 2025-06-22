#include "ParserExport.h"
#include "MExprcppEnums.h"

/*
Implementation to parse the below grammar for mathematical expression
E-> E+F | E-F | F
F-> F*T | F/T | T
T-> (E) | <variable> | <integer> | <double>

After eliminating Left Recursion
E-> FE'
E'-> +FE' | -FE' | $
F-> TF'
F'-> *TF' | /TF' | $
T-> (E) | INTEGER | DECIMAL | VAR | G(E,E) | P(E)

Q-> E INEQ E
INEQ-> MATH_CPP_EQ | MATH_CPP_NEQ | MATH_CPP_LESS_THAN | MATH_CPP_LESS_THAN_EQ
P-> sqrt | sqr | sin
G-> max | min | pow

*/

parse_rc_t E();
static parse_rc_t E_dash();
static parse_rc_t F();
static parse_rc_t F_dash();
static parse_rc_t T();

static parse_rc_t Q();
//static parse_rc_t INEQ();
static parse_rc_t P();
static parse_rc_t G();

parse_rc_t T()
{
    parse_init();

    int initial_chkp;
    CHECKPOINT(initial_chkp);
    do{
        
        token_code = cyylex();

        if(token_code != MATH_CPP_BRACKET_START)
            break;

        err = E();

        if(err == PARSE_ERR)
            break;
        
        token_code = cyylex();

        if(token_code != MATH_CPP_BRACKET_END)
            break;

        RETURN_PARSE_SUCCESS;
        
    }while(0);

    

    RESTORE_CHKP(initial_chkp);

    err = G();

    if(err == PARSE_SUCCESS)
        RETURN_PARSE_SUCCESS;
    
    RESTORE_CHKP(initial_chkp);

    err = P();

    if(err == PARSE_SUCCESS)
        RETURN_PARSE_SUCCESS;
    

    RESTORE_CHKP(initial_chkp);

    err = Q();
    if(err == PARSE_SUCCESS)
        RETURN_PARSE_SUCCESS;
    
    RESTORE_CHKP(initial_chkp);

    token_code = cyylex();

    switch (token_code)
    {
        case MATH_CPP_INT:
        case MATH_CPP_DOUBLE:
        case MATH_CPP_VARIABLE:
            RETURN_PARSE_SUCCESS;

        
        default:
            RETURN_PARSE_ERROR;
        
    }

    RETURN_PARSE_ERROR;
}

parse_rc_t P()
{
    parse_init();

    int initial_chkp;
    CHECKPOINT(initial_chkp);

    do{

        token_code = cyylex();

        if(token_code == MATH_CPP_SQRT)
            RETURN_PARSE_SUCCESS;
    }while(0);

    RESTORE_CHKP(initial_chkp);

    do{

        token_code = cyylex();

        if(token_code == MATH_CPP_SQR)
            RETURN_PARSE_SUCCESS;
    }while(0);

    RESTORE_CHKP(initial_chkp);

    do{

        token_code = cyylex();
        if(token_code == MATH_CPP_SIN)
            RETURN_PARSE_SUCCESS;
    }while(0);

    RESTORE_CHKP(initial_chkp);

    do{

        token_code = cyylex();
        if(token_code == MATH_CPP_COS)
            RETURN_PARSE_SUCCESS;
    }while(0);

    RETURN_PARSE_ERROR;

}

parse_rc_t G()
{
    parse_init();

    int initial_chkp;
    CHECKPOINT(initial_chkp);

    do{
        token_code = cyylex();
        if(token_code == MATH_CPP_MAX)
            RETURN_PARSE_SUCCESS;
    }while(0);

    RESTORE_CHKP(initial_chkp);

    do{
        token_code = cyylex();
        if(token_code == MATH_CPP_MIN)
            RETURN_PARSE_SUCCESS;
    }while(0);

    RESTORE_CHKP(initial_chkp);

    do{
        token_code = cyylex();
        if(token_code == MATH_CPP_POW)
            RETURN_PARSE_SUCCESS;
    }while(0);

    RETURN_PARSE_ERROR;
}

parse_rc_t Q()
{
    parse_init();

    err = E();

    if(err == PARSE_ERR)
        RETURN_PARSE_ERROR;
    
    token_code = cyylex();

    switch (token_code)
    {
        case MATH_CPP_LESS_THAN:
        case MATH_CPP_GREATER_THAN:
        case MATH_CPP_LESS_THAN_EQ:
        case MATH_CPP_GREATER_THAN_EQ:
        case MATH_CPP_EQ:
        case MATH_CPP_NEQ:
            err = E();
            if(err == PARSE_ERR)
                RETURN_PARSE_ERROR;
            RETURN_PARSE_SUCCESS;
        default:
            RETURN_PARSE_ERROR;

    }
    RETURN_PARSE_ERROR;
}

parse_rc_t F_dash()
{
    parse_init();

    int initial_chkp;
    CHECKPOINT(initial_chkp);
    do
    {
        token_code = cyylex();

        if(token_code != MATH_CPP_MUL)
            break;
        
        err = T();
        if(err == PARSE_ERR)
            break;
        
        err = F_dash();
        if(err == PARSE_ERR)
            break;
        
        RETURN_PARSE_SUCCESS;
    } while (0);

    RESTORE_CHKP(initial_chkp);
    do
    {
        token_code = cyylex();

        if(token_code != MATH_CPP_DIV)
            break;
        
        err = T();
        if(err == PARSE_ERR)
            break;
        
        err = F_dash();
        if(err == PARSE_ERR)
            break;
        
        RETURN_PARSE_SUCCESS;
    } while (0);

    RESTORE_CHKP(initial_chkp);
    RETURN_PARSE_SUCCESS;
}


parse_rc_t F()
{
    parse_init();

    err = T();

    if(err == PARSE_ERR)
        RETURN_PARSE_ERROR;
    
    err = F_dash();

    if(err == PARSE_ERR)
        RETURN_PARSE_ERROR;
    
    RETURN_PARSE_SUCCESS;
}

parse_rc_t E_dash()
{
    parse_init();

    int initial_chkp;
    CHECKPOINT(initial_chkp);
    do
    {
        token_code = cyylex();

        if(token_code != MATH_CPP_PLUS)
            break;
        
        err = F();
        if(err == PARSE_ERR)
            break;
        
        err = E_dash();
        if(err == PARSE_ERR)
            break;
        
        RETURN_PARSE_SUCCESS;
    } while (0);

    RESTORE_CHKP(initial_chkp);
    
    do
    {
        token_code = cyylex();

        if(token_code != MATH_CPP_MINUS)
            break;
        
        err = F();
        if(err == PARSE_ERR)
            break;
        
        err = E_dash();
        if(err == PARSE_ERR)
            break;
        
        RETURN_PARSE_SUCCESS;
    } while (0);

    RESTORE_CHKP(initial_chkp);
    RETURN_PARSE_SUCCESS;
    
}

parse_rc_t E()
{
    parse_init();

    int initial_chkp;

    err = F();
    if(err == PARSE_ERR)
        RETURN_PARSE_ERROR;
    
    err = E_dash();
    if(err == PARSE_ERR)
        RETURN_PARSE_ERROR;
    
    RETURN_PARSE_SUCCESS;
}

