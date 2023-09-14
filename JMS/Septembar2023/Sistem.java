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
        

        
        Klijent k1 = new Klijent(32.345,10.456);
        Klijent k2 = new Klijent(23.67,50.234);
        Klijent k3 = new Klijent(78.43,100.566);
        
        k1.Start();
        k2.Start();
        k3.Start();
        
        
        k1.ZatraziStanje(2);
        //k1.ZatraziStanje(3);
        
        
     
        
    }
    
    
  
    
}
