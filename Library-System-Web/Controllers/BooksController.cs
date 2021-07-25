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
    }
}
