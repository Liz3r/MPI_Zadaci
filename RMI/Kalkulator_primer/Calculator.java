
package rmi;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Calculator extends Remote{
    
    public long saberi(long a, long b) throws RemoteException;
    public long oduzmi(long a, long b) throws RemoteException;
    public long pomnozi(long a, long b) throws RemoteException;
    public long podeli(long a, long b) throws RemoteException;

}
