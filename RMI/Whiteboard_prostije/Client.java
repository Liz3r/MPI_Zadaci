/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package rmi;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Scanner;

/**
 *
 * @author Guster
 */
public class Client {
    
    public static void main(String[] args) throws NotBoundException, MalformedURLException, RemoteException{
        
        
        IWhiteboardManager mng = (IWhiteboardManager) Naming.lookup("rmi://localhost:3432/manager");
        
        String opcija;
        Scanner sc = new Scanner(System.in);
        do{
            System.out.println("Odaberi opciju (dodaj, prikazi, exit):");
            opcija = sc.next();
            
            switch(opcija){
                case "dodaj":
                    
                    int tip;
                    String bl,bi;
                    boolean ind;
                    
                    System.out.println("Unesi parametre oblika");
                    System.out.println("Tip:");
                    tip = sc.nextInt();
                    System.out.println("Boja linije:");
                    bl = sc.next();
                    System.out.println("Indikator ispunjenosti (true/false):");
                    ind = sc.nextBoolean();
                    System.out.println("Boja ispune:");
                    bi = sc.next();
                    Shape s = new Shape(tip,bl,bi,ind);
                    mng.add(s);
                    break;
                    
                case "prikazi":
                    System.out.println(mng.showTable());
                    break;
                    
                case "exit":
                    return;
            }
            
            
        }while(opcija != "exit");
    }
}
