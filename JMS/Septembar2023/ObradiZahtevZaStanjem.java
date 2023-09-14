
package sistem;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.MessageListener;
import javax.jms.ObjectMessage;


public class ObradiZahtevZaStanjem implements MessageListener {

    private Klijent cli;
    
    public ObradiZahtevZaStanjem(Klijent k) {
        this.cli = k;
    }

    @Override
    public void onMessage(Message message) {
        
        try {
            this.cli.ObradiZahtevZaStanjem(message);
        } catch (JMSException ex) {
            Logger.getLogger(ObradiZahtevZaStanjem.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
