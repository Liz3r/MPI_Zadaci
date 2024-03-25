
package rmi;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;
import java.util.List;

public class WhiteboardManager extends UnicastRemoteObject implements IWhiteboardManager{

    List<Shape> shapes;
    
    public WhiteboardManager() throws RemoteException{
        super();
        shapes = new ArrayList<Shape>();
    }
    
    @Override
    public boolean add(Shape s) throws RemoteException {
        shapes.add(s);
        return true;
    }

    @Override
    public String showTable() throws RemoteException {
        String ret = "";
        for(Shape s : shapes){
            ret += s.prikaz() + "\n";
        }
        return ret;
    }
    
}
