
package rmi_proba;

import java.io.Serializable;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Student implements Serializable{
    
    public int index;
    public String ime;
    public String prezime;
    public String email;
    
    public Student(int index, String ime, String prezime, String email) throws RemoteException{
        
        this.index = index;
        this.ime = ime;
        this.prezime = prezime;
        this.email = email;
    }
    
    
}
