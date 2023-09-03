
package rmi_proba;

import java.rmi.RemoteException;

class Shape implements IShape{

    int type;
    String bojaIspune;
    String bojaLinije;
    boolean indikatorIspunjenosti;
    
    int version;
    
    public Shape(int type, String bojaIspune, String bojaLinije, boolean indikatorIspunjenosti){
        this.type = type;
        this.bojaIspune = bojaIspune;
        this.bojaLinije = bojaLinije;
        this.indikatorIspunjenosti = indikatorIspunjenosti;
    }
    
    @Override
    public int getVersion() throws RemoteException {
        return this.version;
    }

    @Override
    public void setVersion(int newVersion) throws RemoteException {
        this.version = newVersion;
    }

    @Override
    public void showShape() throws RemoteException {
        System.out.println("Verzija: " + this.version);
        System.out.println("Tip: " + this.type);
        System.out.println("Boja ispune: " + this.bojaIspune);
        System.out.println("Boja linije: " + this.bojaLinije);
        System.out.println("Indikator ispunjenosti: " + this.indikatorIspunjenosti);
    }
    
}
