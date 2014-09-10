<?php

require("connectDB.php");
require("classes.php");

	/*function connect()
	{
		define("DBNAME","facialrec");
		define("DBHOST","localhost");
		define("DBPORT","5432");
		define("DBUSERNAME","postgres");
		define("DBPASSWORD","data");
		define("DEV","true");
		define("CGIPATH","http://localhost/cgi-bin/");
		$pgconn = null;
	
		try
		{
			echo "start\n";
			$conn_string = "host=".DBHOST." port=".DBPORT." dbname=".DBNAME." user=".DBUSERNAME." password=".DBPASSWORD." connect_timeout=5";
			$pgconn = pg_connect($conn_string) or die('connection failed');
			echo pg_options(pg_host($pgconn));
			echo "end\n";
			pg_close($pgconn);
		} 
		catch (Exception $e)
		{
		    echo 'CONNECTDB - Caught exception: ',  $e->getMessage(), "\n";
		    pg_close($pgconn);
		    $pgconn = null;
		}
	}*/
	
	function validateUser($username, $password)
	{
		$errors = array();  	// array to hold validation errors
		$data 	= array(); 	// array to pass back data
	
		if (empty($username))
			$errors['username'] = 'username is required.';

		if (empty($password))
			$errors['password'] = 'password is required.';
			
		if (!empty($errors)) {
		$data['success'] = false;
		$data['errors']  = $errors;
		} 
		else 
		{
			
			$sql = "SELECT * FROM users WHERE userName='".$username."' AND password='".$password."' AND active=true;";
			
			if (mysql_num_rows($results1) == 1)
			{				
				$row1 = mysql_fetch_array($results1);
				$user = User($row1);	
				return json_encode($user); //return userObj if isActive else -1
			}
			else
			{
				$errors['active'] = 'username & password is invalid or user is inactive.';	
			}
			
			$data['success'] = true;
			$data['message'] = 'Success!';
			
		}
		echo json_encode($data); // return all our data to an AJAX call
	}
	
	function getImage($imageID)
	{
		$errors = array();  	
		$data 	= array(); 	
		
		if (empty($imageID))
		$errors['imageID'] = 'ImageID is required.';
		
		if (!empty($errors)) {
		$data['success'] = false;
		$data['errors']  = $errors;
		} 
		else
		{
			$sql = "SELECT * FROM images WHERE id='".$imageID."';";
			if ($results1 = mysql_query($sql))
			{
				if (mysql_num_rows($results1) == 1)
				{				
					$row1 = mysql_fetch_array($results1);
					$img = User($row1);	
					return json_encode($img); //return image obj
				}
				
			}
			$data['success'] = true;
			$data['message'] = 'Success!';
		}
		echo json_encode($data); 		
	}
	
	function getCase($caseID)
	{
		$errors = array();  	
		$data 	= array(); 
		
		if (empty($caseID))
		$errors['caseID'] = 'caseID is required.';
		
		
		if (!empty($errors)) {
		$data['success'] = false;
		$data['errors']  = $errors;
		} 
		else
		{
			$sql = "SELECT * FROM cases WHERE id='".$caseID."';";
				
			if ($results1 = mysql_query($sql))
			{
				if (mysql_num_rows($results1) == 1)
				{				
					$row1 = mysql_fetch_array($results1);
					$case = Case($row1);	
					return json_encode($case); //return case obj
				}
				
			}
			$data['success'] = true;
			$data['message'] = 'Success!';
		}
		echo json_encode($data); 
	}
	
	function getAllCases()
	{
		
		$sql1 = "SELECT * FROM cases;";
		
		if ($results1 = mysql_query($sql1))
		{
			if (mysql_num_rows($results1) > 0)
			{
				$cases = [];
				while ($row1 = mysql_fetch_array($results1))
				{
					$tmp = case($row1);
					$cases[] = $tmp;
				}
				return $cases; //return cases[] of case
			}
		}		
	}

    //GETS
	function getResults($caseID, $fromIndex = 0)
	{
		$errors = array();  	
		$data 	= array(); 
		
		if (empty($caseID))
		$errors['caseID'] = 'caseID is required.';
		
		if (!empty($errors)) {
		$data['success'] = false;
		$data['errors']  = $errors;
		} 
		else
		{
			$sql1 = "SELECT * FROM caseresults WHERE case_id='".$caseID."';";
			
			if ($results1 = mysql_query($sql1))
			{
				if (mysql_num_rows($results1) > 0)
				{
					$results = [];
					while ($row1 = mysql_fetch_array($results1) && $fromIndex < 10)
					{
						$tmp = Result($row1);
						$results[] = $tmp;
						$fromIndex++;
					}
					return $results;
				}
			$data['success'] = true;
			$data['message'] = 'Success!';
			}	
		}
		echo json_encode($data); 
	}
	
	function updateUser($username, $FIELD, $VALUE)
	{
		$errors = array();  	
		$data 	= array(); 
		
		if (empty($username))
		$errors['username'] = 'username is required.';
		 if (empty($FIELD))
		$errors['FIELD'] = 'FIELD is required.';
		 if (empty($caseID))
		$errors['VALUE'] = 'VALUE is required.';
		
		if (!empty($errors)) {
		$data['success'] = false;
		$data['errors']  = $errors;
		} 
		else
		{
			$sql = "UPDATE users
				SET '".$field."' = '".$value."'
				WHERE id = '".$userid."';";			
			if (mysql_query($sql))
			{
				echo "updated";
			}
			else
			{
				if ($debug = 1)
					echo mysql_error();
					
			}
			$data['success'] = true;
			$data['message'] = 'Success!';
		}
		echo json_encode($data); 
	}
	

	function openCase($description, $subName, $subSurname, $subGender, $subAge, $imageid, $status, $progress, $username, $numResults)
	{
		$errors = array();  	
		$data 	= array(); 
		
			if (empty($description))
			$errors['description'] = 'description is required.';
			 if (empty($subName))
			$errors['subName'] = 'subName is required.';
			 if (empty($subSurname))
			$errors['subSurname'] = 'subSurname is required.';
			 if (empty($subGender))
			$errors['subGender'] = 'subGender is required.';
			 if (empty($subAge))
			$errors['subAge'] = 'subAge is required.';
			 if (empty($imageid))
			$errors['imageid'] = 'imageid is required.';
			 if (empty($status))
			$errors['status'] = 'status is required.';
			 if (empty($progress))
			$errors['progress'] = 'progress is required.';
			 if (empty($username))
			$errors['username'] = 'username is required.';
			 if (empty($numResults))
			$errors['numResults'] = 'numResults is required.';
			
			
			if (!empty($errors)) {
			$data['success'] = false;
			$data['errors']  = $errors;
			} 
			else
			{
				$sql = "INSERT INTO cases
					VALUES ('".$description"','".$subName"','".$subSurname"','".$subGender"','".$subAge"','".$imageid"','".$status"','".$progress"','".$username"','".$numResults"'); '";
					
				if ($results = mysql_query($sql))
				{
					$row = mysql_fetch_array($results);
					return $row['id'];
				}
				else
				{
					if ($debug = 1)
					echo mysql_error();
				}
				$data['success'] = true;
				$data['message'] = 'Success!';
			}
			echo json_encode($data); 
		
	}
	
	function register($username, $password, $isActive, $userIP)
	{
		$errors = array();  	
		$data 	= array(); 
		
		if (empty($username))
		$errors['username'] = 'username is required.';
		 if (empty($password))
		$errors['password'] = 'password is required.';
		 if (empty($isActive))
		$errors['isActive'] = 'isActive is required.';
		 if (empty($userIP))
		$errors['userIP'] = 'userIP is required.';
		
		
		if (!empty($errors)) {
			$data['success'] = false;
			$data['errors']  = $errors;
		} 
		else
		{
			$sql = "INSERT INTO users
				VALUES ('".$username."',  '".$password."' , '".$isActive."',  '".$userIP."')";
				if ($results = mysql_query($sql))
				{
					$row = mysql_fetch_array($results);
					return $row['username'];
				}
				else
				{
					if ($debug = 1)
						echo mysql_error();
				}
				$data['success'] = true;
				$data['message'] = 'Success!';
		}
		echo json_encode($data); 
	}
	
	function uploadImage()
	{
		$allowedExts = array("gif", "jpeg", "jpg", "png");
		$temp = explode(".", $_FILES["file"]["name"]);
		$extension = end($temp);
		if ((($_FILES["file"]["type"] == "image/gif")
			|| ($_FILES["file"]["type"] == "image/jpeg")
			|| ($_FILES["file"]["type"] == "image/jpg")
			|| ($_FILES["file"]["type"] == "image/png"))
			&& ($_FILES["file"]["size"] <= 5000000)
			&& in_array($extension, $allowedExts))
		{
			if ($_FILES["file"]["error"] > 0)
			{
				if ($debug = 1)
					echo "Error Code: " . $_FILES["file"]["error"] ;
				return -1;
			}
			else
			{
				$TIMESTAMP = date_timestamp_get();
				$fileName = $TIMESTAMP.".".$extension;
				if (!(file_exists("/" . $fileName)))
				{
					move_uploaded_file($_FILES["file"]["tmp_name"], "caseImages/" . $fileName);
					
					
					return $fileName;
					$sql = "INSERT INTO images
					VALUES ('".$fileName."',  '".$TIMESTAMP."'')";
					if ($results = mysql_query($sql))
					{
						$row = mysql_fetch_array($results);
						return $row['username'];
					}
					else
					{
						if ($debug = 1)
							echo mysql_error();
						return -110;	
					}	
				}
			}
		}
		else
		{
			if ($debug = 1)
				echo "Invalid file, max-size: 5mb";
			return -1;
		}
	}
	
	

?>