
package rmi_proba;

import java.io.IOException;
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.util.ArrayList;
import java.util.List;

public class BankaServer {
    
    public static void main(String[] args) throws RemoteException, MalformedURLException, IOException{
        
        String host = "localhost";
        String port = "1007";
        String service = "bankaService";
        
        LocateRegistry.createRegistry(Integer.parseInt(port));
        
        ArrayList<Racun> racuni;
        racuni = new ArrayList<Racun>();
        
        Racun r1 = new Racun("Petar", 12000);
        Racun r2 = new Racun("Marko", 20000);
        Racun r3 = new Racun("Djordje", 32000);
        Racun r4 = new Racun("Darko", 10000);
        Racun r5 = new Racun("Milos", 5000);
        Racun r6 = new Racun("Ana", 56000);
        Racun r7 = new Racun("Petra", 34000);
        
        racuni.add(r1);
        racuni.add(r2);
        racuni.add(r3);
        racuni.add(r4);
        racuni.add(r5);
        racuni.add(r6);
        racuni.add(r7);
        
        Banka mng = new Banka(racuni);
        
        Naming.rebind("rmi://"+host+":"+port+"/"+service, mng);
        
        System.in.read();
        System.exit(0);
        
    }
}
