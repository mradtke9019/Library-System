using Library_System_Web.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Library_System_Web.ViewModels.Books
{
    public class Details
    {
        public int ISBN { get; set; }
        public Book Book { get; set; }
    }
}
