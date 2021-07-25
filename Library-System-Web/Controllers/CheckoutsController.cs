using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Library_System_Web.Controllers
{
    public class CheckoutsController : Controller
    {
        public IActionResult Index()
        {
            return View();
        }
    }
}
