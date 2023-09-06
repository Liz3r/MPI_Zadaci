
package rmi_proba;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public interface ISoba extends Remote{
    
    public int getCena() throws RemoteException;
    public int getBrojKreveta() throws RemoteException;
    public boolean getRaspolozivost() throws RemoteException;
    public int getId() throws RemoteException;
    public void prikaziSobu() throws RemoteException;
    
    public boolean Rezervisi(Putnik p) throws RemoteException;
}
