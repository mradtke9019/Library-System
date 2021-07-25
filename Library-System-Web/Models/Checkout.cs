using System;
using System.Collections.Generic;

#nullable disable

namespace Library_System_Web.Models
{
    public partial class Checkout
    {
        public int BookIsbn { get; set; }
        public int MemberId { get; set; }
        public DateTime? LoanDate { get; set; }
        public DateTime? DueDate { get; set; }
    }
}
