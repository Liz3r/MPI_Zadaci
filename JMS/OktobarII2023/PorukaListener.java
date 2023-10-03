
package sistem;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.MessageListener;
import javax.jms.ObjectMessage;

public class PorukaListener implements MessageListener {

    Klijent cli;
    
    public PorukaListener(Klijent cli) {
        this.cli = cli;
    }

    @Override
    public void onMessage(Message message) {
        try {
            this.cli.ObradiPoruku((ObjectMessage) message);
        } catch (JMSException ex) {
            Logger.getLogger(PorukaListener.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    
    
}
