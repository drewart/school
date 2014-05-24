import java.util.Date;

class MyTest2 extends Thread
{

  public void run()
  {
    String[] args1 = SysLib.stringToArgs("TestThread2 a 2000 0");
    String[] args2 = SysLib.stringToArgs("TestThread2 b 1000 0");
    SysLib.exec(args1);
    SysLib.exec(args2);
    for (int i = 0; i < 2; i++)
    {
      SysLib.join();
    }

    // SysLib.cout( "Test2 finished\n" );
    SysLib.exit();
  }
}
