﻿using System;
using System.Collections.Generic;

#nullable disable

namespace Library_System_Web.Models
{
    public partial class Member
    {
        public int Id { get; set; }
        public string Email { get; set; }
        public string FirstName { get; set; }
        public string LastName { get; set; }
        public string Address { get; set; }
        public string Phone { get; set; }
    }
}
