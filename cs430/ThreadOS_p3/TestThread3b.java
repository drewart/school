class TestThread3b extends Thread
{
  private String name;
  
  public TestThread3b(String[] paramArrayOfString)
  {
  	this.name = paramArrayOfString[0];
  }
  
  public void run()
  {
      // reads bytes from disk
      byte[] bytes = new byte[512];
      for (int i = 0; i < 500; i++) 
      {
        SysLib.rawread(i, bytes);
      }
   
    SysLib.cout(this.name + " finished...\n");
    SysLib.exit();
  }
}

