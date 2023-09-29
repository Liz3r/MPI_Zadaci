using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FabrikaClient.ServiceReference1;

namespace FabrikaClient
{
    class Program
    {
        static void Main(string[] args)
        {

            Service1Client proxy = new Service1Client();

            string opcija;
            while (true)
            {
                Console.WriteLine("Unesi opciju: (dodaj, flasiraj, prikazi, exit)");
                opcija = Console.ReadLine();

                if (opcija.Equals("dodaj"))
                {
                    Sastojak s = new Sastojak();
                    Console.WriteLine("Naziv sastojka:");
                    s.Naziv = Console.ReadLine();
                    Console.WriteLine("Gustina:");
                    s.Gustina = Double.Parse(Console.ReadLine());
                    Console.WriteLine("Zapremina:");
                    s.Zapremina = Double.Parse(Console.ReadLine());
                    
                    if (proxy.Dodaj(s))
                    {
                        Console.WriteLine("Flasiranje uspesno");
                    }
                    else
                    {
                        Console.WriteLine("Greska");
                    }
                }
                else if (opcija.Equals("flasiraj"))
                {
                    Console.WriteLine("Kolicina:");
                    double kol = Double.Parse(Console.ReadLine());
                    if (proxy.Flasiraj(kol))
                    {
                        Console.WriteLine("Flasiranje uspesno");
                    }
                    else
                    {
                        Console.WriteLine("Greska");
                    }

                }
                else if (opcija.Equals("prikazi"))
                {
                    Console.WriteLine(proxy.Stanje());
                }
                else if (opcija.Equals("exit")) 
                {
                    return;
                }
                else
                {
                    Console.WriteLine("Nevalidna opcija\n");
                }
            }
        }
    }
}
