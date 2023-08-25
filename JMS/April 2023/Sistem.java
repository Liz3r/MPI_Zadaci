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
        

        
        Klijent k1 = new Klijent();
        Klijent k2 = new Klijent();
        Klijent k3 = new Klijent();
        Klijent k4 = new Klijent();
        Klijent k5 = new Klijent();
        Klijent k6 = new Klijent();
        Klijent k7 = new Klijent();
        
        k1.start();
        k2.start();
        k3.start();
        k4.start();
        k5.start();
        k6.start();
        k7.start();
        
        
     
        
    }
    
    
  
    
}
