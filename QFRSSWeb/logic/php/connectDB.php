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
	
	function login()
	{
		try
		{
			if ($pgconn != null)
			{
				$result = pg_query($pgconn, "SELECT * FROM authors");
				if (!$result) {
				    echo "An error occurred.\n";
				    exit;
				}

				$arr = pg_fetch_all($result);
			}
		} 
		catch (Exception $e)
		{
		    echo 'LOGIN - Caught exception: ',  $e->getMessage(), "\n";
		}
	}
?>