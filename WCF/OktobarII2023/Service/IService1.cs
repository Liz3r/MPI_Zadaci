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
    public interface IService1
    {

        [OperationContract]
        bool Prijavi(Student stud, string disciplina);

        [OperationContract]
        bool Odjavi(Student stud, string disciplina);

        [OperationContract]
        string Prijavljeno(Student stud);

        [OperationContract]
        string StudenataPoDisciplini();

        [OperationContract]
        string grupeIUcesnici(string disciplina);
        
    }

    [DataContract]
    public class Student 
    {
        int index;
        string ime;
        string prezime;
        double ocena;

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
        public double Ocena
        {
            get { return ocena; }
            set { ocena = value; }
        }
    }

    

}
