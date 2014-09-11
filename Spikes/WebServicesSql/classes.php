<?php
    //echo "classes.php";
	//Classes
	class Cases {
		public $ID = "";
		public $UserName = "";
		public $Image = "";
		public $sub_Name = "";
		public $sub_Surname = "";
		public $sub_Gender = "";
		public $sub_Age = "";
		public $Description = "";
		public $StatusCode = "";
		public $StatusInfo = "";
		public $NumberOfResults = "";
	}	

	class Image {
		public $ID = "";
		public $Filename = "";
		public $TimeStamp = "";
		public $Location = "";
		//public $Meta = "";
	}
	
	class User {
		//public $ID = "";
		public $Username = "";
		public $UserIP = "";//Only for server side auth.
		public $Active = "";//May user access site
	}
	
	class Result {
		public $ID = "";//ROWID Within the table
		public $ImageCode = "";
		public $CaseID ="";
		public $Image = "";
		public $Match = "";
	}
    
	//Sql row functions
	function Cases($row)
	{
		$tmp = new Cases();
		$tmp->$ID = $row['id'];
		$tmp->$UserID = $row['user_id'];
		$tmp->$Image = getImage($row['image_id']);
		$tmp->$sub_Name = $row['subName'];
		$tmp->$sub_Surname = $row['subSurname'];
		$tmp->$sub_Gender = $row['subGender'];
		$tmp->$sub_Age = $row['subAge'];
		$tmp->$Description = $row['description'];
		$tmp->$StatusCode = $row['status'];
		$tmp->$StatusInfo = $row['progress'];
		$tmp->$NumberOfResults = $row['numResults'];
		return $tmp;
	}
	
	function User($row)
	{
		$tmp = new User();
		$tmp->ID = $row['id'];
		$tmp->Username = $row['userName'];		
		$tmp->Active = $row['active'];
		return $tmp;
	}

	function Result($row)
	{
		$tmp = new Result();
		$tmp->$ID = $row['id'];
		$tmp->$ImageCode = $row['randomIdentifier'];
		$tmp->$Image = getImage($row['image_id']);
		$tmp->$Image = getImage($row['case_id']);
		$tmp->$Match = $row['percentageMatch'];
		return $tmp;
	}
?>