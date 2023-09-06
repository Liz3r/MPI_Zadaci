
package rmi_proba;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface ISobaManager extends Remote{
    
    public void findSobe(int cena, int brojKreveta, boolean raspolozivost) throws RemoteException;
    
    public boolean rezervisiSobu(int id, Putnik p) throws RemoteException;
}
