
package rmi;
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.util.logging.Level;
import java.util.logging.Logger;

public class CalculatorClient {
    
    Calculator calc;

    public CalculatorClient() throws RemoteException {
        try {
            this.calc = (Calculator)Naming.lookup("rmi://localhost:1003/CalculatorService");
        } catch (NotBoundException ex) {
            Logger.getLogger(CalculatorClient.class.getName()).log(Level.SEVERE, null, ex);
        } catch (MalformedURLException ex) {
            Logger.getLogger(CalculatorClient.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
