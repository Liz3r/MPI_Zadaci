using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace TurnirService
{

    [ServiceContract]
    public interface IService1 {

        [OperationContract]
        void Prijava(Student stud, string disciplina);

        [OperationContract]
        void Odjava(Student stud, string disciplina);

        [OperationContract]
        string PrikaziPrijavljeno(Student stud);

        [OperationContract]
        string BrojStudenataPoDisciplini(string disciplina);

        [OperationContract]
        string PrikaziGrupe();
    }


    [DataContract]
    public class Student {

        int index;
        string ime;
        string prezime;
        double prosek;



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
            get { return prezime; }
            set { prezime = value; }
        }

        [DataMember]
        public double Prosek
        {
            get { return prosek; }
            set { prosek = value; }
        }

    }



}
