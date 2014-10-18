$(document).ready(function()
{ 	
	$server = "";
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
			var $ida = (CryptoJS.SHA256("ida"+$("#pass").val()+$("#user").val())).toString();
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
			var $newUser = $("#reg_user").val();
			var $password = (CryptoJS.SHA256("idaqfrss"+Date.now())+"").substr(randomBetween(5,25), 6);
			var $ida = (CryptoJS.SHA256("ida"+$password+$newUser)).toString();
	    	$.post('logic/php/connectDB.php', {action: "registerUser", passKey: $.cookie("ssaP"), ruser: $newUser, pass: $ida}, function(data)
			{					
				$.mobile.navigate("#account", { transition: "slide" });
				error($newUser+" password is: "+$password+"\nCan change once logged in.");
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
					var $ida1 = (CryptoJS.SHA256("ida"+$("#pass").val()+$("#user").val())).toString();
					var $ida2 = (CryptoJS.SHA256("ida"+$pass1+$("#user").val())).toString();
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
	
	var $refreshing = null;
	var $Results = "";
	var $LastIndex = 0;
	var $CaseID = -1;
	var $numberOfResults = 0;

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
						$CaseID = data.message;
						$("#caseID").html($CaseID);
						var $ida = (CryptoJS.SHA256("ida"+$("#pass").val()+$("#user").val())).toString();	
						loader(1, "Starting facial recognition");
						$.post($server+"starter.cgi", { user: $("#user").val(), pass: $ida, caseID: $CaseID }, function(data)
						{
							if (data === "1")
							{
								loader(1, "Started...");
								$("#capturefacepreview").attr('src','');
								$refreshing = setInterval(function(){refreshResultStatus($CaseID);}, 2500);
								OpenCase($CaseID);
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
	
	refreshResultStatus = function($CaseID)
	{
		if ($CaseID > 0)
		{
			$.post('logic/php/connectDB.php', { action: "refresh", passKey: $.cookie("ssaP"), caseID: $CaseID }, function(data)
			{	
				if (data && data.success === true)
				{
					var $result = data.message;	
					updateResults(data.message);
					$("#statusCode").html($result.StatusCode);
					if ($result.StatusInfo === "finished")
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
  
	updateResults = function()
	{
		loader(1, "Updating");
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
						$indexID = $LastIndex;
						$.each( data.message, function( key, val )
						{
							var $img = val.Image;
							if ($img === null)
								$img = jQuery.parseJSON( '{ "ID": "-1", "TimeDate": "undefined", "Location": "none", "Filename": "none.png" }' );
							$new += 	"<li>"+
											"<a class='faceResult"+$indexID+"' id='"+val.ImageCode+"'>"+
												"<img src='"+$server+"geti.cgi?image="+val.ImageCode+"&org=1'>"+
												"<p>Date & Time: "+$img.TimeDate+"</p>"+
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
						$(".faceResult"+$indexID).click(function()
						{
							popImage(this.id+"&org=0",$("#"+this.id+" :nth-child(3)").text(),$("#"+this.id+" :nth-child(4)").text(),$("#"+this.id+" :nth-child(2)").text(),"");
						});						
						loader(0);
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
							val.Image = jQuery.parseJSON( '{ "ID": "-1", "TimeDate": "undefined", "Location": "none", "Filename": "none.png" }' );
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
						popImage("caseImages/"+$case.Image.Filename, "Gender: "+$case.sub_Gender,"Age: "+$case.sub_Age,"DateTime: "+$case.Image.TimeDate,$case.Description);
					});
				}
				else
					$('#casesOverview').html("<h4>No cases created yet</h4>");
			}else
					$('#casesOverview').html("<h4>No cases created yet</h4>");
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
										"<label><span>Is active</span>"+
											"<input type='checkbox' class='active' name='active'";
													if (val.Active === 't')
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
				$("input[name=active]").change(function()
				{
					loader(1,"updating");
					var $user = $(this).parents("div").get(1).id;
					var $box = $(this);
					$box.siblings().text("Is active");
					$.post('logic/php/connectDB.php', { action: "updateUser", passKey: $.cookie("ssaP"), ruser: $user, field: "active", val: this.checked }, function(data)
					{
						if (data && data.success === true)
						{
							$box.siblings().text("Is active - updated");
						}	
						else
						{
							error(JSON.stringify(data.errors));
						}
						loader(0);
					}, 'json').fail(function(data)
					{
						if (data.errors)
							error(JSON.stringify(data.errors));
						else
							error(JSON.stringify(data));
						loader(0);
					});
				});	
				$(".clearpass").click(function()
				{
					var $but = $(this);
					$but.html("Clear Password");
					var $user = $(this).parent().get(0).id;
					var $password = (CryptoJS.SHA256("idaqfrss"+Date.now())+"").substr(5, 6);
					var $ida = (CryptoJS.SHA256("ida"+$password+$user)).toString();
					$.post('logic/php/connectDB.php', { action: "updateUser", passKey: $.cookie("ssaP"), ruser: $user, field: "password", val: $ida }, function(data)
					{
						if (data && data.success === true)
						{
							$but.html("Clear Password - <strong>Cleared</strong>");
							error($user+" password is: "+$password+"\nCan change once logged in.");
						}	
						else
						{
							error(JSON.stringify(data.errors));
						}	
						loader(0);					
					}, 'json').fail(function(data)
					{
						if (data.errors)
							error(JSON.stringify(data.errors));
						else
							error(JSON.stringify(data));
						loader(0);
					});
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

	popImage = function(img, d1,d2,d3,d4)
	{
		$("#d1").html(d1);
		$("#d2").html(d2);
		$("#d3").html(d3);
		$("#d4").html(d4);
		$("#facepreview").attr('src',$server+"geti.cgi?image="+img);
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
					$tmpimg = document.createElement('img');
					$img = document.getElementById('capturefacepreview');
					$tmpimg.src = e.target.result;
					$img.src = resize_image($tmpimg);
				};
				reader.readAsDataURL(input.files[0]);
			} else return -1;
		}
	};
	
	//The img element eg. document.elementById('pic');
	function resize_image(img)
	{	
		if (!!document.createElement('canvas').getContext)
		{	
			canvas = document.createElement('canvas');
			var ctx = canvas.getContext("2d");
			ctx.drawImage(img, 0, 0);
			
			var MAX_WIDTH = 720;
			var MAX_HEIGHT = 1280;
			var width = img.width;
			var height = img.height;
			var flag = false;
			if (width > height)
			{
				if (width > MAX_WIDTH)
				{
					flag = true;
					height *= MAX_WIDTH / width;
					width = MAX_WIDTH;
				}
			} 
			else
			if (height > MAX_HEIGHT)
			{
				flag = true;
				width *= MAX_HEIGHT / height;
				height = MAX_HEIGHT;
			}
			if (flag)
			{
				canvas.width = width;
				canvas.height = height;
				var ctx = canvas.getContext("2d");
				ctx.drawImage(img, 0, 0, width, height);

				var dataurl = canvas.toDataURL("image/jpeg");
				return dataurl;
			}					
		}				
		return img.src;
	}

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
