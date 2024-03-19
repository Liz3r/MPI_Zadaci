
package jms_zbave;

import java.util.List;
import javax.jms.JMSException;
import javax.jms.MessageConsumer;
import javax.jms.Session;
import javax.jms.Topic;
import javax.jms.TopicConnection;
import javax.jms.TopicConnectionFactory;
import javax.jms.TopicSession;
import javax.naming.InitialContext;
import javax.naming.NamingException;

public class Klijent {

    private final Topic tRezultati;
    private final TopicConnectionFactory tcf;
    private final TopicConnection tc;
    private final TopicSession ts;
    
    
    public Klijent() throws NamingException, JMSException{
        
        InitialContext ictx = new InitialContext();
        
        tRezultati = (Topic) ictx.lookup("tRezultati");
        
        tcf = (TopicConnectionFactory) ictx.lookup("tcf");
        
        ictx.close();
        
        tc = (TopicConnection) tcf.createTopicConnection();
        ts = (TopicSession) tc.createSession(true, Session.AUTO_ACKNOWLEDGE);
        
        
    }
    
    public void Start(List<Predmet> predmeti) throws JMSException{
        
        
        for(Predmet predmet : predmeti){
            MessageConsumer sub = ts.createConsumer(tRezultati, "(naziv = '" + predmet.NazivPredmeta + "') AND (sifra = '" + predmet.SifraPredmeta + "')");
            sub.setMessageListener(new RezultatiListener(this));
        }
        tc.start();
        
    }

    void obradiRezultate(Rezultati rezultati) {
        
        System.out.println("Rezultati:\n------" + rezultati.naziv + "----------" + rezultati.sifra + "-----------");
        for(torka t : rezultati.torke){
            System.out.println("|"+ t.brIndexa + " | " + t.ime + " | " + t.prezime + " | " + t.izasao + " | " + t.poeni);
        }
        System.out.println("Broj izaslih: " + rezultati.brIzaslih);
        System.out.println("Broj prijavljenih: " + rezultati.brPrijavljenih);
        System.out.println("Datum: " + rezultati.datum);
        System.out.println("----------------------------");
        System.out.println();
    }
}
