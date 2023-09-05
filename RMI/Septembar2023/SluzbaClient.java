package rmi_proba;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.Scanner;


public class SluzbaClient{
    
    private static IIspitManager mng = null;
    
    public static void main(String[] args) throws NotBoundException, RemoteException, MalformedURLException{
        String host = "localhost";
        String port = "1009";
        String service = "Sistem";
        
        mng = (IIspitManager) Naming.lookup("rmi://"+host+":"+port+"/"+service);
        
        Scanner sc = new Scanner(System.in);
        String option = "";
        
        while(true){
            
            System.out.println("Izaberi opciju: (prijavi,prebroj,exit)");
            option = sc.next();
            
            
                if(option.equals("prijavi")){
                    System.out.println("Ime: ");
                    String ime = sc.next();
                    
                    System.out.println("Prezime: ");
                    String prezime = sc.next();
                    
                    System.out.println("Index: ");
                    int index = sc.nextInt();
                    
                    System.out.println("Email: ");
                    String email = sc.next();
                    
                    System.out.println("Sifra ispita: ");
                    String sifra = sc.next();
                    
                    Student novi = new Student(index,ime,prezime,email);
                    
                    if(mng.prijaviIspit(novi, sifra))
                        System.out.println("Uspesna prijava!");
                    else
                        System.out.println("Neuspesna prijava!");
                }
                else if(option.equals("prebroj")){
                    System.out.println("Sifra ispita: ");
                    String sifraI = sc.next();
                    System.out.println(mng.brojPrijavljenih(sifraI));
                }
                else{
                    return;
                }
            
        }
        
        
        
    }
}
