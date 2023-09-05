
package rmi_proba;

import java.io.IOException;
import java.rmi.Naming;
import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.util.ArrayList;
import java.util.Vector;


public class SluzbaServer {
    
    public static void main(String[] args) throws RemoteException, IOException{
        
         
        String host = "localhost";
        String port = "1009";
        String service = "Sistem";
        
        LocateRegistry.createRegistry(Integer.parseInt(port));
        
        Vector<Ispit> ispiti = new Vector<Ispit>();
        
        Ispit i1 = new Ispit("2OE456B");
        Ispit i2 = new Ispit("2OE456C");
        Ispit i3 = new Ispit("2OE452B");
        Ispit i4 = new Ispit("2OE356F");
        Ispit i5 = new Ispit("2OE356K");
        
        ispiti.add(i1);
        ispiti.add(i2);
        ispiti.add(i3);
        ispiti.add(i4);
        ispiti.add(i5);
       
        IIspitManager imng = new IspitManager(ispiti);
        
        Naming.rebind("rmi://"+host+":"+port+"/"+service, imng);
        System.in.read();
    }
}
