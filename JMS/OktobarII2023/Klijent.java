
package sistem;

import java.util.ArrayList;
import java.util.Date;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.MessageConsumer;
import javax.jms.ObjectMessage;
import javax.jms.Queue;
import javax.jms.QueueConnection;
import javax.jms.QueueConnectionFactory;
import javax.jms.QueueReceiver;
import javax.jms.QueueSession;
import javax.jms.Session;
import javax.jms.Topic;
import javax.jms.TopicConnection;
import javax.jms.TopicConnectionFactory;
import javax.jms.TopicPublisher;
import javax.jms.TopicSession;
import javax.jms.TopicSubscriber;
import javax.naming.InitialContext;
import javax.naming.NamingException;




public class Klijent {

    String nadimak;
    String aktivan;
    
    private final TopicConnectionFactory tcf;
    private final Topic tPoruke;
    private final TopicConnection tc;
    private final TopicSession ts;
    private MessageConsumer tReciever;
    private TopicPublisher tSender;
    
    public Klijent() throws NamingException, JMSException
    {
       InitialContext ictx = new InitialContext();
       
       tcf = (TopicConnectionFactory) ictx.lookup("tcf");
       tPoruke = (Topic) ictx.lookup("tPoruke");
       
       ictx.close();
       
       tc = (TopicConnection) tcf.createConnection();
       ts = (TopicSession) tc.createSession(true,Session.AUTO_ACKNOWLEDGE);
       
    }
    public void Start(String nadimak) throws JMSException
    {
        this.nadimak = nadimak;
        
        tReciever = (MessageConsumer)ts.createConsumer(tPoruke, "nadimak='" + this.nadimak + "'");
        tSender = ts.createPublisher(tPoruke);
        
        tc.start();
        
        tReciever.setMessageListener(new PorukaListener(this));
    }

    void ObradiPoruku(ObjectMessage msg) throws JMSException {
        
        Poruka p = (Poruka) msg.getObject();
        
        System.out.println("---------------------------------");
        System.out.println("Klijent " + this.nadimak + " primio poruku:");
        System.out.println("od: " + p.koSalje);
        System.out.println("vreme: " + p.kada);
        System.out.println("primaoci: " + p.kome);
        System.out.println("naslov: " + p.naslov);
        System.out.println("sadrzaj: " + p.sadrzaj);
        System.out.println("---------------------------------");
    }

    public void PosaljiPoruku(ArrayList<String> kome, String naziv, String sadrzaj) throws JMSException{
        
        String komeSve = "";
        
        for(String k : kome){
            komeSve += k + " ";
        }
        String kada = "12/3/2023 23:34";
        
        Poruka p = new Poruka(this.nadimak,kada,komeSve,naziv,sadrzaj);
        
        for(String k : kome){
            
            ObjectMessage msg = ts.createObjectMessage(p);
            
            msg.setStringProperty("nadimak", k);
            tSender.send(msg);
            ts.commit();
        }
    }

    
}
