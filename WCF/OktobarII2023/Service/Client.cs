using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TurnirClient.ServiceReference1;

namespace TurnirClient
{
    class Program
    {

        static void Main(string[] args)
        {
            Service1Client proxy = new Service1Client();

            Student s1 = new Student { Index = 17950, Ime = "Marija", Prezime = "Markovic", Prosek = 6.78 };
            Student s2 = new Student { Index = 17951, Ime = "Mirko", Prezime = "Miladinovic", Prosek = 6.98 };
            Student s3 = new Student { Index = 17952, Ime = "Zarko", Prezime = "Stevanovic", Prosek = 6.23 };
            Student s4 = new Student { Index = 17953, Ime = "Darko", Prezime = "Nikolic", Prosek = 6.45 };
            Student s5 = new Student { Index = 17954, Ime = "Dunja", Prezime = "Markovic", Prosek = 7.58 };
            Student s6 = new Student { Index = 17955, Ime = "Miroslav", Prezime = "Nikolic", Prosek = 7.48 };
            Student s7 = new Student { Index = 17956, Ime = "Mirsad", Prezime = "Nikolic", Prosek = 8.28 };
            Student s8 = new Student { Index = 17957, Ime = "Aleksa", Prezime = "Stevanovic", Prosek = 8.50 };
            Student s9 = new Student { Index = 17958, Ime = "Strahinja", Prezime = "Nikolic", Prosek = 8.56 };
            Student s10 = new Student { Index = 17959, Ime = "Darko", Prezime = "Miladinovic", Prosek = 9.23 };
            Student s11 = new Student { Index = 17962, Ime = "Nikola", Prezime = "Markovic", Prosek = 6.23 };
            Student s12 = new Student { Index = 17963, Ime = "Nenad", Prezime = "Stevanovic", Prosek = 7.34 };
            Student s13 = new Student { Index = 17964, Ime = "Natasa", Prezime = "Nikolic", Prosek = 9.56 };
            Student s14 = new Student { Index = 17975, Ime = "Mirijana", Prezime = "Miladinovic", Prosek = 9.56 };
            Student s15 = new Student { Index = 17978, Ime = "Barbara", Prezime = "Stevanovic", Prosek = 9.89 };
            Student s16 = new Student { Index = 17989, Ime = "Isidora", Prezime = "Nikolic", Prosek = 10.00 };
            Student s17 = new Student { Index = 17986, Ime = "Milan", Prezime = "Mladenovic", Prosek = 8.52 };
            Student s18 = new Student { Index = 17950, Ime = "Dunja", Prezime = "Markovic", Prosek = 8.95 };
            Student s19 = new Student { Index = 17912, Ime = "Pavle", Prezime = "Miladinovic", Prosek = 6.90 };
            Student s20 = new Student { Index = 17913, Ime = "Dusan", Prezime = "Stevanovic", Prosek = 7.15 };
            Student s21 = new Student { Index = 17914, Ime = "Ivan", Prezime = "Nikolic", Prosek = 7.33 };
            Student s22 = new Student { Index = 17915, Ime = "Marija", Prezime = "Markovic", Prosek = 8.44 };

            proxy.Prijava(s1, "Fudbal");
            proxy.Prijava(s2, "Fudbal");
            proxy.Prijava(s3, "Fudbal");
            proxy.Prijava(s4, "Fudbal");
            proxy.Prijava(s5, "Fudbal");
            proxy.Prijava(s6, "Fudbal");
            proxy.Prijava(s7, "Fudbal");
            proxy.Prijava(s8, "Fudbal");
            proxy.Prijava(s9, "Fudbal");
            proxy.Prijava(s10, "Fudbal");
            proxy.Prijava(s11, "Fudbal");
            proxy.Prijava(s12, "Fudbal");
            proxy.Prijava(s13, "Fudbal");
            proxy.Prijava(s14, "Fudbal");
            proxy.Prijava(s15, "Fudbal");
            proxy.Prijava(s16, "Fudbal");
            proxy.Prijava(s17, "Kosarka");
            proxy.Prijava(s18, "Kosarka");
            proxy.Prijava(s19, "Kosarka");
            proxy.Prijava(s20, "Kosarka");
            proxy.Prijava(s21, "Kosarka");
            proxy.Prijava(s22, "Kosarka");

            
            Console.WriteLine(proxy.PrikaziGrupe());
            proxy.PrikaziGrupe();
            Console.WriteLine("Rebalansiranje---------------\n");
            Console.WriteLine(proxy.PrikaziGrupe());

            Console.ReadLine();

        }
    }
}
