
package rmi_proba;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.List;

public class Banka extends UnicastRemoteObject implements IBanka{
    
    ArrayList<Racun> racuni;
    
    public Banka(ArrayList<Racun> r) throws RemoteException{
        racuni = r;
    }

    @Override
    public boolean Uplati(String korisnik, int kolicina) throws RemoteException {
        for(Racun r : racuni){
            if(r.ProveriKorisnika(korisnik) == true){
                if(r.Uplati(kolicina))
                    return true;
            }
        }
        return false;
    }

    @Override
    public boolean Podigni(String korisnik, int kolicina) throws RemoteException {
        for(Racun r : racuni){
            if(r.ProveriKorisnika(korisnik) == true){
                if(r.Podigni(kolicina))
                    return true;
            }
        }
        return false;
    }
    
}
