
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
        Klijent k3 = new Klijent();
        Klijent k4 = new Klijent();
        Klijent k5 = new Klijent();
        Klijent k6 = new Klijent();
        Klijent k7 = new Klijent();
        
        k1.Start("djura");
        k2.Start("dzoni");
        k3.Start("tanja");
        k4.Start("deblja");
        k5.Start("milica");
        k6.Start("xxxpusislejerxxx");
        k7.Start("niko");
        
        List<String> p1 = new ArrayList<String>();
        p1.add("djura");
        p1.add("dzoni");
        
        k7.Posalji("Poruka neka nesto nekome saljem", "poruka prva", p1);
        
        List<String> p2 = new ArrayList<String>();
        p2.add("djura");
        p2.add("dzoni");
        p2.add("milica");
        p2.add("tanja");
        p2.add("deblja");
        
        k2.Posalji("druga poruka proba proba ", "poruka druga", p2);
        
        List<String> p3 = new ArrayList<String>();
        p3.add("djura");
        p3.add("dzoni");
        p3.add("milica");
        p3.add("tanja");
        p3.add("deblja");
        p3.add("niko");
        
        k6.Posalji("Jedna poruka svima ", "poruka treca", p3);
    }
    
}
