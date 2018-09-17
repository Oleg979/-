using System;
using System.Collections.Generic;

namespace ConsoleApp1
{
    class Client
    {
        private String name;
        private long passport;
        private Ticket ticket;

        public Client(String name, long pass)
        {
            this.name = name;
            this.passport = pass;
            Console.WriteLine("Created client: " + name + " " + passport);
        }

        public override string ToString()
        {
            return this.name + "(" + this.passport + ")";
        }

        public Ticket buyTicket(Plane plane)
        {
            this.ticket = new Ticket(this, plane);
            return ticket;
        }

    }

    class Plane
    {
        private String name;
        private List<Client> clients;

        public Plane(String name)
        {
            this.name = name;
            this.clients = new List<Client>();
            Console.WriteLine("Created aeroplane: " + name);
        }

        public void addClient(Client client)
        {
            this.clients.Add(client);
            Console.WriteLine("Client " + client + " added to plane " + this);
        }

        public void showClients()
        {
            String res = "Clients of " + this + ": ";
            foreach (Client client in clients) { res += client + " "; }
            Console.WriteLine(res);
        }

        public override string ToString()
        {
            return this.name;
        }
    }
    
    class Ticket
    {
        private Client client;
        private Plane plane;
        private DateTime date;

        public Ticket(Client client, Plane plane)
        {
            this.client = client;
            this.plane = plane;
            this.date = DateTime.Now;

            Console.WriteLine("Client " + client + " get ticket to plane " + plane);
            plane.addClient(client);
        }

    }

    class Program
    {
        static void Main(string[] args)
        {
            Client Jack = new Client("Jack", 123456);
            Client John = new Client("John", 678910);
            Client Sam = new Client("Sam", 88888);

            Plane plane1 = new Plane("Plane1");
            Plane plane2 = new Plane("Plane2");

            Jack.buyTicket(plane1);
            John.buyTicket(plane2);
            Sam.buyTicket(plane2);

            plane1.showClients();
            plane2.showClients();

            Console.ReadKey();
        }
    }
}
