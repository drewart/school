import java.util.Vector;

public class QueueNode
{
  private Vector queue;
  
   /**
   * QueueNode() based on QueueNode class for waking and waiting thread ids
   * 
   */
  public QueueNode()
  {
    queue = new Vector();
  }
  
  /**
  *  calls wait if the queue size is 0
  *  @return the thread id waiting on
  */
  public synchronized int threadWait()
  {
    // wait for queue to grow
    if (queue.size() == 0)
    {
        try
        {
            this.wait();
        }
        catch (Exception ignore) {}
    }
    // pop first thread id
    Integer tid = (Integer)queue.remove(0);
    return tid.intValue();
  }

  /**
   * thread id
   * @param tid
   */
  public synchronized void threadWakeUp(int tid)
  {
    // add thread id to queue
    queue.add(new Integer(tid));
    this.notify();
  }
}
