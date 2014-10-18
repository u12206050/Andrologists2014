$(document).ready(function()
{
	/*--- BEGIN ---*/
	$("#output").append("<h1>Starting...</h1><hr>");
	/*--- LIBS ---*/
	if ($)
		$("#output").append("<h3>Jquery: works. (duh) v: "+$.fn.jquery+"</h3>");
	if ($.mobile)
		$("#output").append("<h3>JqueryMobile: works. v: "+$.mobile.version+"</h3>");
	$("#output").append("<h3>Date: "+new Date()+"</h3>");
	
	/*--- Encryption SECURITY ---*/
	$("#output").append("<hr><h2>Testing Security and Encryption</h2><hr>");
	$("#output").append("<h3>Crypto Sha256: sha256(works)="+CryptoJS.SHA256("works")+"</h3>");
	$("#output").append("<h3>AdminPass: "+CryptoJS.SHA256("idaqfrssadmin")+"</h3>");
	$("#output").append("<h4>Should be on deployment: 5656674d2a4c675f8bf727885ff75ea607256c398111a524980ea91ef864f8bd</h4>");
	$randomPassword = (CryptoJS.SHA256("idaqfrss"+Date.now())+"").substr(randomBetween(3,30), 8);
	$("#output").append("<h3>Random password: "+$randomPassword+"</h3>");	
	/*--- CGI ---*/

	$("#output").append("<hr><h2>Testing CGI connection</h2><hr>");
	$("#output").append($("<div>Shold show: <pre>Could not authenticate user</pre></div>"));
	$("#output").append($("<div></div>").load("../starter.cgi"));

	/*--- IMAGE SECURITY ---*/
	$("#output").append("<hr><h2>Testing Image Security</h2><hr>");
	$("#output").append("<h3>Normal image from server: <img src='../images/digital.jpg'></img></h3>");
	$("#output").append("<h3>Secure image from server: <img src='../geti.cgi?image=images/digital.jpg'></img></h3>");
	
	/*--- END ---*/
	$("#output").append("<h1>Finished.</h1><hr>");
});
