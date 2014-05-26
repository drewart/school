
public class Cache 
{
  
  /**
  * The constructor: allocates a cacheBlocks number of cache blocks, each containing blockSize-byte data, on memory
  */
  public Cache( int blockSize, int cacheBlocks )
  {
    
  }
  
  
  /**
  * reads into the buffer[ ] array the cache block specified by blockId from the disk cache 
  * if it is in cache, otherwise reads the corresponding disk block from the disk device. 
  * Upon an error, it should return false, otherwise return true.
  */
  public boolean read( int blockId, byte buffer[ ] )
  {
    throw new Exception("not implemented");
  }
  
  /**
  *  writes the buffer[ ]array contents to the cache block 
  *  specified by blockId from the disk cache if it is in cache
  *  otherwise finds a free cache block and writes the buffer [ ] contents on it. 
  *  No write through. Upon an error, it should return false, otherwise return true.
  *  @param blockId id of the block of disk/memory
  *  @param buffer data to write to disk
  *  @return if successful
  */
  public boolean write( int blockId, byte buffer[ ] )
  {
    throw new Exception("not implemented");
  }
  

  /**
  * sync the cache to the disk if the buffers are dirty
  * writes back all dirty blocks to Disk.java and therefater forces Diskjava to write back all contents to the DISK file. The sync( ) method still maintains clean block copies in Cache.java,
  * method must be called when shutting down ThreadOS.
  */
  public void sync( ) 
  {
    throw new Exception("not implemented");
  }
  
  /**
  *  flush( ) method invalidates all cached blocks.
  *  should be called when you keep running a different test case without receiving any caching effects incurred by the previous test.
  */
  public void flush( )
  {
    throw new Exception("not implemented");
  }
}
