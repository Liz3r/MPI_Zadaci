
package rmi_proba;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Vector;

public class SobaManager extends UnicastRemoteObject implements ISobaManager{

    Vector<Soba> sobe = null;
    
    public SobaManager(Vector<Soba> sobe) throws RemoteException{
        this.sobe = sobe;
    }
    @Override
    public void findSobe(int cena, int brojKreveta, boolean raspolozivost) throws RemoteException {
        boolean imaSlobodnih = false;
        for(Soba soba : sobe){
            if(soba.getCena() <= cena && soba.getBrojKreveta() == brojKreveta && soba.getRaspolozivost() == raspolozivost){
                soba.prikaziSobu();
                imaSlobodnih = true;
            }
        }
        
        if(!imaSlobodnih){
            System.out.println("Nema slobodnih soba");
        }
        System.out.println("--------------------------");
    }

    @Override
    public boolean rezervisiSobu(int id,Putnik p) throws RemoteException {
        for(Soba soba : sobe){
            if(soba.getId() == id){
                soba.Rezervisi(p);
                return true;
                
            }
        }
        return false;
    }
    
}
