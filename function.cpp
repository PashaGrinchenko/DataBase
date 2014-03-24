#include "function.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <windows.h>

using namespace std;

void inPut (bookkeeping* basaDate, int N)
{
    cout << "Please, enter you data:\n";
    cin.ignore(1,'\n');
    for (int i = 0; i < N; ++i)
    {
        cout << "Enter surname:\n";
        cin.getline(basaDate[i].surname,21,'\n');
        cout << "Enter id:\n";
        cin.getline(basaDate[i].id,11,'\n');
        cout << "Enter salary:\n";
        cin.getline(basaDate[i].salary,10,'\n');
        cout << "Enter charge in percent:\n";
        cin.getline(basaDate[i].chargePercent,11,'\n');
        cout << "Enter charge:\n";
        cin.getline(basaDate[i].charge,11,'\n');
    }
}
void outPut(bookkeeping* basaDate, int N)
{
    cout << "****************************************************************************" <<endl;
    cout.setf(ios::left);
    cout.width(0);
    cout << "**";
    cout.width(21);
    cout << "       Surname       " << "**";
    cout.width(11);
    cout << "     ID    " << "**";
    cout.width(10);
    cout << "  Salary  " << "**";
    cout.width(11);
    cout <<" Charge(%) " << "**";
    cout.width(11);
    cout << " Charge($) " << "**" <<endl;
    cout << "****************************************************************************" <<endl;
    for (int i = 0; i < N; ++i)
    {
        cout.setf(ios::left);
        cout.width(0);
        cout << "**";
        cout.setf(ios::left);
        cout.width(21);
        cout <<basaDate[i].surname << "**";
        cout.setf(ios::left);
        cout.width(11);
        cout << basaDate[i].id << "**";
        cout.setf(ios::left);
        cout.width(10);
        cout << basaDate[i].salary << "**";
        cout.setf(ios::left);
        cout.width(11);
        cout << basaDate[i].chargePercent << "**";
        cout.setf(ios::left);
        cout.width(11);
        cout << basaDate[i].charge;
        cout.setf(ios::left);
        cout.width(0);
        cout << "**" << endl;
    }
}
void writeFile(bookkeeping* basaDate, int N)
{
    fstream fout("myfile.txt",ios::out|ios::binary|ios::trunc);
    fout.write((char*)basaDate,N*sizeof(bookkeeping));
    fout.close();
}
void readFile(bookkeeping* basaDate, int N)
{
    fstream fin("myfile.txt",ios::out|ios::binary);
    if (!fin.is_open())
    {
        cout << "File is not exist\n";
    }
    while (!fin.eof())
    {
        fin.read((char*)basaDate,N*sizeof(bookkeeping));
    }
    fin.close();
}
void menu (bookkeeping* basaDate, int n)
{
    int N;
    N = n;
    cout << "Enter size of database (max=20):\n";
    cin >> N;
    char tag;
    while (1)
    {
        system("cls");
        cout << "To iput basadate push 1\n";
        cout << "To output basadate push 2\n";
        cout << "To save basadate push 3\n";
        cout << "To read basadate push 4\n";
        cout << "To sort basadate push 5\n";
        cout << "To exit push 0\n";
        tag = getch();
        if (tag == '0')
        {
            system("cls");
            exit(0);
        }
        if (tag == '1')
        {
            system("cls");
            inPut(basaDate, N);
        }
        if (tag == '2')
        {
            outPut(basaDate, N);
            system ("pause");
        }
        if (tag == '3')
        {
            system("cls");
            writeFile(basaDate, N);
        }
        if (tag == '4')
        {
            system("cls");
            readFile(basaDate, N);
        }
        if (tag == '5')
        {
            system("cls");
            mergeOption(basaDate, N);
        }

    }
}
void Merge(bookkeeping* basaDate, int l, int r, int upDown, int (*fun)(bookkeeping, bookkeeping))
{
    if (l < r)
    {
        Merge(basaDate, l, (r+l)/2, upDown, (*fun));
        Merge(basaDate, (r+l)/2+1, r, upDown, (*fun));
        MergeTo(basaDate, l, (r+l)/2, (r+l)/2+1, r, upDown, (*fun));
    }
}

void MergeTo(bookkeeping* basaDate, int startA, int endA, int startB, int endB, int upDown, int (*fun)(bookkeeping, bookkeeping))
{
    int fStart = startA;
    int fEnd = endB;
    int i = 0; //индекс результирующего массива
    bookkeeping* fr = new bookkeeping[endB-startA+1];//рузельтирующий массив
    while (startA <= endA && startB <= endB)
    {
        if (order(upDown))
        {
            if (((*fun)(basaDate[startA], basaDate[startB])) < 0)
            {
                fr[i] = basaDate[startA];
                ++startA;
            }
            else
            {
                fr[i] = basaDate[startB];
                ++startB;
            }
        }
        else
        {
            if (((*fun)(basaDate[startA], basaDate[startB])) < 0)
            {
                fr[i] = basaDate[startB];
                ++startB;
            }
            else
            {
                fr[i] = basaDate[startA];
                ++startA;
            }
        }
        ++i;
    }
    if (startA <= endA)
    {
        for (int j = startA; j <= endA; ++j)
        {
            fr[i] = basaDate[j];
            ++i;
        }
    }
    else
    {
        for (int j = startB; j <= endB; ++j)
        {
            fr[i] = basaDate[j];
            ++i;
        }
    }
    i = 0;
    for ( int k = fStart; k <= fEnd; ++k)
    {
        basaDate[k] = fr [i];
        ++i;
    }
    delete []fr;
}

void MergeUser(bookkeeping* basaDate, int N, int upDown,int (*fun)(bookkeeping, bookkeeping))
{
    int l = 0;
    int r = N-1;
    Merge(basaDate, l, r, upDown, (*fun));
}

bool order (int upDown)
{
    return !(upDown%2);
}
int cmpSurname (bookkeeping ch1, bookkeeping ch2)
{
    return strcmp(ch1.surname,ch2.surname);
}
int cmpId (bookkeeping ch1, bookkeeping ch2)
{
    return strcmp(ch1.id,ch2.id);
}
int cmpSum (bookkeeping ch1, bookkeeping ch2)
{
    return strcmp(ch1.salary,ch2.salary);
}
int cmpChargePercent (bookkeeping ch1, bookkeeping ch2)
{
    return strcmp(ch1.chargePercent,ch2.chargePercent);
}
int cmpCharge (bookkeeping ch1, bookkeeping ch2)
{
    return strcmp(ch1.charge,ch2.charge);
}
void mergeOption (bookkeeping* basaDate, int N)
{
    typedef int (*fun)(bookkeeping, bookkeeping);
    fun* ptr = new fun[5];
    ptr[0] = cmpSurname;
    ptr[1] = cmpId;
    ptr[2] = cmpSum;
    ptr[3] = cmpChargePercent;
    ptr[4] = cmpCharge;
    cout << "To sort Basadate by surname A-->Z push 1\n";
    cout << "To sort Basadate by surname Z-->A push 2\n";
    cout << "To sort Basadate by id A-->Z push 3\n";
    cout << "To sort Basadate by id Z-->A push 4\n";
    cout << "To sort Basadate by sum A-->Z push 5\n";
    cout << "To sort Basadate by sum Z-->A push 6\n";
    cout << "To sort Basadate by chargepercent A-->Z push 7\n";
    cout << "To sort Basadate by chargepercent Z-->A push 8\n";
    cout << "To sort Basadate by charge A-->Z push 9\n";
    cout << "To sort Basadate by charge Z-->A pus 10\n";
    char tag;
    cin >> tag;
    if (tag == '1')
    {
        MergeUser(basaDate, N, 2, ptr[0]);
    }
    if (tag == '2')
    {
        MergeUser(basaDate, N, 1, ptr[0]);
    }
    if (tag == '3')
    {
        MergeUser(basaDate, N, 2, ptr[1]);
    }
    if (tag == '4')
    {
        MergeUser(basaDate, N, 1, ptr[1]);
    }
    if (tag == '5')
    {
        MergeUser(basaDate, N, 2, ptr[2]);
    }
    if (tag == '6')
    {
        MergeUser(basaDate, N, 1, ptr[2]);
    }
    if (tag == '7')
    {
        MergeUser(basaDate, N, 2, ptr[3]);
    }
    if (tag == '8')
    {
        MergeUser(basaDate, N, 1, ptr[3]);
    }
    if (tag == '9')
    {
        MergeUser(basaDate, N, 2, ptr[4]);
    }
    if (tag == '10')
    {
        MergeUser(basaDate, N, 1, ptr[4]);
    }
    delete []ptr;
}
