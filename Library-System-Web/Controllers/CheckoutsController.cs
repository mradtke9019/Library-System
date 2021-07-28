using Library_System_Web.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Library_System_Web.ViewModels.Checkouts;

namespace Library_System_Web.Controllers
{
    public class CheckoutsController : Controller
    {
        private readonly ILogger<CheckoutsController> _logger;
        private readonly LibrarySystemContext _librarySystemContext;
        public CheckoutsController(ILogger<CheckoutsController> logger, LibrarySystemContext context)
        {
            _logger = logger;
            _librarySystemContext = context;
        }
        [HttpGet]
        public IActionResult Index(int ISBN)
        {
            ViewModels.Checkouts.Index model = new ViewModels.Checkouts.Index();
            model.Book = _librarySystemContext.Books.First(x => x.Isbn == ISBN);
            model.Checkout = new Checkout();
            model.Checkout.LoanDate = DateTime.Now;
            model.Checkout.BookIsbn = ISBN;
            model.Checkout.MemberId = 1;
            // Default Due Date is 1 week
            model.Checkout.DueDate = DateTime.Now.AddDays(7);
            return View(model);
        }

        [HttpPost]
        public IActionResult Add(ViewModels.Checkouts.Index data)
        {
            _librarySystemContext.Checkouts.Add(data.Checkout);
            return RedirectToAction();
        }
    }
}
