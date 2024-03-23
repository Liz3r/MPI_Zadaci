
package jms_zbave;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.MessageListener;
import javax.jms.TextMessage;

public class NovaPorukaListener implements MessageListener {

    Klijent cli;
    
    public NovaPorukaListener(Klijent aThis) {
        this.cli = aThis;
    }

    @Override
    public void onMessage(Message message) {
        TextMessage msg = (TextMessage) message;
        
        String naslov;
        try {
            naslov = msg.getStringProperty("naslov");
            String posiljalac = msg.getStringProperty("posiljalac");
            String datum = msg.getStringProperty("date");
            String primaoci = msg.getStringProperty("primaoci");
            String sadrzaj = (String)msg.getText();
            
            this.cli.ObradiPrijem(naslov,posiljalac,datum,primaoci,sadrzaj);
        } catch (JMSException ex) {
            Logger.getLogger(NovaPorukaListener.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        
    }
    
}
