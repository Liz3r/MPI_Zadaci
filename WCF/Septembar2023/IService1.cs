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
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService1" in both code and config file together.
    
    [ServiceContract]
    public interface ISistem
    {
        [OperationContract]
        bool Prijavi(Student stud, List<Predmet> predmeti,string rok);
        [OperationContract]
        Obavestenje Odjavi(Student stud, Predmet ispit);
        [OperationContract]
        List<string> PrijavljeniIspiti(Student stud, string rok);
        [OperationContract]
        Hashtable StudenataPoIspitu(string rok);
        [OperationContract]
        List<Student> PrijaviliIspit(string rok, Predmet predmet);

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

    [DataContract]
    public class Prijava {

        Student stud;
        Predmet pred;
        string rok;

        [DataMember]
        public Student Stud
        {
            get { return stud; }
            set { stud = value; }
        }
    
        [DataMember]
        public Predmet Pred
        {
            get { return pred; }
            set { pred = value; }
        }

        [DataMember]
        public string Rok
        {
            get { return rok; }
            set { rok = value; }
        }
    }

    [DataContract]
    public class Obavestenje 
    {
        bool success;
        string error;

        [DataMember]
        public bool Success
        {
            get { return success; }
            set { success = value; }
        }

        [DataMember]
        public string Error
        {
            get { return error; }
            set { error = value; }
        }

    }

}
