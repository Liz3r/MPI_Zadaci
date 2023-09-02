
package rmi;
import java.io.IOException;
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.logging.Level;
import java.util.logging.Logger;

public class CalculatorClient {
    
    

    public static void main(String[] args){
        
    
        try {
            try {
            Calculator calc = (Calculator)Naming.lookup("rmi://localhost:1007/calculator");
            System.out.println(calc.pomnozi(6, 9));
            System.out.println(calc.saberi(6, 9));
            System.out.println(calc.podeli(6, 9));
            System.out.println(calc.oduzmi(6, 9));
            System.out.println(calc.pomnozi(62, 19));
        } catch (NotBoundException ex) {
            Logger.getLogger(CalculatorClient.class.getName()).log(Level.SEVERE, null, ex);
        } catch (MalformedURLException ex) {
            Logger.getLogger(CalculatorClient.class.getName()).log(Level.SEVERE, null, ex);
        }
            
            
            
            System.in.read();
            System.exit(0);
        } catch (IOException ex) {
            Logger.getLogger(CalculatorServer.class.getName()).log(Level.SEVERE, null, ex);
        }
        
    }
}
