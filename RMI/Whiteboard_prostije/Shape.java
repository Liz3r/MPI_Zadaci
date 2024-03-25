
package rmi;

import java.io.Serializable;

public class Shape implements Serializable{
    
    int tip;
    String bojaLinije;
    String bojaIspune;
    boolean indikator;
    
    public Shape(int tip, String bl, String bi, boolean ind){
        this.tip = tip;
        this.bojaLinije = bl;
        this.bojaIspune = bi;
        this.indikator = ind;
    }
    
    public String prikaz(){
        String ret = "tip: " + Integer.toString(this.tip) + "  boja linije: " + this.bojaLinije + "  boja ispune: " + this.bojaIspune + " indikator ispunjenosti: " + this.indikator;
        return ret;
    }
}
