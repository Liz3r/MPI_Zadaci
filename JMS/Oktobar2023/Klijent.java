
package sistem;

import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.ObjectMessage;
import javax.jms.Queue;
import javax.jms.QueueConnection;
import javax.jms.QueueConnectionFactory;
import javax.jms.QueueReceiver;
import javax.jms.QueueSession;
import javax.jms.Session;
import javax.naming.InitialContext;
import javax.naming.NamingException;




public class Klijent {

    private double zeljenaTemp;
    private double odstupanje;
    private final Queue qPosaljiIzmerenuTemperaturu;
    private final QueueConnectionFactory qcf;
    private final QueueConnection qc;
    private final QueueSession qs;
    private QueueReceiver qIzmerenoReceiver;
    
    public Klijent() throws NamingException, JMSException
    {
        
        InitialContext ictx = new InitialContext();
        
        qPosaljiIzmerenuTemperaturu = (Queue) ictx.lookup("qPosaljiIzmerenuTemperaturu");
        qcf = (QueueConnectionFactory) ictx.lookup("qcf");
        
        ictx.close();
        
        qc = (QueueConnection) qcf.createQueueConnection();
        qs = (QueueSession) qc.createSession(true, Session.AUTO_ACKNOWLEDGE);
        
    }
    
    
    public void Start(double zeljenaTemp, double odstupanje) throws JMSException{
        this.zeljenaTemp = zeljenaTemp;
        this.odstupanje = odstupanje;
        
        qIzmerenoReceiver = (QueueReceiver) qs.createReceiver(qPosaljiIzmerenuTemperaturu, "(zeljena = " + zeljenaTemp + ") AND (odstupanje = " + odstupanje + ")");
        qIzmerenoReceiver.setMessageListener(new IzmerenoListener(this));
        
        
        
        qc.start();
    }

    void obradiIzmereno(Message msg) throws JMSException {
        
        double izmereno = msg.getDoubleProperty("izmereno");
        
        if(izmereno < this.zeljenaTemp - this.odstupanje){
            System.out.println("Grejem |||| lokacija zeljena: " + this.zeljenaTemp + " // lokacija odstupanje: " + this.odstupanje + "// izmereno: " + izmereno);
        }else if(izmereno > this.zeljenaTemp + this.odstupanje){
            System.out.println("Hladim |||| lokacija zeljena: " + this.zeljenaTemp + " // lokacija odstupanje: " + this.odstupanje + "// izmereno: " + izmereno);
        }else{
            System.out.println("OK |||| lokacija zeljena: " + this.zeljenaTemp + " // lokacija odstupanje: " + this.odstupanje + "// izmereno: " + izmereno);
        }
        
    }
}

//rutracker.org