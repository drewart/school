
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class Logger {


   private static File file = new File("threados.log");

   public static void Log(String message) { 
      try {
	      synchronized ( file ) {
          if (!file.exists()) {
            file.createNewFile();
          }
          
          FileWriter fw = new FileWriter(file.getAbsoluteFile(),true /*append*/);
          BufferedWriter bw = new BufferedWriter(fw);
          bw.write(message);
          bw.write("\n");
          bw.close();
	      }
      } catch(IOException ioe) { System.err.println(ioe.toString()); }
   }
  
   public static void main(String[] args) {
      Log("a log message");
   }
}


