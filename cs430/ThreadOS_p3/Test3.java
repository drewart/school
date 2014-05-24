import java.util.Date;

class Test3 extends Thread
{
 
  public void run()
  {
    //runs 2 sets of math and dist threads
    String[] exec1 = SysLib.stringToArgs("TestThread3a math1");
    String[] exec2 = SysLib.stringToArgs("TestThread3b disk1");
    String[] exec3 = SysLib.stringToArgs("TestThread3a math2");
    String[] exec4 = SysLib.stringToArgs("TestThread3b disk2");
    
    long lastTime = new Date().getTime();
    
    
		SysLib.exec(exec1);
		SysLib.exec(exec2);
		SysLib.exec(exec3);
		SysLib.exec(exec4);
		
		SysLib.join();
		SysLib.join();
		SysLib.join();
		SysLib.join();
    
    long currentTime = new Date().getTime();
    
    SysLib.cout("elapsed time = " + (currentTime - lastTime) + " msec.\n");
    SysLib.exit();
  }
}

