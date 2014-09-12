<?php
    //echo "classes.php";
	//Classes
	class Cases {
		public $ID = "";
		public $Username = "";
		public $Image = "";
		public $sub_Name = "";
		public $sub_Surname = "";
		public $sub_Gender = "";
		public $sub_Age = "";
		public $Description = "";
		public $StatusCode = "";
		public $StatusInfo = "";
		public $NumberOfResults = "";
		
		function printX()
		{
			echo "<h5>Case details</h5>";
			echo "<h6>ID: <strong>".this->ID."</strong></h6>";
			echo "<h6>UserID: <strong>".this->$Username."</strong></h6>";
			echo "<h6>Image: <strong>".this->Image."</strong></h6>";
			echo "<h6>sub_Name: <strong>".this->sub_Name."</strong></h6>";
			echo "<h6>sub_Surname: <strong>".this->sub_Surname."</strong></h6>";
			echo "<h6>sub_Gender: <strong>".this->sub_Gender."</strong></h6>";
			echo "<h6>sub_Age: <strong>".this->sub_Age."</strong></h6>";
			echo "<h6>Description: <strong>".this->Description."</strong></h6>";
			echo "<h6>StatusCode: <strong>".this->StatusCode."</strong></h6>";
			echo "<h6>StatusInfo: <strong>".this->StatusInfo."</strong></h6>";
			echo "<h6>NumberOfResults: <strong>".this->NumberOfResults."</strong></h6>";
		}
	}	

	class Image {
		public $ID = "";
		public $TimeStamp = "";
		public $LocationX = "";
		public $Filename = "";
		//public $Meta = "";
	}
	
	class User {
		//public $ID = "";
		public $Username = "";
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
		if ($row != null)
		{
			$tmp->ID = $row['id'];
			$tmp->Username = $row['username'];
			$tmp->Image = getImage($row['image_id'],1);
			$tmp->sub_Name = $row['subName'];
			$tmp->sub_Surname = $row['subSurname'];
			$tmp->sub_Gender = $row['subGender'];
			$tmp->sub_Age = $row['subAge'];
			$tmp->Description = $row['description'];
			$tmp->StatusCode = $row['progess'];
			$tmp->StatusInfo = $row['status'];
			$tmp->NumberOfResults = $row['numResults'];
		}
		else
		{
			$tmp->ID =  "test";
			$tmp->Username = "test";
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

	function Image($row)
	{
		$tmp = new Image();
		$tmp->ID = $row['id'];		
		$tmp->TimeStamp = $row['timestamp'];
		$tmp->LocationX = $row['Location'];
		$tmp->Filename = $row['filename'];
		return $tmp;
	}
	
	function User($row)
	{
		$tmp = new User();
		$tmp->Username = $row['username'];		
		$tmp->Active = $row['active'];
		return $tmp;
	}

	function Result($row)
	{
		$tmp = new Result();
		$tmp->ID = $row['id'];
		$tmp->ImageCode = $row['randomIdentifier'];
		$tmp->Image = getImage($row['image_id'],0);
		$tmp->Match = $row['percentageMatch'];
		return $tmp;
	}
?>