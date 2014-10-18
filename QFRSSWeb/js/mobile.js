$(document).bind('mobileinit',function()
{
	$.mobile.defaultPageTransition = "slide";
});

function randomBetween(min,max)
{
    return Math.floor(Math.random()*(max-min+1)+min);
}