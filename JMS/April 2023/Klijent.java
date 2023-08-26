
package sistem;

import com.sun.accessibility.internal.resources.accessibility;
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
import javax.jms.TextMessage;
import javax.naming.InitialContext;
import javax.naming.NamingException;


public class Klijent {

    int id;
    ArrayList<String> mojiPoslovi = new ArrayList<String>();
    private final QueueConnectionFactory qcf;
    private final Queue qPoslovi;
    private final QueueConnection qc;
    private final QueueSession qs;
    private QueueReceiver qPomocListener;
    private final Queue qSaljePomoc;
    private QueueSender qPomocSender;
    private QueueReceiver qOdgovorListener;
    private QueueSender qTraziPomoc;
    
    public Klijent(int id) throws NamingException, JMSException
    {
      
        this.id = id;
        
        InitialContext ictx = new InitialContext();
        
        qPoslovi = (Queue)ictx.lookup("qTrazePomoc");
        qSaljePomoc = (Queue)ictx.lookup("qSaljePomoc");
        qcf = (QueueConnectionFactory)ictx.lookup("qcf");
        
        ictx.close();
     
        qc = (QueueConnection) qcf.createQueueConnection();
        qs = (QueueSession) qc.createSession(true, Session.AUTO_ACKNOWLEDGE);
        
      
    }
    
    
    public void Pomoc(String posao) throws JMSException
    {
        
        Message msg = qs.createMessage();
        msg.setStringProperty("posao", posao);
        msg.setIntProperty("myId", this.id);
        qTraziPomoc.send(msg);
        System.out.println(this.id + " Trazim pomoc");
        qs.commit();
    }    
    public void start() throws JMSException
    {
        
        String mSelect = "";
        for(String el : this.mojiPoslovi){
            if(this.mojiPoslovi.indexOf(el) == this.mojiPoslovi.size()-1){
                mSelect += "(posao = '" + el + "')";
            }else{
                mSelect += "(posao = '" + el + "') OR ";
            }
        }
        qPomocListener = (QueueReceiver)qs.createReceiver(qPoslovi, mSelect);
        
        qPomocListener.setMessageListener(new ObradiZahtevZaPoslom(this));
        
        qTraziPomoc = (QueueSender) qs.createSender(qPoslovi);
        qPomocSender = (QueueSender)qs.createSender(qSaljePomoc);
        
        qOdgovorListener = (QueueReceiver)qs.createReceiver(qSaljePomoc, "kome = " +this.id);
        
        qOdgovorListener.setMessageListener(new OdgovorListener(this));
        
        qc.start();
    }
    
    public boolean DodajPosao(String posao){
        if(this.mojiPoslovi.size() >= 1){
        for(String el : this.mojiPoslovi){
            if(el == posao){
                return true;
            }else{
                this.mojiPoslovi.add(posao);
                return true;
            }
            
        }
        return false;
        }else{
            this.mojiPoslovi.add(posao);
            return true;
        }
    }
    
    public boolean UkloniPosao(String posao){
        for(String el : this.mojiPoslovi){
            if(el == posao){
                this.mojiPoslovi.remove(el);
                return true;
            }
            
        }
        return false;
    }

    void obradiZahtev(Message message) throws JMSException {
        
        int koTrazi = message.getIntProperty("myId");
        
        TextMessage msg = qs.createTextMessage();
        msg.setIntProperty("kome", koTrazi);
        msg.setIntProperty("ko", this.id);
        msg.setText(this.id + " pomogao bratu " + koTrazi);
        
        
        qPomocSender.send(msg);
        
        qs.commit();
        System.out.println(this.id + " pomogao bratu " + koTrazi);
        
    }

    void obradiOdgovor(Message message) throws JMSException {
        
        int ko = message.getIntProperty("ko");
        System.out.println(this.id+": hvala brate " + ko);
    }

    
    
    

    
  
}
