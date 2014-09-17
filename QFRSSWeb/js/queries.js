$(document).ready(function()
{ 	
	$.removeCookie("ssaP");
	loader = function(inout, msg)
	{
		if (inout === 1)
		{
			if (msg === "")
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
	};
  
	var $L = 0;
	error = function(msg)
	{
		if (msg !== "")
		{
			$("#INFOMsg").text(msg);
			$.mobile.navigate('#INFO', {transition: 'pop', role: 'dialog'});
		}
	};
  
	$("#btnLogin").click(function(){login(); return false;});
	$("#btnregister").click(function(){register(); return false;});
	$("#facepic").change(function()
	{
		if (readURL(this) == -1)
		{
			label("facepic").text("Invalid file type").fadeIn();
		} else
			label("facepic").text("valid").hide();
	});
	$("#submitCapture").click(function(){CreateCase(); return false;});
	$("#btnRefresh").click(function(){updateResults();});
	$("#stopRefreshing").click(function(){stopRefreshing();});
	$("#btnUpdatePassword").click(function(){updatePassword(); return false;});  
	$("#btnChangePassword").click(function()
		{
			clearHide(["u_oldpass","u_pass","u_repass", "updatePassError"]);
			$.mobile.navigate('#changePassword', {transition: 'pop', role: 'dialog'});
		});  
	$(".showText").click(function(){error($(this).text());});    
	 

	$("div[data-role='page']").on("pagebeforeshow" , function()
	{
		if (this.id !== "contactus" && this.id !== "about" && this.id !== "login" && $L === 0)
			logout();
		if (this.id !== "captureface")
			clearHide(["fname","surname","age","desc","facepic"]);
	});
	$("#contactus").on("pagebeforecreate" , function()
	{
		loader(1);
		$("#contacUsContent").load("contactus.html");
	});
	$("#about").on("pagebeforecreate" , function()
	{
		loader(1);
		$("#aboutContent").load("about.html");
	});
	/*$("#account").on("pagebeforeshow" , function()
	{
		if (this.id !== "login" && $L === 0)
			logout();
	});
	$("#results").on("pagebeforeshow" , function()
	{
		if (this.id !== "login" && $L === 0)
			logout();
	});
	$("#captureface").on("pagebeforeshow" , function()
	{
		if (this.id !== "login" && $L === 0)
			logout();
	});*/
	$("div[data-role='page']").on("pageshow" , function()
	{
		loader(0);
	});

	$("div[data-role='page']").on("swiperight", function()
	{
		$.mobile.back({ transition: "slide" });
	});
	$("#login").on("swipeleft", function()
	{
		$.mobile.back({ transition: "slide" });
	});
	$("#account").on("swipeleft", function()
	{
		if ($L === 1)
		{
			if ($CaseID === -1)
				$.mobile.navigate("#captureface", { transition: "slide" });
			else
				$.mobile.navigate("#results", { transition: "slide" });
		}
		else
			logout();
	});

	login = function()
	{
		loader(1);
		if (validate([["user","Username",true],["pass","Password",true]]))
		{		
			var $ida = Sha256.hash("ida"+$("#pass").val()+$("#user").val());
    		$.post('logic/php/connectDB.php', { action: "login", user: $("#user").val(), pass: $ida }, function(data)
			{	
				if (data && data.success === true)
				{
					$.cookie("ssaP", data.passkey);
					$L = 1;
					$("#loginError").fadeOut().text("");					
					$("#Userlogged").text("Welcome "+$("#user").val());
					$("#u_user").val($("#user").val());
					$("#casesOverview").html("");					
					$.mobile.navigate("#account", { transition: "slide" });
					outputAllCases();
					if (data.admin === true)
						$("#adminLink").fadeIn();					
				}	
				else
				{					
					var $out = "";	
					if (data.errors)
					{					
						$.each( data.errors, function( key, val )
						{
							$out += val+"\n";
						});
						$("#loginError").text($out).fadeIn();
					}
					else error("Failed to login. "+JSON.stringify(data));
					loader(0);
				}	
			}, 'json').fail(function(data)
			{
				error("Failed to login. "+JSON.stringify(data));
				loader(0);
			});			
		} else
			loader(0);
	};

	logout = function()
	{
		$.removeCookie("ssaP");
		$.post('logic/php/connectDB.php', { action: "logout" }, function(data)
			{				
				$L = 0;
				$.mobile.navigate("#login", { transition: "slide" });
				clearHide(["user","pass","loginError"]);
				location.reload(true);
				error(data);
			});

	};

	register = function()
	{
		if ($("#user").val() !== "admin")
		{
			error("Admin functionality not allowed!");
			return;	
		}
		loader(1);
		if (validate([["reg_user","Username",true]]))
		{
			var $ida = Sha256.hash("idaqfrss"+$("#reg_user").val());
	    	$.post('logic/php/connectDB.php', {action: "registerUser", passKey: $.cookie("ssaP"), ruser: $("#reg_user").val(), pass: $ida}, function(data)
			{	
				$.mobile.navigate("#account", { transition: "slide" });
			}).fail(function(data)
			{
				// place error code here
				error(data.errors);
			});
		} else
			loader(0);
	};	

	updateUser = function(form)
	{
		$.post('logic/php/connectDB.php', form.serialize()).done(function(data)
		{	
			$.mobile.navigate("#account", { transition: "slide" });
		}).fail(function(data)
		{
			// place error code here

		});
	};

	updatePassword = function(form)
	{
		if ($L === 1)
		{
			if (validate([["u_pass","Password",true],["u_repass","Re-enter password",true],["u_oldpass","Current Password",true]]))
			{
				$pass1 = $("#u_pass").val();
				$pass2 = $("#u_repass").val();
				if ($pass1 === $pass2)
				{
					var $ida1 = Sha256.hash("ida"+$("#pass").val()+$("#user").val());
					var $ida2 = Sha256.hash("ida"+$pass1+$("#user").val());
					$.post('logic/php/connectDB.php', { action: "updatePassword", passKey: $.cookie("ssaP"), newPass: $ida2, oldPass: $ida1 }, function(data)
					{	
						if (data && data.success === true)
						{
							$.cookie("ssaP", data.passkey);
							clearHide(["u_oldpass","u_pass","u_repass", "updatePassError"]);
							$("#updatePassError").text(data.message).fadeIn();				
						}	
						else
						{					
							var $out = "";	
							if (data.errors)
							{					
								$.each( data.errors, function( key, val )
								{
									$out += val+"\n";
								});
								$("#updatePassError").text($out).fadeIn();
							}
							else error("Failed to update password. "+JSON.stringify(data));
							loader(0);
						}
					}, 'json').fail(function(data)
					{
						error("Failed to update password. "+JSON.stringify(data));
						loader(0);
					});
				}
				else
				{
					$("#u_repass").text("New passwords do not match").show();
				}
			}
		} else logout();	
	};

	clearHide = function(inputs)
	{
		for	(var index = 0; index < inputs.length; index++)
		{
			var input = inputs[index];
			var lbl = label(input);
			$("#"+input).val('');
			$("#"+input).text('');
			if (lbl !== null)
			{
				lbl.text('');
				lbl.hide();
			}
		}
	}

	//Send an array of inputs eg. [["textBox","Description",true,false],["textBox","Description",true,false]]
	validate = function(inputs)
	{
		var flag = true;
		for	(var index = 0; index < inputs.length; index++)
		{
			var input = inputs[index];

			var lbl = label(input[0]);
			var field = checkInput($("#"+input[0]), input[1], input[2], input[3]);

			if (field !== 1)
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
	};

	label = function(input)
	{
		return $("label[for='"+$("#"+input).attr('id')+"']");
	};
	//isSpecial [1]=isNumber [2]=Gender, [3]=Image
	checkInput = function(input, name, testLength, isSpecial)
	{	
		
		var value = input.val();
		if (value === '')
			return name+" is required";
		if (testLength === true && (value.length < 2 || value.length > 20))
			return name+" should be more than 2 less than 20";
		if (isSpecial === 1 && isNaN(value) === true)
			return name+" may only contain numerals";
		if (isSpecial === 2 && value !== 'M' && value !== 'F')
			return name+" must select valid gender";	
		if (isSpecial === 3)
		{
			var extension = value.substr( (value.lastIndexOf('.') +1) );
			if (extension !== "jpg" && extension !== "jpeg")
				return name+" invalid file. Image jpg/jpeg only";
		}
		return 1;
	};

	CreateCase = function()
	{
		loader(1, "Creating case");
		if ($refreshing !== null)
		{
			clearInterval($refreshing);
		}
		if (validate([["fname","First Name",true],["surname","Surname",true],["gender","Gender",false,2],["age","Age",false,1]]) === true)
		{	
			$img = $("#capturefacepreview").attr('src');
			if (label("facepic").text() == "valid" && $img !== "")
			{				
	      		$.post('logic/php/connectDB.php', { action: "createCase", passKey: $.cookie("ssaP"), fname: $("#fname").val(), surname: $("#surname").val(), gender: $("#gender").val(), age: $("#age").val(), desc: $("#desc").val(), facepic: $img }, function(data)
				{	
					if (data && data.success === true) 
					{		
						loader(1, "Starting facial recognition");			
						$CaseID = data.message;
						$("#caseID").html($CaseID);
						var $ida = Sha256.hash("ida"+$("#pass").val()+$("#user").val());	
						$.post('http://localhost/starter.cgi', { user: $("#user").val(), pass: $ida, caseID: $CaseID }, function(data)
						{
							if (data === 1)
							{
								loader(1, "Started...");
								$refreshing = setInterval(function(){refreshResultStatus();}, 2500);
								$("#statusCode").html("1");
								$("#statusInfo").html("Started");
								$("#noOfResults").html("0");							
								$.mobile.navigate("#results");
							}
							else
							{
								loader(0);
								error(data);
							}
						}).fail(function(data)
						{
							error("Starting facial recognition failed. "+JSON.stringify(data));
							loader(0);	
						});					
					}
					else
					{
						var $out = "";	
						if (data.errors)
						{					
							$.each( data.errors, function( key, val )
							{
								$out += val+"\n";
							});
							error($out);
						}
						else error("Failed to create case. "+JSON.stringify(data));
						loader(0);
					}						
				}, 'json').fail(function(data)
				{
					error("Failed to create case. "+JSON.stringify(data));
					loader(0);	
				});
			} 
			else
			{ 
				error("No valid picture selected");
				loader(0);  
			}                                                                                                                                                                     			
		}
		else
			loader(0);			
	};

	OpenCase = function(CaseID)
	{
		loader(1);
		if (CaseID !== $CaseID)
		{
			stopRefreshing();
			$Results = "";
			$LastIndex = 0;
			$numberOfResults = 0;			
			$CaseID = CaseID;
			var $case = $cases[CaseID];
			$("#caseID").html($CaseID);
			$("#statusCode").html($case.StatusCode);
			$("#statusInfo").html($case.StatusInfo);
			$("#noOfResults").html($case.NumberOfResults);
      $('#resultOverview').html("").trigger('create');
			updateResults();
			$.mobile.navigate("#results");
		}
		else
		{
			$.mobile.navigate("#results");
		}
	};

	stopRefreshing = function()
	{
		if ($refreshing !== null)
		{
			clearInterval($refreshing);
			$refreshing = null;
		}
	};
	
	refreshResultStatus = function()
	{
		if ($CaseID > 0)
		{
			$.post('logic/php/connectDB.php', { action: "refresh", passKey: $.cookie("ssaP"), caseID: $CaseID }, function(data)
			{	
				if (data.success === true)
				{
					var $result = data.message;	
					updateResults(data.message);
					$("#statusCode").html($result.StatusCode);
					if ($result.StatusCode === 3)
						stopRefreshing();
					$("#statusInfo").html($result.StatusInfo);
					$("#noOfResults").html($result.NumberOfResults);
				}
				else
				{
					error(data.errors);
				}
			}, 'json').fail(function(data)
			{
				stopRefreshing();
				error("Refreshing Case progress failed. "+JSON.stringify(data));
			});
		}
		else
			stopRefreshing();
	};
	
	var $refreshing = null;
	var $Results = "";
	var $LastIndex = 0;
	var $CaseID = -1;
	var $numberOfResults = 0;
  
	updateResults = function()
	{
		loader(1, "Updateing");
		if ($CaseID > -1)
		{
			if (validate([["user","Username",true],["pass","Password",true]]))
			{
				$.post('logic/php/connectDB.php', { action: "getResults", passKey: $.cookie("ssaP"), caseID: $CaseID, LastIndex: $LastIndex }, function(data)
				{	
					if (data && data.success === true)
					{
						loader(1, "Loading Results...");
						var $new = "<div data-role='collapsible'>"+
									"<h2>Results from no."+$numberOfResults+"</h2>"+
									"<ul data-role='listview'>";
						$.each( data.message, function( key, val )
						{
							var $img = val.Image;
							if ($img === null)
								$img = jQuery.parseJSON( '{ "ID": "-1", "TimeStamp": "undefined", "Location": "none", "Filename": "none.png" }' );
							$new += 	"<li>"+
											"<a class='faceResult' id='"+val.ImageCode+"'>"+
												"<img src='http://localhost:1080/cgi-bin/geti.qfr?image="+val.ImageCode+"'>"+
												"<p>Date & Time: "+$img.TimeStamp+"</p>"+
												"<p>Location: "+$img.LocationX+"</p>"+
												"<p>Match: "+val.Match+"</p>"+
											"</a>"+
										"</li>";
									$numberOfResults++;
									$LastIndex = val.ID;
						});
						$new += "	</ul>"+
								"</div>";
						$('#resultOverview').append($new).trigger('create');	
						$(".faceResult").click(function()
						{
							popImage(this.id+"&original=1");
						});						
						loader(0);
					}
					else
					{
						error(data.errors);
					}
					loader(0);
				}, 'json').fail(function(data)
				{
					error("Getting case results failed. "+JSON.stringify(data));
					loader(0);
				});
			} else
				loader(0);
		} else
		{
			$.mobile.navigate('#account', {transition: 'slide'});
			error("No case selected");
			loader(0);
		}
	};
  
	var $cases = [];
	//Formats the json data into the correct format
	outputAllCases = function()
	{
		loader(1,"Getting all cases");
		$.post('logic/php/connectDB.php', { action: "getCases", passKey: $.cookie("ssaP") }, function(data)
		{	
			if (data && data.success === true)
			{
				if (data.message)
				{
					$group = 2;
					var $new = "<div data-role='collapsible' data-theme='e' data-content-theme='e'>"+
								"<h2>Recent Cases 1</h2>"+
								"<ul data-role='listview' data-split-icon='eye' data-split-theme='b'>";
					$.each( data.message, function( key, val )
					{		
						if ((key+1) % 10 === 0)
			            {
			            	$new += "	</ul>"+
									"</div>";
			            	$new += "<div data-role='collapsible' data-theme='e' data-content-theme='e'>"+
										"<h2>Recent Cases "+($group++)+"</h2>"+
										"<ul data-role='listview' data-split-icon='eye' data-split-theme='b'>";
			            }			
						if (val.Image === null)
							val.Image = jQuery.parseJSON( '{ "ID": "-1", "TimeStamp": "undefined", "Location": "none", "Filename": "none.png" }' );
						var $img = val.Image;
						$cases[val.ID] = val;
						$new += 	"<li id='"+val.ID+"'>"+
			                            "<a class='aCase'>"+
			                                "<h3>"+val.sub_Name+" "+val.sub_Surname+"</h3>"+
			                                "<p>No. of results: "+val.NumberOfResults+"</p>"+
			                            "</a>"+
			                            "<a class='aPreview'>Preview</a>"+
			                        "</li>";			            
					});
					$new += "	</ul>"+
							"</div>";
					$('#casesOverview').html($new).trigger('create');
					$(".aCase").click(function(){OpenCase($(this).parent().get(0).id);});
					$(".aPreview").click(function()
					{
						var $case = $cases[$(this).parent().get(0).id];
						popImage("caseImages/"+$case.Image.Filename, "Gender: "+$case.sub_Gender,"Age: "+$case.sub_Age,"DateTime: "+$case.Image.TimeStamp,$case.Description,false);
					});
				}
				else
					$('#casesOverview').html("<h4>No cases created yet</h4>");
			}
			else
			{
				$('#casesOverview').html("<h3 class='error'>Failed to load cases</h3><h4 class='error'>Errors: "+JSON.stringify(data)+"</h4>");
			}
			loader(0);
		}, 'json').fail(function(data)
		{
			$('#casesOverview').html("<h3 class='error'>Failed to load cases</h3><h4 class='error'>Errors: "+JSON.stringify(data)+"</h4>");
			loader(0);
		});	
	};

	getNimda = function()
	{
		loader(1, "Loading Users...");
		$.post('logic/php/connectDB.php', { action: "getUsers", passKey: $.cookie("ssaP") }, function(data)
		{	
			if (data && data.success === true)
			{				
				var $new = "<div data-role='collapsible'>"+
							"<h2>Users</h2>"+
							"<ul data-role='listview'>";
				$.each( data.message, function( key, val )
				{					
					$new += 	"<li>"+
									"<div id='"+val.Username+"'>"+
										"<h3>"+val.Username+"</h3>"+
										"<label>Is active"+
											"<input type='checkbox' class='active' name='active'";
													if (val.Active)
														$new += " checked";
					$new += 				" />"+
										" </label>"+
										"<button data-theme='c' class='clearpass'>Clear Password</button>"+
									"</div>"+
								"</li>";
				});	
				$new += "	</ul>"+
						"</div>";	
				$new += "<div data-role='collapsible'  data-theme='e'>"+
							"<h2>Add new user</h2>"+
							"<ul data-role='listview'>";	
				$new += 		"<li>"+
									"<input id='reg_user' name='reg_user' placeholder='New Username'>"+
									"<label for='reg_user' class='error'></label>"+
									"<button id='btnRegUser'>Create</button>"+	
								"</li>";		
				$new += "	</ul>"+
						"</div>";	
				$('#userView').html($new).trigger('create');	
				$("input[name=active]").on("checked", function()
				{
					
				});	
				$(".clearpass").click(function()
				{
					
				});
				$("#btnRegUser").click(function()
				{
					register();
				});					
				loader(0);
			}
			else
			{
				error(data.errors);
			}
			loader(0);
		}, 'json').fail(function(data)
		{
			error("Getting users failed"+JSON.stringify(data));
			loader(0);
		});
	};

	popImage = function(img, d1,d2,d3,d4,cgi)
	{
		$("#d1").html(d1);
		$("#d2").html(d2);
		$("#d3").html(d3);
		$("#d4").html(d4);
		if (cgi === false)
			$("#facepreview").attr('src',img);
		else
			$("#facepreview").attr('src',"http://localhost/cgi-bin/geti.qfr?image="+img+"&original=1");
		$.mobile.navigate('#popup', {transition: 'pop', role: 'dialog'});
	};

	readURL = function(input)
	{
		if (input.files && input.files[0])
		{
			if(input.files[0].type == "image/jpeg")
			{
				var reader = new FileReader();
				reader.onload = function (e)
				{
					$('#capturefacepreview').attr('src', e.target.result);
				};
				reader.readAsDataURL(input.files[0]);
			} else return -1;
		}
	};

	/*if ($("#user").val() === "" || $("#pass").val() === "")
	{
		$.mobile.navigate("#login");
	}
	$.post('logic/php/connectDB.php', { action: "test" }, function(data)
	{	
		error("Testing. "+JSON.stringify(data));	
	}, 'json').fail(function(data)
			{
				error("Error in script "+JSON.stringify(data));
				loader(0);
			});*/
	loader(0);
});
