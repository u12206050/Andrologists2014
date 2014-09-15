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
		
		public function printX()
		{
			echo "<h5>Case details</h5>";
			echo "<p>ID: <strong>".$this->ID."</strong></p>";
			echo "<p>UserID: <strong>".$this->Username."</strong></p>";
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
			$tmp->ID = "0";
			$tmp->Username = "user";
			$tmp->Image = Image(null);
			$tmp->sub_Name = "Preview_John";
			$tmp->sub_Surname = "Preview_Smith";
			$tmp->sub_Gender = "M";
			$tmp->sub_Age = "1";
			$tmp->Description = "Preview_Found in area 51";
			$tmp->StatusCode = "3";
			$tmp->StatusInfo = "Preview";
			$tmp->NumberOfResults = "1";
		}
		return $tmp;
	}

	function Image($row)
	{
		$tmp = new Image();
		if ($row != null)
		{
			$tmp->ID = $row['id'];		
			$tmp->TimeStamp = $row['timestamp'];
			$tmp->LocationX = $row['Location'];
			$tmp->Filename = $row['filename'];
		}
		else
		{
			$tmp->ID = "0";
			$tmp->TimeStamp = "32/13/3125 25:60";
			$tmp->LocationX = "Area 51";
			$tmp->Filename = "notfound.jpg";
		}
		return $tmp;
	}
	
	function User($row)
	{
		$tmp = new User();
		if ($row != null)
		{
			//$tmp->ID = $row['id'];	
			$tmp->Username = $row['username'];		
			$tmp->Active = $row['active'];
		}
		else
		{
			//s$tmp->ID = "0";
			$tmp->Username = "Preview_user";
			$tmp->Active = "true";
		}
		return $tmp;
	}

	function Result($row)
	{
		$tmp = new Result();
		if ($row != null)
		{
			$tmp->ID = $row['id'];
			$tmp->ImageCode = $row['randomIdentifier'];
			$tmp->Image = getImage($row['image_id'],0);
			$tmp->Match = $row['percentageMatch'];
		}
		else
		{
			$tmp->ID = "0";
			$tmp->ImageCode = "0";
			$tmp->Image = Image(null);
			$tmp->Match = "101%";
		}
		return $tmp;
	}
?>