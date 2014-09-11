<?php
	//Variables
	define("DBNAME","qfrss");
	define("DBHOST","localhost");
	define("DBPORT","5432");
	define("DBUSERNAME","postgres");
	define("DBPASSWORD","data");
	define("DEV","true");
	define("CGIPATH","http://localhost/cgi-bin/");
	$pgconn = null;
	
	echo "<h3>Require all php files</h3>";
	require './classes.php';
	echo "<h3>Done</h3>";
	
	//TestClasses
	echo "<h3>Test printing of classes</h3>";
	try
	{
		$tmp = xcase(null);
		$tmp->printX();
	} 
	catch (Exception $e)
	{
	    echo 'TestClass - Caught exception: ',  $e->getMessage(), "\n";	    
	}
	echo "<h3>Done</h3>";
	
	//TestConnection
	echo "<h3>Tring to connect to Postgre Server</h3><pre>";
	connect();
	echo "</pre><h3>Finished</h3>";

	function connect()
	{
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
		    echo 'CONNECTDB - Caught exception: ',  $e->getMessage(), "\n";
		    pg_close($pgconn);
		    $pgconn = null;
		}
	}

	
?>