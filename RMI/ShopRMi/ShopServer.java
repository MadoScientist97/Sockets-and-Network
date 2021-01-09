/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import static java.time.LocalDateTime.now;

public class ShopServer {
    public static void main(String [] args) throws Exception{
	 //System.setProperty("java.rmi.server.hostname", "10.0.0.1");
      Registry registry;
      String s_name="RMIServer";
      String hostname = "localhost";
      int port= 10001;
      
      try { 
         // Instantiating the implementation class 
         String bindLocation = "rmi://" + hostname + ":" + port + "/"+s_name;
         ShopI skeleton = new Shop(20,20,20); 
         registry = LocateRegistry.createRegistry(port);
         System.out.println("Registry created");
         registry.rebind(s_name,skeleton); 
         System.out.println("Server ready"); 
         
         while(true){
         //Timestamp ts = new Timestamp(time);
         System.out.println("\nAvailable Item: Time:"+now());
         System.out.println(skeleton.toString());
         Thread.sleep(2000);
         }
         
      } catch (RemoteException e) { 
         System.out.println("Server exception: " + e.getMessage()); 
         
      } 
    
}
   
}
