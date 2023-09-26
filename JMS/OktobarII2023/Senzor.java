
package sistem;

import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.Queue;
import javax.jms.QueueConnection;
import javax.jms.QueueConnectionFactory;
import javax.jms.QueueSender;
import javax.jms.QueueSession;
import javax.jms.Session;
import javax.naming.InitialContext;
import javax.naming.NamingException;

public class Senzor {

    private final Queue qPosaljiIzmerenuTemperaturu;
    private final QueueConnectionFactory qcf;
    private final QueueConnection qc;
    private final QueueSession qs;
    private final QueueSender sender;
 
    //ova klasa ne treba da se pise, ovde je samo radi provere
    
    public Senzor() throws NamingException, JMSException
    {
        
        InitialContext ictx = new InitialContext();
        
        qPosaljiIzmerenuTemperaturu = (Queue) ictx.lookup("qPosaljiIzmerenuTemperaturu");
        qcf = (QueueConnectionFactory) ictx.lookup("qcf");
        
        ictx.close();
        
        qc = (QueueConnection) qcf.createQueueConnection();
        qs = (QueueSession) qc.createSession(true, Session.AUTO_ACKNOWLEDGE);
        
        sender = (QueueSender) qs.createSender(qPosaljiIzmerenuTemperaturu);
        
        qc.start();
    }
    
    public void Posalji(double zeljena, double odstupanje) throws JMSException{
        
        Message msg = qs.createMessage();
        
        msg.setDoubleProperty("zeljena", zeljena);
        msg.setDoubleProperty("odstupanje", odstupanje);
        
        double izmereno = Math.random()*100;
        msg.setDoubleProperty("izmereno", izmereno);
        
        sender.send(msg);
        qs.commit();
    }
}