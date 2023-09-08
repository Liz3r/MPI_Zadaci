using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace WcfService4
{
    [ServiceContract]
    public interface IService1
    {

        [OperationContract]
        Matrica setMatrix(Matrica mat);

        [OperationContract]
        Matrica getMatrix();

        [OperationContract]
        Matrica Saberi(Matrica mat);

        [OperationContract]
        Matrica SkalProd(int[] skal);

        [OperationContract]
        Matrica MatProd(Matrica mat);

        [OperationContract]
        Matrica Transpon();

    }

    [DataContract]
    public class Matrica {

        int rows;
        int cols;
        bool greska;
        string poruka;
        int[,] values;

        [DataMember]
        public int Rows
        {
            get { return rows; }
            set { rows = value; }
        }

        [DataMember]
        public int Cols
        {
            get { return cols; }
            set { cols = value; }
        }
        [DataMember]
        public bool Greska 
        {
            get { return greska; }
            set { greska = value; }
        }
        [DataMember]
        public string Poruka
        {
            get { return poruka; }
            set { poruka = value; }
        }

        [DataMember]
        public int[,] Values
        {
            get { return values; }
            set { values = value; }
        }
    }


}
