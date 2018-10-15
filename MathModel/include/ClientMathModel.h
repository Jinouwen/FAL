#ifndef CLIENTMATHMODEL_H
#define CLIENTMATHMODEL_H
#include "MathModel.h"

class ClientMathModel:public MathModel
{
    public:
        ClientMathModel();
        virtual ~ClientMathModel();
        Player myself;
        void showMyself();
    protected:

    private:
};

#endif // CLIENTMATHMODEL_H
