package rmi_proba;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IIspit extends Remote{
    
    public boolean prijaviIspit(Student stud) throws RemoteException;
    
    public int brojPrijavljenih() throws RemoteException;
    
    public String getSifra() throws RemoteException;
}
