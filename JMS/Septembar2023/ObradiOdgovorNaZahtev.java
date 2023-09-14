
package sistem;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.MessageListener;


public class ObradiOdgovorNaZahtev implements MessageListener {

    Klijent cli;
            
    public ObradiOdgovorNaZahtev(Klijent k) {
        this.cli = k;
    }

    @Override
    public void onMessage(Message message) {
        try {
            this.cli.ObradiOdgovorNaZahtevv(message);
        } catch (JMSException ex) {
            Logger.getLogger(ObradiOdgovorNaZahtev.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
    
}
