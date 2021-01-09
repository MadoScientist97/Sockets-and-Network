/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.util.*;
import java.rmi.Naming;
import java.rmi.RemoteException;

public class ShopClient {
    
    public static void main(String args[]) throws RemoteException, InterruptedException{  
        if(args.length<3){
          System.out.println("\nPlease Enter Two arguements <Fruit Name> <Fruit Quantity> Fruitnames are Mango(m),Apple(a),Kiwi(k)");
          System.exit(1);
        }
        try{
           ShopI consumer_stub = (ShopI) Naming.lookup("rmi://"+args[0]+":10001/RMIServer");
           System.out.println("Connected to RMI server");
                System.out.println("---------------------------------");
                System.out.println("Items Available");
                System.out.println(consumer_stub.getItem(args[1],Integer.parseInt(args[2])));
                     

       }catch(Exception e){
           System.out.println(e.getMessage());
       }
    }
    
}
