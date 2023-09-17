
package rmi_proba;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.List;

public interface ISobaManager extends Remote{
    
    String prikaziSobe(int maxCena, int brKreveta) throws RemoteException;
    
    String rezervisiSobu(int idSobe, Putnik put) throws RemoteException;
    
}
