

public class SyncQueue
{
  private QueueNode[] queue = null;
  private final int QUEUE_MAX = 10;
  private final int NO_PID = -1;

  
  public SyncQueue()
  {
    init(QUEUE_MAX);
  }
  
  public SyncQueue(int size)
  {
    init(size);
  }
  
    
  private void init(int queueSize)
  {
    queue = new QueueNode[queueSize];
    for (int i = 0; i < queueSize; i++) {
      queue[i] = new QueueNode();
    }
  }
  
  public int enqueueAndSleep(int id)
  {
    if ((id >= 0) && (id < queue.length)) 
    {
      return queue[id].sleep();
    }
    return -1;
  }

    public void dequeueAndWakeup(int id, int tid)
  {
    if ((paramInt1 >= 0) && (paramInt1 < queue.length)) {
      queue[paramInt1].wakeup(paramInt2);
    }
  }

  public void dequeueAndWakeup(int paramInt)
  {
    dequeueAndWakeup(paramInt, 0);
  }
}

