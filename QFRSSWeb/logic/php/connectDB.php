<?php
	//Variables
	define("DBNAME","postgres");
	define("DBHOST","localhost");
	define("DBPORT","5432");
	define("DBUSERNAME","postgres");
	define("DBPASSWORD","data");
	$pgconn = null;
	
	try
	{
		echo "start\n";
		$conn_string = "host=".DBHOST." port=".DBPORT." dbname=".DBNAME." user=".DBUSERNAME." password=".DBPASSWORD." connect_timeout=5";
		$pgconn = pg_connect($conn_string) or die('connection failed');
		echo pg_options(pg_host($pgconn));
		echo "end\n";
		pg_close($pgconn);
	} 
	catch (Exception $e)
	{
	    echo 'Caught exception: ',  $e->getMessage(), "\n";
	}
	//connect to a database named "test" on the host "sheep" with a username and password
?>