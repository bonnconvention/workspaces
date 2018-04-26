(function($) {
  // This jQuery function is called when the document is ready
  $(function() {
    var f = $('form.comment-form');
    var t = $('#comments h2.title.comment-form');
    if(t.length > 0) {f.hide()};
    t.html("<a href='#'>" + t.text() + "</a><br />");
    t.click(function(evt) {
      //Prevent the default event of going to the top of the page
      //when the title is clicked.
      evt.preventDefault();
      f.toggle('fast', function() {
      // Animation complete.
    });
    //add css class to H2 title when clicked//
    $(this).toggleClass("open");
    });
  });
})(jQuery);
