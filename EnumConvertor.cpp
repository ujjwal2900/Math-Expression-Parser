#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stack>
#include "ParserExport.h"
#include "MExprcppEnums.h"

lex_data_t **mexpr_convert_infix_to_postfix(lex_data_t *infix, int sizein, int &sizeout)
{
    std::stack<lex_data_t *> st;                                                                                                                                                                                                                                                                                                                

    lex_data_t **postfixExp;
    postfixExp = (lex_data_t **)malloc(sizein * sizeof(lex_data_t));
    int idx = 0;
    printf("Enum sizein - %d\n", sizein);
    

    for(int i=0;i<sizein;i++)
    {

        lex_data_t lex_data = infix[i];
        //std::cout << infix[i].token_val ;

        if(Math_cpp_is_operand(lex_data.token_code)){
            postfixExp[sizeout] = &infix[i];
            sizeout++;
        }
        
        else if(lex_data.token_code == MATH_CPP_BRACKET_START)
            st.push(&infix[i]);
        
        else if(lex_data.token_code == MATH_CPP_BRACKET_END){
            
            while(!st.empty() && st.top()->token_code != MATH_CPP_BRACKET_START){
                postfixExp[sizeout] = st.top();
                sizeout++;
                st.pop();
            }
            st.pop();
        }
        
        else{
            while(!st.empty() &&
                    Math_cpp_operator_precedence(lex_data.token_code) <= Math_cpp_operator_precedence(st.top()->token_code))
            {
                postfixExp[sizeout] = st.top();
                sizeout++;
                st.pop();
            }
            st.push(&infix[i]);
        }

    }
    

    while(!st.empty())
    {
        postfixExp[sizeout] = st.top();
        sizeout++;
        st.pop();
    }

    printf("Print the postfix array : ");
    for(int i=0;i<sizeout;i++)
    {
        lex_data_t *lex_data = postfixExp[i];
        printf("%s ", lex_data->token_val);
        
    }
    printf("\n");

    printf("Enum Sizeout - %d\n", sizeout);
    return postfixExp;
}