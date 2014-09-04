<?php
//Simple Gets
	function getImage($imageID)
	{
		//return image
		$sql = "SELECT * FROM images WHERE id='".$imageID."';";
		
		
		if ($results1 = mysql_query($sql))
		{
			if (mysql_num_rows($results1) == 1)
			{				
				$row1 = mysql_fetch_array($results1);
				$img = User($row1);	
				return json_encode($img);
			}
			
		}
		
		
	}
	
	function getUser($userID)
	{
		//return user obj
		$sql = "SELECT * FROM users WHERE id='".$userID."';";
		
		
		if ($results1 = mysql_query($sql))
		{
			if (mysql_num_rows($results1) == 1)
			{				
				$row1 = mysql_fetch_array($results1);
				$user = User($row1);	
				return json_encode($user);
			}
			
		}
		
		
	}
	
	function getCase($caseID)
	{
		//return case obj
		
		$sql = "SELECT * FROM cases WHERE id='".$caseID."';";
		
		
		if ($results1 = mysql_query($sql))
		{
			if (mysql_num_rows($results1) == 1)
			{				
				$row1 = mysql_fetch_array($results1);
				$case = Case($row1);	
				return json_encode($case);
			}
			
		}
	}
	
	function getAllCases()
	{
		//return cases[] of case
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
				return $cases;
			}
		}		
	}

    //GETS
	function getResults($caseID, $fromIndex = 0)
	{
		//(limit 10)
		
		$sql1 = "SELECT * FROM caseResults WHERE case_id='".$caseID."';";
		
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
		}	
		
	}
	
	function updateUser($UserID, $FIELD, $VALUE)
	{
		//update field to value
		
		$sql = "UPDATE users
				SET '".$field."' = '".$value."'
				WHERE id = '".$userid."';";			
			if (mysql_query($sql))
			{
				return 1;
			}
			else
			{
				if ($debug = 1)
					echo mysql_error();
				return -120;	
			}
	}
	
	
	function validateUser($username, $password)
	{
		//return userid if isActive else -1
		$sql = "SELECT * FROM users WHERE userName='".$username."' AND password='".$password."'";
				
			if ($results = mysql_query($sql))
			{
				$row = mysql_fetch_array($results);
				
				if($row['active'] == 'true')
				{
					return $row['id'];
				}
				else
				return -1;
			}
			else
			{
				return -1;	
			}
		
		
	}
	
	//function openCase($userid, $imagepath, $name, $surname, $age, $gender, $description, $subName, )
	
	function openCase($userid, $imageid, $status, $progress, $description)
	{
			$sql = "INSERT INTO cases
				VALUES ('".$description"' , '".$imageid"',  '".$status"',  '".$progress"' , '".$userid"' ); '";
				
			if ($results = mysql_query($sql))
			{
				$row = mysql_fetch_array($results);
				return $row['id'];
			}
			else
			{
				if ($debug = 1)
					echo mysql_error();
				return -110;	
			}
		
	}
	
	function register($username, $password)
	{
		$sql = "INSERT INTO users
				VALUES ('".$username."',  '".$password."')";
			if ($results = mysql_query($sql))
			{
				$row = mysql_fetch_array($results);
				return $row['ID'];
			}
			else
			{
				if ($debug = 1)
					echo mysql_error();
				return -110;	
			}
	}
	

?>