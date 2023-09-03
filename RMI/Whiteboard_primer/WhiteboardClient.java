
package rmi_proba;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.Scanner;

public class WhiteboardClient {
    
    public static Whiteboard obj = null;
    
    public static void main(String[] args) throws NotBoundException, MalformedURLException, RemoteException{
        
        String host = "localhost";
        String port = "1003";
        String service = "whiteboard";
        
        
        obj = (Whiteboard)Naming.lookup("rmi://"+host+":"+port+"/"+service);
        
        String option;
        Scanner sc = new Scanner(System.in);
        while(true){
        
            System.out.println("Option: (draw,read,exit)");
            option = sc.next();
            
            switch(option){
                case "draw":
                    System.out.println("Shape type:");
                    int type = sc.nextInt();
                    
                    System.out.println("Shape boja ispune:");
                    String bojaIspune= sc.next();
                    
                    System.out.println("Shape boja linije:");
                    String bojaLinije = sc.next();
                    
                    System.out.println("Shape indikator ispunjenosti:");
                    boolean indikator = (boolean)sc.nextBoolean();
                    
                    obj.dodajOblik(type, bojaIspune, bojaLinije, indikator);
                    
                case "read":
                    int i = 0;
                    for(IShape s : obj.preuzmiStanje()){
                        System.out.print(++i + ":   ");
                        s.showShape();
                    }
                case "exit":
                    return;
                    
                default:
                    return;
                
                
            }
                
            
            
            
            
            
        }
        
    }
}
