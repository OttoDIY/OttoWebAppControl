function connectToBle() {
  // Connect to a device by passing the service UUID
  blueTooth.connect(0xFFE0, gotCharacteristics);
}


// A function that will be called once got characteristics
function gotCharacteristics(error, characteristics) {
  if (error) { 
    console.log('error: ', error);
  }
  console.log('characteristics: ', characteristics);
  blueToothCharacteristic = characteristics[0];

  blueTooth.startNotifications(blueToothCharacteristic, gotValue, 'string');
  
  isConnected = blueTooth.isConnected();
  if(isConnected) {
    document.getElementsByClassName('container__bluetooth--icon')[0].style.display = "block";
    document.getElementsByClassName('container__bluetooth--icon')[0].style.backgroundColor = "#32D900";
    SetRobot();
    Swal.fire('Connected!', '', 'success');
  }
  // Add a event handler when the device is disconnected
  blueTooth.onDisconnected(onDisconnected);
}


// A function that will be called once got values
function gotValue(value) {
//  console.log('value: ', value);
  receivedValue = value;
  SensorsView();

}


function onDisconnected() {
  console.log('Device got disconnected.');
  isConnected = false;
  OttoConnected = false;
}


function sendData(command) {
  const inputValue = command;
  if (!("TextEncoder" in window)) {
    console.log("Sorry, this browser does not support TextEncoder...");
  }
  var enc = new TextEncoder(); // always utf-8
  blueToothCharacteristic.writeValue(enc.encode(inputValue));
}
