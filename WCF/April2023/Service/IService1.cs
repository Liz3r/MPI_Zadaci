using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace FabrikaService
{

    [ServiceContract]
    public interface IService1
    {
        [OperationContract]
        bool Dodaj(Sastojak s);

        [OperationContract]
        bool Flasiraj(double kolicina);

        [OperationContract]
        string Stanje();
        
    }

    [DataContract]
    public class Sastojak
    {
        string naziv;
        double zapremina;
        double gustina;

        [DataMember]
        public string Naziv 
        {
            get { return naziv; }
            set { naziv = value; }
        }

        [DataMember]
        public double Zapremina
        {
            get { return zapremina; }
            set { zapremina = value; }
        }

        [DataMember]
        public double Gustina
        {
            get { return gustina; }
            set { gustina = value; }
        }
        
    }
}
