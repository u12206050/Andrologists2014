function readURL(input)
{
	if (input.files && input.files[0])
	{
		var reader = new FileReader();
		reader.onload = function (e)
		{
			$('#facepreview').attr('src', e.target.result);
		}
		reader.readAsDataURL(input.files[0]);
	}
}



$(document).ready(function(){  
	$("#facepic").change(function(){
		readURL(this);
	});
	
		var $username = $('#user'), $password = $('#pass'), $lvl = $('#rights'), $code = $('#uCode');
	$("#btnlogin").click(function(){
		$.ajax({                                      
		    type: 'post',
		    url: 'logic/connectDB.php',                  
		    data: {action:'login',userid:$code.val()},                                       
		    dataType: 'html',  
			error: function(out)
			{
				alert(out);
			},			    
		    success: function(out)
		    {     	    
			if (out < 1)
			{
				alert('Unique code is incorrect');    
			}
			else
			{					
				$.mobile.navigate("#editor");
				openAsset();
			}
		    } 			    
		});
	});
	
	
	$("#btnregister").click(function(){
		if (checkInput(1) == 1)
		{			
			$.ajax({                                      
			    type: 'post',
			    url: 'logic/connectDB.php',                  
			    data: {action:'register',user:$username.val(),pass:$password.val(),lvl:$lvl.val()},                                       
			    dataType: 'html',  
				error: function(out)
				{
					alert(out);
				},
			    success: function(out)
			    {     				    
				if (out < 1)
				{
					alert('Sorry, you could not be registered');    
				}
				else
				{		
					alert('Your unique code is: ' + out);	
					$code.val(out);
					$.mobile.navigate( "#editor" );
					openAsset();
				}
			    } 
			});
		}
	});
	
	$("#btnOpen").click(function(){openAsset();});
	$("#btnSave").click(function(){saveAsset();});
	function openAsset()
	{		
		$.ajax({                                      
			type: 'post',
			url: 'logic/connectDB.php',                  
			data: {action:'read',userid:$code.val()},                                       
			dataType: 'text',                     
			success: function(out)
			{     
				if(checkData(out) == 1)
				{
					$("#textedt").val(out);
				} 
				else	
				{		
					$("#textedt").val("The Editor");	
					$.mobile.navigate("#login");
				}
			} 
		});
	}
	
	function saveAsset()
	{
		$.ajax({                                      
			type: 'post',
			url: 'logic/connectDB.php',                  
			data: {action:'write',contents:$("#textedt").val(),userid:$code.val()},  
			dataType: 'text',                     
			success: function(out)
			{     
				if(checkData(out) == 1)
				{
				    alert('saved');
				} 
			} 
		});
	}
	
	function checkData($data)
	{
		if ($data == "0")
			alert('Please login to view');
		else if ($data == "-1")
			alert("You don't have the appropriate rights");
		else
			return 1;
	}
	
	function checkInput($level)
	{
		var $username = $('#user'), $password = $('#pass');
		if ($username.val() == '') {
			alert('Please enter username');
			$username.focus();
		} else if($password.val() == '') {
			alert('Please enter password');
			$password.focus();
		} else {
			if ($level == 1)
				if($('#rights').val() == '' || $('#rights').val() == 'Choose asset rights') {
					alert('Please select an asset right');
					$('#rights').focus();
					return false;
				}
			return true;
		}
		
		return false;
	}
	
});