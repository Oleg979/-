class Client
    {

        public readonly string Name;
        public readonly long Passport;
        public readonly string Password;
        public readonly bool IsAdmin;

        public Ticket Ticket { get; private set; }

        public Client(string name, long pass, string password, bool isAdmin)
        {
            IsAdmin = isAdmin;
            Name = name;
            Passport = pass;
            Password = password;
            Ticket = null;
            Console.WriteLine("Created client: " + this);
        }

        public Ticket BuyTicket(Plane plane)
        {
            Ticket = new Ticket(this, plane);
            return Ticket;
        }

        public override string ToString() => Name + "(" + Passport + ")" + (IsAdmin ? " with admin rights" : "");

    }
}

class Plane
    {
        public readonly string name;
        public readonly List<Ticket> tickets;

        public Plane(string name)
        {
            this.name = name;
            tickets = new List<Ticket>();
            Console.WriteLine("Created aeroplane: " + name);
        }

        public void AddClient(Ticket ticket)
        {
            tickets.Add(ticket);
            Console.WriteLine("Client " + ticket.client + " added to plane " + this);
        }

        public void ShowClients()
        {
            string res = "Clients of " + this + ": ";
            foreach (var ticket in tickets) { res += ticket.client + " "; }
            Console.WriteLine(res);
        }

        public override string ToString() => name;
    }
}

class Ticket
    {
        public readonly Client client;
        public readonly Plane plane;
        public readonly DateTime date;

        public Ticket(Client client, Plane plane)
        {
            this.client = client;
            this.plane = plane;
            date = DateTime.Now;

            Console.WriteLine("Client " + client + " get ticket to plane " + plane);
            plane.AddClient(this);
        }

        public override string ToString() => "Client: " + client + " Plane: " + plane + " Date: " + date;

    }

class ManagementSystem
    {
        public List<Client> clients = new List<Client>();
        public List<Plane> planes = new List<Plane>();

        public Client CurrentUser = null;

        public ManagementSystem()
        {
            clients.Add(new Client("Oleg", 123, "123", true));
        }

        public
            void AddPlane(Plane plane)
        {
            planes.Add(plane);
        }

        public int SignUp(long passport, string password, string name)
        {
            foreach (var c in clients)
                if (c.Passport == passport)
                    return 0;
            Client client = new Client(name, passport, password, false);
            clients.Add(client);
            CurrentUser = client;
            return 1;
        }

        public int LogIn(long passport, string password)
        {
            foreach (var c in clients)
                if (c.Passport == passport)
                {
                    if (c.Password != password) return 1;
                    CurrentUser = c;
                    return 2;
                }
            return 0;
        }

        public void LogOut()
        {
            CurrentUser = null;
        }
}

class Program
    {

        private static ManagementSystem ms = new ManagementSystem();

        static void w(string s) { Console.WriteLine(s); }
        static void line() { Console.WriteLine(); }
        static string rl() { return Console.ReadLine(); }

        static void Greeting()
        {
            line();

            w("Welcome to the Airport Manager!\n1. Log in\n2. Sign up");
            var res = rl();
            if (res == "1") LogIn(); else if(res == "2") Signup();
        
            line();
        }

        static void LogIn()
        {
            line();

            w("Enter you passport:");
            var login = long.Parse(rl());
            w("Enter your password:");
            var pass = rl();

            var res = ms.LogIn(login, pass);

            if (res == 0)
            {
                w("This user doesn't exist. You need to sign up first.");
                Greeting();
            }
            else if (res == 1)
            {
                w("Wrong password. Try again.");
                Greeting();
            }
            else
            {
                line();
                w("Welcome, " + ms.CurrentUser.Name + "!");
                if (ms.CurrentUser.IsAdmin) AdminMenu();
                else UserMenu();
            }

        }

        static void Signup()
        {
            line();

            w("Enter you passport:");
            var login = long.Parse(rl());
            w("Enter your name:");
            var name = rl();
            w("Enter your password:");
            var pass = rl();

            var res = ms.SignUp(login, pass, name);

            if (res == 0)
            {
                w("This user already exist. You need to log in.");
                Greeting();
            }
            else
            {
                w("Welcome, " + ms.CurrentUser.Name + "!");
                if (ms.CurrentUser.IsAdmin) AdminMenu();
                else UserMenu();
            }
            
        }


        static void UserMenu()
        {
            line();

            w("What do you want to do?\n1. Buy ticket\n2. Show my ticket\n3. Logout");
            var res = rl();
            if (res == "1") BuyTicket(); else if (res == "2") ShowTicket(); else if (res == "3") Logout();

            line();
        }

        static void Logout()
        {
            ms.LogOut();
            Greeting();
        }

        static void ShowTicket()
        {
            line();

            Ticket ticket = ms.CurrentUser.Ticket;
            if (ticket == null) w("You have no ticket.");
            else w(ticket.ToString());

            UserMenu();
        }

        static void BuyTicket()
        {
            line();

            w("Select a plane: ");
            for (var i = 0; i < ms.planes.Count; i++) w(i + 1 + ". " + ms.planes[i]);
            var res = int.Parse(rl());
            if (res < 1 || res > ms.planes.Count) w("Error!");
            else ms.CurrentUser.BuyTicket(ms.planes[res - 1]);
       
            UserMenu();
        }


        static void AdminMenu()
        {
            line();

            w("What do you want to do?\n1. Show all planes and their tickets\n2. Show all clients\n3. Logout");
            var res = rl();
            if (res == "1") ShowAllPlanes(); else if (res == "2") ShowAllClients(); else if (res == "3") Logout();

            line();
        }

        static void ShowAllClients()
        {
            line();

            foreach (var client in ms.clients)
                w(client + "(" + (client.Ticket != null ? client.Ticket.plane.ToString() : "No ticket") + ")");
            
            AdminMenu();
        }

        static void ShowAllPlanes()
        {
            line();

            foreach (var plane in ms.planes)
            {
                var tickets = ": ";
                foreach (var ticket in plane.tickets) tickets += "(" + ticket.client + ") ";
                w(plane + tickets);
            }

            AdminMenu();
        }

        static void Main(string[] args)
        {
            ms.SignUp(777, "777", "Dima");
            ms.SignUp(555, "555", "Karina");

            ms.AddPlane(new Plane("Airbus"));
            ms.AddPlane(new Plane("Boeing"));

            ms.clients[1].BuyTicket(ms.planes[0]);
            ms.clients[2].BuyTicket(ms.planes[1]);



            Greeting();
            Console.ReadKey();
        }
 }
