
//Прототипы используемых в данном задании функций:

int IncByValue( int e) 
{
  return e+1;
}

void IncByPointer(int* x)
{
  (*x)++;
}

void IncByReference(int& x)
{
  x++;
}

void Swap( int& x, int& y )
{
  int temp = x; 
  x = y; 
  y = temp;
}

void Swap( int* x, int* y )
{
  int temp = (*x); 
  (*x) = *y; 
  *y = temp;
}

void VarArgs(int arg1,...){

}