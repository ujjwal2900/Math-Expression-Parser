%{

#include "ParserExport.h"
#include "MExprcppEnums.h"

#include <assert.h>


stack_t undo_stack = {-1, {0,0,0}};

char lex_buffer[MAX_STRING_SIZE];

// position where the lexical parser is currently parsing the string
// act as a cursor in the  input string
char *curr_ptr = lex_buffer;
char *lex_curr_token;  /* points to the token on the top of stack */
int lex_curr_token_len; /* represent the length of the token on the top of stack */


/* Push the lexical in the stack */
static void lex_push(lex_data_t lex_data){

    if(undo_stack.top>MAX_MEXPR_LEN-1)
    {
        fprintf(stderr,"No more space left in the stack \n");
        assert(undo_stack.top<MAX_MEXPR_LEN-1);
    }
    undo_stack.data[++undo_stack.top] = lex_data;

    lex_curr_token = (char *)lex_data.token_val;
    lex_curr_token_len = lex_data.token_len;
}

/* Pop the lexical data from the stack */
static lex_data_t lex_pop(){

    if(undo_stack.top==-1){
    
        fprintf(stderr,"No element in the stack to pop out \n");
        assert(undo_stack.top==0);
    }
    lex_data_t res = undo_stack.data[undo_stack.top];
    undo_stack.top--;

    if(undo_stack.top > -1){
        lex_data_t lex_top = undo_stack.data[undo_stack.top];
        lex_curr_token = (char *)lex_top.token_val;
        lex_curr_token_len = lex_top.token_len;
    }
    else{
        lex_curr_token = NULL;
        lex_curr_token_len = 0;
    }
    return res;
}

/*
void RESTORE_CHKP(int a){

    while(undo_stack.top != a){

        lex_pop();
    }
    
}
*/

static void process_white_space(int n){

    lex_data_t lex_data;
    curr_ptr +=n;
    lex_data.token_code = PARSER_WHITE_SPACE;
    lex_data.token_len = n;
    lex_data.token_val = NULL; /* no need to allocate memory for spaces */
    lex_push(lex_data);
}

void parser_stack_reset(){

    int data_len = 0;
    lex_data_t lex_data;
    while(undo_stack.top >= 0){
        lex_data = lex_pop();
        data_len += lex_data.token_len;
        if(lex_data.token_code == PARSER_WHITE_SPACE)
            continue;

        lex_data.token_code = 0;
        lex_data.token_len = 0;
    }
    curr_ptr -= data_len;
}

void lex_set_scan_buffer(const char *buffer){

    yy_scan_string(buffer);
}

/*
cyylex()
-- wrapper over inbuilt lex func in yylex()
-- push token obtained from yylex() onto lexical stack
-- spaces are automatically pushed on lexical stack, Dev need not bother about them
*/
int cyylex(){

    int token_code = yylex();
    lex_data_t lex_data;
    lex_data.token_code = token_code;
    lex_data.token_len = yyleng;
    curr_ptr += yyleng;
    lex_data.token_val = (char *)calloc(1, yyleng+1);
    strncpy(lex_data.token_val, yytext, yyleng+1); /* One extra for null character at the end */
    lex_push(lex_data);
    return token_code;
}

/*
yyrewind()
Move the lexical cursor backwards on input string
Empties the lexical stack incrementally
need to handle whitespaces as well
*/

void yyrewind(int n){

    if(n<=0)
        return ;
    if(curr_ptr == lex_buffer)
        return ;
    int data_len = 0;
    lex_data_t lex_data;
    while(n){
        lex_data = lex_pop();
        data_len += lex_data.token_len;
        if(lex_data.token_code == PARSER_WHITE_SPACE)
            continue;
        n--;
        lex_data.token_code = 0;
        lex_data.token_len = 0;
    }
    curr_ptr -= data_len;
    yy_scan_string(curr_ptr); /* tell the lexical analyzer where we currently are */

}


// dedicated to declare all global variables which parser will use END



%}

%%

 // Write Regular expressions here to generate tokens

"(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])" {
    
    return MATH_CPP_IPV4;
}

"(" {
    return MATH_CPP_BRACKET_START;
}

")" {
    return MATH_CPP_BRACKET_END;
}

"<=" {
    return MATH_CPP_LESS_THAN_EQ;
}

">=" {
    return MATH_CPP_GREATER_THAN_EQ;
}

"<" {
    return MATH_CPP_LESS_THAN;
}

">" {
    return MATH_CPP_GREATER_THAN;
}

"=" {
    return MATH_CPP_EQ;
}

"!=" {
    return MATH_CPP_NEQ;
}

"and" {
    return MATH_CPP_AND;
}

"or" {
    return MATH_CPP_OR;
}

"*" {
    return MATH_CPP_MUL;
}

"+" {
    return MATH_CPP_PLUS;
}

"-" {
    return  MATH_CPP_MINUS;
}

"/" {
    return MATH_CPP_DIV;
}

"," {
    return MATH_CPP_COMMA;
}

"sqrt" {
    return MATH_CPP_SQRT;
}

"sqr" {
    return MATH_CPP_SQR;
}

"mmax" {
    return MATH_CPP_MAX;
}

"mmin" {
    return MATH_CPP_MIN;
}

"sin" {
    return MATH_CPP_SIN;
}

"cos" {
    return MATH_CPP_COS;
}

"pow" {
    return MATH_CPP_POW;
}

\n {
    return PARSER_EOL;
}

"\\\n" {

}

[ ] {
    /* Ignore */
    /* it will push 1 white space on to the stack */
    process_white_space(1);
}

[\t] {
    /*ignore*/
    /* it will push 4 white spaces on to the stack */
    process_white_space(4);
}

"\\q" {
    return PARSER_QUIT;
}

0|-?[1-9][0-9]* {
    return MATH_CPP_INT;
}

-?[0-9]*\.[0-9]+ {
    return MATH_CPP_DOUBLE;
}

[a-zA-Z]+ {
    return MATH_CPP_VARIABLE;
}

[a-zA-Z0-9_]+ {
    return MATH_CPP_IDENTIFIER;
}

[a-zA-Z0-9_]+\.[a-zA-Z0-9_]+ {
    return MATH_CPP_IDENTIFIER_IDENTIFIER;
}

'[^']*' {
    // string enclosed within single quotes
    return MATH_CPP_STRING;
}

\"[^"]*\" {
    // string enclosed within double quotes
    return MATH_CPP_STRING;
}


. {
    // ignore any other character
}






%%

extern void Parse_Equations();
extern parse_rc_t A();
extern parse_rc_t Q();
extern parse_rc_t E();
extern lex_data_t **mexpr_convert_infix_to_postfix(lex_data_t *infix, int sizein, int &sizeout);

// C main function
int main(int argc, char **argv)
{
    while(1){

        printf("Input-> ");
        fgets(lex_buffer, sizeof(lex_buffer), stdin);

        if(lex_buffer[0] == '\n'){
            lex_buffer[0] = 0;
            continue;
        }

        lex_set_scan_buffer(lex_buffer);

        //Parse_Equations();
        //parse_rc_t err = A();

        #if 1
        parse_rc_t err = E();

        if(err == PARSE_ERR){
            printf("E : rejected\n");
            for(int i=0;i<=undo_stack.top;i++){

                lex_data_t *lex_data = &undo_stack.data[i];
                printf("%s", lex_data->token_val);
            }
            printf("\n");
        }
        else{
            //yyrewind(1);

            int token_code = cyylex();
            if(token_code != PARSER_EOL)
                printf("E : Rejected\n");
            else
                printf("E : Accepted\n");

            for(int i=0;i<=undo_stack.top;i++){

                lex_data_t *lex_data = &undo_stack.data[i];
                printf("%s", lex_data->token_val);
            }
            
            printf("\n");
        }
        #endif

        #if 1

        int sizeout = 0;
        lex_data_t **postfix_array = mexpr_convert_infix_to_postfix(
                                        undo_stack.data,
                                        undo_stack.top,
                                        sizeout);

        //print the postfix array here to verify
        printf("Sizeout - %d\n", sizeout);
        printf("Print the postfix array : ");
        for(int i=0;i<sizeout;i++)
        {
            lex_data_t *lex_data = postfix_array[i];
            printf("%s ", lex_data->token_val);
            
        }
        printf("\n");

        //free(lex_data->token_val);
            //free(lex_data);
        #endif

        

        # if 0
        parse_rc_t err = Q();
        if(err==PARSE_ERR){
            printf("A : rejected\n");
            for(int i=0;i<=undo_stack.top;i++){

                lex_data_t *lex_data = &undo_stack.data[i];
                printf("%s", lex_data->token_val);
            }
        }
        else{
                printf("A : accepted\n");

            for(int i=0;i<=undo_stack.top;i++){

                lex_data_t *lex_data = &undo_stack.data[i];
                printf("%s", lex_data->token_val);
            }
            
            
        }
        #endif

        parser_stack_reset();

        /*
        yy_scan_string(lex_buffer);

        int token_code;
        
        token_code = yylex();
        while(token_code != PARSER_EOL){

            printf("token_code=%d, token-%s, token_len=%d\n", token_code, yytext, yyleng);
            token_code = yylex();
        }
        */
    }
}