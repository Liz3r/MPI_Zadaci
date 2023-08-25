
package sistem;

import java.util.ArrayList;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.MessageConsumer;
import javax.jms.MessageListener;
import javax.jms.ObjectMessage;
import javax.jms.Queue;
import javax.jms.QueueConnection;
import javax.jms.QueueConnectionFactory;
import javax.jms.QueueReceiver;
import javax.jms.QueueSender;
import javax.jms.QueueSession;
import javax.jms.Session;
import javax.naming.InitialContext;
import javax.naming.NamingException;


public class Klijent {

    int id;
    ArrayList<String> mojiPoslovi;
    private final QueueConnectionFactory qcf;
    private final Object qPoslovi;
    
    public Klijent(int id) throws NamingException, JMSException
    {
      
        this.id = id;
        
        InitialContext ictx = new InitialContext();
        
        qPoslovi = ictx.lookup("qTrazePomoc");
        qcf = (QueueConnectionFactory)ictx.lookup("qcf");
        
        ictx.close();
     
      
    }
    
    public boolean DodajPosao(String posao){
        for(String el : mojiPoslovi){
            if(el == posao){
                return true;
            }else{
                mojiPoslovi.add(posao);
                return true;
            }
            
        }
        return false;
    }
    
    public boolean UkloniPosao(String posao){
        for(String el : mojiPoslovi){
            if(el == posao){
                this.mojiPoslovi.remove(el);
                return true;
            }
            
        }
        return false;
    }
    
    
    public void start() throws JMSException
    {
        
        
    }

    
  
}
