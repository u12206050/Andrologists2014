<?php require('header.php');?>
    <div id="loader">
        <img src="images/loader.gif">
        <p id="loadingInfo" class="center">loading...</p>
    </div>
    <div id="fader"></div>    
    
    <!--HOME-->
    <div data-role="page" id="login" data-theme="a">
        <div data-role="header" data-position="inline">
            <h1>Login</h1>
            <?php require('menu.html');?>    
        </div>
        <div data-role="content" data-theme="e">
            <div class="maxWidth center">
                <form id="frmlogin" action="" method="post"> 
                    <p>To start please login in:</p> 
                    <div class="border-wrap" >
                        <input type="text" name="user" id="user" data-theme="d" placeholder="Username"/>
                        <label for="user" class="error">Username required</label>
                    
                        <input type="password" name="pass" id="pass" data-theme="d" placeholder="Password"/>
                        <label for="pass" class="error">Password required</label>                        
                    </div>  
                    <div class="center">  
                        <label id="loginError" class="error"></label>                   
                        <input type="submit" id="btnLogin" class="ui-shadow ui-btn ui-corner-all ui-btn-icon-left center button-wrap" data-icon="check" value="Enter" data-transition="slideup"/>
                    </div>  
                </form>
            </div>
        </div>
        <div data-role="footer" data-position='fixed' data-theme="d">
            <p class='center'>V.Moodley | Z.Bloom | G.Lamusse | H.Mistry<p>
            <p class='center'>Andrologists © 2014<p>
        </div>
    </div>  

    <!--ACCOUNT-->
    <div data-role="page" id="account" data-theme="a">
        <div data-role="header" data-position="inline">
            <h1>Account</h1>
            <h3 id="Userlogged"></h3>                        
        </div>
        <div data-role="content" data-theme="a"> 
            <div class="maxWidth center ui-responsive">               
                <div class="center" id="casesOverview"></div>
                <div class="ui-grid-b ui-responsive center">
                    <div class="ui-block-a"><button data-theme="b" class="ui-btn-icon-left ui-icon-refresh block-button" data-icon="refresh" onClick="outputAllCases();">Reload Cases</button></div>     
                    <div class="ui-block-b"><button data-theme="c" id="btnChangePassword" class="ui-btn-icon-left ui-icon-alert block-button" data-icon="alert">Password</button></div>
                    <div class="ui-block-c"><button data-theme="c" id='adminLink' class="ui-btn-icon-left ui-icon-gear block-button" data-icon="gear" onClick="$.mobile.navigate('#admin', { transition: 'slide' });getNimda();" style='display: none'>Administration</button></div>
                </div>   
            </div>              
        </div>
        <div data-role="footer" data-position='fixed' data-theme="d">
            <?php require('menuAlt.html');?> 
        </div>
    </div>  

    <!--CAPTURE FACE-->
    <div data-role="page" id="captureface" data-theme="a">
        <div data-role="header" data-position="inline">
            <h1>Capture Face</h1>
        </div>
        <form id="uploadFace" runat="server" enctype="multipart/form-data" data-ajax="false" method="post" action="">
            <div data-role="content" data-theme="e">                
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
                                        <option name="gender" id="genderG" value=""/>
                                        <label for="genderG">Select Gender</label>
                                        <option name="gender" id="genderM" value="M"/>
                                        <label for="genderM">Male</label>
                                        <option name="gender" id="genderF" value="F"/>
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
                            <!--<iframe src="facefrm.php"></iframe>-->
                            <input type="file" capture="camera" accept="image/*" id="facepic" name="facepic" data-theme="d"/>
                            <label for="facepic" class="error"></label>
                            <input type="hidden" name="action" value="openCase"/>                                 
                            <div class="ui-grid-solo">
                                <div class="ui-block-a center"><img class="ui-corner-all" id="capturefacepreview" src="images/digital.jpg"/></div>
                            </div>
                        </div>
                    </div> 
                </div>    
            </div>
            <div data-role="footer" data-position='fixed' data-theme="d">
                <div class="ui-grid-a center">
                    <div class="ui-block-a">
                        <a href="#account" class="ui-shadow ui-btn ui-corner-all ui-btn-icon-left ui-icon-delete button-wrap" data-transition="slide">Cancel</a>
                    </div>
                    <div class="ui-block-b">
                        <a id="submitCapture" class="ui-shadow ui-btn ui-corner-all ui-btn-icon-left ui-icon-check button-wrap" data-icon="check" data-transition="slide">Submit</a>
                    </div>
                </div>
            </div>
        </form>
    </div> 

    <!--CAPTURE FACE_RESULTS-->
    <div data-role="page" id="results" data-theme="e">
        <div data-role="header" data-position="inline">
            <h1>Case: <strong id="caseID">-999</strong></h1>
            <?php //require('menualt.html');?> 
        </div>
        <div data-role="content" data-theme="a">
            <div class="ui-grid-b ui-responsive center">                                    
                <div class="ui-block-a"><p>StatusCode: <strong id="statusCode">-11</strong></p></div>
                <div class="ui-block-b"><p>StatusInfo: <strong id="statusInfo">none</strong></p></div>                    
                <div class="ui-block-c"><p>Results: <strong id="noOfResults">-1</strong></p></div> 
            </div>
            <div id="resultOverview" data-role="collapsible-set" data-theme="d" data-content-theme="e">
                
            </div>
        </div>
        <div data-role="footer" data-position='fixed' data-theme="d">
            <h4><button id="btnRefresh" class="ui-shadow ui-btn ui-corner-all ui-btn-icon-left ui-icon-refresh button-wrap" data-icon="refresh">Get Results</button></div></h4>      
        </div>
    </div>

    <!--VIEW ORIGINAL DIALOG-->
    <div data-role="dialog" id="popup" data-theme="b">
        <div data-role="header">
            <h1>Closer look</h1>
            <div class="ui-grid-b ui-responsive center">
                <div class="ui-block-a"><div id="d1" class="showText ui-btn ui-shadow ui-btn button-wrap">DATE_DATA</div></div>               
                <div class="ui-block-b"><div id="d2" class="showText ui-shadow ui-btn button-wrap">TIME_DATA</div></div>
                <div class="ui-block-c"><div id="d3" class="showText ui-shadow ui-btn ui-btn-icon-left ui-icon-clock button-wrap">LOCATION_DATA</div></div>
            </div>
        </div>
        <div role="main" class="ui-content" data-theme="c">
            <div class="ui-grid-solo">
                <div class="ui-block-a center"><img class="ui-corner-all" id="facepreview" src="" alt="image holder"/></div>
            </div>
        </div>
        <div data-role="footer">
            <h4 id="d4" class="center"></h4>
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

    <!--INFO-->
    <div data-role="dialog" id="INFO" data-theme="c">
        <div data-role="header">
            <h1>Info</h1>
        </div>
        <div class="ui-content"  data-theme="c">
            <div class="ui-grid-solo">
                <div class="ui-block-a center">     
                    <p id="INFOMsg"></p>
                </div>
            </div>
        </div>
    </div>

    <!--PASSWORD-->
    <div data-role="dialog" id="changePassword" data-theme="c">
        <div data-role="header">
            <h1>Change password</h1>
        </div>
        <div class="ui-content"  data-theme="c">
            <div class="ui-grid-solo">
                <div class="ui-block-a center">     
                    <legend>Change password:</legend> 
                    <form id="frmUpdatePassword" action="" method="post"> 
                        <input type="password" name="u_oldpass" id="u_oldpass" placeholder="Current Password"/> 
                        <label for="u_oldpass" class="error"></label>                              
                        <input type="password" name="u_pass" id="u_pass" placeholder="New Password"/>
                        <label for="u_pass" class="error"></label>                            
                        <input type="password" name="u_repass" id="u_repass" placeholder="Re-enter Password"/> 
                        <label for="u_repass" class="error"></label>                                                        
                        <label id="updatePassError" class="error"></label>                   
                        <input data-theme="b" type="submit" id="btnUpdatePassword" class="ui-shadow ui-btn ui-corner-all ui-btn-icon-left center button-wrap" data-icon="check" value="Update"/>                        
                    </form>
                </div>
            </div>
        </div>
    </div>

    <!--ADMIN-->
    <div data-role="page" id="admin" data-theme="e">
        <div data-role="header" data-position="inline">
            <h1>Administration</h1>  
        </div>
        <div data-role="content" data-theme="a">
            <div id="userView" data-role="collapsible-set" data-theme="e" data-content-theme="a">
                
            </div>           
        </div>
        <div data-role="footer" data-position='fixed' data-theme="d">
            <h4><a href="#account" class="ui-shadow ui-btn ui-corner-all ui-btn-icon-left ui-icon-user button-wrap">Account</a></h4>      
        </div>
    </div>  
<?php require('footer.php');?> 
