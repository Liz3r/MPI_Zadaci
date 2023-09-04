
package rmi_proba;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Vector;

public class WhiteboardImpl extends UnicastRemoteObject implements Whiteboard{
    
    private Vector<IShape> shapes;
    
    public WhiteboardImpl() throws RemoteException{
        
        shapes = new Vector<IShape>();
        
    }

    @Override
    public boolean dodajOblik(int type, String bojaIspune, String bojaLinije, boolean indikatorIspunjenosti) throws RemoteException {
        IShape ns = new Shape(type,bojaIspune, bojaLinije, indikatorIspunjenosti);
        shapes.addElement(ns);
        return true;
    }

    @Override
    public Vector<IShape> preuzmiStanje() throws RemoteException {
        return shapes;
    }

    
}
