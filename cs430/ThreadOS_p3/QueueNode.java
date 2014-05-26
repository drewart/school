import java.util.Vector;

public class QueueNode
{
  private Vector queue;
  
  public QueueNode()
  {
    queue = new Vector();
  }
  
  public synchronized int sleep()
  {
    if (queue.size() == 0)
    {
        try
        {
            this.wait();
        }
        catch (InterruptedException localInterruptedException) {}
    }
    Integer tid = (Integer)queue.remove(0);
    return tid.intValue();
  }

  /**
   * thread id
   * @param tid
   */
  public synchronized void wakeup(int tid)
  {
    queue.add(new Integer(tid));
    this.notify();
  }
}
