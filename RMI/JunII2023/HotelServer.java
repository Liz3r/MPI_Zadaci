
package rmi_proba;

import java.io.IOException;
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.util.Vector;

public class HotelServer {
    
    public static void main(String[] args) throws RemoteException, MalformedURLException, IOException{
        
        String host = "localhost";
        String port = "1010";
        String service = "hotelService";
        
        LocateRegistry.createRegistry(Integer.parseInt(port));
        
        Soba s1 = new Soba(500,3,true);
        Soba s2 = new Soba(800,5,true);
        Soba s3 = new Soba(300,2,true);
        Soba s4 = new Soba(200,2,true);
        Soba s5 = new Soba(600,3,true);
        Soba s6 = new Soba(900,3,true);
        
        Vector<Soba> sb = new Vector<Soba>();
        
        sb.add(s1);
        sb.add(s2);
        sb.add(s3);
        sb.add(s4);
        sb.add(s5);
        sb.add(s6);
        
        SobaManager mng = new SobaManager(sb);
        
        Naming.rebind("rmi://"+host+":"+port+"/"+service, mng);
        
        System.in.read();
    }
}
