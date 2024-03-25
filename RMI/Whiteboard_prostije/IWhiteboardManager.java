
package rmi;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IWhiteboardManager extends Remote{
    
    public boolean add(Shape s) throws RemoteException;
    
    public String showTable() throws RemoteException;
}
