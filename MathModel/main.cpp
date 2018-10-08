#include <Card.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <ctime>

#include "MathModel.h"
#include "ClientApp.h"
using namespace std;

int main()
{
    //printf("233");

    //MathModel mm;
    //mm.startLocalGame();//参数为随机种子，缺省为0表示以当前时间随机

    //SOCKET s=socket(AF_INET,SOCK_STREAM,0);
    ClientApp ca;
    ca.connect();
    ca.test();
    system("pause");
//
    return 0;
}
