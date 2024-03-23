
package jms_zbave;

import java.util.Date;
import java.util.List;
import java.util.Scanner;
import javax.jms.JMSException;
import javax.jms.MessageConsumer;
import javax.jms.Session;
import javax.jms.TextMessage;
import javax.jms.Topic;
import javax.jms.TopicConnection;
import javax.jms.TopicConnectionFactory;
import javax.jms.TopicPublisher;
import javax.jms.TopicSession;
import javax.jms.TopicSubscriber;
import javax.naming.InitialContext;
import javax.naming.NamingException;

public class Klijent {

    private final Topic tPoruke;
    private final TopicConnectionFactory tcf;
    private final TopicConnection tc;
    private final TopicSession ts;

    private String nadimak;
    private MessageConsumer subscriber;
    private TopicPublisher publisher;
    
    public Klijent() throws NamingException, JMSException{
        
        InitialContext ictx = new InitialContext();
        
        tPoruke = (Topic) ictx.lookup("tPoruke");
        tcf = (TopicConnectionFactory) ictx.lookup("tcf");
        
        ictx.close();
        
        tc = (TopicConnection) tcf.createTopicConnection();
        ts = (TopicSession) tc.createTopicSession(true, Session.AUTO_ACKNOWLEDGE);
        
    }
    
    public void Start(String nadimak) throws JMSException{
        //Scanner sc = new Scanner(System.in);
        //System.out.println("Unesi nadimak:");
        //this.nadimak = sc.next();
        if(nadimak == ""){
            return;
        }
        
        this.nadimak = nadimak;
        
        subscriber = ts.createConsumer(tPoruke, "primaoci LIKE " + "'%" + this.nadimak + "%'" );
        subscriber.setMessageListener(new NovaPorukaListener(this));
        
        tc.start();
        
        publisher = ts.createPublisher(tPoruke);
        
    }
    
    public void Posalji(String poruka, String naslov, List<String> primaoci) throws JMSException{
        
        TextMessage msg = ts.createTextMessage(poruka);
        String primaociString = "";
         
        for(String primalac : primaoci){
            primaociString += primalac + ",";
        }
        primaoci.remove(primaoci.size()-1);
        
        msg.setStringProperty("primaoci",primaociString);
        msg.setStringProperty("naslov", naslov);
        msg.setStringProperty("posiljalac", this.nadimak);
        msg.setStringProperty("date",(new Date()).toString());
        
        publisher.publish(msg);
        ts.commit();
    }

    void ObradiPrijem(String naslov, String posiljalac, String datum, String primaoci, String sadrzaj) {
        
        System.out.println("---------------------------------");
        System.out.println("Klijent " + this.nadimak + " primio poruku:" + naslov);
        System.out.println("od: " + posiljalac);
        System.out.println("datum: " + datum);
        System.out.println("primaoci: " + primaoci);
        System.out.println("sadrzaj: " + sadrzaj);
        System.out.println("---------------------------------");
    }
}
