
package rmi_proba;

import java.io.Serializable;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.Vector;

public class Ispit extends UnicastRemoteObject implements IIspit,Serializable{

    private String sifra;
    private Vector<Student> prijavili;
    
    public Ispit(String sifra) throws RemoteException{
        
        this.sifra = sifra;
        prijavili = new Vector<Student>();
    }
    
    
    
    @Override
    public boolean prijaviIspit(Student stud) throws RemoteException {
        for(Student s : prijavili){
            if(s.index == stud.index)
                return false;
        }
        prijavili.add(stud);
        return true;
    }

    @Override
    public int brojPrijavljenih() throws RemoteException {
        return this.prijavili.size();
    }

    @Override
    public String getSifra() throws RemoteException {
        return this.sifra;
    }
    
}
