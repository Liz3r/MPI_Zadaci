/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package sistem;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.jms.JMSException;
import javax.jms.Message;
import javax.jms.MessageListener;

/**
 *
 * @author Guster
 */
public class vracamSortListener implements MessageListener {

    Klijent cli;
    public vracamSortListener(Klijent k) {
        this.cli = k;
    }

    @Override
    public void onMessage(Message message) {
        try {
            cli.obradiVracenSort(message);
        } catch (JMSException ex) {
            Logger.getLogger(vracamSortListener.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
}
