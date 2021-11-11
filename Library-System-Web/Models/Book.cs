using System;
using System.Collections.Generic;

#nullable disable

namespace Library_System_Web.Models
{
    public partial class Book
    {
        public int Isbn { get; set; }
        public int OrganizationId { get; set; }
        public int Copies { get; set; }
        public string Title { get; set; }
        public string Summary { get; set; }
        public string ImagePath { get; set; }
    }
}
