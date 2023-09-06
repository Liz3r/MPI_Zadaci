
package rmi_proba;

import java.io.Serializable;

public class Putnik implements Serializable{
    
    String ime;
    String prezime;
    int jmbg;
    
    public Putnik(String ime, String prezime, int jmbg){
        this.ime = ime;
        this.prezime = prezime;
        this.jmbg = jmbg;
    }
}
