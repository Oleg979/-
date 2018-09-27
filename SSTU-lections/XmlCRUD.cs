using System;
using System.Xml.Linq;

namespace XmlParser
{
    class Program
    {

        private static XDocument xdoc = XDocument.Load("../../Inventory.xml");

        private static void Menu()
        {
            Console.WriteLine();
            Console.WriteLine("What do you want to do?");
            Console.WriteLine("1. Show all books\n2. Add new book\n3. Edit book\n4. Delete book");
            Console.WriteLine();
            var res = Console.ReadLine();
            Console.WriteLine();
            switch (res)
            {
                case "1":
                    ReadAll();
                    break;
                case "2":
                    AddBook();
                    break;
                case "3":
                    EditBook();
                    break;
                case "4":
                    DeleteBook();
                    break;
                default:
                    Console.WriteLine("Unknown command!");
                    Menu();
                    break;
            }
        }

        private static void ReadAll()
        {
            foreach (XElement element in xdoc.Element("INVENTORY").Elements("BOOK"))
            {
                string title = element.Element("TITLE").Value;
                string author = element.Element("AUTHOR").Value;
                string binding = element.Element("BINDING").Value;
                string pages = element.Element("PAGES").Value;
                string price = element.Element("PRICE").Value;

                Console.WriteLine("Title: " + title);
                Console.WriteLine("Author: " + author);
                Console.WriteLine("Binding: " + binding);
                Console.WriteLine("Pages: " + pages);
                Console.WriteLine("Price: " + price);

                Console.WriteLine();
            }

            Menu();
        }

        private static void AddBook()
        {
            Console.Write("Enter title: ");
            var title = Console.ReadLine();
            Console.Write("Enter author: ");
            var author = Console.ReadLine();
            Console.Write("Enter binding: ");
            var binding = Console.ReadLine();
            Console.Write("Enter pages: ");
            var pages = Console.ReadLine();
            Console.Write("Enter price: ");
            var price = Console.ReadLine();

            XElement root = xdoc.Element("INVENTORY");
            root.Add(new XElement("BOOK",
                    new XElement("TITLE", title),
                    new XElement("AUTHOR", author),
                    new XElement("BINDING", binding),
                    new XElement("PAGES", pages),
                    new XElement("PRICE", price)
                ));
            xdoc.Save("../../Inventory.xml");
            Console.WriteLine("Added successfully.");
            Menu();
        }

        private static void EditBook()
        {
            var BookNumber = ShowAndChoose("edit");
            if (BookNumber == -1) Error();
 
            Console.WriteLine("1. Title\n2. Author\n3. Binding\n4. Pages\n5. Price");
            Console.Write("Enter number of tag you want to edit: ");
            var TagNumber = int.Parse(Console.ReadLine());
            var TagName = "";
            switch(TagNumber)
            {
                case 1:
                    TagName = "TITLE";
                    break;
                case 2:
                    TagName = "AUTHOR";
                    break;
                case 3:
                    TagName = "BINDING";
                    break;
                case 4:
                    TagName = "PAGES";
                    break;
                case 5:
                    TagName = "PRICE";
                    break;
                default:
                    Error();
                    break;
            }

            Console.Write("Enter new value for " +  TagName + ": ");
            var newValue = Console.ReadLine();

            var counter = 0;
            foreach (XElement element in xdoc.Element("INVENTORY").Elements("BOOK"))
                if (counter++ == (BookNumber - 1))
                {
                    element.Element(TagName).Value = newValue;
                    xdoc.Save("../../Inventory.xml");
                    Console.WriteLine("Edited successfully.");
                    Menu();
                }
        }

        private static void DeleteBook()
        {
            var res = ShowAndChoose("delete");
            if (res == -1) Error();
   
            var counter = 0;
            foreach (XElement element in xdoc.Element("INVENTORY").Elements("BOOK"))
                if (counter++ == (res - 1))
                {
                    element.Remove();
                    xdoc.Save("../../Inventory.xml");
                    Console.WriteLine("Removed successfully.");
                    Menu();
                }   
        }

        private static int ShowAndChoose(string type)
        {
            var books = xdoc.Element("INVENTORY").Elements("BOOK");
            var counter = 1;
            foreach (XElement element in books)
            {
                string title = element.Element("TITLE").Value;
                Console.WriteLine(counter + ". " + title);
                counter++;
            }

            Console.WriteLine();
            Console.Write("Enter number of book you want to " + type + ": ");
            var res = int.Parse(Console.ReadLine());
            Console.WriteLine();

            if (res < 1 || res >= counter) return -1;
            else return res;
        }

        private static void Error()
        {
            Console.WriteLine("Error! Returning to menu...");
            Menu();
        }

        static void Main(string[] args)
        {
            Menu();
        }
    }
}
