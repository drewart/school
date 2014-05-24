
/**
* SyncQueue class a monitor class
*/
public class SyncQueue
{
  private QueueNode[] queue = null;
  private final int QUEUE_MAX = 10;
  private final int NO_PID = -1;

  /**
  *  default constructor
  */
  public SyncQueue()
  {
    init(QUEUE_MAX);
  }
  
  /**
  * @param size is the size of the queue
  */
  public SyncQueue(int size)
  {
    init(size);
  }
  
  /**
  * setup queue size of QueueNode
  * @param queueSize size of the queue of threads
  */
  private void init(int queueSize)
  {
    // builds init queue
    queue = new QueueNode[queueSize];
    for (int i = 0; i < queueSize; i++) 
      queue[i] = new QueueNode();
  }
  
  /**
  * enqueueAndSleep
  * @param tid  to enqueue and sleep/wait
  * @return child id waiting on
  */
  public int enqueueAndSleep(int id)
  {
    //Logger.Log("enqueue : " + id);
    if ((id >= 0) && (id < queue.length)) 
    {
      return queue[id].threadWait();
    }
    return -1;
  }
  
  /**
  * dequeueAndWakeup used in join()
  * @param pid the parent id to dequeue and wake up
  * @param tid the child id to wake
  */
  public void dequeueAndWakeup(int pid, int tid)
  {
    //Logger.Log("dequeue : " + pid + " : " + tid);
    if ((pid >= 0) && (pid < queue.length)) 
    {
      queue[pid].threadWakeUp(tid);
    }
  }
  
  /**
  * dequeueAndWakeup
  * @param pid the parent id to dequeue and wake up
  */
  public void dequeueAndWakeup(int pid)
  {
    dequeueAndWakeup(pid, 0);
  }
}

