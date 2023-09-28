
package rmi_proba;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public interface IRacun extends Remote{
    
    boolean Uplati(int kolicina) throws RemoteException;
    
    boolean Podigni(int kolicina) throws RemoteException;
    
    boolean ProveriKorisnika(String korisnik) throws RemoteException;
}
