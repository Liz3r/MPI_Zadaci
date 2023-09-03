
package rmi_proba;

import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Vector;

public interface Whiteboard extends Remote{
    
    public boolean dodajOblik(int type, String bojaIspune, String bojaLinije, boolean indikatorIspunjenosti) throws RemoteException;
    
    public Vector<IShape> preuzmiStanje() throws RemoteException;
    
}
