import java.io.*;
import java.util.*;

public class Shell extends Thread 
{

 static int historyCnt = 0;
 
 static String shellPrompt = "shell[hist]% ";

 //ctor 
 public Shell()
 {

 }


 // public thread run call
 public void run()
 {
   // waiting shell
   while(true)
   {
     String commandLine;
     // wait for input
     do { 
       StringBuffer buffer = new StringBuffer();
       SysLib.cerr(shellPrompt.replaceAll("hist",Integer.toString(historyCnt)));
       SysLib.cin( buffer );

       commandLine = buffer.toString();
 
     } while (commandLine.length() == 0);

     SysLib.cout("running: " + commandLine+"\n");
      
     StringTokenizer tokens = new StringTokenizer(commandLine);

     String cmd,arg = "";

     // build command split by dilims ;,&
     while(tokens.hasMoreTokens())
     {
         StringBuffer args = new StringBuffer();
         cmd = tokens.nextToken();

         // handle exit
         if (cmd.equals("exit"))
         {
           SysLib.sync(); 
           SysLib.exit();
           return;
         }
         
         // gets the args for the command
         while(tokens.hasMoreTokens())
         {
            arg = tokens.nextToken().trim();
	    SysLib.cout("arg: '" + arg + "'\n");

            if (arg.equals(";") || arg.equals("&"))
            {
                SysLib.cout("break");
		break;
            }

            if (args.length() > 0)
              args.append(" ");
	    
            args.append(arg);
         }
         
         String command =  cmd; 
         if (args.length() > 0) 
            command += " " + args.toString(); 

         SysLib.cout("running command: '" + cmd + "' Args:'" + args.toString() + "'\n");

         String cmdArray[] = SysLib.stringToArgs( command );

         if (SysLib.exec(cmdArray) < 0)
         {
            SysLib.cerr("Error executing: '" + command + "'\n");
         }

         if (arg.trim() == ";" || !tokens.hasMoreTokens())
            SysLib.join();     // wait for child to finish
     }

     historyCnt++;

     //while (SysLib.join() > 0) { SysLib.sleep(200); }   //make sure all child threads are done before next command

   }//end while
  

 }//end run


}//end class
