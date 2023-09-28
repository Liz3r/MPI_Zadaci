
package rmi_proba;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IBanka extends Remote{
    
    boolean Uplati(String korisnik, int kolicina) throws RemoteException;
    
    boolean Podigni(String korisnik, int kolicina) throws RemoteException;
}
