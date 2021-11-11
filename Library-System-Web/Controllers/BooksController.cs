using Library_System_Web.Models;
using Library_System_Web.ViewModels.Books;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Library_System_Web.Controllers
{
    public class BooksController : Controller
    {
        private readonly ILogger<BooksController> _logger;
        private readonly LibrarySystemContext _librarySystemContext;
        public BooksController(ILogger<BooksController> logger, LibrarySystemContext context)
        {
            _logger = logger;
            _librarySystemContext = context;
        }
        public IActionResult Index()
        {
            return View();
        }

        public IActionResult Details(int ISBN)
        {
            Details model = new Details();
            model.ISBN = ISBN;
            model.Book = _librarySystemContext.Books.FirstOrDefault(x => x.Isbn == ISBN);

            return View(model);
        }

        [HttpGet]
        public IActionResult Search(string term, bool featured = false)
        {
            List<Book> books;
            // Return the featured books
            if (featured)
            {
                // Get all the 
                List<int> ids = _librarySystemContext.FeaturedBooks.Select(x => x.BookIsbn).ToList();
                books = ids.Select(x => _librarySystemContext.Books.Where(y => y.Isbn == x).First()).ToList();
                return PartialView("_BookResults", books);
            }

            if (string.IsNullOrEmpty(term))
                return null;
            // Extremely innefficient if we have a large table. We are getting the entire table from the database
            books = _librarySystemContext.Books.ToList();
            var type = books.GetType().GetGenericArguments()[0];
            var properties = type.GetProperties();
            books = books.Where(x => properties.Any(p => p != null && p.GetValue(x) != null && p.GetValue(x).ToString().ToLower().Contains(term.ToLower()))).ToList();

            return PartialView("_BookResults", books);
        }
    }
}
