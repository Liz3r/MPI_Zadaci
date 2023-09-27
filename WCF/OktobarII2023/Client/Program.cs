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

            Student stud = new Student();

            Console.WriteLine("Unesi ime:");
            stud.Ime = Console.ReadLine();
            Console.WriteLine("Unesi prezime:");
            stud.Prezime = Console.ReadLine();
            stud.Index = 1234;
            stud.Ocena = 8.43;
            Console.WriteLine();

            proxy.Prijavi(stud, "Fudbal");
            proxy.Prijavi(stud, "Kosarka");

            Console.WriteLine(proxy.Prijavljeno(stud));

            Console.WriteLine(proxy.StudenataPoDisciplini());

            Console.WriteLine(proxy.grupeIUcesnici("Fudbal"));

            proxy.Odjavi(stud, "Fudbal");

            Console.WriteLine(proxy.Prijavljeno(stud));

            Console.ReadLine();

        }
    }
}
