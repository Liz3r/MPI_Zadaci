
package rmi_proba;

import java.io.Serializable;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Vector;

public class IspitManager extends UnicastRemoteObject implements IIspitManager,Serializable{

    private Vector<Ispit> ispiti;
    
    public IspitManager(Vector<Ispit> ispiti) throws RemoteException{
        
        this.ispiti = ispiti;
    }
    @Override
    public boolean prijaviIspit(Student stud, String sifra) throws RemoteException {
        for(Ispit i : ispiti){
            if(i.getSifra().equals(sifra))
                if(i.prijaviIspit(stud))
                    return true;
                else 
                    return false;
        }
        return false;
    }

    @Override
    public int brojPrijavljenih(String sifra) throws RemoteException {
        for(Ispit i : ispiti){
            if(i.getSifra().equals(sifra))
                return i.brojPrijavljenih();
        }
        return -1;
    }
    
}
