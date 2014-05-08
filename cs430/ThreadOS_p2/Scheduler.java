import java.util.*;
import java.util.logging.Logger;

public class Scheduler extends Thread
{
  
  //private final static Logger LOGGER = Logger.getLogger(Scheduler.class.getName());  

  
    private Vector queue0;
    private Vector queue1;
    private Vector queue2;
    
    
    private int timeSlice;
    private static final int DEFAULT_TIME_SLICE = 500;

    // New data added to p161 
    private boolean[] tids; // Indicate which ids have been used
    private static final int DEFAULT_MAX_THREADS = 10000;

    // A new feature added to p161 
    // Allocate an ID array, each element indicating if that id has been used
    private int nextId = 0;
    private void initTid( int maxThreads ) {
      tids = new boolean[maxThreads];
      for ( int i = 0; i < maxThreads; i++ )
          tids[i] = false;
    }

    // A new feature added to p161 
    // Search an available thread ID and provide a new thread with this ID
    private int getNewTid( ) {
      for ( int i = 0; i < tids.length; i++ ) {
          int tentative = ( nextId + i ) % tids.length;
          if ( tids[tentative] == false ) {
        tids[tentative] = true;
        nextId = ( tentative + 1 ) % tids.length;
        return tentative;
          }
      }
      return -1;
    }

    // A new feature added to p161 
    // Return the thread ID and set the corresponding tids element to be unused
    private boolean returnTid( int tid ) {
      if ( tid >= 0 && tid < tids.length && tids[tid] == true ) {
          tids[tid] = false;
          return true;
      }
      return false;
    }

    // A new feature added to p161 
    // Retrieve the current thread's TCB from the queue0
    public TCB getMyTcb( ) {
      Thread myThread = Thread.currentThread( ); // Get my thread object
      synchronized( queue0 ) {
          for ( int i = 0; i < queue0.size( ); i++ ) {
            TCB tcb = ( TCB )queue0.elementAt( i );
            Thread thread = tcb.getThread( );
            if ( thread == myThread ) // if this is my TCB, return it
                return tcb;
          }
      }
      
      synchronized( queue1 ) {
          for ( int i = 0; i < queue1.size( ); i++ ) {
            TCB tcb = ( TCB )queue1.elementAt( i );
            Thread thread = tcb.getThread( );
            if ( thread == myThread ) // if this is my TCB, return it
                return tcb;
          }
      }
      
      synchronized( queue2 ) {
          for ( int i = 0; i < queue2.size( ); i++ ) {
            TCB tcb = ( TCB )queue2.elementAt( i );
            Thread thread = tcb.getThread( );
            if ( thread == myThread ) // if this is my TCB, return it
                return tcb;
          }
      }
      
      return null;
    }

    

    
    // A new feature added to p161 
    // Return the maximal number of threads to be spawned in the system
    public int getMaxThreads( ) {
      return tids.length;
    }
    
    


    

    public Scheduler( ) {
      timeSlice = DEFAULT_TIME_SLICE;
      queue0 = new Vector( );
      queue1 = new Vector( );
      queue2 = new Vector( );
      initTid( DEFAULT_MAX_THREADS );
      
    }

    public Scheduler( int quantum ) {
      timeSlice = quantum;
      queue0 = new Vector( );
      queue1 = new Vector( );
      queue2 = new Vector( );
      initTid( DEFAULT_MAX_THREADS );
      
    }

    // A new feature added to p161 
    // A constructor to receive the max number of threads to be spawned
    public Scheduler( int quantum, int maxThreads ) {
      timeSlice = quantum;
      queue0 = new Vector( );
      queue1 = new Vector( );
      queue2 = new Vector( );
      initTid( maxThreads );
      
    }

    private void schedulerSleep( ) {
      try {
          Thread.sleep( timeSlice );
      } catch ( InterruptedException e ) {
      }
    }

    // A modified addThread of p161 example
    public TCB addThread( Thread t ) {
      //t.setPriority( 2 );
      TCB parentTcb = getMyTcb( ); // get my TCB and find my TID
      int pid = ( parentTcb != null ) ? parentTcb.getTid( ) : -1;
      int tid = getNewTid( ); // get a new TID
      if ( tid == -1)
          return null;
      TCB tcb = new TCB( t, tid, pid ); // create a new TCB
      queue0.add( tcb );
      return tcb;
    }

    // A new feature added to p161
    // Removing the TCB of a terminating thread
    public boolean deleteThread( ) {
      TCB tcb = getMyTcb( ); 
      if ( tcb!= null )
          return tcb.setTerminated( );
      else
          return false;
    }

    public void sleepThread( int milliseconds ) {
      try {
          sleep( milliseconds );
      } catch ( InterruptedException e ) { }
    }
    
    private synchronized boolean hasLowerQueue()
    {
      return (queue0.size( ) != 0) && (queue1.size() != 0);
    }
    
    // A modified run of p161
    public void run( ) {
      Thread current = null;
    
      //this.setPriority( 6 );
      int timeFactor = 1;
      
      while ( true ) {
          try {
            boolean inFCFSQueue = false;
            TCB currentTCB = null;
            // get the next TCB and its thread
                  
            if ( queue0.size( ) != 0) {
              Log.Log("in queue 0");
              currentTCB = (TCB)queue0.firstElement( );
              timeFactor = 1;
            } else if (queue1.size() != 0) {
              Log.Log("in queue 1");
              currentTCB = (TCB)queue1.firstElement( );
              timeFactor = 2;
            } else if (queue2.size() != 0) {
              Log.Log("in queue 2");
              currentTCB = (TCB)queue2.firstElement( );
              inFCFSQueue = true;
              timeFactor = 4;
              
            } else {
              continue;
            }

            //LOGGER.info(String.format("queue : %d",timeFactor));
            //LOGGER.info("term: " + currentTCB.getTerminated( ));
            
            Log.Log(String.format("queue : %d",timeFactor));
            Log.Log("term: " + currentTCB.getTerminated( ));
            
            if ( currentTCB.getTerminated( ) == true ) {
                if (queue0.contains( currentTCB ))
                  queue0.remove( currentTCB );
                
                if (queue1.contains( currentTCB ))
                  queue1.remove( currentTCB );
                  
                if (queue2.contains( currentTCB ))
                  queue2.remove( currentTCB );
                  
                returnTid( currentTCB.getTid( ) );
                continue;
            }
            
            current = currentTCB.getThread( );
            if ( current != null ) {
                if ( current.isAlive( ) ) {
                  current.resume();   //current.setPriority( 4 );
                } else {
                  // Spawn must be controlled by Scheduler
                  // Scheduler must start a new thread
                    Log.Log("starting " + current.getName().toString() );
                    Log.Log("isAlive " + current.isAlive() );
                    Log.Log("getState " + current.getState().toString() );
                    if (current.getState() != Thread.State.TERMINATED)
                      current.start( ); 
                  
                  //current.setPriority( 4 );
                }
            }
            
            // sleep for a factor
            for(int i = 0; i < timeFactor; i++)
            {
              schedulerSleep( );
              if (inFCFSQueue && hasLowerQueue()) //break sleep to work on lower queue 
                break;
            }
            
            // System.out.println("* * * Context Switch * * * ");
    
            if ( current != null && current.isAlive( ) )
                current.suspend(); //current.setPriority( 2 );
              
            synchronized ( queue0 ) {
              // move q0 to q1
              if (queue0.contains( currentTCB )) {
                queue0.remove( currentTCB ); // rotate this TCB to the end
                
                synchronized ( queue1 ) {
                  queue1.add( currentTCB );
                }
                continue;
              }
            }
            // move q1 to q2
            synchronized ( queue1 ) {
              if (queue1.contains(currentTCB)) {
                  queue1.remove( currentTCB ); // rotate this TCB to the end
                  
                synchronized ( queue2 ) {
                  queue2.add( currentTCB );
                }		
                continue;								
              }
            }
            
            // FCFS modifed  round-robin timeSlice * 2
            synchronized ( queue2 ) {
              if (queue2.contains( currentTCB )) {
                  queue2.remove( currentTCB );
                  queue2.add( currentTCB );   //add to end of queue
                  continue;
              }
            }
            
          } catch ( NullPointerException e3 ) { 
          } catch ( IllegalThreadStateException ite ) { System.out.println(ite.toString()); }
          
      }
      
    } // end run()

}//end class