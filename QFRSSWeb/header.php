<?php 
    include_once("logic/php/connectDB.php");
    session_start();

    $url = 'http://' . $_SERVER['SERVER_NAME'] . $_SERVER['REQUEST_URI'];
    $default = "Location: /".$_SERVER['SERVER_NAME'];
    if (isset($_REQUEST["action"]) && $_REQUEST["action"] == "logout")
    {
        unset($_SESSION["user"]);
    }
    //still need to put in the links
    if (!DEV && !isset($_SESSION["user"]))
    {

        if (strpos($url,'capture')){
            header($default);
        } elseif (strpos($url,'results')){ 
            header($default);
        } elseif (strpos($url,'cases')){
            header($default);
        } elseif (strpos($url,'account')){
            header($default);
        }
    }
    else
    {
        if (strpos($url,'register')) 
        {
            header($default);
        }
        header($default+"#account");
    }


    echo '<!DOCTYPE html>
            <html class="ui-mobile">
                <head>';
    echo file_get_contents("includes.html");  
    echo '      </head>
            <body class="ui-mobile-viewport">';
?>