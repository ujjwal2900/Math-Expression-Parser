#include "MexprTree.h"
#include <stack>
#include "Dtypes.h"
#include "Operators.h"

MexprNode::MexprNode() {

    //Base class constructor
    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
    this->lst_left = NULL;
    this->lst_right = NULL;

}

MexprNode::~MexprNode() {

    //Base class destructor
}

MexprTree::MexprTree() {

    root = NULL;
    lst_head = NULL;
}

MexprTree::MexprTree(lex_data_t **postfix_lex_data_array, int size)
{
    MexprTree();

    std::stack<MexprNode *> stack;
    
    for(int i=0;i<size;i++)
    {
        lex_data_t *elem = postfix_lex_data_array[i];
        if( !(Math_cpp_is_operand(elem->token_code)) || !(Math_cpp_is_operator(elem->token_code)) )
            continue;

        if(Math_cpp_is_operand(elem->token_code)){
            MexprNode *node = Dtype::factory((mexprcpp_dtypes_t)elem->token_code);

            Dtype *dtype = dynamic_cast<Dtype *>(node);
            dtype->SetValue((void *) elem->token_val);
            stack.push(node);
        }
        else if(Math_cpp_is_unary_operator(elem->token_code)){
            
            MexprNode *node = Operator::factory((mexprcpp_operators_t)elem->token_code);
            
            MexprNode *left = stack.top();
            stack.pop();
            node->left = left;
            node->right = NULL;
            left->parent = node;

            stack.push(node);

        }
        else {

            assert(Math_cpp_is_operand(elem->token_code));
            MexprNode *node = Operator::factory((mexprcpp_operators_t)elem->token_code);

            MexprNode *right = stack.top();
            stack.pop();
            MexprNode *left = stack.top();
            stack.pop();

            node->left = left;
            node->right = right;
            left->parent = node;
            right->parent = node;
            stack.push(node);

        }
    }
    this->root = stack.top();
    stack.pop();
    assert(stack.empty());
    assert(!this->root->parent);
}


void PrintInorder(MexprNode *node)
{
    if(root == NULL)
        return ;
    
    PrintInorder(node->left);
    //std::cout << Operator(node).name << " ";
    PrintInorder(node->right);

}

MexprTree::InorderPrint(MexprTree *tree)
{
    if(tree == NULL)
        return;
    
    PrintInorder(tree->root);
}