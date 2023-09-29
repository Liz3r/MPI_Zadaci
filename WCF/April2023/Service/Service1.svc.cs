using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace FabrikaService
{
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class Service1 : IService1
    {

        List<Sastojak> sastojci;
        double zapremina;
        double gustina;
        double kapacitet;
        
        public Service1()
        {
            this.kapacitet = 500;
            gustina = 0;
            zapremina = 0;
            sastojci = new List<Sastojak>();
        }

        public bool Dodaj(Sastojak s)
        {
            if (zapremina + s.Zapremina > kapacitet)
                return false;
            if(zapremina == 0)
            {
                sastojci.Add(s);
                zapremina = s.Zapremina;
                gustina = s.Gustina;
            }
            sastojci.Add(s);
            double staraZapremina = zapremina;
            double dodataZapremina = s.Zapremina;
            double novaZapremina = zapremina + s.Zapremina;

            double udeoStareZapremine = staraZapremina / novaZapremina;
            double udeoDodateZapremine = dodataZapremina / novaZapremina;

            gustina = udeoStareZapremine * gustina + udeoDodateZapremine * s.Gustina;

            return true;
        }

        public bool Flasiraj(double kolicina)
        {
            if (zapremina < kolicina)
                return false;

            zapremina -= kolicina;
            return true;
        }

        public string Stanje()
        {
            string ret = "";
            ret += "Sastojci: ";
            foreach(Sastojak s in sastojci)
            {
                ret += "( " + s.Naziv + " | " + s.Gustina + " | " + s.Zapremina + " )\n";
            }

            ret += "\nGustina: " + gustina + "\n";
            ret += "\nZapremina: " + zapremina + "\n";
            ret += "\nKapacitet: " + kapacitet + "\n\n";

            return ret;
        }
    }
}
