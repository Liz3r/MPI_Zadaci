
package rmi_proba;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Racun extends UnicastRemoteObject implements IRacun{

    String imeKorisnika;
    int stanje;
    
    public Racun(String korisnik, int stanje) throws RemoteException{
        this.imeKorisnika = korisnik;
        this.stanje = stanje;
    }
    
    @Override
    public boolean Uplati(int kolicina) throws RemoteException {
        stanje += kolicina;
        return true;
    }

    @Override
    public boolean Podigni(int kolicina) throws RemoteException {
        if(stanje < kolicina){
            return false;
        }else{
            stanje -= kolicina;
            return true;
        }
    }

    @Override
    public boolean ProveriKorisnika(String korisnik) throws RemoteException {
        return imeKorisnika.equals(korisnik);
    }
    
}
