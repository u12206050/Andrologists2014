<?php

	if (isset($_REQUEST["action"]))
	{
		//Variables
		define("DBNAME","quant");
		define("DBHOST","localhost");
		define("DBPORT","5432");
		define("DBUSERNAME","postgres");
		define("DBPASSWORD","root");
		define("DEV","true");
		define("CGIPATH","http://localhost/cgi-bin/");
		$pgconn = null;	
		if (connect() != null)
			require("functions.php");
		else
			return "Database could not be connected";
	}
	function connect()
	{
		try
		{
			//echo "start\n";
			$conn_string = "host=".DBHOST." port=".DBPORT." dbname=".DBNAME." user=".DBUSERNAME." password=".DBPASSWORD." connect_timeout=5";
			$pgconn = pg_connect($conn_string) or die('connection failed');
			//echo pg_options(pg_host($pgconn));				
		} 
		catch (Exception $e)
		{
		    //echo 'CONNECTDB - Caught exception: ',  $e->getMessage(), "\n";
		    pg_close($pgconn);
		    $pgconn = null;
		}
		return $pgconn;
	}

	function disconnect()
	{
		if ($pgconn != null)
		{
			pg_close($pgconn);
			$pgconn = null;
		}
	}
?>
