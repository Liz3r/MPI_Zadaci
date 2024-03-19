
package jms_zbave;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import javax.jms.JMSException;
import javax.jms.ObjectMessage;
import javax.jms.Session;
import javax.jms.Topic;
import javax.jms.TopicConnection;
import javax.jms.TopicConnectionFactory;
import javax.jms.TopicPublisher;
import javax.jms.TopicSession;
import javax.naming.InitialContext;
import javax.naming.NamingException;


public class JMS_zbaVe {

    public static void main(String[] args) throws NamingException, JMSException {
        
        Klijent k1 = new Klijent();
        Klijent k2 = new Klijent();
        
        
        Predmet AOR = new Predmet("AOR", "2OER3425");
        Predmet OOP = new Predmet("OOP", "2OER7825");
        Predmet RS = new Predmet("RS", "2OER3827");
        Predmet DS = new Predmet("DS", "2OER9999");
        Predmet PS = new Predmet("PS", "2OER04256");
        
        InitialContext ictx = new InitialContext();
        Topic tRezultati = (Topic) ictx.lookup("tRezultati");
        TopicConnectionFactory tcf = (TopicConnectionFactory) ictx.lookup("tcf");
        ictx.close();
        TopicConnection tc = (TopicConnection) tcf.createTopicConnection();
        TopicSession ts = (TopicSession) tc.createSession(true, Session.AUTO_ACKNOWLEDGE);
        TopicPublisher publisher = ts.createPublisher(tRezultati);
        
        torka t11 = new torka(17460,"Petar", "Petrovic",true,65);
        torka t12 = new torka(17461,"Petar", "Markovic",true,65);
        torka t13 = new torka(17462,"Nikola", "Petrovic",true,65);
        torka t14 = new torka(17463,"Marko", "Markovic",true,65);
        
        torka t21 = new torka(17466,"Strahinja", "Petrovic",true,65);
        torka t22 = new torka(17467,"Goran", "Vasiljevic",true,65);
        torka t23 = new torka(17468,"Mitar", "Petrovic",true,65);
        torka t24 = new torka(17469,"Marko", "Stevanovic",true,65);
        
        List<torka> torke1 = new ArrayList<torka>();;
        torke1.add(t11);
        torke1.add(t12);
        torke1.add(t13);
        torke1.add(t14);
        
        List<torka> torke2 = new ArrayList<torka>();;
        torke2.add(t21);
        torke2.add(t22);
        torke2.add(t23);
        torke2.add(t24);
        
        Rezultati rez1 = new Rezultati(torke1,123,34,new Date(15345),"PS", "2OER04256");
        Rezultati rez2 = new Rezultati(torke2,6,3,new Date(153465),"DS", "2OER9999");
        
        
        List<Predmet> predmeti1  = new ArrayList<Predmet>();
        predmeti1.add(DS);
        
        List<Predmet> predmeti2  = new ArrayList<Predmet>();;
        predmeti1.add(PS);
        
        k1.Start(predmeti2);
        k2.Start(predmeti1);
        
        
        //slanje
        ObjectMessage pubMsg1 = ts.createObjectMessage(rez1);
        ObjectMessage pubMsg2 = ts.createObjectMessage(rez2);
        
        pubMsg1.setStringProperty("naziv", "PS");
        pubMsg1.setStringProperty("sifra", "2OER04256");
        
        pubMsg2.setStringProperty("naziv", "DS");
        pubMsg2.setStringProperty("sifra", "2OER9999");
        
        publisher.publish(pubMsg1);
        publisher.publish(pubMsg2);
        ts.commit();
        
    }
    
}
