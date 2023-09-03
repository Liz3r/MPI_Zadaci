package rmi_proba;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface IShape extends Remote{
    
    int getVersion() throws RemoteException;
    
    void setVersion(int newVersion) throws RemoteException;
    
    void showShape() throws RemoteException;
}
