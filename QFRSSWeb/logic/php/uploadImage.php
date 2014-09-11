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
				}
			}
		}
		else
		{
			if ($debug = 1)
				echo "Invalid file, max-size: 5mb";
			return -1;
		}
	}
	//Save
	//Return
?>