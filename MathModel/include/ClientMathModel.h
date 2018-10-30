#ifndef CLIENTMATHMODEL_H
#define CLIENTMATHMODEL_H
#include "MathModel.h"
#include <iomanip>
using namespace std;

class ClientMathModel:public MathModel
{
    public:
        ClientMathModel();
        virtual ~ClientMathModel();
        Player myself;
        void showMyself();
        void init(int myId,string str);
        void ClientShowSituation(int opt = 0);

        bool passFlag[3];
        string playerName[3],ldstr[3];
        cardSet table;
        int myId,leftId,rightId,cardNum[3],ldId,bldFlag[3],scoreRate,springFlag,playerScore[3];
    protected:
    private:
};

#endif // CLIENTMATHMODEL_H
