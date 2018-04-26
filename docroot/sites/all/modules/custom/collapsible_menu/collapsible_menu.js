//alert("HOOO HOO HAA hAA!");
//$(document).ready(function() {
  //jQuery('#block-menu-block-1 .menu li:has(ul)').css('list-style-image', 'url(images/expand.gif)');
  jQuery('#block-menu-block-1').find('ul.menu li:has(ul)').css('list-style-image', 'url(/images/expand.gif)');
  jQuery('#block-menu-block-1 .menu li:has(ul)').click(function(event) {
    if(this == event.target) {
      if($(this).children().is(':hidden')) {
        $(this).css('list-style-image', 'url(images/collapse.gif)').children().slideDown();
      }else{
        $(this).css('list-style-image', 'url(images/expand.gif)').children().slideUp();
      }
    }
    return false;
  }).css('cursor', 'pointer');
 
  jQuery('#block-menu-block-1 .menu li:not(:has(ul))').css({'cursor': 'default', 'list-style-image':'none'});
//});
