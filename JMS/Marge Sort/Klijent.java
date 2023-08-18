
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

    public static int idGen = 1;
    private int id;
    
    private final QueueConnection qc;
    private final QueueSession qs;
    private final Queue qTrazimSort;
    private final Queue qVratiSort;
    private final QueueSender senderTraziSort;
    private final QueueSender senderSortiranog;
    private QueueReceiver traziSortListener;
    private QueueReceiver vratiSortListener;
    private MessageConsumer vratiSortListenerDrugi;
    
    public Klijent() throws NamingException, JMSException
    {
      this.id = idGen++;
      
      InitialContext ictx = new InitialContext();
      
      qTrazimSort = (Queue) ictx.lookup("qTrazimSort");
      qVratiSort = (Queue) ictx.lookup("qVratiSort");
      
      
      QueueConnectionFactory qcf = (QueueConnectionFactory) ictx.lookup("qcf");
      
      ictx.close();
      
      qc = (QueueConnection) qcf.createQueueConnection();
      qs = (QueueSession) qc.createQueueSession(true, Session.AUTO_ACKNOWLEDGE);
      
      senderTraziSort = qs.createSender(qTrazimSort);
      senderSortiranog = qs.createSender(qVratiSort);
      
     
      
    }
    
    
    public void start() throws JMSException
    {
        traziSortListener = qs.createReceiver(qTrazimSort);
        vratiSortListener = qs.createReceiver(qVratiSort,"kome = "+ this.id);
        
        qc.start();
        
        traziSortListener.setMessageListener(new nekoTraziSortListener(this));
        vratiSortListener.setMessageListener(new vracamSortListener(this));
        
        
    }

    
    public void zatraziSort(ArrayList<Integer> niz, int sortId) throws JMSException{
        
        ObjectMessage sendMsg = qs.createObjectMessage(niz);
        sendMsg.setIntProperty("koTrazi", id);
        int si = sortId;
        sendMsg.setIntProperty("SortId", si);
        
        senderTraziSort.send(sendMsg);
        qs.commit();
    }
    
    public void obradiSort(Message message) throws JMSException {
        
        ObjectMessage msg = (ObjectMessage) message;
        ArrayList<Integer> niz = (ArrayList<Integer>)msg.getObject();
        
        int sId = msg.getIntProperty("SortId");
        
        int len = niz.size();
        
        if(len == 1){
            /*int koTrazi = msg.getIntProperty("koTrazi");
            ObjectMessage sm = qs.createObjectMessage(niz);
            sm.setIntProperty("SortId", sId);
            sm.setIntProperty("kome", koTrazi);
            senderSortiranog.send(sm);
            qs.commit();*/
            //System.out.println(this.id);
            
        }else{
            
            ArrayList<Integer> niz1 = new ArrayList<Integer>();
            ArrayList<Integer> niz2 = new ArrayList<Integer>();
            
            for(int i = 0; i < len; i++){
                if(i < len/2){
                    niz1.add(niz.get(i));
                }else{
                    niz2.add(niz.get(i));
                }
            }
            System.out.print("ID: " + this.id);
            System.out.print("Niz1: ");
            for(Integer el : niz1){
                System.out.print(el);
                System.out.print(" ");
            }
            System.out.println();
            System.out.print("Niz2: ");
            for(Integer el : niz2){
                System.out.print(el);
                System.out.print(" ");
            }
            System.out.println();
            
            this.zatraziSort(niz1,sId);
            this.zatraziSort(niz2,sId);
            
        }
    }

    
    public void obradiVracenSort(Message message) throws JMSException{
        
        
        ObjectMessage msg1 = (ObjectMessage) message;
        
        int sId = msg1.getIntProperty("SortId");
        vratiSortListenerDrugi = qs.createConsumer(qVratiSort,"(kome = "+ this.id +") AND (sortId = "+sId+")");
        
        Message rmsg2 = vratiSortListenerDrugi.receive();
        ObjectMessage msg2 = (ObjectMessage) rmsg2;
        
        
        ArrayList<Integer> niz1 = (ArrayList<Integer>)msg1.getObject();
        ArrayList<Integer> niz2 = (ArrayList<Integer>)msg2.getObject();
        
        
        System.out.println("Primio 2 poruke");
    }
  
}
