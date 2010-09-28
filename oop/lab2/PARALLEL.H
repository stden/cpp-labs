// Файл: Parallelogram.h
// Объявление класса Параллелограмм
// Автор: Волынко Е.
// Дата: 16.05.10, Редакция: 1.0


#include "CoPoint.h"
#include "CoList.h"

/*
 * Параллелограмм лежащий на меньшем ребре
 */
class CParallelogram {
private:
  CList<CCountedPoint> m_list;

//Количество экземпляров класса прямоугольник
  static int countreal;

  //Общее количество созданных когда-либо экземпляров
  static int countall;

  //Идентификатор
  int m_id;
public:
  /*
  * Конструктор
  * x - левая нижняя точка, y - левая верхняя, l - Длина меньшего ребра
  */
  CParallelogram(const CCountedPoint& x, const CCountedPoint& y, const double& l);

  /*
  * Деструктор
  */
  ~CParallelogram(void);


  void MovedXdY(double dx, double dy);
  void MoveToPoint(const CCountedPoint& P);

  const CList<CCountedPoint>& getPoints() { return m_list; }
  const CCountedPoint& getPoint(int index);

  static int getCount() { return countreal; }

  int getId() { return m_id; }


  friend ostream& operator << (ostream& s, CParallelogram& r) {
    s << "  " << "Parallelogram" << ": " << endl;
    r.getPoints().goFirst();

    do {
      s << "    (" << r.getPoints().getElem().getValue() << "), " << endl;
    } while (r.getPoints().goNext());

    s << "    (" << r.getPoints().getElem().getValue() << ")";
    s << endl;

    return (s);
  }

};
