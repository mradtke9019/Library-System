using Library_System_Web.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Library_System_Web.ViewModels.Checkouts;
using Microsoft.AspNetCore.Identity;

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
            if(User.Identity.Name == null)
            {
                RedirectToAction("Index", "Checkouts");
            }
            // Get the users corresponding account
            Member member = _librarySystemContext.Members.FirstOrDefault(x => x.Email == User.Identity.Name);
            if(member == null)
            {
                member = new Member()
                {
                    Email = User.Identity.Name,
                };
                _librarySystemContext.Members.Add(member);
                _librarySystemContext.SaveChanges();
                member = _librarySystemContext.Members.FirstOrDefault(x => x.Email == User.Identity.Name);
            }
            data.Checkout.MemberId = member.Id;
            _librarySystemContext.Checkouts.Add(data.Checkout);
            _librarySystemContext.SaveChanges();
            return RedirectToAction("Index");
        }
    }
}
