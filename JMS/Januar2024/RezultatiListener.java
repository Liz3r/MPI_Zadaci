
package jms_zbave;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.MessageListener;
import javax.jms.ObjectMessage;

public class RezultatiListener implements MessageListener {

    Klijent cli;
    
    public RezultatiListener(Klijent aThis) {
        this.cli = aThis;
    }

    @Override
    public void onMessage(Message message) {
        ObjectMessage objMsg = (ObjectMessage) message;
        
        try {
            Rezultati rezultati = (Rezultati)objMsg.getObject();
            this.cli.obradiRezultate(rezultati);
            
        } catch (JMSException ex) {
            Logger.getLogger(RezultatiListener.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
