$(document).ready(function(){ 
	var loader = function(inout, msg)
	{
		if (inout == 1)
		{
			if (msg == "")
				$("#loadingInfo").text("loading...");
			else
				$("#loadingInfo").text(msg);
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
	$("#btnLogin").click(function(){login($("#login")); return false;});
	$("#btnregister").click(function(){register($("#register")); return false;});
	$("#facepic").change(function(){readURL(this);});
	$("#submitCapture").click(function(){CreateCase($("#uploadFace")); return false;});
	$("#btnRefresh").click(function(){refreshResultStatus();});
	$("#stopRefreshing").click(function(){stopRefreshing();});
	$(".faceResult").click(function(){openOriginal(this);});
	$(".aCase").click(function(){OpenCase($(this).attr("id"));});
	$(".aPreview").click(function(){openPreview(this);});
	    
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
	
	var $username = $('#user'), $password = $('#pass');

	login = function(form)
	{
		loader(1);

		if (validate([["user","Username",true],["pass","Password",true]]))
		{
			if ($("#user").val() == "admin")
			{
				$.mobile.navigate("#account");
			}
			else
			{
		    		$.post('logic/php/connectDB.php', form.serialize()).done(function(data)
				{	
					if (data.success == true)
					{
						$("#Userlogged").text($("user").val());
						outputAllCases(data.message);
						$.mobile.navigate("#account");
					}	
					else
					{
						error("Failed to login. "+data);
					}	
					loader(0);
				}).fail(function(data)
				{
					// place error code here
					error("Failed to login. ");
					loader(0);
				});
			}
		} else
		{
			loader(0);	
		}	
	};

	register = function(form)
	{
		if ($username != "Admin")
		{
			error("Admin functionality not allowed!");
			return;	
		}
		loader(1);
		if (validate([["user","Username",true],["pass","Password",true]]))
		{
	    	$.post('logic/php/connectDB.php', form.serialize()).done(function(data)
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
		loader(1, "Creating case");
		if ($refreshing != null)
		{
			clearInterval($refreshing);
		}
		if (validate([["fname","First Name",true],["surname","Surname",true],["gender","Gender",false,2],["age","Age",false,1],["facepic","Picture",false,3]]) == 1)
		{			
			$.post('logic/php/connectDB.php', form.serialize()).done(function(data)
			{	
				if (data.success == true)
				{		
					loader(1, "Starting facial recognition");	
					$result = data.message[0];		
					$CaseID = result.ID;
					$("#caseID").html($CaseID);
					$.post('logic/cgi/startRec.cgi', { user: $("#user").val(), pass: $("#pass").val(), caseID: $CaseID }).done(function(data)
					{
						if (data == 1)
						{
							loader(1, "Started...");
							$refreshing = setInterval(function(){refreshResultStatus();}, 2500);
							$("#statusCode").html("1");
							$("#statusInfo").html("Started");
							$("#noOfResults").html("0");							
							$.mobile.navigate("#results");
						}
					}).fail(function(data)
					{
						error("Starting facial recognition failed. "+data);
						loader(0);	
					});					
				}
				else
				{
					error(data.errors);
				}
				loader(0);	
				
			}).fail(function(data)
			{
				error("Refreshing Case progress failed. "+data);
				loader(0);	
			});                                                                                                                                                                        			
		}
		else
			loader(0);			
	}

	OpenCase = function(CaseID)
	{

	}

	ClearUser = function()
	{
		$('#casesOverview').html("");
		ClearResults();
	}

	ClearResults = function()
	{
		$("#statusCode").html("");
		$("#statusInfo").html("");
		$("#noOfResults").html("");
		$('#resultOverview').html("").trigger('create');	
	}

	stopRefreshing = function()
	{
		if ($refreshing != null)
		{
			clearInterval($refreshing);
		}
	}
	
	refreshResultStatus = function()
	{
		if ($CaseID > 0)
		{
			$.post('logic/php/connectDB.php', { action: "refresh", user: $("#user").val(), pass: $("#pass").val(), caseID: $CaseID }).done(function(data)
			{	
				if (data.success == true)
				{
					$result = data.message;	
					updateResults(data.message);
					$("#statusCode").html($result.StatusCode);
					$("#statusInfo").html($result.StatusInfo);
					$("#noOfResults").html($result.NumberOfResults);
				}
				else
				{
					error(data.errors);
				}
			}).fail(function(data)
			{
				stopRefreshing();
				error("Refreshing Case progress failed. "+data.errors);
			});
		}
		else
			stopRefreshing();
	}
	
	$refreshing = null;
	$Results = "";
	$LastIndex = 0;
	$CaseID = -1;
	updateResults = function()
	{
		loader(1, "Updateing");
		if ($CaseID > 0)
		{
			if (validate([["user","Username",true],["pass","Password",true]]))
			{
				$.post('logic/php/connectDB.php', { action: "getResults", user: $("#user").val(), pass: $("#pass").val(), caseID: $CaseID, index: $LastIndex }).done(function(data)
				{	
					if (data.success == true)
					{
						loader(1, "Loading Results...");
						outputResults(data.message[0]);
					}
					else
					{
						error(data.errors);
					}
					loader(0);
				}).fail(function(data)
				{
					error("Getting case results failed. "+data.errors);
					loader(0);
				});
			} else
				loader(0);
		} else
		{
			error("No case selected");
			loader(0);
		}
	}	
	//Formats the json data into the correct format
	outputAllCases = function(data)
	{
		loader(1);
		$new = "<div data-role='collapsible'>"+
					"<h2>Recent Cases:</h2>"+
					"<ul data-role='listview' data-split-icon='eye' data-split-theme='a'>";
		$.each( data, function( key, val )
		{
			$img = val.Image;
			if ($img.success == true)
				$img = message[0];
			else
				$img = jQuery.parseJSON( '{ "ID": "-1", "TimeStamp": "undefined", "Location": "none"  }' );
			$new += 	"<li>"+
                            "<div class='aCase' id="+val.ID+">"+
                                "<h3>"+val.sub_Name+" "+val.sub_Surname+"</h3>"+
                                "<p>"+val.Description+"</p>"+
                                "<p>"+val.StatusInfo+" | No. of results: "+val.NumberOfResults+"</p>"+
                            "</div>"+
                            "<div class='aPreview' id='"+$img.Filename+"'>Preview</a>"+
                        "</li>";
		});
		$new = "	</ul>"+
				"</div>";
		$('#casesOverview').html($tmp).trigger('create');	
		loader(0);
	}

	$numberOfResults = 0;
	outputResults = function(data)
	{
		loader(1);
		$new = "<div data-role='collapsible'>"+
					"<h2>Results from no."+$numberOfResults+"</h2>"+
					"<ul data-role='listview'>";
		$.each( data, function( key, val )
		{
			$img = val.Image;
			if ($img.success == true)
				$img = message[0];
			else
				$img = jQuery.parseJSON( '{ "ID": "-1", "TimeStamp": "undefined", "Location": "none"  }' );
			$new += 	"<li>"+
							"<div class='faceResult'>"+
								"<img id='"+val.ImageCode+"' src='http://localhost/geti.cgi?image"+val.ImageCode+"&original=1'>"+
								"<h3>"+$img.TimeStamp+"</h3>"+
								"<p>Location: "+$img.LocationX+"</p>"+
								"<p>Match: "+val.Match+"</p>"+
							"</div>"+
						"</li>";
					$numberOfResults++;
					$LastIndex = val.ID;
		});
		$new = "	</ul>"+
				"</div>";
		$tmp += $new;
		$('#resultOverview').html($tmp).trigger('create');	
		loader(0);
	}

	openOriginal = function(obj)
	{
		loader(1,"Getting original");
		$timestamp = $(obj+" > h3").html();
		var arr = $timestamp.split(' ');
		$("#facepreview").src = "http://localhost/geti.cgi?image"+$(obj+" > img").attr("id")+"&original=1";
		$("#orgDate").html(arr[0]);
		$("#orgTime").html(arr[1]);
		$("#orgLocation").html($(obj+" > p:first-child").html());
		$("#orgMatch").html("Recognition match: "+$(obj+" > p:last-child").html());
		$.mobile.changePage('#results', {transition: 'pop', role: 'dialog'});
		loader(0);
	}
	openPreview = function(obj)
	{
		loader(1,"Previewing Case");
		$("#facepreview").src = "http://localhost/caseImages/"+$(obj).attr("id");
		$("#orgDate").html("");
		$("#orgTime").html("");
		$("#orgLocation").html("");
		$("#orgMatch").html("");
		$.mobile.changePage('#results', {transition: 'pop', role: 'dialog'});
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

