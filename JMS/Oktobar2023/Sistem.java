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
        

        Senzor sistem = new Senzor();
        
        Klijent k1 = new Klijent();
        Klijent k2 = new Klijent();
        
        k1.Start(30, 2.645);
        k2.Start(26.7,9.23);
        
        sistem.Posalji(30, 2.645);
        sistem.Posalji(30, 2.645);
        sistem.Posalji(30, 2.645);
        sistem.Posalji(30, 2.645);
        sistem.Posalji(30, 2.645);
        sistem.Posalji(30, 2.645);
        sistem.Posalji(26.7, 9.23);
        sistem.Posalji(26.7, 9.23);
        sistem.Posalji(26.7, 9.23);
        sistem.Posalji(26.7, 9.23);
        sistem.Posalji(26.7, 9.23);
        
        
        
        
        
    }
    
    
  
    
}
