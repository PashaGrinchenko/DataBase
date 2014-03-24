#ifndef FUNCTION_H
#define FUNCTION_H

struct bookkeeping
{
    char surname[21];
    char id[11];
    char salary[10];
    char chargePercent[11];
    char charge[11];
};

void inPut (bookkeeping* basaDate, int userSizeOfBasaDate);
void outPut(bookkeeping* basaDate, int userSizeOfBasaDate);
void writeFile(bookkeeping* basaDate, int userSizeOfBasaDate);
void readFile(bookkeeping* basaDate, int userSizeOfBasaDate);
void menu (bookkeeping* basaDate, int userSizeOfBasaDate);
void Merge(bookkeeping* basaDate, int startIndex, int lastIndex, int upDown, int (*fun)(bookkeeping, bookkeeping));
void MergeTo(bookkeeping* basaDate, int startA, int endA, int startB, int endB, int upDown, int (*fun)(bookkeeping, bookkeeping));
void MergeUser(bookkeeping* basaDate, int sizeOfBasadate, int upDown, int (*fun)(bookkeeping, bookkeeping));
bool order (int upDown);
int cmpSurname (bookkeeping characteristic1, bookkeeping characteristic2);
int cmpId (bookkeeping characteristic1, bookkeeping characteristic2);
int cmpSum (bookkeeping characteristic1, bookkeeping characteristic2);
int cmpChargePercent (bookkeeping characteristic1, bookkeeping characteristic2);
int cmpCharge (bookkeeping characteristic1, bookkeeping characteristic2);
void mergeOption (bookkeeping* basaDate, int userSizeOfBasaDate);


#endif // FUNCTION_H
