#include <Card.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <ctime>

#include "ClientApp.h"
using namespace std;

int main()
{
    //printf("233");

    //MathModel mm;
    //mm.startLocalGame();//����Ϊ������ӣ�ȱʡΪ0��ʾ�Ե�ǰʱ�����

    //SOCKET s=socket(AF_INET,SOCK_STREAM,0);
    ClientApp ca;
    ca.connect();
    ca.test();
    system("pause");
//
    return 0;
}
