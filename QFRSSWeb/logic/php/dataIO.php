<?php

require("classes.php");
require("connectDB.php");
	
	function validateUser($username, $password)
	{
		$conn = connect();
		$username = trim(mysql_real_escape_string($username));
		$password = trim(mysql_real_escape_string($password));
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
			$sql = pg_query($conn, "SELECT * FROM users WHERE userName='".$username."' AND password='".$password."' AND active=true;");
			
			if ($results = pg_fetch_row($sql) == 1)
			{				
				$row1 = pg_fetch_row($results1);
				$user = User($row1);	
				$data['success'] = true;
				$data['message'] = $user; //return userObj if isActive else -1
			}
			else
			{
				$data['success'] = false;
				$errors['Failed in'] = "validateUser";
				$errors['SQL error'] = pg_last_error($conn);
				$data['errors'] = 'Success!';				
			}
		}
		disconnect();
		return json_encode($data); // return all our data to an AJAX call
	}
	
	function getImage($imageID, $b)
	{
		$conn = connect();
		$imageID = trim(mysql_real_escape_string($imageID));
		$img = null;
		if (empty($imageID))
			return $img;
		
		if ($b = "1")
				$sql = pg_query($conn, "SELECT * FROM images WHERE id='".$imageID."';");
			else
				$sql = pg_query($conn, "SELECT id, timestamp, Location FROM images WHERE id='".$imageID."';");
		
		
		if ($results = pg_fetch_row($sql)==1)
		{				
			$row1 = pg_fetch_row($results1);
			$img = Image($row1); 			
		}
		disconnect();
		return $img;		
	}
	
	function getCase($caseID, $progress)
	{
		$conn = connect();
		$caseID = trim(mysql_real_escape_string($caseID));
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
			$sql = null;
			if ($progress = "1")
				$sql = pg_query($conn, "SELECT status, progress, numResults  FROM cases WHERE id='".$caseID."';");
			else
				$sql = pg_query($conn, "SELECT * FROM cases WHERE id='".$caseID."';");
			
			if ($results = pg_fetch_row($sql)==1)
			{				
				$row1 = pg_fetch_row($results1);
				$case = Cases($row1);	
				$data['success'] = true;
				$data['message'] = $case; 
			}
			else
			{
				$data['success'] = false;
				$errors['Failed in'] = "SQL Failed in getCase";
				$errors['SQL error'] = pg_last_error($conn);
				$data['errors'] = 'Success!';
			}
		}
		disconnect();
		return json_encode($data); 
	}
	
	function getAllCases($userName)
	{
		$conn = connect();
		$userName = trim(mysql_real_escape_string($userName));
		$errors = array();  	
		$data 	= array(); 
		
		if (empty($userName))
		$errors['userName'] = 'userName is required.';
		
		if (!empty($errors)) {
		$data['success'] = false;
		$data['errors']  = $errors;
		} 
		else
		{
			$sql = pg_query($conn, "SELECT * FROM cases WHERE username='".$userName."';");
			
				
				if (pg_num_rows($sql) > 0)
				{
					$casesarr = array();  
					while ($row1 = pg_fetch_row($results1))
					{
						$tmp = Cases($row1);
						$casesarr[] = $tmp;
					}
					$data['success'] = true;
					$data['message'] = $casearr; 
				}	
				else
				{
					$data['success'] = false;
					$errors['Failed in'] = "SQL Failed in getAllCases";
					$errors['SQL error'] = pg_last_error($conn);
					$data['errors'] = 'Success!';
				}
		}
		disconnect();
		return json_encode($data); 	
	}

	function getResults($caseID, $fromIndex)
	{
		$conn = connect();
		$caseID = trim(mysql_real_escape_string($caseID));
	
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
			$sql = pg_query($conn, "SELECT * FROM caseresults WHERE case_id='".$caseID."' AND id >= '" .$fromIndex."';");
			
			
				if (pg_num_rows($sql) > 0)
				{
					$results = array();
					$start = 0;
					while ($row1 = pg_fetch_row($sql) && $start < 10)
					{
						$tmp = Result($row1);
						$results[] = $tmp;
						$start++;
					}
					$data['success'] = true;
					$data['message'] = $results; 
				}
				else
				{
					$data['success'] = false;
					$errors['Failed in'] = "SQL Failed in getResults";
					$errors['SQL error'] = pg_last_error($conn);
					$data['errors'] = 'Success!';
				}
				
		}
		disconnect();
		return json_encode($data); 
	}
	
	function updateUser($username, $FIELD, $VALUE)
	{
		$conn = connect();
		$userName = trim(mysql_real_escape_string($userName));
		$FIELD = trim(mysql_real_escape_string($FIELD));
		$VALUE = trim(mysql_real_escape_string($VALUE));
		
		$errors = array();  	
		$data 	= array(); 
		
		if (empty($username))
		$errors['username'] = 'username is required.';
		 if (empty($FIELD))
		$errors['FIELD'] = 'FIELD is required.';
		 if (empty($VALUE))
		$errors['VALUE'] = 'VALUE is required.';
		
		if (!empty($errors)) {
		$data['success'] = false;
		$data['errors']  = $errors;
		} 
		else
		{
			
			$sql = pg_query($conn, "UPDATE users
				SET '".$FIELD."' = '".$VALUE."'
				WHERE username = '".$username."';");	
				
			if ($sql)
			{
				$data['success'] = true;
			}
			else
			{
				$data['success'] = false;
				$errors['Failed in'] = "SQL Failed in updateUser";
				$errors['SQL error'] = pg_last_error($conn);
				$data['errors'] = 'Success!';
			}
		}
		disconnect();
		return json_encode($data); 
	}
	

	function openCase($description, $subName, $subSurname, $subGender, $subAge, $imageid, $status, $progress, $username, $numResults)
	{
		$conn = connect();
		$description = trim(mysql_real_escape_string($description));
		$subName = trim(mysql_real_escape_string($subName));
		$subSurname = trim(mysql_real_escape_string($subSurname));
		$subGender = trim(mysql_real_escape_string($subGender));
		$subAge = trim(mysql_real_escape_string($subAge));
		$imageid = trim(mysql_real_escape_string($imageid));
		$status = trim(mysql_real_escape_string($status));
		$progress = trim(mysql_real_escape_string($progress));
		$username = trim(mysql_real_escape_string($username));
		$numResults = trim(mysql_real_escape_string($numResults));
		
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
				 $sql = pg_query($conn,"INSERT INTO cases
					VALUES ('".$description."','".$subName."','".$subSurname."','".$subGender."','".$subAge."','".$imageid."','".$status."','".$progress."','".$username."','".$numResults."'); '");
				
	
				if ($sql)
				{
					$row = pg_fetch_row($sql);
					$data['success'] = true;
					$data['message'] = $row['id'];
				}
				else
				{
					$data['success'] = false;
					$errors['Failed in'] = "SQL Failed in openCase";
					$errors['SQL error'] = pg_last_error($conn);
					$data['errors'] = 'Success!';
				}
			}
			disconnect();
			return json_encode($data); 
		
	}
	
	function register($username, $password, $isActive)
	{
		$conn = connect();
		
		$username = trim(mysql_real_escape_string($username));
		$password = trim(mysql_real_escape_string($password));
		$isActive = trim(mysql_real_escape_string($isActive));
		$userIP = trim(mysql_real_escape_string($userIP));
		
		$errors = array();  	
		$data 	= array(); 
		
		if (empty($username))
		$errors['username'] = 'username is required.';
		 if (empty($password))
		$errors['password'] = 'password is required.';
		 if (empty($isActive))
		$errors['isActive'] = 'isActive is required.';
	
		
		
		if (!empty($errors)) {
			$data['success'] = false;
			$data['errors']  = $errors;
		} 
		else
		{
			 $sql = pg_query($conn,"INSERT INTO users
				VALUES ('".$username."',  '".$password."' , '".$isActive."')");
				
				if ($sql)
				{
					$row = pg_fetch_row($sql);
					$data['success'] = true;
					$data['message'] = $row['username'];
				}
				else
				{
					$data['success'] = false;
					$errors['Failed in'] = "SQL Failed in register";
					$errors['SQL error'] = pg_last_error($conn);
					$data['errors'] = 'Success!';
				}
				
		}
		disconnect();
		return json_encode($data); 
	}
	
	function uploadImage()
	{
		$conn = connect();
		
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
					$sql =  pg_query($conn,"INSERT INTO images
					VALUES ('".$fileName."',  '".$TIMESTAMP."'')");
					
					if ($sql)
					{
						$row = pg_fetch_row($sql);
						$data['success'] = true;
						$data['message'] = $row['username'];
					}
					else
					{
						$data['success'] = false;
						$errors['Failed in'] = "SQL Failed in uploadImage";
						$errors['SQL error'] = pg_last_error($conn);
						$data['errors'] = 'Success!';
					}	
				}
			}
		}
		else
		{
			if ($debug = 1)
			{
				$data['success'] = false;
				$errors['Failed in'] = "SQL Failed in uploadImage: Invalid file, max-size: 5mb";
				$errors['SQL error'] = pg_last_error($conn);
				$data['errors'] = 'Success!';
			}
				
			
		}
		disconnect();
		return json_encode($data);
		
	}
	
	

?>