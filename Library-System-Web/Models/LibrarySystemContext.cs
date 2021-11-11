using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;

#nullable disable

namespace Library_System_Web.Models
{
    public partial class LibrarySystemContext : DbContext
    {
        public LibrarySystemContext()
        {
        }

        public LibrarySystemContext(DbContextOptions<LibrarySystemContext> options)
            : base(options)
        {
        }

        public virtual DbSet<Author> Authors { get; set; }
        public virtual DbSet<Book> Books { get; set; }
        public virtual DbSet<BookCategorization> BookCategorizations { get; set; }
        public virtual DbSet<Category> Categories { get; set; }
        public virtual DbSet<Checkout> Checkouts { get; set; }
        public virtual DbSet<Contributor> Contributors { get; set; }
        public virtual DbSet<FeaturedBook> FeaturedBooks { get; set; }
        public virtual DbSet<Member> Members { get; set; }
        public virtual DbSet<Organization> Organizations { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            if (!optionsBuilder.IsConfigured)
            {
#warning To protect potentially sensitive information in your connection string, you should move it out of source code. You can avoid scaffolding the connection string by using the Name= syntax to read it from configuration - see https://go.microsoft.com/fwlink/?linkid=2131148. For more guidance on storing connection strings, see http://go.microsoft.com/fwlink/?LinkId=723263.
                optionsBuilder.UseSqlServer("Server=(LocalDb)\\MSSQLLocalDB;Database=LibrarySystem;user=admin;password=Summer2021");
            }
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.HasAnnotation("Relational:Collation", "SQL_Latin1_General_CP1_CI_AS");

            modelBuilder.Entity<Author>(entity =>
            {
                entity.Property(e => e.Id).ValueGeneratedNever();

                entity.Property(e => e.Name)
                    .IsRequired()
                    .HasMaxLength(100)
                    .IsUnicode(false);
            });

            modelBuilder.Entity<Book>(entity =>
            {
                entity.HasKey(e => new { e.Isbn, e.OrganizationId });

                entity.Property(e => e.Isbn).HasColumnName("ISBN");

                entity.Property(e => e.ImagePath)
                    .HasMaxLength(100)
                    .IsUnicode(false);

                entity.Property(e => e.Summary)
                    .HasMaxLength(500)
                    .IsUnicode(false);

                entity.Property(e => e.Title)
                    .IsRequired()
                    .HasMaxLength(100)
                    .IsUnicode(false);
            });

            modelBuilder.Entity<BookCategorization>(entity =>
            {
                entity.HasKey(e => new { e.BookIsbn, e.CategoryId });

                entity.ToTable("BookCategorization");

                entity.Property(e => e.BookIsbn).HasColumnName("BookISBN");
            });

            modelBuilder.Entity<Category>(entity =>
            {
                entity.Property(e => e.Id).ValueGeneratedNever();

                entity.Property(e => e.CategoryName)
                    .IsRequired()
                    .HasMaxLength(50)
                    .IsUnicode(false);
            });

            modelBuilder.Entity<Checkout>(entity =>
            {
                entity.HasKey(e => new { e.BookIsbn, e.MemberId });

                entity.Property(e => e.BookIsbn).HasColumnName("BookISBN");

                entity.Property(e => e.DueDate).HasColumnType("date");

                entity.Property(e => e.LoanDate).HasColumnType("date");
            });

            modelBuilder.Entity<Contributor>(entity =>
            {
                entity.HasKey(e => new { e.BookIsbn, e.AuthorId });

                entity.Property(e => e.BookIsbn).HasColumnName("BookISBN");
            });

            modelBuilder.Entity<FeaturedBook>(entity =>
            {
                entity.HasNoKey();

                entity.Property(e => e.BookIsbn).HasColumnName("BookISBN");
            });

            modelBuilder.Entity<Member>(entity =>
            {
                entity.Property(e => e.Id).ValueGeneratedNever();

                entity.Property(e => e.Address)
                    .HasMaxLength(100)
                    .IsUnicode(false);

                entity.Property(e => e.Email)
                    .HasMaxLength(100)
                    .IsUnicode(false);

                entity.Property(e => e.FirstName)
                    .HasMaxLength(50)
                    .IsUnicode(false);

                entity.Property(e => e.LastName)
                    .HasMaxLength(50)
                    .IsUnicode(false);

                entity.Property(e => e.Phone)
                    .HasMaxLength(20)
                    .IsUnicode(false);
            });

            modelBuilder.Entity<Organization>(entity =>
            {
                entity.ToTable("Organization");

                entity.Property(e => e.Id).ValueGeneratedNever();

                entity.Property(e => e.Name)
                    .HasMaxLength(50)
                    .IsUnicode(false);
            });

            OnModelCreatingPartial(modelBuilder);
        }

        partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
    }
}
