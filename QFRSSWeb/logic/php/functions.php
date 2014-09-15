<?php
	if (isset($_REQUEST["action"]))
	{
		session_start();

		if ($_REQUEST["action"] == "logout")
		{
			session_destroy();
		}
		require("classes.php");
		require("dataIO.php");
		if ($_REQUEST["action"] == "test")
		{
			$conn = connect();
			$stat = pg_connection_status($conn);
			if ($stat === PGSQL_CONNECTION_OK) {
				echo 'Connection status ok';
			} else {
				echo 'Connection status bad';
			} 
			echo pg_connection_reset($conn);
			disconnect();
		}
		else
		if ($_POST["action"] == "login")
		{
			$username = $_POST["user"];
			$password = $_POST["pass"];
			$data = validateUser($username, $password);
			if ($data['success'] == true)
			{
				$_SESSION['username'] = $data['message']->Username;
				$data['passkey'] = md5(substr($password,4,10)+get_client_ip());
				$_SESSION['user'] = $data['passkey'];
				$data['admin'] = false;
				if ($data['message']->Username == "admin")
				{
					$data['admin'] = true;
					$_SESSION['admin'] = true;
				}
			}
			echo json_encode($data);
		} 
		else
		if ($_POST["action"] == "register")
		{
			$username = $_POST["user"];
			$password = $_POST["pass"];
			$isActive = 'true';
			$data = register($username, $password, $isActive);
			echo json_encode($data);
		} 
		else
		if ($_POST["action"] == "refresh") //getCase
		{
			$caseId = $_POST["caseID"];
			$username = $_POST["user"];
			$password = $_POST["pass"];
			$data = array(); 
			if($_SESSION['user']->Username == $username)
			{
				$progress = 1;
				$data = getCase($caseID, $progress);
				echo json_encode($data);
			}
			else 
			{
				$data["success"] = false;
				$data["message"] = "User is not logged in";
			}
			echo json_encode($data);
		} 
		else
		if ($_POST["action"] == "openCase")
		{
			$description = $_POST["desc"];
			$subName = $_POST["fname"];
			$subSurname = $_POST["surname"];
			$subGender = $_POST["gender"];
			$subAge = $_POST["age"];
			$imageid = $_POST["facepic"];
			$status = 'started';
			$progress = 1;
			$username = $_POST["user"];
			$numResults = 0;
			
			$data = openCase($description, $subName, $subSurname, $subGender, $subAge, $imageid, $status, $progress, $username, $numResults);
		
			echo json_encode($data);
		} 
		else
		if ($_POST["action"] == "getResults")
		{
			$passKey = $_POST["passKey"];
			if (isset($_SESSION['user']) && $_SESSION['user'] == $passKey &&isset($_POST['LastIndex']) && isset($_POST['caseID']))
			{
				$fromIndex = $_POST["LastIndex"];
				$caseID = $_POST["caseID"];			
				$data = getResults($caseID, $fromIndex);
				if ($data['success'] == false)
				{
					$data["success"] = true;
					$tmp = array(); 
					$tmp[] = Result(null);
					$data["message"] = $tmp;			
				}				
			}
			else
			{
				$data["success"] = false;
				$data["errors"] = "Incorrect arguments supplied, please login";
			}
			echo json_encode($data);
		} 
		else
		if ($_POST["action"] == "getCases")
		{			
			$passKey = $_POST["passKey"];
			if (isset($_SESSION['user']) && $_SESSION['user'] == $passKey)
			{
				$data = getAllCases($_SESSION['username']);
				if ($data['success'] == false)
				{
					$data['success'] = true;
					$tmp = array(); 
					$tmp[] = Cases(null);
					$data['message'] = $tmp; 			
				}				
			}
			else
			{
				$data["success"] = false;
				$data["errors"] = "Incorrect arguments supplied, please login";
			}
			echo json_encode($data);
		}
		else
		if ($_POST["action"] == "getUsers")
		{			
			$passKey = $_POST["passKey"];
			if (isset($_SESSION['user']) && isset($_SESSION['admin']) && $_SESSION['user'] == $passKey && $_SESSION['admin'] == true)
			{
				$data = getUsers();
				if ($data['success'] == false)
				{
					$data['success'] = true;
					$tmp = array(); 
					$tmp[] = User(null);
					$data['message'] = $tmp; 			
				}				
			}
			else
			{
				$data["success"] = false;
				$data["errors"] = "You are not allowed to access this. Admin only.";
			}
			echo json_encode($data);
		}
		
		//uploadImage & updateUser
		
	} else
		echo "No action specified.";

	function get_client_ip()
	{
	    $ipaddress = '';
	    if (getenv('HTTP_CLIENT_IP'))
	        $ipaddress = getenv('HTTP_CLIENT_IP');
	    else if(getenv('HTTP_X_FORWARDED_FOR'))
	        $ipaddress = getenv('HTTP_X_FORWARDED_FOR');
	    else if(getenv('HTTP_X_FORWARDED'))
	        $ipaddress = getenv('HTTP_X_FORWARDED');
	    else if(getenv('HTTP_FORWARDED_FOR'))
	        $ipaddress = getenv('HTTP_FORWARDED_FOR');
	    else if(getenv('HTTP_FORWARDED'))
	       $ipaddress = getenv('HTTP_FORWARDED');
	    else if(getenv('REMOTE_ADDR'))
	        $ipaddress = getenv('REMOTE_ADDR');
	    else
	        $ipaddress = date("l");
	    return $ipaddress;
	}
?>