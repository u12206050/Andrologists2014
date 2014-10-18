<?php
	//Variables
	$conn = null;
	$_REQUEST["action"] = "Tests";
	echo "<h3>Require all php files</h3>";	
	echo require("classes.php");
	echo "<h3>Done</h3>";
	
	//TestClasses
	echo "<h3>Test printing of classes</h3>";
	try
	{
		$tmp = Cases(null);
		$tmp->printX();
	} 
	catch (Exception $e)
	{
	    echo 'TestClass - Caught exception: ',  $e->getMessage(), "\n";	    
	}
	echo "<h3>Done</h3>";
	
	//TestConnection
	echo "<h3>Tring to connect to Postgre Server</h3><pre>";
	tryconnect();
	echo "</pre><h3>Finished</h3>";

	function tryconnect()
	{
		try
		{
			echo "start\n";
			echo require("connectDB.php");
			$conn = connect();
			$result = pg_query($conn, "INSERT INTO users VALUES ('name', 'pass', true)");
			if (!$result) {
			  echo ".\nInsert error occurred.\n";
			  echo pg_last_error($conn);
			}
			else
			{
				echo ".\nInsert successful.\n";
			}
			$result = pg_query($conn, "DELETE FROM users WHERE username = 'name' AND password = 'pass'");
			if (!$result) {
			  echo ".\nDELETE error occurred.\n";
			  echo pg_last_error($conn);
			}
			else
			{
				echo ".\nDELETE successful.\n";
			}
			echo "end\n";
			pg_close($conn);
		} 
		catch (Exception $e)
		{
		    echo 'CONNECTDB - Caught exception: ',  $e->getMessage(), "\n";
		    pg_close($conn);
		    $conn = null;
		}
	}

	
?>
