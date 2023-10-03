
package sistem;

import java.io.Serializable;

class Poruka implements Serializable{
    
    String koSalje;
    String kada;
    String kome;
    String naslov;
    String sadrzaj;
    
    public Poruka(String koSalje, String kada, String kome, String naslov,String sadrzaj){
        this.koSalje = koSalje;
        this.kada = kada;
        this.kome = kome;
        this.naslov = naslov;
        this.sadrzaj = sadrzaj;
    }
}
