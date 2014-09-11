$(document).ready(function(){ 
	var loader = function(inout)
	{
		if (inout == 1)
		{
			$("#fader").fadeIn();
			$("#loader").fadeIn();
		} else
		{
			$("#loader").fadeOut();
			$("#fader").fadeOut();			
		}
	}
	var error = function(msg)
	{
		if (msg.length > 1)
		{
			label("ErrorMsg").text(msg);
			$("#fader").fadeIn();
			$("#ErrorMsg").fadeIn();
		} else
		{
			$("#fader").fadeOut();
			$("#ErrorMsg").fadeOut();
		}
	}
	loader(0);
	error("");
	$("#btnLogin").click(function(){login(this); return false;});
	$("#btnregister").click(function(){register(this); return false;});
	$("#facepic").change(function(){readURL(this);});
	$("#submitCapture").click(function(){CreateCase(this); return false;});
	    
	$('#uploadFace').validate(
	{	    
	    errorPlacement: function (error, element) {
	        error.appendTo(element.parent().prev());
	    },
	    submitHandler: function (form) {
	        $.post('process.php', function(form)
			{		
				//$.mobile.navigate("#results");
			}).fail(function(data)
			{
				// place error code here
			});
	        return false;
	    }
	});

	$("div[data-role='page']").on("pageshow" , function() {
		loader(0);
	});

	$("#btnLoadResults").click(function(){outputResults();});
	
	var $username = $('#user'), $password = $('#pass');

	login = function(form){
		loader(1);

		if (validate([["user","Username",true],["pass","Password",true]]))
		{
	    	$.post('logic/php/connectDB.php', function(form)
			{	
				loader(0);
				$.mobile.navigate("#account");
			}).fail(function(data)
			{
				// place error code here

			});
		} else
			loader(0);		
	};

	register = function(form){
		if ($username != "Admin")
		{
			error("Admin functionality not allowed!");
			return;	
		}
		loader(1);

		if (validate([["user","Username",true],["pass","Password",true]]))
		{
	    	$.post('logic/php/connectDB.php', function(form)
			{	
				$.mobile.navigate("#account");
			}).fail(function(data)
			{
				// place error code here

			});
		} else
			loader(0);
	};	

	//Send an array of inputs eg. [["textBox","Description",true,false],["textBox","Description",true,false]]
	validate = function(inputs)
	{
		var flag = true;
		for	(index = 0; index < inputs.length; index++)
		{
			var input = inputs[index];

			var lbl = label(input[0]);
			var field = checkInput($("#"+input[0]), input[1], input[2], input[3]);

			if (field != 1)
			{
				$("#"+input[0]).focus();
				lbl.text(field);
				lbl.fadeIn();
				flag = false;
			} else
			{
				lbl.hide();
			}
		}
		return flag;
	}

	label = function(input)
	{
		return $("label[for='"+$("#"+input).attr('id')+"']");
	}
	//isSpecial [1]=isNumber [2]=Gender, [3]=Image
	checkInput = function(input, name, testLength, isSpecial)
	{	
		
		var value = input.val();
		if (value == '')
			return name+" is required";
		if (testLength == true && (value.length < 2 || value.length > 20))
			return name+" should be more than 2 less than 20";
		if (isSpecial == 1 && isNaN(value) == true)
			return name+" may only contain numerals";
		if (isSpecial == 2 && value != 'M' && value != 'F')
			return name+" must select valid gender";	
		if (isSpecial == 3)
		{
			var extension = value.substr( (value.lastIndexOf('.') +1) );
			if (extension != "jpg" && extension != "jpeg")
				return name+" invalid file. Image jpg/jpeg only";
		}
		return 1;
	}

	CreateCase = function(form)
	{
		loader(1);
		if (validate([["fname","First Name",true],["surname","Surname",true],["gender","Gender",false,2],["age","Age",false,1],["facepic","Picture",false,3]]) == 1)
		{
			$.post('logic/php/connectDB.php', function(form)
			{	
				$.mobile.navigate("#results");
			}).fail(function(data)
			{
				// place error code here

			});
			
		}
		else
			loader(0);			
	}

	
	$tmp = '<div data-role="collapsible"> <h2>One month ago</h2> <ul data-role="listview" data-split-icon="gear" data-split-theme="a"> <li> <a href="#popup"> <img src="images/digital.jpg"> <h3>25 July 2014</h3> <p>Camera Location: Entrance</p> </a> <a href="#popup" data-rel="dialog" data-transition="pop">View original</a> </li> <li> <a href="#popup"> <img src="images/digital.jpg"> <h3>22 July 2014</h3> <p>Camera Location: South Exit</p> </a> <a href="#popup" data-rel="dialog" data-transition="pop">View original</a> </li> <li> <a href="#popup"> <img src="data:image/png;base64,R0lGODlhEAAOALMAAOazToeHh0tLS/7LZv/0jvb29t/f3//Ub//ge8WSLf/rhf/3kdbW1mxsbP//mf///yH5BAAAAAAALAAAAAAQAA4AAARe8L1Ekyky67QZ1hLnjM5UUde0ECwLJoExKcppV0aCcGCmTIHEIUEqjgaORCMxIC6e0CcguWw6aFjsVMkkIr7g77ZKPJjPZqIyd7sJAgVGoEGv2xsBxqNgYPj/gAwXEQA7"> <h3>3 July 2014</h3> <p>Camera Location: Bull street</p> </a> <a href="#popup" data-rel="dialog" data-transition="pop">View original</a> </li> </ul> </div>';
 //Formats the json data into the correct format
	outputResults = function()
	{
		loader(1);
		$vas = '<div data-role="collapsible"><h2>Upto three months</h2><ul data-role="listview" data-split-icon="gear" data-split-theme="a"><li><a href="#popup"><img src="images/digital.jpg"><h3>25 May 2014</h3><p>Camera Location: South Exit</p></a><a href="#popup" data-rel="dialog" data-transition="pop">View original</a></li><li><a href="#popup"><img src="images/digital.jpg"><h3>25 May 2014</h3><p>Camera Location: South Entrance</p></a><a href="#popup" data-rel="dialog" data-transition="pop">View original</a></li><li><a href="#popup"><img src="data:image/png;base64,R0lGODlhEAAOALMAAOazToeHh0tLS/7LZv/0jvb29t/f3//Ub//ge8WSLf/rhf/3kdbW1mxsbP//mf///yH5BAAAAAAALAAAAAAQAA4AAARe8L1Ekyky67QZ1hLnjM5UUde0ECwLJoExKcppV0aCcGCmTIHEIUEqjgaORCMxIC6e0CcguWw6aFjsVMkkIr7g77ZKPJjPZqIyd7sJAgVGoEGv2xsBxqNgYPj/gAwXEQA7"><h3>25 May 2014</h3><p>Camera Location: South Entrance</p></a><a href="#popup" data-rel="dialog" data-transition="pop">View original</a></li></ul></div><div data-role="collapsible"><h2>Later than three months ago</h2><ul data-role="listview" data-split-icon="gear" data-split-theme="a"><li><a href="#popup"><img src="images/digital.jpg"><h3>26 March 2014</h3><p>Camera Location: South Park</p></a><a href="#popup" data-rel="dialog" data-transition="pop">View original</a></li><li><a href="#popup"><img src="images/digital.jpg"><h3>26 March 2014</h3><p>Camera Location: South Exit</p></a><a href="#popup" data-rel="dialog" data-transition="pop">View original</a></li><li><a href="#popup"><img src="data:image/png;base64,R0lGODlhEAAOALMAAOazToeHh0tLS/7LZv/0jvb29t/f3//Ub//ge8WSLf/rhf/3kdbW1mxsbP//mf///yH5BAAAAAAALAAAAAAQAA4AAARe8L1Ekyky67QZ1hLnjM5UUde0ECwLJoExKcppV0aCcGCmTIHEIUEqjgaORCMxIC6e0CcguWw6aFjsVMkkIr7g77ZKPJjPZqIyd7sJAgVGoEGv2xsBxqNgYPj/gAwXEQA7"><h3>12 March 2014</h3><p>Camera location: Main rd. South</p></a><a href="#popup" data-rel="dialog" data-transition="pop">View original</a></li></ul></div>';
		$tmp += $vas;
		$('#resultOverview').html($tmp).trigger('create');	
		loader(0);
	}

	readURL = function(input)
	{

		if (input.files && input.files[0])
		{
			var reader = new FileReader();
			reader.onload = function (e)
			{
				$('#capturefacepreview').attr('src', e.target.result);
			}
			reader.readAsDataURL(input.files[0]);
		}
	}

});

