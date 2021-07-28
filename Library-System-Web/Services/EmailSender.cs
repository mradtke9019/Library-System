using Microsoft.AspNetCore.Identity.UI.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Mail;
using System.Threading.Tasks;

namespace Library_System_Web.Services
{
    public class EmailSender : IEmailSender
    {
        public string username { get; set; }
        public string password { get; set; }
        public EmailSender(string user, string pass)
        {
            username = user;
            password = pass;
        }
        public Task SendEmailAsync(string email, string subject, string htmlMessage)
        {
            using (var message = new MailMessage())
            {
                message.To.Add(new MailAddress(email, email));
                message.From = new MailAddress(username);
                message.Subject = subject;
                message.IsBodyHtml = true; //to make message body as html  
                message.Body = htmlMessage;

                using (SmtpClient client = new SmtpClient("smtp.gmail.com", 587))
                {
                    client.Port = 587;
                    client.EnableSsl = true;
                    client.UseDefaultCredentials = false;
                    client.Credentials = new NetworkCredential(username, password);
                    //client.DeliveryMethod = SmtpDeliveryMethod.Network;
                    client.Send(message);
                }
            }

            return Task.CompletedTask;
        }
    }
}
