package rmi;

import java.io.IOException;
import java.rmi.Remote;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.util.logging.Level;
import java.util.logging.Logger;

public class CalculatorServer {

    
    public CalculatorServer(String host, String port, String service) {
        
        try {
            LocateRegistry.createRegistry(Integer.parseInt(port));
            System.out.println("Registar napravljen");
        } catch (RemoteException ex) {
            System.out.println("Registar vec postoji");
        }
        
        
        
        try{
            
            
            CalculatorImpl c = new CalculatorImpl();
            Naming.rebind("rmi://"+host+":"+port+"/"+service, c);
        
        }catch(Exception e){
        
        }
    }
    
    public static void main(String[] args){
        
    
        try {
            String a0 = "localhost";
            String a1 = "1007";
            String a2 = "calculator";
            new CalculatorServer(a0,a1,a2);
            
            System.in.read();
            System.exit(0);
        } catch (IOException ex) {
            Logger.getLogger(CalculatorServer.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
}
