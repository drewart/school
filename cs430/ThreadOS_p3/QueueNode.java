import java.util.Vector;

public class QueueNode
{
  private Vector queue;
  
  public QueueNode()
  {
    queue = new Vector();
    queue.clear();
  }
  
  public synchronized int sleep()
  {
    if (queue.size() == 0) 
    {
      try
      {
        wait();
      }
      catch (InterruptedException localInterruptedException) {}
    }
    Integer localInteger = (Integer)queue.remove(0);
    return localInteger.intValue();
  }
  
  public synchronized void wakeup(int pid)
  {
    queue.add(new Integer(pid));
    notify();
  }
}
