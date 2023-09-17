
package rmi_proba;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ISoba extends Remote{
    
    boolean isFree() throws RemoteException;
    
    boolean rezervisi(Putnik p) throws RemoteException;
    
    int getCena() throws RemoteException;
    
    int getBrKreveta() throws RemoteException;
    
    int getId() throws RemoteException;
}
