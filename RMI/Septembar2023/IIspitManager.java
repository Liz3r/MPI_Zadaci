package rmi_proba;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IIspitManager extends Remote{
    
    public boolean prijaviIspit(Student stud, String sifra) throws RemoteException;
    
    public int brojPrijavljenih(String sifra) throws RemoteException;
    
    
}
