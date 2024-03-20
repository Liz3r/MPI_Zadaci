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

        List<Disciplina> discipline;
        Disciplina d1 = new Disciplina("Fudbal");
        Disciplina d2 = new Disciplina("Kosarka");

        Service1()
        {
            discipline= new List<Disciplina>();
            Disciplina d1 = new Disciplina("Fudbal");
            Disciplina d2 = new Disciplina("Kosarka");
            discipline.Add(d1);
            discipline.Add(d2);
        }

     

        public string BrojStudenataPoDisciplini(string disciplina)
        {
            string ret = "";
            foreach (Disciplina d in discipline)
            {
                ret += d.StudPoDisciplini() + "\n";
            }
            return ret;
        }

        public void Odjava(Student stud, string disciplina)
        {
            foreach (Disciplina d in discipline)
            {
                if(d.naziv == disciplina)
                {
                    d.Odjavi(stud);
                }
            }
        }

        public void Prijava(Student stud, string disciplina)
        {
            foreach(Disciplina d in discipline)
            {
                if(d.naziv == disciplina)
                {
                    d.DodajStudenta(stud);
                    break;
                }   
            }

        }

        public string PrikaziGrupe()
        {
            string ret = "";
            foreach (Disciplina d in discipline)
            {
                 ret += d.Prikaz();
            }
            return ret;
        }

        public string PrikaziPrijavljeno(Student stud)
        {
            string ret = "Prijave studenta " + stud.Index + " " + stud.Ime + " " + stud.Prezime + ":\n";
            foreach (Disciplina d in discipline)
            {
                ret += d.Prijavio(stud);
            }
            return ret;
        }
    }


    public class Disciplina
    {
        public string naziv;
        public int brojPrijavljenih;
        public List<List<Student>> prijavljeni;

        public Disciplina(string naziv)
        {
            this.naziv = naziv;
            prijavljeni = new List<List<Student>>();
        }

        public string Prijavio(Student stud)
        {
            foreach (List<Student> grupa in prijavljeni)
            {
                foreach(Student studGrp in grupa)
                {
                    if(studGrp.Index == stud.Index)
                    {
                        return this.naziv + " ";
                    }
                }
            }
            return "";
        }

        public void Rebalansiranje()
        {
            foreach (List<Student> grupa in prijavljeni)
            {
                if (grupa.Count > 1)
                {
                    for (int i = 0; i < grupa.Count; i++)
                    {
                        for (int j = i + 1; j < grupa.Count; j++)
                        {
                            if (grupa.ElementAt(i).Prosek < grupa.ElementAt(j).Prosek)
                            {
                                Student tmp = grupa.ElementAt(i);
                                grupa.Insert(i, grupa.ElementAt(j));
                                grupa.RemoveAt(i + 1);

                                grupa.Insert(j, tmp);
                                grupa.RemoveAt(j + 1);
                            }
                        }
                    }
                }

            }
            foreach (List<Student> grupa in prijavljeni)
            {
                if(grupa.Count == 8)
                for(int i = 0; i < grupa.Count-1; i++)
                {
                    foreach (List<Student> grupaProvera in prijavljeni)
                    {
                            if(grupa.ElementAt(i).Prosek < grupaProvera.ElementAt(i + 1).Prosek)
                            {
                                Student tmp = grupa.ElementAt(i);
                                grupa.Insert(i, grupaProvera.ElementAt(i + 1));
                                grupa.RemoveAt(i + 1);

                                grupaProvera.Insert(i + 1,tmp);
                                grupaProvera.RemoveAt(i + 2);
                                i = 0;
                            }
                    }
                }
            }
        }

        public void DodajStudenta(Student stud)
        {
            if(prijavljeni != null)
            foreach(List<Student> grupa in prijavljeni)
            {
                if(grupa.Count < 8)
                {
                    grupa.Add(stud);
                    return;
                }
            }
            List<Student> novaGrupa = new List<Student>();
            novaGrupa.Add(stud);
            prijavljeni.Add(novaGrupa);
        }

        public string Prikaz()
        {
            string ret = "";

            foreach(List<Student> grupa in prijavljeni)
            {
                ret += "Grupa " + prijavljeni.IndexOf(grupa) + ":\n";
                foreach(Student stud in grupa)
                {
                    ret += "" + stud.Index + " " + stud.Ime + " " + stud.Prezime + " " + stud.Prosek + "||\n";
                }
                ret += "\n";
            }

            Rebalansiranje();
            return ret;
        }

        public string StudPoDisciplini()
        {
            string ret = this.naziv;

            int ukupno = 0;
            foreach (List<Student> grupa in prijavljeni)
            {
                ukupno += grupa.Count;
            }

            ret += ": " + ukupno + "\n";

            return ret;
        }

        public void Odjavi(Student stud)
        {
            foreach (List<Student> grupa in prijavljeni)
            {
                foreach(Student studGrp in grupa)
                {
                    if(stud.Index == studGrp.Index)
                    {
                        grupa.Remove(stud);
                        return;
                    }
                }
            }
        }

    }

}
