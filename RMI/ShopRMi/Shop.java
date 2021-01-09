/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Shop  extends UnicastRemoteObject implements ShopI {
   private int kiwi;
   private int mango;
   private int apple;

    public Shop(int kiwi, int mango, int apple) throws Exception{
        this.kiwi = kiwi;
        this.mango = mango;
        this.apple = apple;
    }

    @Override
    public String toString() {
        return  "\nKiwi= " + kiwi + "\nMango=" + mango + "\nApple=" + apple;
    }
    public boolean emptyBucket(int n)  throws RemoteException{
	
	if(this.mango ==0 || this.mango < n ){
		return false;	
	}	

	if(this.kiwi ==0 || this.kiwi < n){
		return false;	
	}

	if(this.apple ==0 || this.apple< n){
		return false;	
	}
	return true;
}
    @Override
    public synchronized String getItem(String f,int num) throws RemoteException {
	boolean available;	
        if("m".equals(f)){
		 
	    available=emptyBucket(num);
            if(available){ 
		mango=mango-num;
	    }
	    else{
		return num+" items Not Available " +"\n"+this.toString();
	  }
	}          
        if("k".equals(f)){
	    available=emptyBucket(num);
             if(available){ 
		kiwi=kiwi-num;
	    }
	    else{
		return num+" items Not Available"+"\n"+this.toString();
	  }         
        }
        if("a".equals(f)){
            available=emptyBucket(num);
             if(available){ 
		apple=apple-num;
	    }
	    else{
		return num+" items Not Available"+"\n"+this.toString();
	  }
        }
       return this.toString();
        
    }
     
    
}
