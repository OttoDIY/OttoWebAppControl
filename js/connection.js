let ROBOT = "";
let OttoConnected = false;

function OttoConnection(robot) {
    if (robot != ROBOT && ROBOT != '') {
        Swal.fire({
            icon: 'info',
            title: 'Disconnect your '+ROBOT+' before connecting your '+robot,
            text: 'To disconnect, click the icon of the robot that is already connected and press the button to disconnect it.'
        })
    } else {
        ROBOT = robot;
        if(isConnected) {
            Swal.fire({
                icon: 'question',
                title: 'Do you want to disconnect your '+robot+' robot?',
                showDenyButton: false,
                showCancelButton: true,
                confirmButtonText: 'Yes',
                }).then((result) => {
                if (result.isConfirmed) {
                    onDisconnected()
                    SetRobot()
                    document.getElementsByClassName('container__bluetooth--icon')[0].style.display = "none";
                    document.getElementsByClassName('container__bluetooth--icon')[0].style.backgroundColor = "#FF5700";
                    Swal.fire('Your '+robot+' is disconnected!', '', 'info')
                } 
            })
        } else {
            Swal.fire({
                title: 'Connect an '+robot+'?',
                icon: 'question',
                html:
                    'If you have a <a href="https://www.ottodiy.com/" target="_blank">Otto DIY</a> robot and you want to connect it to this app:<br> ' +
                    '1. Your Otto must have a bluetooth module <br>' +
                    '2. Upload the code as appropriate.<ul><li>OttoStarter <a href="OttoS_BLE.ino" target="_blank">Arduino Ino</a> or <a href="https://ivanr3d.com/tools/otto/codes/" target="_blank">Web Installer</a></li> <li>OttoWheels <a href="OttoW_BLE.ino" target="_blank">Arduino Ino</a> or <a href="https://ivanr3d.com/tools/otto/codes/" target="_blank">Web Installer</a></li>',
                showDenyButton: true,
                showCancelButton: false,
                confirmButtonText: 'Connect',
                denyButtonText: `Cancel`,
                }).then((result) => {
                if (result.isConfirmed) {
                    OttoConnected = true
                    connectToBle()
                } else {
                    ROBOT = "";
                    Swal.fire('No robot connected!', '', 'info')
                } 
            })
        }
    }
    
}

function SetRobot() {
    document.getElementById("disconnectMessage--container").style.display == "none" ? document.getElementById("disconnectMessage--container").style.display = "flex" : document.getElementById("disconnectMessage--container").style.display = "none";

    document.getElementsByClassName("lever")[0].style.display == "none" ? document.getElementsByClassName("lever")[0].style.display = "flex" : document.getElementsByClassName("lever")[0].style.display = "none";

    document.getElementById("functions--section").style.display == "none" ? document.getElementById("functions--section").style.display = "flex" : document.getElementById("functions--section").style.display = "none";

    if (ROBOT == 'Otto Starter') {
        document.getElementById("OttoStarter").classList.toggle('green--mask');
        if (isConnected) {
            document.getElementById("dir--keys").style.display == "none" ? document.getElementById("dir--keys").style.display = "flex" : document.getElementById("dir--keys").style.display = "none";
            CreateGesturesButtons();
            CreateUltrasound();
            CreateAvoidance();
            CreateForce();
        } else {
            ROBOT = "";
            document.getElementById("dir--keys").style.display == "flex" ? document.getElementById("dir--keys").style.display = "none" : null;
            FunctionsDestroyer();
        }
    }
    else if (ROBOT == 'Otto Wheels') {
        document.getElementById("OttoWheels").classList.toggle('green--mask');
        if (isConnected) {
            document.getElementById("joystick--control").style.display == "none" ? document.getElementById("joystick--control").style.display = "flex" : document.getElementById("joystick--control").style.display = "none";
            document.getElementsByClassName("slider--container")[0].style.display = "none";
            CreateUltrasound();
            CreateInfrared();
            CreateAvoidance();
            CreateLineFollower();
        } else {
            ROBOT = "";
            document.getElementById("joystick--control").style.display == "flex" ? document.getElementById("joystick--control").style.display = "none" : null;
            FunctionsDestroyer();
        }
    }
}
