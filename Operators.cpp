#include "Operators.h"

//base class
Operator::Operator(){

    this->opid = MATH_CPP_OPR_INVALID;
    this->name = "";
    this->is_unary = false;
}

Operator::~Operator(){


}

OperatorPlus::OperatorPlus(){

    this->opid = MATH_CPP_PLUS;
    this->name = "+";
    this->is_unary = false;
}

OperatorPlus::~OperatorPlus(){


}

OperatorMinus::OperatorMinus(){

    this->opid = MATH_CPP_MINUS;
    this->name = "+";
    this->is_unary = false;
}

OperatorMinus::~OperatorMinus(){

    
}

OperatorMul::OperatorMul(){
    
    this->opid = MATH_CPP_MUL;
    this->name = "*";
    this->is_unary = false;
}

OperatorMul::~OperatorMul(){

}

OperatorDiv::OperatorDiv(){

    this->opid = MATH_CPP_DIV;
    this->name = "/";
    this->is_unary = false;
}

OperatorDiv::~OperatorDiv(){

}

OperatorEq::OperatorEq(){

    this->opid = MATH_CPP_EQ;
    this->name = "=";
    this->is_unary = false;
}

OperatorEq::~OperatorEq(){

}

OperatorNeq::OperatorNeq(){

    this->opid = MATH_CPP_NEQ;
    this->name = "!=";
    this->is_unary = false;
}

OperatorNeq::~OperatorNeq(){

}

OperatorLessThan::OperatorLessThan(){

    this->opid = MATH_CPP_LESS_THAN;
    this->name = "<";
    this->is_unary = false;
}

OperatorLessThan::~OperatorLessThan(){

}

OperatorGreaterThan::OperatorGreaterThan(){

    this->opid = MATH_CPP_GREATER_THAN;
    this->name = ">";
    this->is_unary = false;
}

OperatorGreaterThan::~OperatorGreaterThan(){

}

OperatorSqr::OperatorSqr(){

    this->opid = MATH_CPP_SQR;
    this->name = "sqr";
    this->is_unary = false;
}

OperatorSqr::~OperatorSqr(){

}

OperatorSqrt::OperatorSqrt(){

    this->opid = MATH_CPP_SQRT;
    this->name = "sqrt";
    this->is_unary = false;
}

OperatorSqrt::~OperatorSqrt(){

}

OperatorMax::OperatorMax(){

    this->opid = MATH_CPP_MAX;
    this->name = "mmax";
    this->is_unary = false;
}

OperatorMax::~OperatorMax(){

}

OperatorMin::OperatorMin(){

    this->opid = MATH_CPP_MIN;
    this->name = "mmin";
    this->is_unary = false;
}

OperatorMin::~OperatorMin(){

}

Operator * Operator::factory(mexprcpp_operators_t opr_code){

    if (opr_code == MATH_CPP_PLUS)
        return new OperatorPlus();
    else if (opr_code == MATH_CPP_MINUS)
        return new OperatorMinus();
    else if (opr_code == MATH_CPP_MUL)
        return new OperatorMul();
    else if (opr_code == MATH_CPP_DIV)
        return new OperatorDiv();
    else if(opr_code == MATH_CPP_EQ)
        return new OperatorEq();
    else if(opr_code == MATH_CPP_NEQ)
        return new OperatorNeq();
    else if(opr_code == MATH_CPP_LESS_THAN)
        return new OperatorLessThan();
    else if(opr_code == MATH_CPP_GREATER_THAN)
        return new OperatorGreaterThan();
    else if(opr_code == MATH_CPP_SQR)
        return new OperatorSqr();
    else if(opr_code == MATH_CPP_SQRT)
        return new OperatorSqrt();
    else if(opr_code == MATH_CPP_MAX)
        return new OperatorMax();
    else if(opr_code == MATH_CPP_MIN)
        return new OperatorMin();
    
    return NULL;

}


