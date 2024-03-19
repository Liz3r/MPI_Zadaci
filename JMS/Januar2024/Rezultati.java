
package jms_zbave;

import java.io.Serializable;
import java.util.Date;
import java.util.List;

public class Rezultati implements Serializable{
    
    List<torka> torke;
    int brPrijavljenih;
    int brIzaslih;
    Date datum;
    String naziv;
    String sifra;
    
    public Rezultati(List<torka> torke, int prijavljenih, int izaslih, Date datum, String naziv, String sifra){
        this.torke = torke;
        this.brPrijavljenih = prijavljenih;
        this.brIzaslih = izaslih;
        this.datum = datum;
        this.naziv = naziv;
        this.sifra = sifra;
    }
    
}
