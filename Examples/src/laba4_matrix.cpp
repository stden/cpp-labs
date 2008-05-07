#include <iostream.h>
#include <conio.h>
#include <iomanip.h>

class Matrix {
  private:
    int** num;
    int rows, columns;
  public:
    Matrix();
    Matrix(int, int);
    Matrix(Matrix&);
    ~Matrix();

    friend istream& operator >>(istream& s, Matrix& m);
    friend ostream& operator <<(ostream& s, Matrix& m);
    Matrix& operator =(Matrix&);
    Matrix& operator +(Matrix&);
    Matrix& operator -(Matrix&);
    Matrix& operator +=(Matrix&);
    Matrix& operator -=(Matrix&);
    Matrix& operator *(Matrix&);
    Matrix& operator ~();
    Matrix operator [](int);
};

Matrix::Matrix(Matrix &m) {
  rows = m.rows;
  columns = m.columns;
  num = new int* [rows];
  for (int i=0; i<rows; i++) {
    num[i] = new int [columns];
    for (int j=0; j<columns; j++)
      *(*(num+i)+j) = *(*(m.num+i)+j);
  }
}

Matrix::~Matrix() {
  for (int i=0; i<rows; i++)
    delete [] num[i];
  delete [] num;
}

Matrix::Matrix() {
  rows = 0;
  columns = 0;
}

Matrix::Matrix(int x, int y) {
  rows=x;
  columns=y;
  num = new int* [rows];
  for (int b=0; b<rows; b++)
    num[b] = new int[columns];
}

istream& operator >>(istream& s, Matrix &m) {
  if ((m.rows == 0)||(m.columns == 0)) {
    cout << " Input number of rows: \n";
    cin >> m.rows;
    cout << endl;
    cout << " Input number of columns: \n ";
    cin >> m.columns;
    cout << endl;
    m.num = new int* [m.rows];
    for (int i=0; i<m.rows; i++)
      m.num[i] = new int [m.columns];
  };
  for (int i=0; i<m.rows; i++) {
    for (int j=0; j<m.columns; j++) {
      cout << "Input matrix element \n["<< i+1<< ", "<< j+1<< "]: ";
      s >>*(*(m.num+i)+j);
    };
  };
  return s;
}

ostream& operator <<(ostream& os, Matrix &m) {
  for (int i=0; i<m.rows; i++) {
    for (int j=0; j<m.columns; j++)
      os << setw(5) << *(*(m.num+i)+j);
    os << endl;
  };
  return os;
}

Matrix& Matrix::operator = (Matrix& m) {
  if ((rows=m.rows) && (columns=m.columns)) {
    for(int i=0;i<m.rows;i++)
    for(int j=0;j<m.columns;j++)
    num[i][j]=m.num[i][j];
  };
  return *this;
}

Matrix& Matrix::operator + (Matrix& m) {
  if ((rows == m.rows)&&(columns = m.columns)) {
    Matrix* buf = new Matrix(*this);
    for(int i = 0; i<m.rows;i++)
    for(int j = 0;j<m.columns;j++)
    *(*(buf->num+i)+j) += *(*(m.num+i)+j);
    return *buf;
  }
  else
  return *this;
};

Matrix& Matrix::operator += (Matrix& m) {
  if ((rows == m.rows)&&(columns = m.columns)) {
    for(int i = 0; i<m.rows;i++)
    for(int j = 0;j<m.columns;j++)
    *(*(num+i)+j) += *(*(m.num+i)+j);
  };
  return *this;
};

Matrix& Matrix::operator - (Matrix& m) {
  if ((rows == m.rows)&&(columns = m.columns)) {
    Matrix* buf = new Matrix(*this);
    for(int i = 0; i<m.rows;i++)
      for(int j = 0;j<m.columns;j++)
        *(*(buf->num+i)+j) -= *(*(m.num+i)+j);
    return *buf;
  } else return *this;
};

Matrix& Matrix::operator -= (Matrix& m) {
  if ((rows == m.rows)&&(columns = m.columns)) 
    for(int i = 0; i<m.rows;i++)
      for(int j = 0; j<m.columns;j++) 
        *(*(num+i)+j) -= *(*(m.num+i)+j);  
  return *this;
};

Matrix& Matrix::operator * (Matrix& m) {
  if (columns == m.rows) {
    Matrix* buf = new Matrix(rows, m.columns);
    for(int i=0; i<rows; i++)
    for(int j=0; j<m.columns;j++) {
      (*(*(buf->num+i)+j)) = 0;
      for (int k=0; k<columns; k++) (*(*(buf->num+i)+j)) += (*(*(num+j)+k)) * (*(*(m.num+k)+i));
    };
    return *buf;
  }
  else
  return *this;
};

Matrix& Matrix::operator ~ () {
  Matrix* buf = new Matrix(columns,rows);
  for(int i=0; i<rows; i++)
  for(int j=0; j<columns; j++) *(*(buf->num+j)+i) = (*(*(num+i)+j));
  return *buf;
};

Matrix Matrix::operator [] (int n) {
  Matrix temp;
  temp.rows=1;
  temp.columns=columns;
  for(int i=0;i<columns;i++) temp.num[0][i]=num[i][n-1];
  return temp;
}

int main() {
  // clrscr();
  // Тестирование программы
  Matrix t(2, 2); 
//  t[0][0] = 1;
  // Тестирование в интерактивном режиме
  Matrix m1(2, 2), m2(2, 2), m3;
  cout<<"Input first Matrix";
  cin >>m1;
  cout<<"Input second <Matrix";
  cin>>m2;
  cout <<"matrix first is :: \n"<<m1<<'\n';
  cout <<"matrix second is :: \n"<<m2<<'\n';
  m3=m1+m2;
  cout<<"First Matrix Add Second \n"<<m3<<'\n';
  m3-=m2;
  cout<<"Third Matrix Mines second Matrix \n "<<'\n'<<m3;
  m3=m3*m3;
  cout<<"Third Matrix Multiply Third Matrix \n "<<'\n'<<m3;
  m1=~m1;
  cout<<"Transponirovanie First Matrix \n"<<m1<<'\n';
  getch();
  return 0;
}
