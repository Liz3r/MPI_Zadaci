
package rmi;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.logging.Level;
import java.util.logging.Logger;

public class CalculatorImpl extends UnicastRemoteObject implements Calculator{

    public CalculatorImpl() throws RemoteException
    {
        super();
    };
    
    @Override
    public long saberi(long a, long b) throws RemoteException {
        return a + b;
    }

    @Override
    public long oduzmi(long a, long b) throws RemoteException {
        return a - b;
    }

    @Override
    public long pomnozi(long a, long b) throws RemoteException {
        return a*b;
    }

    @Override
    public long podeli(long a, long b) throws RemoteException {
        if(b == 0){
            try {
                throw new Exception("deljenje nulom");
                
            } catch (Exception ex) {
                Logger.getLogger(CalculatorImpl.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        else {
            return a/b;
        }
        return 0;
    }
    
}
