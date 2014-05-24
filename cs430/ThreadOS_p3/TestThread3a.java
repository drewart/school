class TestThread3a extends Thread
{
  private String name;
  
  public TestThread3a(String[] paramArrayOfString)
  {
  	this.name = paramArrayOfString[0];
  }
  
  public void run()
  {
      // run some math function 
      double d;
      
      for (int i = 0; i < 100000000 ; i++) 
      {
        for ( int j = 2; j < 4 ; j++)
          d = Math.pow(i,j);
      }
   
    SysLib.cout(this.name + " finished...\n");
    SysLib.exit();
  }
}

