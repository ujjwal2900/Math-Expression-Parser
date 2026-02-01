#ifndef __DTYPES__
#define __DTYPES__

#include <string>
#include "MexprTree.h"
#include "MExprcppEnums.h"


class Dtype:public MexprNode {


    private:

    protected:
        Dtype();


    public:
        mexprcpp_dtypes_t did; // Dtype ID
        virtual ~Dtype();
        /* Method return a new object instance of particular data type passed as an argument to this function */
        static Dtype *factory(mexprcpp_dtypes_t did);
        virtual void SetValue(void *value) = 0;
        virtual void SetValue(Dtype*) = 0;

};

class Dtype_INT: public Dtype {

    private:

    protected:

    public:

    /* Data struct that will store int*/
    struct{
        int int_val;
    }dtype;


    Dtype_INT();
    Dtype_INT(int val); 
    ~Dtype_INT();
    virtual void SetValue(void *value) override;
    virtual void SetValue(Dtype*) override;

};

class Dtype_DOUBLE: public Dtype {

    private:

    protected:

    public:

    /* Data struct that will store double*/
    struct{
        double double_val;
    }dtype;


    Dtype_DOUBLE();
    Dtype_DOUBLE(double val); 
    ~Dtype_DOUBLE();
    virtual void SetValue(void *value) override;
    virtual void SetValue(Dtype*) override;

};

class Dtype_STRING: public Dtype {

    private:

    protected:

    public:

    /* Data struct that will store int*/
    struct{
        std::string string_val;
    }dtype;


    Dtype_STRING();
    ~Dtype_STRING();
    virtual void SetValue(void *value) override;
    virtual void SetValue(Dtype*) override;

};



#endif