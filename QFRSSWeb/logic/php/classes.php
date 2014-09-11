<?php
    echo "classes.php";
	//Classes
	class XCase {
		public $ID = "";
		public $UserID = "";
		public $Image = "";
		public $sub_Name = "";
		public $sub_Surname = "";
		public $sub_Gender = "";
		public $sub_Age = "";
		public $Description = "";
		public $StatusCode = "";
		public $StatusInfo = "";
		public $NumberOfResults = "";

		public function printX() 
		{
			echo "<h5>Case details</h5>";
			echo "<p>ID: <strong>".$this->ID."</strong></p>";
			echo "<p>UserID: <strong>".$this->UserID."</strong></p>";
			echo "<p>Image: <strong>".$this->Image."</strong></p>";
			echo "<p>sub_Name: <strong>".$this->sub_Name."</strong></p>";
			echo "<p>sub_Surname: <strong>".$this->sub_Surname."</strong></p>";
			echo "<p>sub_Gender: <strong>".$this->sub_Gender."</strong></p>";
			echo "<p>sub_Age: <strong>".$this->sub_Age."</strong></p>";
			echo "<p>Description: <strong>".$this->Description."</strong></p>";
			echo "<p>StatusCode: <strong>".$this->StatusCode."</strong></p>";
			echo "<p>StatusInfo: <strong>".$this->StatusInfo."</strong></p>";
			echo "<p>NumberOfResults: <strong>".$this->NumberOfResults."</strong></p>";
		}
	}	

	class Image {
		public $ID = "";
		public $Filename = "";
		public $TimeStamp = "";
		public $Location = "";
		//public $Meta = "";
	}
	
	class User {
		public $ID = "";
		public $Username = "";
		public $UserIP = "";//Only for server side auth.
		public $Active = "";//May user access site
	}
	
	class Result {
		public $ID = "";//ROWID Within the table
		public $ImageCode = "";
		public $Image = "";
		public $Match = "";
	}
    
	//Sql row functions
	function xcase($row)
	{
		$tmp = new XCase;
		if ($row != null)
		{
			$tmp->ID = $row['id'];
			$tmp->UserID = $row['user_id'];
			$tmp->Image = getImage($row['image_id']);
			$tmp->sub_Name = $row['subName'];
			$tmp->sub_Surname = $row['subSurname'];
			$tmp->sub_Gender = $row['subGender'];
			$tmp->sub_Age = $row['subAge'];
			$tmp->Description = $row['description'];
			$tmp->StatusCode = $row['status'];
			$tmp->StatusInfo = $row['progress'];
			$tmp->NumberOfResults = $row['numResults'];
		}
		else
		{
			$tmp->ID = "test";
			$tmp->UserID = "test";
			$tmp->Image = "test";
			$tmp->sub_Name = "test";
			$tmp->sub_Surname = "test";
			$tmp->sub_Gender = "test";
			$tmp->sub_Age = "test";
			$tmp->Description = "test";
			$tmp->StatusCode = "test";
			$tmp->StatusInfo = "test";
			$tmp->NumberOfResults = "test";
		}
		return $tmp;
	}

	function image($row)
	{
		$tmp->ID = $row['id '];
		$tmp->Filename = $row['filename'];
		$tmp->TimeStamp = $row['timestamp'];
		$tmp->Location = $row['location'];
		//public $Meta = "";
	}
	
	function user($row)
	{
		$tmp = new User();
		if ($row != null)
		{
			$tmp->ID = $row['id'];
			$tmp->Username = $row['userName'];		
			$tmp->Active = $row['active'];
		}
		return $tmp;
	}

	function result($row)
	{
		$tmp = new Result();
		if ($row != null)
		{
			$tmp->ID = $row['id'];
			$tmp->ImageCode = $row['randomIdentifier'];
			$tmp->Image = getImage($row['image_id']);
			$tmp->Match = $row['percentageMatch'];
		}
		return $tmp;
	}

	function getImage($imageID)
	{
		echo $imageID;
		return new Image();
	}
?>