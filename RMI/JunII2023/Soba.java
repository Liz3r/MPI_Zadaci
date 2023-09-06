
package rmi_proba;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;



public class Soba extends UnicastRemoteObject implements ISoba{

    static int idGen = 0;
    
    int id;
    int cena;
    int brojKreveta;
    
    Putnik rezervisao = null;
    
    public Soba(int cena, int brojKreveta, boolean raspoloziva) throws RemoteException{
        this.cena = cena;
        this.brojKreveta = brojKreveta;
        this.id = ++idGen;
    }
   

    @Override
    public boolean Rezervisi(Putnik p) throws RemoteException {
        if(rezervisao == null){
            this.rezervisao = p;
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
    public int getBrojKreveta() throws RemoteException {
        return this.brojKreveta;
    }

    @Override
    public boolean getRaspolozivost() throws RemoteException {
        return (rezervisao == null)? true: false;
    }

    @Override
    public void prikaziSobu() {
        System.out.println("ID: " + this.id);
        System.out.println("Cena: " + this.cena);
        System.out.println("Broj kreveta: " + this.brojKreveta);
        String slobodna = (rezervisao == null)? "slobodna":"zauzeta";
        System.out.println("Rezervisana: " + slobodna);
        System.out.println();
    }

    @Override
    public int getId() throws RemoteException {
        return this.id;
    }
    
}
