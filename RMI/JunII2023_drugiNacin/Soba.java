
package rmi_proba;

import java.io.Serializable;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Soba extends UnicastRemoteObject implements ISoba,Serializable{

    static int idGen = 0;
    int id;
    int cena;
    int brKreveta;
    Putnik korisnik;
    
    Soba(int cena, int brKreveta) throws RemoteException{
        this.cena = cena;
        this.brKreveta = brKreveta;
        this.korisnik = null;
        id = ++idGen;
    }
    
    @Override
    public boolean isFree() throws RemoteException {
        return (korisnik == null)? true:false;
    }

    @Override
    public boolean rezervisi(Putnik p) throws RemoteException {
        if(korisnik == null){
            korisnik = p;
            return true;
        }else{
            return false;
        }
    }

    @Override
    public int getCena() throws RemoteException {
       return this.cena;
    }

    @Override
    public int getBrKreveta() throws RemoteException {
        return this.brKreveta;
    }

    @Override
    public int getId() throws RemoteException {
        return this.id;
    }
    
    
}
