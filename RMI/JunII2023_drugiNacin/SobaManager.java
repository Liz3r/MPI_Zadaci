
package rmi_proba;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.List;

public class SobaManager extends UnicastRemoteObject implements ISobaManager{

    ArrayList<Soba> sobe;
    
    SobaManager(ArrayList<Soba> sobe) throws RemoteException{
        this.sobe = sobe;
    }
    @Override
    public String prikaziSobe(int maxCena, int brKreveta) throws RemoteException {
        
        String ret = "";
        
        int cena,brKrev,id;
        boolean slobodna;
                
        for(Soba s : sobe){
            cena = s.getCena();
            brKrev = s.getBrKreveta();
            id = s.getId();
            slobodna = s.isFree();
            if(cena < maxCena && brKrev == brKreveta){
                    
            ret += "Soba ("+id+"):\n";
            ret += "----------------\n";
            ret += "Cena: " + cena + "\n";
            ret += "Broj kreveta: " + brKreveta + "\n";
            ret += "Raspolozivost: " + ((slobodna)?"Slobodna\n":"Zauzeta\n");
            ret += "+++++++++++++++++++++++++++++++++++++++++++++++++++++\n";
            }
           }
        if(ret.equals(""))
            ret = "Nema soba koje zadovoljavaju parametre";
        return ret;
    }

    @Override
    public String rezervisiSobu(int idSobe,Putnik put) throws RemoteException {
        
        
        for(Soba s : sobe){
            if(s.getId() == idSobe){
                if(s.isFree()){
                    s.rezervisi(put);
                    return "Soba rezervisana";
                }else{
                    return "Trazena soba nije slobodna";
                }
            }
        }
        return "Soba nije nadjena";
    }
    
}
