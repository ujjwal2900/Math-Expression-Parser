#include "Dtypes.h"

Dtype::Dtype(){

    did = MATH_CPP_DTYPE_INVALID;
}

Dtype::~Dtype(){


}

Dtype_INT::Dtype_INT(){

    this->did = MATH_CPP_INT;
}

Dtype_INT::Dtype_INT(int val){

    this->did = MATH_CPP_INT;
    this->dtype.int_val = val;
}

Dtype_INT::~Dtype_INT(){


}

void  Dtype_INT::SetValue(void *value) {

    int val = atoi((const char *)value);
    this->dtype.int_val = val;
}

void Dtype_INT::SetValue(Dtype* value) {

    this->dtype.int_val = dynamic_cast<Dtype_INT*>(value)->dtype.int_val;
}

Dtype_DOUBLE::Dtype_DOUBLE(){

    this->did = MATH_CPP_DOUBLE;
}

Dtype_DOUBLE::Dtype_DOUBLE(double val){

    this->did = MATH_CPP_DOUBLE;
    this->dtype.double_val = val;
}

Dtype_DOUBLE::~Dtype_DOUBLE(){


}

void  Dtype_DOUBLE::SetValue(void *value) {

    double val = (double)atof((const char *)value);
    this->dtype.double_val = val;
}

void Dtype_DOUBLE::SetValue(Dtype* value) {

    this->dtype.double_val = dynamic_cast<Dtype_DOUBLE*>(value)->dtype.double_val;
}


Dtype_STRING::Dtype_STRING(){

    this->did = MATH_CPP_STRING;
}

Dtype_STRING::~Dtype_STRING(){
    
}

void  Dtype_STRING::SetValue(void *value) {

    this->dtype.string_val.assign(std::string((char *)value));

    //remove the "" on both the sisdes of the strings if present
    //remove the '' on both the sides of the strings if present

    if(this->dtype.string_val.length() >=2 && this->dtype.string_val.front() == '"' && this->dtype.string_val.back() == '"'){
        this->dtype.string_val.erase(0,1);  // Remove first character
        this->dtype.string_val.erase(this->dtype.string_val.size()-1);  // Remove last character
    }

    if(this->dtype.string_val.length() >=2 && this->dtype.string_val.front() == '\'' && this->dtype.string_val.back() == '\''){
        this->dtype.string_val.erase(0,1);  // Remove first character
        this->dtype.string_val.erase(this->dtype.string_val.size()-1);  // Remove last character
    }



    /*
    this->dtype.string_val.erase(
        std::remove(this->dtype.string_val.begin(), this->dtype.string_val.end(), '\"'),
        this->dtype.string_val.end() );
    this->dtype.string_val.erase(
        std::remove(this->dtype.string_val.begin(), this->dtype.string_val.end(), '\''),
        this->dtype.string_val.end());
    */
}

void Dtype_STRING::SetValue(Dtype* value) {

    Dtype_STRING *value_str = dynamic_cast<Dtype_STRING *>(value);
    this->dtype.string_val = value_str->dtype.string_val;
    //this->SetValue(&value_str->dtype.string_val.c_str());
}


Dtype *Dtype::factory(mexprcpp_dtypes_t did)
{
    if(did == MATH_CPP_INT)
        return  new Dtype_INT();
    else if( did == MATH_CPP_DOUBLE)
        return  new Dtype_DOUBLE();
    else if( did == MATH_CPP_STRING)
        return  new Dtype_STRING();
    
    return NULL;

}