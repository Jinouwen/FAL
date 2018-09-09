#include <Card.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

#include "MathModel.h"
using namespace std;

int main()
{
    //printf("233");
    /*MathModel mm;
    mm.dealtCards();
    mm.display();
    */

    Player p;
    p.addCard(1);
    p.addCard(2);
    p.addCard(3);
    p.addCard(4);
    p.addCard(5);
    p.addCard(6);
    p.addCard(9);
    p.addCard(10);
    p.addCard(11);
    p.showAllCard();
    puts("");
    p.showType();
    return 0;
}
