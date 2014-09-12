<?php
	if (isset($_REQUEST["action"]))
	{
		if ($_REQUEST["action"] == "logout")
		{
			logout();
		}
		require("classes.php");
		require("dataIO.php");


		if ($_POST["action"] == "login")
		{
			$username = $_POST["user"];
			$password = $_POST["pass"];
			$data = validateUser($username, $password);
			if ($data.success = true)
			{
				$_SESSION[user] = $data.message;
				$data = getAllCases($username);
			}
			return $data;
		} 
		else
		if ($_POST["action"] == "register")
		{
			$username = $_POST["user"];
			$password = $_POST["pass"];
			$isActive = 'true';
			$data = register($username, $password, $isActive);
			return $data;
		} 
		else
		if ($_POST["action"] == "refresh") //getCase
		{
			$caseId = $_POST["caseID"];
			$progress = 1;
			$data = getCase($caseID, $progress);
			return $data;
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
		
			return $data;
		} 
		else
		if ($_POST["action"] == "getResults")
		{
			$caseID = $_POST["caseID"];
			$fromIndex = $_POST["LastIndex"];
			
			$data = getResults($caseID, $fromIndex);
			
			return $data;
		} 
		else
		if ($_POST["action"] == "getCases")
		{
			$username = $_POST["user"];
			
			$data = getAllCases($userName);
			return $data;
		}
		
		//uploadImage & updateUser
		
	}

?>