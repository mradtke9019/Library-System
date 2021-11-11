using Library_System_Web.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Library_System_Web.ViewModels.Checkouts
{
    public class Index
    {
        public Library_System_Web.Models.Book Book { get; set; }
        public Checkout Checkout { get; set; }
    }
}
