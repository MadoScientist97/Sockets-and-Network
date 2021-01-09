import java.rmi.*;
interface ShopI extends Remote{
        public String getItem(String f,int num) throws RemoteException;
        
}
