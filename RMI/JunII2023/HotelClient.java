
package rmi_proba;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Scanner;

public class HotelClient {
    
    
    private static ISobaManager mng = null;
    
    public static void main(String[] args) throws NotBoundException, MalformedURLException, RemoteException{
        
        String host = "localhost";
        String port = "1010";
        String service = "hotelService";
        
        mng = (ISobaManager)Naming.lookup("rmi://"+host+":"+port+"/"+service);
        
        
        while(true){
            
            String opcija;
            System.out.println("Izaberi opciju: (sobe,rezervisi,exit)");
            
            Scanner sc = new Scanner(System.in);
            
            opcija = sc.next();
            
            if(opcija.equals("sobe")){
                int cena;
                int brojKreveta;
                boolean raspoloziva;
                
                System.out.println("Maksimalna cena: ");
                cena = sc.nextInt();
                System.out.println("Broj kreveta: ");
                brojKreveta = sc.nextInt();
                System.out.println("Raspoloziva: (true/false)");
                raspoloziva = sc.nextBoolean();
                
                mng.findSobe(cena, brojKreveta, raspoloziva);
                
            }else if(opcija.equals("rezervisi")){
                System.out.println("ID sobe: ");
                int id = sc.nextInt();
                
                System.out.println("PUTNIK INFO");
                System.out.println("Ime: ");
                String ime = sc.next();
                System.out.println("Prezime:");
                String prezime = sc.next();
                System.out.println("JMBG:");
                int jmbg = sc.nextInt();
                
                Putnik p = new Putnik(ime,prezime,jmbg);
                
                mng.rezervisiSobu(id, p);
                
            }else if(opcija.equals("exit")){
                return;
            }else{
                return;
            }
            
            
            
        }
        
    }
    
}
