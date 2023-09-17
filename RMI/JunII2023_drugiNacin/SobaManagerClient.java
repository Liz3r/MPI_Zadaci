
package rmi_proba;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.ArrayList;
import java.util.Scanner;

public class SobaManagerClient {
    
    
    public static void main(String[] args) throws NotBoundException, MalformedURLException, RemoteException{
        
        
        ISobaManager mng = (ISobaManager) Naming.lookup("rmi://localhost:1004/sobeManager");
        
        Scanner sc = new Scanner(System.in);
        String option;
        
        while(true){
            
            System.out.println("Izaberi opciju (prikaz,rezervacija,exit)");
            option = sc.next();
            
            if(option.equals("prikaz")){
                int c,bk;
                System.out.println("Maksimalna cena:");
                c = sc.nextInt();
                System.out.println("Broj kreveta:");
                bk = sc.nextInt();
                
                String por = (String)mng.prikaziSobe(c, bk);
                
                System.out.println(por);
                
                
                
            }else if(option.equals("rezervacija")){
            
                String ime,prezime;
                int jmbg;
                int ids;
                
                System.out.println("Ime:");
                ime = sc.next();
                System.out.println("Prezime");
                prezime = sc.next();
                System.out.println("JMBG:");
                jmbg = sc.nextInt();
                System.out.println("ID zeljene sobe:");
                ids = sc.nextInt();
                
                Putnik p = new Putnik(ime,prezime,jmbg);
                
                String odg = mng.rezervisiSobu(ids, p);
                System.out.println(odg);
            }else if(option.equals("exit")){
                return;
            }else{
                System.out.println("Nepostojeca opcija");
            }
        
        }
    }
}
