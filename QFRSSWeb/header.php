<?php 
    if (isset($_SESSION["user"]))
        unset($_SESSION["user"]);
    
    echo '<!DOCTYPE html>
            <html class="ui-mobile">
                <head>';
    echo file_get_contents("includes.html");  
    echo '      </head>
            <body class="ui-mobile-viewport">';
?>