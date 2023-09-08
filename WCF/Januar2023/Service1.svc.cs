using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;

namespace WcfService4
{
     public class Service1 : IService1
    {
        Matrica matA = null;

        public Matrica getMatrix()
        {
            Matrica ret = new Matrica();

            if(matA != null)
            {
                ret.Greska = true;
                ret.Poruka = "Nije setovana matrica";
            }
            else if (matA.Cols <= 0 || matA.Rows <= 0 || matA.Values == null || matA == null)
            {
                ret.Greska = true;
                ret.Poruka = "Matrica koja je setovana nije validna";
            }
            else
            {
                ret.Cols = matA.Cols;
                ret.Rows = matA.Rows;
                ret.Greska = matA.Greska;
                ret.Poruka = matA.Poruka;
                ret.Values = matA.Values;
            }
            return ret;
        }

        public Matrica MatProd(Matrica mat)
        {
            Matrica ret = new Matrica();

            if (matA.Cols != mat.Rows || mat.Cols <= 0 || mat.Rows <= 0 || matA.Values == null)
            {
                ret.Greska = true;
                ret.Poruka = "Matrice nisu kompatabilne";

            }
            else
            {
                for (int i = 0; i < matA.Rows; i++)
                {
                    for (int j = 0; j < matA.Cols; j++)
                    {
                        ret.Values[i,j] = 0;
                    }
                }

                for (int p = 0; p < mat.Cols; p++) {
                    for (int i = 0; i < matA.Rows; i++)
                    {
                        for (int j = 0; j < matA.Cols; j++) //matA.Cols = mat.Rows
                        {
                            ret.Values[p,i] += matA.Values[i,j] * mat.Values[j,p];
                        }
                    }
                }
                ret = matA;
            }
            return ret;
        }

        public Matrica Saberi(Matrica mat)
        {
            Matrica ret = new Matrica();
            
            if (mat.Cols != matA.Cols || mat.Rows != matA.Rows || mat.Values == null || matA.Values == null)
            {
                ret.Greska = true;
                ret.Poruka = "Matrice nisu kompatabilne";

            }
            else
            {
                for(int i = 0; i < matA.Rows; i++)
                {
                    for(int j = 0; j < matA.Cols; j++)
                    {
                        matA.Values[i,j] += mat.Values[i,j];
                    }
                }
                ret = matA;
            }
            return ret;
        }

        public Matrica setMatrix(Matrica mat)
        {
            Matrica ret = new Matrica();
            if (mat.Cols <= 0 || mat.Rows <= 0 || mat.Greska == true || mat.Values == null)
            {
                ret.Greska = true;
                ret.Poruka = "Nije validna matrica";
                
            }
            else
            {
                matA = mat;
                ret = matA;
            }

            return ret;
        }

        public Matrica SkalProd(int[] skal)
        {
            Matrica ret = new Matrica();
            ret.Cols = skal.Length;
            ret.Rows = 1;
            if (skal.Length != matA.Cols)
            {
                ret.Greska = true;
                ret.Poruka = "nevalidan unos";
            }
            else
            {
                for (int j = 0; j < matA.Rows; j++)
                {
                    ret.Values[0,j] = 0;
                }
                
                for (int i = 0; i < matA.Rows; i++)
                {
                    for(int j = 0; j < matA.Cols; j++)
                    {
                        ret.Values[0,j] += matA.Values[i,j] * skal[j];
                    }
                }
            }
            return ret;
        }

        public Matrica Transpon()
        {
            Matrica ret = new Matrica();
            ret = matA;

            if(matA.Greska == false)
            {
                ret.Cols = matA.Rows;
                ret.Rows = matA.Cols;
                for (int i = 0; i < matA.Rows; i++)
                {
                    for (int j = 0; j < matA.Cols; j++)
                    {
                        ret.Values[j,i] = matA.Values[i,j];
                    }
                }
            }

            return ret;
        }

        
    }
}
