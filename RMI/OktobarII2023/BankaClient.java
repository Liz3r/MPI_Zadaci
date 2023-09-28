package rmi_proba;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Scanner;

public class BankaClient {
    
    
    public static void main(String[] args) throws NotBoundException, MalformedURLException, RemoteException{
    
        String host = "localhost";
        String port = "1007";
        String service = "bankaService";
        
        
        
        IBanka banka = (IBanka) Naming.lookup("rmi://"+host+":"+port+"/"+service);
        
        Scanner sc = new Scanner(System.in);
        String opcija;
        while(true){
            System.out.println("Odaberi opciju: (podigni, uplati, exit)");
            opcija = sc.nextLine();
            
            if(opcija.equals("podigni")){
                System.out.println("Ime korisnika:");
                String ime = sc.nextLine();
                System.out.println("Kolicina:");
                int kolicina = sc.nextInt();
                
                if(banka.Podigni(ime, kolicina)){
                    System.out.println("Podizanje izvrseno");
                }else{
                    System.out.println("Greska");
                }
                
            }else if(opcija.equals("uplati")){
                System.out.println("Ime korisnika:");
                String ime = sc.nextLine();
                System.out.println("Kolicina:");
                int kolicina = sc.nextInt();
                
                if(banka.Uplati(ime, kolicina)){
                    System.out.println("Uplata izvrsena");
                }else{
                    System.out.println("Greska");
                }
                
            }else if(opcija.equals("exit")){
                return;
            }else{
                System.out.println("Nevalidna opcija");
            }
        }
    }
}
