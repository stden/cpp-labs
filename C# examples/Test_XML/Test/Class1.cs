using System;
using csUnit;
using Test;

[TestFixture]
public class �����_������������ {
  [Test]
  public void ���������() {
    Assert.Equals(1, Program.fact(1));
    Assert.Equals(2, Program.fact(2));
    Assert.Equals(6, Program.fact(3));
  }
  [Test]
  public void ����������() {
    Assert.Equals(1, 1*1);
    Assert.Equals(4, 2*2);
    Assert.Equals(91, 3*3);
  }
}
