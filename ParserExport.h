#ifndef __PARSER_EXPORT__
#define __PARSER_EXPORT__


// Write all the supporting C-code declarations/definitions

// Define all supportive data structures BEGIN

typedef enum parse_rc_{

    PARSE_ERR,
    PARSE_SUCCESS
}parse_rc_t;

typedef struct lex_data_ {

    int token_code;
    int token_len;
    char* token_val;

}lex_data_t;

#define MAX_MEXPR_LEN 512
#define MAX_STRING_SIZE 512

typedef struct stack_ {

    int top;
    lex_data_t data[MAX_MEXPR_LEN];
} stack_t;

// Define all supportive data structures END

// dedicated to declare all global variables which parser will use BEGIN


extern  "C" int yylex(); /* C linkage in a Cpp program */
extern char lex_buffer[MAX_STRING_SIZE];
extern stack_t undo_stack;
extern char *curr_ptr;
extern int cyylex();
extern void yyrewind(int n);
extern void parser_stack_reset();
extern void lex_set_scan_buffer(const char *buffer);
extern char *lex_curr_token;
extern int lex_curr_token_len;


#define CHECKPOINT(a)   \
    a = undo_stack.top

extern void RESTORE_CHKP(int a);

#define PARSER_LOG_ERR(token_obtained, expected_token)  \
        printf("%s(%d): Token Obtained=%d(%s), expected token=%d\n",   \
        __FUNCTION__,__LINE__,token_obtained,lex_curr_token,expected_token);


#define parse_init()    \
    int token_code = 0;     \
    int _lchkp = undo_stack.top;    \
    parse_rc_t err = PARSE_SUCCESS

#define RETURN_PARSE_SUCCESS    \
        return PARSE_SUCCESS;

#define RETURN_PARSE_ERROR  \
        { printf("Error at - %s \n", lex_curr_token); \
          RESTORE_CHKP(_lchkp);  \
          return PARSE_ERR; }

#endif