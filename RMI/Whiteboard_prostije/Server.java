
package rmi;

import java.io.IOException;
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;

public class Server {
    
    
    public static void main(String[] args) throws RemoteException, MalformedURLException, IOException{
        
        LocateRegistry.createRegistry(3432);
        
        IWhiteboardManager mng = new WhiteboardManager();
        Naming.rebind("rmi://localhost:3432/manager", mng);
        
        System.in.read();
    }
}
