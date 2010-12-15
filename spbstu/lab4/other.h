//Прототипы используемых в данном задании функций:

int IncByValue(int e);

void IncByPointer(int* x);

void IncByReference(int& x);

void Swap(int& x, int& y);

void Swap(int* x, int* y);

void VarArgs(int arg1,...);

void VarArgs2(int arg1,...);

// Поиск минимального элемента в массиве
// Возвращает: указатель на минимальный элемент
int* MyMin(int* ar,int size);