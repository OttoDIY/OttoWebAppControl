// Keep variables with the keyword 'var' to avoid the calibration popup from failing
var r = document.getElementById("right-slider--container");
var l = document.getElementById("left-slider--container");
var rfoot = document.getElementById("right-foot-slider--container");
var lfoot = document.getElementById("left-foot-slider--container");

var rlslider = document.getElementById("right-leg-slider");
var llslider = document.getElementById("left-leg-slider");
var rfslider = document.getElementById("right-foot-slider");
var lfslider = document.getElementById("left-foot-slider");

var RightLeg = document.getElementsByClassName("OttoLeg")[0];
var LeftLeg = document.getElementsByClassName("OttoLeg")[1];
var RightFoot = document.getElementsByClassName("OttoLeg--heel")[0];
var LeftFoot = document.getElementsByClassName("OttoLeg--heel")[1];

var RightLegPlus = document.getElementById("right-leg-plus");
var RightLegMinus = document.getElementById("right-leg-minus");
var LeftLegPlus = document.getElementById("left-leg-plus");
var LeftLegMinus = document.getElementById("left-leg-minus");
var RightFootPlus = document.getElementById("right-foot-plus");
var RightFootMinus = document.getElementById("right-foot-minus");
var LeftFootPlus = document.getElementById("left-foot-plus");
var LeftFootMinus = document.getElementById("left-foot-minus");

r.onmouseover = function() { RightLeg.style.backgroundColor = "red"; };
r.onmouseout = function() { RightLeg.style.backgroundColor = "white"; };
l.onmouseover = function() { LeftLeg.style.backgroundColor = "red"; };
l.onmouseout = function() { LeftLeg.style.backgroundColor = "white"; };
rfoot.onmouseover = function() { RightFoot.style.backgroundColor = "red"; document.getElementsByClassName("OttoLeg--foot")[0].style.backgroundColor = "red"; };
rfoot.onmouseout = function() { RightFoot.style.backgroundColor = "white"; document.getElementsByClassName("OttoLeg--foot")[0].style.backgroundColor = "white"; };
lfoot.onmouseover = function() { LeftFoot.style.backgroundColor = "red"; document.getElementsByClassName("OttoLeg--foot")[1].style.backgroundColor = "red"; };
lfoot.onmouseout = function() { LeftFoot.style.backgroundColor = "white"; document.getElementsByClassName("OttoLeg--foot")[1].style.backgroundColor = "white"; };

RightLegPlus.onclick = function() { rlslider.value++; rlvalue.innerText = rlslider.value; if(OttoConnected){bipedCalibration();}};
RightLegMinus.onclick = function() { rlslider.value--; rlvalue.innerText = rlslider.value; if(OttoConnected){bipedCalibration();}};
LeftLegPlus.onclick = function() { llslider.value++; llvalue.innerText = llslider.value; if(OttoConnected){bipedCalibration();}};
LeftLegMinus.onclick = function() { llslider.value--; llvalue.innerText = llslider.value; if(OttoConnected){bipedCalibration();}};
RightFootPlus.onclick = function() { rfslider.value++; rfvalue.innerText = rfslider.value; if(OttoConnected){bipedCalibration();}};
RightFootMinus.onclick = function() { rfslider.value--; rfvalue.innerText = rfslider.value; if(OttoConnected){bipedCalibration();}};
LeftFootPlus.onclick = function() { lfslider.value++; lfvalue.innerText = lfslider.value; if(OttoConnected){bipedCalibration();}};
LeftFootMinus.onclick = function() { lfslider.value--; lfvalue.innerText = lfslider.value; if(OttoConnected){bipedCalibration();}};

rlslider.oninput = function() { rlvalue.innerText = rlslider.value; if(OttoConnected){bipedCalibration();}};
llslider.oninput = function() { llvalue.innerText = llslider.value; if(OttoConnected){bipedCalibration();}};
rfslider.oninput = function() { rfvalue.innerText = rfslider.value; if(OttoConnected){bipedCalibration();}};
lfslider.oninput = function() { lfvalue.innerText = lfslider.value; if(OttoConnected){bipedCalibration();}};