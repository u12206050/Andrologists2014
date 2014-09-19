<?php
	function validateUser($username, $password)
	{
		$conn = connect(); if ($conn == null) return null;		
		//echo "Connection is: ".pg_connection_reset($conn);
		$username = trim(pg_escape_string($conn,$username));
		$password = trim(pg_escape_string($conn,$password));
		//echo $password;
		$errors = array();  	// array to hold validation errors
		$data 	= array(); 	// array to pass back data
	
		if (empty($username))
			$errors['username'] = 'username is required.';

		if (empty($password))
			$errors['password'] = 'password is required.';
			
		if (!empty($errors)){
		$data['success'] = false;
		$data['errors']  = $errors;
		} 
		else 
		{
			try
			{		
				$query = "SELECT * FROM users WHERE userName='{$username}' AND password=crypt('{$password}', '2a068uKrXaZiFsbdet62kkZSSOida') AND active=true;";								
				$sql = pg_query($conn, $query);
				//echo $query;	
				if (pg_num_rows($sql) == 1)
				{			
					$row = pg_fetch_array($sql);	
					$user = User($row);	
					$data['success'] = true;
					$data['message'] = $user; //return userObj if isActive else -1
				}
				else
				{
					$data['success'] = false;
					$errors['Reason'] = "Invalid username and/or password entered";	
				}
			}
			catch (Exception $e)
			{
				$data['success'] = false;
				$errors['Failed in'] = "validateUser: ".$e->getMessage()."\n";
				$errors['SQL error'] = pg_last_error($conn);
			}
		}
		$data['errors']  = $errors;	
		disconnect();
		return $data; // return all our data to an AJAX call
	}

	function getUsers()
	{
		$conn = connect(); if ($conn == null) return null;	
		$data = array(); 
		$data['success'] = false;
		if ($_SESSION['admin'] == true)
		{				
			try
			{		
				$query = "SELECT * FROM users WHERE username <> 'admin';";								
				$sql = pg_query($conn, $query);
				//echo $query;	
				if (pg_num_rows($sql) > 0)
				{		
					$users = array();
					while ($row = pg_fetch_array($sql))
					{
						$tmp = User($row);
						$users[] = $tmp;
					}	
					$data['success'] = true;
					$data['message'] = $users; //return userObj if isActive else -1
				}
				else
				{
					$data['success'] = false;
					$errors['errors'] = "No users exist";	
				}
			}
			catch (Exception $e)
			{
				$data['success'] = false;
				$errors['Failed in'] = "getUsers: ".$e->getMessage()."\n";
				$errors['SQL error'] = pg_last_error($conn);
			}
		}
		else
			$errors = "You are not an administrator";
		$data['errors']  = $errors;	
		disconnect();
		return $data; // return all our data to an AJAX call
	}
	
	function getImage($imageID, $b)
	{
		$conn = connect(); if ($conn == null) return null;
		$imageID = trim(pg_escape_string($imageID));
		$img = Image(null);
		if (empty($imageID))
			return $img;
		
		if ($b == "1")
				$sql = pg_query($conn, "SELECT * FROM images WHERE id='{$imageID}'");
			else
				$sql = pg_query($conn, "SELECT id, timedate, location FROM images WHERE id='{$imageID}'");
		
		if ($sql)
		{
			if ($results = pg_fetch_array($sql))
			{				
				$img = Image($results); 			
			}
		}
		disconnect();
		return $img;		
	}
	
	function getCase($caseID, $progress)
	{
		$conn = connect(); if ($conn == null) return null;
		$caseID = trim(pg_escape_string($caseID));
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
			if ($progress == "1")
				$sql = pg_query($conn, "SELECT status, progress, num_results  FROM cases WHERE id='{$caseID}';");
			else
				$sql = pg_query($conn, "SELECT * FROM cases WHERE id='{$caseID}';");
			
			if ($results = pg_fetch_array($sql)==1)
			{				
				$case = Cases($results);	
				$data['success'] = true;
				$data['message'] = $case; 
			}
			else
			{
				$data['success'] = false;
				$errors['Failed in'] = "SQL Failed in getCase";
				$errors['SQL error'] = pg_last_error($conn);
				$data['errors']  = $errors;
			}
		}
		disconnect();
		return $data; 
	}
	
	function getAllCases($userName)
	{		
		$userName = trim(pg_escape_string($userName));
		$errors = array();  	
		$data 	= array(); 
		$conn = connect(); if ($conn == null) $errors['SQL error'] = "Connection to database failed";
		if (empty($userName))
		$errors['userName'] = 'userName is required.';
		
		$data['success'] = false;
		if (empty($errors)) 
		{
			$sql = pg_query($conn, "SELECT * FROM cases WHERE username='{$userName}';");		
			if ($sql)
			{
				if (pg_num_rows($sql) > 0)
				{
					$casesarr = array();  
					while ($row = pg_fetch_array($sql))
					{
						$tmp = Cases($row);
						//$tmp->printX();
						$casesarr[] = $tmp;
					}
					$data['success'] = true;
					$data['message'] = $casesarr; 
				}
				else
				{
					$data['success'] = false;
					$errors['message'] = "No cases";
				}
			}
			else			
			{
				$data['success'] = false;
				$errors['Failed in'] = "SQL Failed in getAllCases";
				$errors['SQL error'] = pg_last_error($conn);				
			}
		}
		$data['errors']  = $errors;
		disconnect();
		return $data; 	
	}

	function getResults($caseID, $fromIndex)
	{
		$conn = connect(); if ($conn == null) return null;
		$caseID = trim(pg_escape_string($caseID));
		$fromIndex = trim(pg_escape_string($fromIndex));
		
		$errors = array();  	
		$data 	= array(); 
		
		
		if (empty($caseID))
		$errors['caseID'] = 'caseID is required.';
		
		$data['success'] = false;
		if (empty($errors))
		{
			$sql = pg_query($conn, "SELECT * FROM case_results WHERE case_id='{$caseID}' AND id >= '{$fromIndex}' LIMIT 10;");
			if ($sql)
			{	
				if (pg_num_rows($sql) > 0)
				{
					$results = array();
					while ($row = pg_fetch_array($sql))
					{
						$tmp = Result($row);
						$results[] = $tmp;
					}
					$data['success'] = true;
					$data['message'] = $results; 
				}
				else
				{
					$data['success'] = false;
					$errors['Failed in'] = "SQL Failed in getResults";
					$errors['SQL error'] = pg_last_error($conn);
				}
			}
			else			
			{
				$data['success'] = false;
				$errors['Failed in'] = "SQL Failed in getAllCases";
				$errors['SQL error'] = pg_last_error($conn);				
			}
				
		}
		$data['errors']  = $errors;
		disconnect();
		return $data; 
	}
	
	function updateUser($username, $FIELD, $VALUE)
	{
		$conn = connect(); if ($conn == null) return null;
		$userName = trim(pg_escape_string($userName));
		$FIELD = trim(pg_escape_string($FIELD));
		$VALUE = trim(pg_escape_string($VALUE));
		
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
			if ($FIELD == "password")
				$sql = pg_query($conn, "UPDATE users
										SET password = crypt('{$VALUE}', '2a068uKrXaZiFsbdet62kkZSSOida')
										WHERE username = '{$username}';");
			else
				$sql = pg_query($conn, "UPDATE users
										SET {$FIELD} = '{$VALUE}'
										WHERE username = '{$username}';");	
				
			if ($sql)
			{
				$data['success'] = true;
				$data['message'] = "{$username} has been updated";
			}
			else
			{
				$data['success'] = false;
				$errors['Failed in'] = "SQL Failed in updateUser";
				$errors['SQL error'] = pg_last_error($conn);
				$data['errors']  = $errors;
			}
		}
		disconnect();
		return $data; 
	}
	

	function createCase($description, $subName, $subSurname, $subGender, $subAge, $imageid, $status, $progress, $username, $numResults)
	{
		$conn = connect(); if ($conn == null) return null;
		$description = trim(pg_escape_string($description));
		$subName = trim(pg_escape_string($subName));
		$subSurname = trim(pg_escape_string($subSurname));
		$subGender = trim(pg_escape_string($subGender));
		$subAge = trim(pg_escape_string($subAge));
		$imageid = trim(pg_escape_string($imageid));
		$status = trim(pg_escape_string($status));
		$username = trim(pg_escape_string($username));
		$progress = 1;
		$numResults = 0;
		
		$errors = array();  	
		$data 	= array(); 
		
			if (empty($description))
				$description = "None";
			 if (empty($subName))
			$errors['subName'] = 'subName is required.';
			 if (empty($subSurname))
			$errors['subSurname'] = 'subSurname is required.';
			 if (empty($subGender))
			$errors['subGender'] = 'subGender is required.';
			 if (empty($subAge))
			$errors['subAge'] = 'subAge is required.';
			 if (empty($imageid))
			$errors['imageid'] = 'picture is required.';
			 if (empty($status))
			$errors['status'] = 'status is required.';
			 if (empty($username))
			$errors['username'] = 'username is required.';			
			
			if (!empty($errors)) {
			$data['success'] = false;
			$data['errors']  = $errors;
			} 
			else
			{
				$query = "INSERT INTO cases (description,sub_name,sub_surname,sub_gender,sub_age,image_id,status,progress,username,num_results)
					VALUES ('{$description}','{$subName}','{$subSurname}','{$subGender}',{$subAge},{$imageid},'{$status}','{$progress}','{$username}',{$numResults}) RETURNING id";
				//echo $query;
				$sql = pg_query($conn,$query);
				
	
				if ($sql)
				{
					$data['success'] = true;
					$row = pg_fetch_array($sql);
					$data['message'] = $row['0'];
				}
				else
				{
					$data['success'] = false;
					$errors['Failed in'] = "SQL Failed in openCase";
					$errors['SQL error'] = pg_last_error($conn);
					$data['errors']  = $errors;
				}
			}
			disconnect();
			return $data; 
		
	}
	
	function register($username, $password, $isActive)
	{
		$conn = connect(); if ($conn == null) return null;
		
		$username = trim(pg_escape_string($username));
		$password = trim(pg_escape_string($password));
		$isActive = trim(pg_escape_string($isActive));
		
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
				VALUES ('{$username}',  crypt('{$password}', '2a068uKrXaZiFsbdet62kkZSSOida') , '{$isActive}')");
				
				if ($sql)
				{
					$data['success'] = true;
					$data['message'] = "{$username} has been created";
				}
				else
				{
					$data['success'] = false;
					$errors['Failed in'] = "SQL Failed in register";
					$errors['SQL error'] = pg_last_error($conn);
					$data['errors']  = $errors;
				}				
		}
		disconnect();
		return $data; 
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
				if (DEV)
					echo "Error Code: " . $_FILES["file"]["error"] ;
			}
			else
			{
				$timestamp = microtime(get_as_float);
				$fileName = uniqid().".".$extension;
				if (!(file_exists("/" . $fileName)))
				{
					move_uploaded_file($_FILES["file"]["tmp_name"], UPLOAD_DIR . $fileName);
					return insertImage($fileName);				
				}
			}
		}
		return -1;
	}

	function saveImage($base64img)
	{	    
		$timestamp = microtime(get_as_float);
		//echo date("D/M/Y H:i:s.u" , $date);
	    $base64img = str_replace('data:image/jpeg;base64,', '', $base64img);
	    $data = base64_decode($base64img);
	    $filename = uniqid() . '.jpg';
	    //echo "FILENAME: ".$filename;
	    $file = UPLOAD_DIR . $filename;
	    file_put_contents($file, $data);
	    return insertImage($filename, $timestamp);
	}

	function insertImage($filename, $timestamp)
	{
		$conn = connect(); if ($conn == null) return null;
		$sql =  pg_query($conn,"INSERT INTO images (filename, timedate) VALUES ('{$filename}', {$timestamp}) RETURNING id");
		if ($sql)
		{
			$row = pg_fetch_array($sql);
			$imageID = $row['0'];
			disconnect();
			return $imageID;
		}
		else
		{
			echo pg_last_error($conn);
		}
		disconnect();
		return -1;
	}
?>
