<?php
	//Authenticate
	//Validate
	//Upload
	function uploadBookImage()
	{
		$allowedExts = array("gif", "jpeg", "jpg", "png");
		$temp = explode(".", $_FILES["file"]["name"]);
		$extension = end($temp);
		if ((($_FILES["file"]["type"] == "image/gif")
			|| ($_FILES["file"]["type"] == "image/jpeg")
			|| ($_FILES["file"]["type"] == "image/jpg")
			|| ($_FILES["file"]["type"] == "image/pjpeg")
			|| ($_FILES["file"]["type"] == "image/x-png")
			|| ($_FILES["file"]["type"] == "image/png"))
			&& ($_FILES["file"]["size"] <= 2000000)
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
				$fileName = md5_file($Title.$user->ID).".".$extension;
				if (!(file_exists("chirpdata/user/" . $fileName)))
				{
					move_uploaded_file($_FILES["file"]["tmp_name"], "bookImages/" . $fileName);
					return $fileName;
				}
			}
		}
		else
		{
			if ($debug = 1)
				echo "Invalid file, max-size: 2mb";
			return -1;
		}
	}
	//Save
	//Return
?>