let KEY;

function selectRobot(el) {
    el.classList.toggle("green--mask");
}

window.addEventListener('keydown', function (e) {
    KEY++;
    if(KEY == 1) {
        if (e.key == "ArrowUp") {
            btnPressed("up");
        }
        else if (e.key == "ArrowDown") {
            btnPressed("down");
        }
        else if (e.key == "ArrowRight") {
            btnPressed("right");
        }
        else if (e.key == "ArrowLeft") {
            btnPressed("left");
        }
        else if (e.key == "s") {
            btnPressed("s");
        }
    } 
}, false);

window.addEventListener('keyup', function (e) {
    KEY = 0;
}, false);

function btnPressed(btn) {
    
    if (OttoConnected) { 
        if (btn == "up") {
            changeBackgroundColor("up");
            Forward();
        }
        else if  (btn == "down"){
            changeBackgroundColor("down");
            Backward();
        }
        else if  (btn == "right"){
            changeBackgroundColor("right");
            Right();
        }
        else if  (btn == "left"){
            changeBackgroundColor("left");
            Left();
        }
        else if  (btn == "s"){
            changeBackgroundColor("s");
            Stop();
        }
        else {
            //Stop();
        }
            
    }
}

function changeBackgroundColor(btn) {
    if (btn == "up") {
        document.getElementsByClassName('up')[0].style.backgroundColor = "#FF5700";
        document.getElementsByClassName('right')[0].style.backgroundColor = "#32D900";
        document.getElementsByClassName('down')[0].style.backgroundColor = "#32D900";
        document.getElementsByClassName('left')[0].style.backgroundColor = "#32D900";
    }
    else if (btn == "right") {
        document.getElementsByClassName('up')[0].style.backgroundColor = "#32D900";
        document.getElementsByClassName('right')[0].style.backgroundColor = "#FF5700";
        document.getElementsByClassName('down')[0].style.backgroundColor = "#32D900";
        document.getElementsByClassName('left')[0].style.backgroundColor = "#32D900";
    }
    else if (btn == "down") {
        document.getElementsByClassName('up')[0].style.backgroundColor = "#32D900";
        document.getElementsByClassName('right')[0].style.backgroundColor = "#32D900";
        document.getElementsByClassName('down')[0].style.backgroundColor = "#FF5700";
        document.getElementsByClassName('left')[0].style.backgroundColor = "#32D900";
    }
    else if (btn == "left") {
        document.getElementsByClassName('up')[0].style.backgroundColor = "#32D900";
        document.getElementsByClassName('right')[0].style.backgroundColor = "#32D900";
        document.getElementsByClassName('down')[0].style.backgroundColor = "#32D900";
        document.getElementsByClassName('left')[0].style.backgroundColor = "#FF5700";
    }
    else if (btn == "s") {
        document.getElementsByClassName('up')[0].style.backgroundColor = "#32D900";
        document.getElementsByClassName('right')[0].style.backgroundColor = "#32D900";
        document.getElementsByClassName('down')[0].style.backgroundColor = "#32D900";
        document.getElementsByClassName('left')[0].style.backgroundColor = "#32D900";
    }
}