
package rmi_proba;

import java.io.IOException;
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.util.ArrayList;

public class SobaManagerServer {
    
    
    public static void main(String[] args) throws RemoteException, MalformedURLException, IOException{
    
        ArrayList<Soba> sobe = new ArrayList<Soba>();
        Soba s1 = new Soba(700,2);
        Soba s2 = new Soba(900,4);
        Soba s3 = new Soba(300,1);
        Soba s4 = new Soba(200,1);
        Soba s5 = new Soba(450,2);
        Soba s6 = new Soba(670,5);
        Soba s7 = new Soba(920,3);
        Soba s8 = new Soba(550,4);
        Soba s9 = new Soba(500,4);
        
        sobe.add(s1);
        sobe.add(s2);
        sobe.add(s3);
        sobe.add(s4);
        sobe.add(s5);
        sobe.add(s6);
        sobe.add(s7);
        sobe.add(s8);
        sobe.add(s9);
        
        LocateRegistry.createRegistry(1004);
        
        ISobaManager mng = new SobaManager(sobe);
        
        Naming.rebind("rmi://localhost:1004/sobeManager", mng);
        
        System.in.read();
    }
}
