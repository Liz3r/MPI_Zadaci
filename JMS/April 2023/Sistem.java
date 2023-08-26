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

/**
 *
 * @author Guster
 */
public class Sistem {


    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws JMSException, NamingException {
        

        
        Klijent k1 = new Klijent(1);
        Klijent k2 = new Klijent(2);
        Klijent k3 = new Klijent(3);
        
        k1.DodajPosao("Fotokopiranje");
        k2.DodajPosao("Stampanje");
        k2.DodajPosao("Pecatiranje");
        k3.DodajPosao("Stampanje");
        
        k1.start();
        k2.start();
        k3.start();
        
        
        k1.Pomoc("Stampanje");
     
        
    }
    
    
  
    
}
