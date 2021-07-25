using Library_System_Web.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;

namespace Library_System_Web.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;
        private readonly LibrarySystemContext _librarySystemContext;

        public HomeController(ILogger<HomeController> logger, LibrarySystemContext context)
        {
            _logger = logger;
            _librarySystemContext = context;
        }

        public IActionResult Index()
        {
            // Get all the 
            List<int> ids = _librarySystemContext.FeaturedBooks.Select(x => x.BookIsbn).ToList();
            Library_System_Web.ViewModels.Home.Index model = new ViewModels.Home.Index();
            model.FeaturedBooks = ids.Select(x => _librarySystemContext.Books.Where(y => y.Isbn == x).First()).ToList();// _librarySystemContext.Books.Where(x => ids.Contains(x.Isbn)).ToList();
            return View(model);
        }

        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
