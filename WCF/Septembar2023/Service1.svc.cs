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

    [ServiceBehavior(InstanceContextMode = InstanceContextMode.Single)]
    public class Sistem : ISistem
    {

        static IList prijave = new List<Prijava>();

        public Obavestenje Odjavi(Student stud, Predmet ispit)
        {
            Obavestenje o = new Obavestenje();

            foreach(Prijava p in prijave)
            {
                if(p.Stud.Index == stud.Index && ispit.Sifra == p.Pred.Sifra)
                {
                    prijave.Remove(p);
                    o.Success = true;
                    return o;
                }
            }
            o.Success = false;
            o.Error = "Nije pronadjena prijava sa navedenim studentom i ispitom";
            return o;
        }

        public bool Prijavi(Student stud, List<Predmet> predmeti,string rok)
        {
            Prijava pr;
            foreach (Predmet p in predmeti)
            {
                bool postoji = false;
                foreach(Prijava pri in prijave)
                {
                    if(pri.Stud.Index == stud.Index && pri.Pred.Sifra == p.Sifra && pri.Rok == rok)
                    {
                        postoji = true;
                        break;
                    }

                }
                if (!postoji) {
                    pr = new Prijava();
                    pr.Stud = stud;
                    pr.Pred = p;
                    pr.Rok = rok;
                }
            }

            return true;
        }

        public List<Student> PrijaviliIspit(string rok, Predmet predmet)
        {
            List<Student> ret = new List<Student>();

            foreach(Prijava p in prijave)
            {
                if(p.Pred.Sifra == predmet.Sifra && p.Rok == rok)
                {
                    ret.Add(p.Stud);
                }
            }
            return ret;
        }

        public List<string> PrijavljeniIspiti(Student stud, string rok)
        {
            List<string> ret = new List<string>();

            foreach(Prijava p in prijave)
            {
                if(p.Stud.Index == stud.Index && p.Rok == rok)
                {
                    ret.Add(p.Pred.Naziv);
                }
            }

            return ret;
        }

        public Hashtable StudenataPoIspitu(string rok)
        {

            Hashtable ret = new Hashtable();

            foreach (Prijava p in prijave)
            {
                if (ret.Contains(p.Rok))
                {
                    ret[p.Rok] = (int)ret[p.Rok] + 1;
                }
                else
                {
                    ret.Add(p.Rok,1);
                }
            }
            return ret;
        }

        
    }
}



