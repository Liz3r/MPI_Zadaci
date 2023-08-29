using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace WcfService3
{
    
    [ServiceContract]
    public interface ISistem
    {
        [OperationContract]
        bool Prijavi(Student stud, ArrayList predmeti);
        [OperationContract]
        bool Odjavi(Student stud, string ispit);
        [OperationContract]
        ArrayList PrijavljeniIspiti(Student stud, string rok);
        [OperationContract]
        int StudenataPoIspitu(string rok);
        [OperationContract]
        ArrayList StudenataPoIspitu(string rok, Predmet predmet);

    }

    [DataContract]
    public class Student
    {
        int index = 0;
        string ime = "";
        string prezime = "";

        [DataMember]
        public int Index
        {
            get { return index; }
            set { index = value; }
        }

        [DataMember]
        public string Ime
        {
            get { return ime; }
            set { ime = value; }
        }
        [DataMember]
        public string Prezime
        {
            get { return Prezime; }
            set { Prezime = value; }
        }


    }

    [DataContract]
    public class Predmet 
    {
        string naziv;
        string sifra;

        [DataMember]
        public string Sifra 
        {
            get { return sifra; }
            set { sifra = value; }
        }

        [DataMember]
        public string Naziv
        {
            get { return naziv; }
            set { naziv = value; }
        }
    }


}