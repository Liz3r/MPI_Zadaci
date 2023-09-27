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
    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class Service1 : IService1
    {
        Hashtable nazivi;
        int brGrupa;
        int ucesnikaPoGrupi;
        Student[,,] grupe;
        public Service1() {

            brGrupa = 5;
            ucesnikaPoGrupi = 16;

            
            nazivi = new Hashtable();
            nazivi["Fudbal"] = 0;
            nazivi["Kosarka"] = 1;
            nazivi["Odbojka"] = 2;
            //...
            //   [indeksi naziva disciplina, broj grupa u odredjenoj disciplini, broj ucesnika u grupi] 
            grupe = new Student[nazivi.Count,5,16];
            for(int i = 0; i <  nazivi.Count; i++)
            {
                
                for(int j = 0; j < brGrupa; j++)
                {
                    for(int p = 0; p < ucesnikaPoGrupi; p++)
                    {
                        grupe[i, j, p] = null;
                    }
                }
            }
        }

        public string grupeIUcesnici(string disciplina)
        {
            string ret = "";

            for (int i = 0; i < brGrupa; i++)
            {
                ret += "Grupa " + i + ": \n";
                for (int j = 0; j < ucesnikaPoGrupi; j++)
                {
                    if (grupe[(int)nazivi[disciplina], i, j] != null)
                    {
                        ret += grupe[(int)nazivi[disciplina], i, j].Ime + " "
                            + grupe[(int)nazivi[disciplina], i, j].Prezime + " "
                            + grupe[(int)nazivi[disciplina], i, j].Index + " "
                            + grupe[(int)nazivi[disciplina], i, j].Ocena + " | ";
                    }
                }
                ret += "\n";
            }

            return ret;

        }

        public bool Odjavi(Student stud, string disciplina)
        {

            if (nazivi[disciplina] == null)
                return false;

            for(int i = 0; i < brGrupa; i++)
            {
                for(int j = 0; j < ucesnikaPoGrupi; j++)
                {

                    if (grupe[(int)nazivi[disciplina], i, j] != null && grupe[(int)nazivi[disciplina], i, j].Index == stud.Index) 
                    {
                        grupe[(int)nazivi[disciplina], i, j] = null;
                        return true;
                    }
                }
            }
            return false;
        }

        public bool Prijavi(Student stud, string disciplina)
        {
            if (nazivi[disciplina] == null)
                return false;

            for (int i = 0; i < brGrupa; i++)
            {
                for (int j = 0; j < ucesnikaPoGrupi; j++)
                {
                    if (grupe[(int)nazivi[disciplina], i, j] == null)
                    {
                        grupe[(int)nazivi[disciplina], i, j] = stud;
                        return true;
                    }
                }
            }
            return false;
        }

        public string Prijavljeno(Student stud)
        {
            string ret = "";

            for (int p = 0; p < nazivi.Count; p++)
            {
                for (int i = 0; i < brGrupa; i++)
                {
                    for (int j = 0; j < ucesnikaPoGrupi; j++)
                    {
                        if(grupe[p, i, j] != null && grupe[p,i,j].Index == stud.Index)
                        {
                            string[] nzk = new string[nazivi.Count];
                            nazivi.Keys.CopyTo(nzk, 0);

                            ret += nzk[p] + " ";
                        }
                    }
                }
            }
            return ret;
        }

        public string StudenataPoDisciplini()
        {
            string ret = "";
            int count;

            string[] nzk = new string[nazivi.Count];
            nazivi.Keys.CopyTo(nzk, 0);

            for (int i = 0; i < nazivi.Count; i++)
            {
                ret += nzk[i];
                ret += ": ";

                count = 0;

                for (int j = 0; j < brGrupa; j++)
                {
                    for(int p = 0; p < ucesnikaPoGrupi; p++)
                    {
                        if(grupe[i,j,p] != null)
                        {
                            count++;
                            break;
                        }
                    }
                }

                ret += count + "\n";
            }

            return ret;
        }


        private void Rebalansiraj()
        {
            //... rebalansiranje matrice 
        }
    }
}
