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
			echo "<p>sub_Name: <strong>".$this->sub_Name."</strong></p>";
			echo "<p>sub_Surname: <strong>".$this->sub_Surname."</strong></p>";
			echo "<p>sub_Gender: <strong>".$this->sub_Gender."</strong></p>";
			echo "<p>sub_Age: <strong>".$this->sub_Age."</strong></p>";
			echo "<p>Description: <strong>".$this->Description."</strong></p>";
			echo "<p>StatusCode: <strong>".$this->StatusCode."</strong></p>";
			echo "<p>StatusInfo: <strong>".$this->StatusInfo."</strong></p>";
			echo "<p>NumberOfResults: <strong>".$this->NumberOfResults."</strong></p>";
			echo "<p>Image: </p>";
			$this->Image->printX();
		}
	}	

	class Image {
		public $ID = "";
		public $TimeDate = "";
		public $LocationX = "";
		public $Filename = "";
		
		public function printX()
		{
			echo "<h5>Image details</h5>";
			echo "<p>ID: <strong>".$this->ID."</strong></p>";
			echo "<p>TimeDate: <strong>".$this->TimeDate."</strong></p>";
			echo "<p>Location: <strong>".$this->LocationX."</strong></p>";
			echo "<p>Filename: <strong>".$this->Filename."</strong></p>";
		}
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
			$tmp->sub_Name = $row['sub_name'];
			$tmp->sub_Surname = $row['sub_surname'];
			$tmp->sub_Gender = $row['sub_gender'];
			$tmp->sub_Age = $row['sub_age'];
			$tmp->Description = $row['description'];
			$tmp->StatusCode = $row['progress'];
			$tmp->StatusInfo = $row['status'];
			$tmp->NumberOfResults = $row['num_results'];
		}
		else
		{
			$tmp->ID = "0";
			$tmp->Username = "testuser";
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
			$tmp->TimeDate = $row['timedate'];
			$tmp->LocationX = $row['location'];
			$tmp->Filename = $row['filename'];
		}
		else
		{
			$tmp->ID = "0";
			$tmp->TimeDate = "undefined";
			$tmp->LocationX = "undefined";
			$tmp->Filename = "undefined";
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
			$tmp->Username = "testuser";
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
			$tmp->ImageCode = $row['random_identifier'];
			$tmp->Image = getImage($row['face_id'],0);
			$tmp->Match = $row['percentage_match'];
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
