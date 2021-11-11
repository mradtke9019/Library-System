// Please see documentation at https://docs.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.
var input = document.getElementById("Searchbar");

// Execute a function when the user releases a key on the keyboard
input.addEventListener("keyup", function (event) {
    // Number 13 is the "Enter" key on the keyboard
    if (event.keyCode === 13) {
        // Cancel the default action, if needed
        event.preventDefault();
        // Trigger the button element with a click
        document.getElementById("Searchbutton").click();
    }
});


function SearchForBook(featured) {

    let term = $("#Searchbar").val();
    var searchGif = $("#searchgif");
    var noDisplayClass = "d-none";

    if (!term && !featured) {
        console.log("No search value");
        return;
    }
    searchGif.removeClass(noDisplayClass);

    let url = "/Books/Search";
    if (featured) {
        url += "?featured=true";
        console.log("Getting featured books " + term);
    }
    else {

        url += "?term=" + term;
        console.log("Searching for " + term);
    }

    $.ajax({
        url: url,
        error: function () {
            console.log("error in ajax call")
        }

    }).done(function (data) {
        console.log("Done with ajax call");
        if (!data) {
            console.log("No results");
            $("#booklist").html("No results");
            $("#showFeaturedButton").removeClass(noDisplayClass)
        }
        else {
            $("#showFeaturedButton").addClass(noDisplayClass)
            $("#booklist").html(data);
        }
        searchGif.addClass(noDisplayClass);
    });
}