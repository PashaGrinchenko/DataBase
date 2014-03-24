#include "function.h"
#include <iostream>

using namespace std;

int main()
{
    int n = 20;
    bookkeeping* basaDate = new bookkeeping[n];
    menu(basaDate, n);
    return 0;
}
