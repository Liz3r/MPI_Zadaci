
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

    public static int idGen = 0;
    private int myId;
    private double zeljenaTemp;
    private double odstupanje;
    
    private final QueueConnectionFactory qcf;
    private final QueueConnection qc;
    private final QueueSession qs;
    private final Queue qZatraziStanje;
    private final Queue qOdgovoriNaZahtev;
    private final Queue qNaloziAkciju;
    private QueueReceiver zahtevZaStanjemReceiver;
    private QueueReceiver odgovorNaZahtevReceiver;
    private QueueReceiver primiNalogReceiver;
    private QueueSender zahtevSender;
    private QueueSender odgovorNaZahtevSender;
    private QueueSender nalogSender;
    

    
    public Klijent(double zeljenaTemp, double dozvoljenoOdstupanje) throws NamingException, JMSException
    {
        myId = ++idGen;
        this.zeljenaTemp = zeljenaTemp;
        this.odstupanje = dozvoljenoOdstupanje;
        
        InitialContext ictx = new InitialContext();
        
        qcf = (QueueConnectionFactory) ictx.lookup("qcf");
        
        qZatraziStanje = (Queue) ictx.lookup("qZatraziStanje");
        qOdgovoriNaZahtev = (Queue) ictx.lookup("qOdgovoriNaZahtev");
        qNaloziAkciju = (Queue) ictx.lookup("qNaloziAkciju");
        
        ictx.close();
        
        
        
        qc = (QueueConnection) qcf.createQueueConnection();
        qs = (QueueSession) qc.createSession(true,Session.AUTO_ACKNOWLEDGE);
        
        
    }
    
    
    public void Start() throws JMSException{
        
        zahtevZaStanjemReceiver = (QueueReceiver) qs.createReceiver(qZatraziStanje,"id = " + this.myId);
        odgovorNaZahtevReceiver = (QueueReceiver) qs.createReceiver(qOdgovoriNaZahtev, "id = " + this.myId);
        primiNalogReceiver = (QueueReceiver) qs.createReceiver(qNaloziAkciju, "id = " + this.myId);
        
        qc.start();
        
        zahtevZaStanjemReceiver.setMessageListener(new ObradiZahtevZaStanjem(this));
        odgovorNaZahtevReceiver.setMessageListener(new ObradiOdgovorNaZahtev(this));
        primiNalogReceiver.setMessageListener(new ObradiAkciju(this));
        
        
        zahtevSender = (QueueSender) qs.createSender(qZatraziStanje);
        odgovorNaZahtevSender = (QueueSender) qs.createSender(qOdgovoriNaZahtev);
        nalogSender = (QueueSender) qs.createSender(qNaloziAkciju);
    }

    public void ZatraziStanje(int komeId) throws JMSException{
        
        Message msg = qs.createMessage();
        
        msg.setIntProperty("koTrazi", myId);
        msg.setIntProperty("id", komeId);
        
        
        zahtevSender.send(msg);
        qs.commit();
    }
    
    public void ObradiZahtevZaStanjem(Message message) throws JMSException {
        int koTrazi = message.getIntProperty("koTrazi");
        
        double izmereno = this.izmeriTemp();
        Podaci p = new Podaci(this.myId,this.zeljenaTemp,this.odstupanje,izmereno);
        
        ObjectMessage msg = (ObjectMessage) qs.createObjectMessage(p);
        msg.setIntProperty("id", koTrazi);
        
        if(msg != null){
        odgovorNaZahtevSender.send(msg);
        qs.commit();
        }
    }
    
    
    public double izmeriTemp(){
        return Math.random() * 100;
    }

    public void ObradiOdgovorNaZahtevv(Message message) throws JMSException {
        ObjectMessage msg = (ObjectMessage) message;
        
        Podaci p;
        p = (Podaci) msg.getObject();
        
        int koTrazi = p.id;
        
        String akcija = "";
        
        if((p.izmerenaTemp + p.dozvoljenoOdstupanje) > p.zeljenaTemp){
            akcija = "Hladi";
        }else if((p.izmerenaTemp - p.dozvoljenoOdstupanje) < p.zeljenaTemp){
            akcija = "Grej";
        }else{
            akcija = "Ok";
        }
        TextMessage sendMsg = (TextMessage) qs.createTextMessage(akcija);
        sendMsg.setIntProperty("id", koTrazi);
        
        nalogSender.send(sendMsg);
        qs.commit();
        
    }

    public void obradiNalog(Message message) throws JMSException {
        TextMessage msg = (TextMessage) message;
        String text = (String) msg.getText();
        
        if(text.equals("Hladi")){
            System.out.println("Klijent " + myId + ": Hladim");
        }else if(text.equals("Grej")){
            System.out.println("Klijent " + myId + ": Grejem");
        }else if(text.equals("Ok")){
            System.out.println("Klijent " + myId + ": Temperatura ok");
        }else{
            System.out.println("Klijent " + myId + ": Nepoznata akcija");
        }
    }
}
