
package sistem;

import java.io.Serializable;

public class Podaci implements Serializable{
    
    int id;
    double zeljenaTemp;
    double dozvoljenoOdstupanje;
    double izmerenaTemp;
    
    public Podaci(int id, double zeljenaTemp, double dozvoljenoOdstupanje, double izmerenaTemp){
        this.id = id;
        this.zeljenaTemp = zeljenaTemp;
        this.dozvoljenoOdstupanje = dozvoljenoOdstupanje;
        this.izmerenaTemp = izmerenaTemp;
    }
}
