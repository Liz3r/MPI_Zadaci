
package jms_zbave;

import java.io.Serializable;


public class torka implements Serializable{
    
    int brIndexa;
    String ime;
    String prezime;
    boolean izasao;
    double poeni;
    
    public torka(int brIndexa, String ime, String prezime, boolean izasao, double poeni){
        this.brIndexa = brIndexa;
        this.ime = ime;
        this.prezime = prezime;
        this.izasao = izasao;
        this.poeni = poeni;
    }
}
