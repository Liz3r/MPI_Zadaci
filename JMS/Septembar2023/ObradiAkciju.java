
package sistem;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.MessageListener;

public class ObradiAkciju implements MessageListener {

    Klijent cli;
    public ObradiAkciju(Klijent aThis) {
        this.cli = aThis;
    }

    @Override
    public void onMessage(Message message) {
        try {
            this.cli.obradiNalog(message);
        } catch (JMSException ex) {
            Logger.getLogger(ObradiAkciju.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
