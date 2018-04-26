(function ($) {

  Drupal.behaviors.node_reminder = {
    attach: function (context, settings) {
      var tab = $('.vertical-tabs a:contains("Reminder")');
      var checkbox = $('#edit-reminder input[name="active"]');

      // Edit the tab summary on page load
      tab.find('.summary').text(checkbox.attr('checked') ? 'Enabled' : 'Disabled');

      // Edit the tab summary when the Enabled checkbox is clicked
      $('#edit-reminder input[name="active"]', context).click(function () {
        $('.vertical-tabs .selected .summary').text($(this).attr('checked') ? 'Enabled' : 'Disabled');
      });
    }
  };

})(jQuery);
