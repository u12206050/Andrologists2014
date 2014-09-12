<?php require('header.php');?>
    <div id="loader">
        <img src="images/loader.gif">
        <p id="loadingInfo">loading...</p>
    </div>
    <div id="fader"></div>
    <div id="ErrorMsg">        
        <label for="ErrorMsg"></label>
        <a href="logic/php/testConnect.php" class="ui-shadow ui-btn ui-corner-all ">TestConnection</a>
        <button onClick="$('#ErrorMsg').fadeOut();$('#fader').fadeOut();">ok</button>
    </div>
    
    <!--HOME-->
    <div data-role="page" id="login" data-theme="a">
        <div data-role="header" data-position="inline">
            <h1>Login</h1>
            <?php require('menumin.html');?>    
        </div>
        <div data-role="content" data-theme="a">
            <div class="maxWidth center">
                <form id="login" action="" method="post"> 
                    <p>To start please login in:</p> 
                    <div class="border-wrap">
                        <input type="text" name="user" id="user" data-theme="d" placeholder="Username"/>
                        <label for="user" class="error">Username required</label>
                    
                        <input type="text" name="pass" id="pass" data-theme="d" placeholder="Password"/>
                        <label for="pass" class="error">Password required</label>                        
                    </div>  
                    <div class="center"> 
                        <input type="hidden" name="action" value="openCase"/>                     
                        <input type="submit" id="btnLogin" class="ui-shadow ui-btn ui-corner-all ui-btn-icon-left center button-wrap" data-icon="check" value="Submit" data-transition="slideup"/>
                    </div>  
                </form>
            </div>
        </div>
        <div data-role="footer" data-theme="d">
            <?php
                if (isset($_SESSION["user"]))
                {
                    include('menuAlt.html');
                }
            ?> 
        </div>
    </div>  

    <!--ACCOUNT-->
    <div data-role="page" id="account" data-theme="a">
        <div data-role="header" data-position="inline">
            <h1>Account</h1>
            <h3 id="Userlogged"></h3>
            <?php require('menumin.html');?>              
        </div>
        <div data-role="content" data-theme="a">                
            <div class="ui-grid-a ui-responsive center">
                <div class="ui-block-a">
                    <div class="border-wrap">
                        <div class="center" id="casesOverview">
                            <div data-role="collapsible"> <h2>Recent Cases:</h2> 
                                <ul data-role="listview" data-split-icon="eye" data-split-theme="a"> 
                                    <li>
                                        <a href="#results?id=0">
                                            <h3>Subject name and Surname</h3> 
                                            <p>DATETIME : Description</p>
                                        </a> 
                                        <a href="#popup" data-rel="dialog" data-transition="pop">Preview</a>
                                    </li> 
                                    <li>
                                        <a href="#results?id=1">
                                            <h3>Subject name and Surname</h3> 
                                            <p>DATETIME : Description</p>
                                        </a> 
                                        <a href="#popup" data-rel="dialog" data-transition="pop">Preview</a>
                                    </li>
                                    <li>
                                        <a href="#results?id=2">
                                            <h3>Subject name and Surname</h3> 
                                            <p>DATETIME : Description</p>
                                        </a> 
                                        <a href="#popup" data-rel="dialog" data-transition="pop">Preview</a>
                                    </li>
                                </ul> 
                            </div>
                        </div>   
                        <button data-theme="c" onClick="$.mobile.navigate('#captureface');">New Case</button> 
                    </div>
                </div>  
                <div class="ui-block-b">
                    <div class="border-wrap">
                        Edit Information:
                            <form class="ui-hide-label">
                                <label for="user">Username:</label>
                                <input type="text" name="user" id="user" placeholder="Username"/>
                                <label for="pass">Password:</label>
                                <input type="password" name="pass" id="pass" placeholder="Password"/>
                                <label for="repass">Re-enter password:</label>
                                <input type="password" name="repass" id="pass" placeholder="Re-enter Password"/>
                                <input type="hidden" name="action" value="openCase"/>      
                                <input type="submit" value="Update"></input>
                            </form>
                        <img class="ui-corner-all" id="casefacepreview" src="images/notfound.jpg"/>
                    </div>
                </div>
            </div>
        </div>
        <div data-role="footer" data-theme="d">
            <?php require('menuAlt.html');?> 
        </div>
    </div>  

    <!--CAPTURE FACE-->
    <div data-role="page" id="captureface" data-theme="c">
        <div data-role="header" data-position="inline">
            <h1>Capture Face</h1>
        </div>
        <form id="uploadFace" runat="server" method="post" action="">
            <div data-role="content" data-theme="a">                
                    <div class="ui-grid-a ui-responsive center">                                    
                        <div class="ui-block-a">
                            <div class="border-wrap">
                                <input type="text" id="fname" name="fname" data-theme="d" placeholder="Name"/>
                                <label for="fname" class="error">Subject's name or 'none'</label>
                           
                                <input type="text" id="surname" name="surname" data-theme="d" placeholder="Surname"/>
                                <label for="surname" class="error">Subject's surname or 'none'</label>
                                <div data-role="fieldcontainer">
                                    <fieldset data-role="controlgroup" data-type="horizontal">                                    
                                        <select name="gender" id="gender">
                                            <option name="gender" id="genderG" value="" required/>
                                            <label for="genderG">Select Gender</label>
                                            <option name="gender" id="genderM" value="M" required/>
                                            <label for="genderM">Male</label>
                                            <option name="gender" id="genderF" value="F"  />
                                            <label for="genderF">Female</label>
                                        </select>
                                    </fieldset>                                    
                                    <label for="gender" class="error"></label> 
                                </div>                            
                                <input type="number" min="1" id="age" name="age" data-theme="d" placeholder="Age"/>
                                <label for="age" class="error"></label>                             
                                <textarea id="desc" name="desc" data-theme="d" placeholder="Note"></textarea>
                                <label for="desc" class="error"></label> 
                            </div>
                       </div>
                        <div class="ui-block-b">
                            <div class="border-wrap">
                                <input type="file" capture="camera" accept="image/*" id="facepic" name="facepic" data-theme="d" placeholder="Take a picture"/>
                                <label for="facepic" class="error"></label>
                                <input type="hidden" name="action" value="openCase"/>                                 
                                <div class="ui-grid-solo">
                                    <div class="ui-block-a center"><img class="ui-corner-all" id="capturefacepreview" src="images/digital.jpg"/></div>
                                </div>
                            </div>
                        </div>
                    </div>                
            </div>
            <div data-role="footer" data-theme="d">
                <div class="ui-grid-a center">
                    <div class="ui-block-a">
                        <div class="ui-bar ui-bar-a">
                            <a href="#account" class="ui-shadow ui-btn ui-corner-all ui-btn-icon-left ui-icon-delete" data-transition="slidedown">Cancel</a>
                        </div>
                    </div>
                    <div class="ui-block-b">
                        <div class="ui-bar ui-bar-a">
                            <input type="submit" id="submitCapture" class="ui-shadow ui-btn ui-corner-all ui-btn-icon-left center ui-icon-check button-wrap" data-icon="check" value="Submit" data-transition="slideup"/>
                        </div>
                    </div>
                </div>
            </div>
        </form>
    </div> 

    <!--CAPTURE FACE_RESULTS-->
    <div data-role="page" id="results" data-theme="e">
        <div data-role="header" data-position="inline">
            <h1>Case: <strong id="caseID">-999</strong></h1>
            <?php require('menualt.html');?> 
        </div>
        <div data-role="content" data-theme="a">
            <div id="" data-role="collapsibleset" data-content-theme="a">
                
                <div class="ui-grid-b ui-responsive center">                                    
                    <div class="ui-block-b"><h3>StatusCode: <strong id="statusCode">-11</strong></h3></div>
                    <div class="ui-block-b"><h3>StatusInfo: <strong id="statusInfo">none</strong></h3></div>                    
                    <div class="ui-block-c"><h3>Results: <strong id="noOfResults">-1</strong></h3></div> 
                </div>
                <div id="resultOverview">
                    <div data-role="collapsible"> <h2>One month ago</h2> 
                        <ul data-role="listview" data-split-icon="gear" data-split-theme="a"> 
                            <li>
                                <a href="#popup"> <img src="images/digital.jpg"> <h3>25 July 2014</h3> 
                                <p>Camera Location: Entrance</p> </a> <a href="#popup" data-rel="dialog" data-transition="pop">View original</a> </li> 
                            <li>
                                <a href="#popup"> <img src="images/digital.jpg"> <h3>22 July 2014</h3> 
                                <p>Camera Location: South Exit</p> </a> <a href="#popup" data-rel="dialog" data-transition="pop">View original</a> </li> 
                            <li>
                                <a href="#popup"> <img src="images/digital.jpg"> <h3>3 July 2014</h3> 
                                <p>Camera Location: Bull street</p> </a> <a href="#popup" data-rel="dialog" data-transition="pop">View original</a> </li> 
                        </ul> 
                    </div>
                </div>
            </div>
        </div>
        <div data-role="footer" data-theme="d">
            <h4><button id="btnRefresh" class="ui-shadow ui-btn ui-corner-all ui-btn-icon-left ui-icon-refresh button-wrap">Refresh</button></div></h4>
            
        </div>
    </div>

    <!--VIEW ORIGINAL DIALOG-->
    <div data-role="dialog" id="popup" data-theme="c">
        <div data-role="header">
            <h1>Original Picture</h1>
            <div class="ui-grid-b ui-responsive center">
                <div class="ui-block-a"><div id="orgDate" class="ui-btn ui-shadow ui-btn ui-btn-icon-left ui-icon-calendar button-wrap">DATE_DATA</div></div>               
                <div class="ui-block-b"><div id="orgTime" class="ui-shadow ui-btn ui-btn-icon-left ui-icon-clock button-wrap">TIME_DATA</div></div>
                <div class="ui-block-c"><div id="orgLocation" class="ui-shadow ui-btn ui-btn-icon-left ui-icon-location button-wrap">LOCATION_DATA</div></div>
            </div>
        </div>
        <div role="main"  class="ui-content"  data-theme="c">
            <div class="ui-grid-solo">
                <div class="ui-block-a center"><img class="ui-corner-all" id="facepreview" src="images/notfound.jpg"/><!--<?php echo CGIPATH;?>geti.q?image=main.jpg--></div>
            </div>
        </div>
        <div data-role="footer">
            <h4 id="orgMatch">Recognition match: 0%</h4>
        </div>
    </div>  

    <!--CONTACT US-->
    <div data-role="page" id="contactus" data-theme="a">
        <div data-role="header" data-position="inline">
            <h1>Contact Us</h1>
            <?php require('menu.html');?>  
        </div>
        <div data-role="content" data-theme="a">
            <div id="contacUsContent">loading...</div>            
        </div>
    </div>  

    <!--ABOUT-->
    <div data-role="page" id="about" data-theme="a">
        <div data-role="header" data-position="inline">
            <h1>About</h1>
            <?php require('menu.html');?>
        </div>
        <div data-role="content" data-theme="a">
            <div id="aboutContent">loading...</div>
        </div>
    </div>  
<?php require('footer.php');?> 