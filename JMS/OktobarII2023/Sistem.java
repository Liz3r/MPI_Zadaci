/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package sistem;

import java.util.ArrayList;
import javax.jms.JMSException;
import javax.jms.ObjectMessage;
import javax.jms.Topic;
import javax.jms.TopicConnection;
import javax.jms.TopicConnectionFactory;
import javax.jms.TopicPublisher;
import javax.jms.TopicSession;
import javax.naming.InitialContext;
import javax.naming.NamingException;


public class Sistem {


    public static void main(String[] args) throws JMSException, NamingException {
        
        Klijent k1 = new Klijent();
        Klijent k2 = new Klijent();
        Klijent k3 = new Klijent();
        Klijent k4 = new Klijent();
        Klijent k5 = new Klijent();
        Klijent k6 = new Klijent();
        
        k1.Start("Zika");
        k2.Start("Pera");
        k3.Start("Laza");
        k4.Start("Kurac lipov");
        k5.Start("Labud");
        k6.Start("Stojke556");
        
        ArrayList<String> lista = new ArrayList<String>();
        lista.add("Pera");
        lista.add("Laza");
        lista.add("Stojke556");
        
        k2.PosaljiPoruku(lista, "Poruka neka", "Neki sadrzaj neke poruke jebem li ga");
    }

    
  
    
}
