using System;
using System.Data;

namespace Test {
  internal class Program {
    private static void Main(string[] args) {
      �����(1, fact(1));
      �����(2, fact(2));
      �����(6, fact(3));
      
      �������_DS ds = new �������_DS();
      ds.�������.Add�������Row(1, "������1");
      ds.�������.Add�������Row(2, "234������1");
      ds.�������.Add�������Row(3, "fdgdfg������1");
      ds.�������.Add�������Row(4, "dgdfg������1");
      ds.WriteXml("Test.xml");
      ds.ReadXml("Test.xml");
      ds.�������[3].������������ = "ssffdfdgsgfd";
      foreach (�������_DS.�������Row ������ in ds.�������) {
        Console.WriteLine("(" + ������.id + ") - " + ������.������������);        
      }
      
      DataSet f = new DataSet();
      DataTable ������� = f.Tables.Add("�������");
      for(int i=0;i<8;i++)
        �������.Columns.Add("�������"+i);

      for (int i = 0; i < 8; i++)
        �������.Columns.Add("�������"+i);
      
      Console.ReadLine();
    }

    public static int fact(int N) {
      int res = 1;
      for(int i=1;i<=N;i++)
        res *= i;
      return res;
    }

    private static void �����(int ���������, int ����) {
      if (��������� != ����)
        Console.WriteLine("��������� = " + ��������� + " ���� = " + ����);
    }
  }
}