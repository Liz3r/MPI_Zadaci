
package rmi_proba;

import java.io.IOException;
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;

public class WhiteboardServer{
    
    
    
    
    public static void main(String[] args) throws RemoteException, MalformedURLException, IOException{
        
        String host = "localhost";
        String port = "1004";
        String service = "whiteboard";
        
        LocateRegistry.createRegistry(Integer.parseInt(port));
        
        Whiteboard obj = new WhiteboardImpl();
        
        //rmi://localhost:1003/whiteboard
        Naming.rebind("rmi://"+host+":"+port+"/"+service, obj);
        System.in.read();
    }
}
