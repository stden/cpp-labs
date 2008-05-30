using System;
using System.Data;

namespace Test {
  internal class Program {
    private static void Main(string[] args) {
      Равно(1, fact(1));
      Равно(2, fact(2));
      Равно(6, fact(3));
      
      Вопросы_DS ds = new Вопросы_DS();
      ds.Вопросы.AddВопросыRow(1, "Вопрос1");
      ds.Вопросы.AddВопросыRow(2, "234Вопрос1");
      ds.Вопросы.AddВопросыRow(3, "fdgdfgВопрос1");
      ds.Вопросы.AddВопросыRow(4, "dgdfgВопрос1");
      ds.WriteXml("Test.xml");
      ds.ReadXml("Test.xml");
      ds.Вопросы[3].ТекстВопроса = "ssffdfdgsgfd";
      foreach (Вопросы_DS.ВопросыRow вопрос in ds.Вопросы) {
        Console.WriteLine("(" + вопрос.id + ") - " + вопрос.ТекстВопроса);        
      }
      
      DataSet f = new DataSet();
      DataTable Вопросы = f.Tables.Add("Вопросы");
      for(int i=0;i<8;i++)
        Вопросы.Columns.Add("Колонка"+i);

      for (int i = 0; i < 8; i++)
        Вопросы.Columns.Add("Колонка"+i);
      
      Console.ReadLine();
    }

    public static int fact(int N) {
      int res = 1;
      for(int i=1;i<=N;i++)
        res *= i;
      return res;
    }

    private static void Равно(int Ожидается, int Есть) {
      if (Ожидается != Есть)
        Console.WriteLine("Ожидается = " + Ожидается + " Есть = " + Есть);
    }
  }
}