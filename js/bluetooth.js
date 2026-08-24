// Characteristics resolved after connecting, picked by their properties.
let writeCharacteristic = null;
let notifyCharacteristic = null;

// Writes are serialized: the browser rejects a GATT operation started while
// another one is still running (the joystick can fire faster than that).
let writeQueue = Promise.resolve();

const CHARACTERISTIC_PROPERTIES = ['broadcast', 'read', 'writeWithoutResponse', 'write', 'notify', 'indicate', 'authenticatedSignedWrites', 'reliableWrite', 'writableAuxiliaries'];


function connectToBle() {
  // Connect to a device by passing the service UUID
  blueTooth.connect(0xFFE0, gotCharacteristics);
}


function listProperties(characteristic) {
  const properties = characteristic.properties || {};
  return CHARACTERISTIC_PROPERTIES.filter(function (name) { return properties[name]; });
}


function canWrite(characteristic) {
  const properties = characteristic.properties || {};
  return !!(properties.write || properties.writeWithoutResponse || properties.authenticatedSignedWrites);
}


function canNotify(characteristic) {
  const properties = characteristic.properties || {};
  return !!(properties.notify || properties.indicate);
}


// A function that will be called once got characteristics
function gotCharacteristics(error, characteristics) {
  if (error) {
    console.log('error: ', error);
  }
  console.log('characteristics: ', characteristics);
  if (!characteristics || !characteristics.length) {
    Swal.fire({
      icon: 'error',
      title: 'No characteristic found',
      text: 'The device was paired but the service FFE0 is empty, so no command can be sent.'
    });
    return;
  }
  characteristics.forEach(function (characteristic) {
    console.log('  ' + characteristic.uuid + ' -> ' + listProperties(characteristic).join(', '));
  });

  // Bluetooth modules do not agree on the order of the characteristics inside
  // the FFE0 service, and some of them split the serial port in two: one
  // characteristic to notify and another one to write. Picking
  // characteristics[0] blindly ends up writing to a read/notify only
  // characteristic, which the browser rejects with
  // "NotSupportedError: GATT operation not permitted."
  writeCharacteristic = characteristics.find(canWrite) || null;
  notifyCharacteristic = characteristics.find(canNotify) || null;
  blueToothCharacteristic = writeCharacteristic || characteristics[0];

  if (notifyCharacteristic) {
    blueTooth.startNotifications(notifyCharacteristic, gotValue, 'string');
  } else {
    console.warn('No characteristic supports notifications, sensor values will not be received.');
  }

  isConnected = blueTooth.isConnected();
  if(isConnected) {
    document.getElementsByClassName('container__bluetooth--icon')[0].style.display = "block";
    document.getElementsByClassName('container__bluetooth--icon')[0].style.backgroundColor = "#32D900";
    SetRobot();
    if (writeCharacteristic) {
      Swal.fire('Connected!', '', 'success');
    } else {
      Swal.fire({
        icon: 'error',
        title: 'Connected, but this module cannot receive commands',
        html: 'None of the characteristics of the service FFE0 accepts writes, so the robot will ignore every command.<br>Check that your bluetooth module is a BLE 4.0 serial module (HM-10 and compatibles).'
      });
    }
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
  writeCharacteristic = null;
  notifyCharacteristic = null;
  blueToothCharacteristic = null;
}


// Try the write flavours the characteristic advertises, newest API first.
// writeValue() is deprecated and picks the flavour on its own, so it stays as
// the last resort for older browsers.
function writeChunk(chunk) {
  const properties = writeCharacteristic.properties || {};
  const attempts = [];
  if (properties.writeWithoutResponse && writeCharacteristic.writeValueWithoutResponse) {
    attempts.push(function () { return writeCharacteristic.writeValueWithoutResponse(chunk); });
  }
  if (properties.write && writeCharacteristic.writeValueWithResponse) {
    attempts.push(function () { return writeCharacteristic.writeValueWithResponse(chunk); });
  }
  attempts.push(function () { return writeCharacteristic.writeValue(chunk); });

  return attempts.reduce(function (chain, attempt) {
    return chain.catch(attempt);
  }, Promise.reject());
}


function writeBytes(bytes) {
  // BLE 4.0 serial modules only forward 20 bytes per write (23 bytes MTU
  // minus the 3 bytes ATT header), longer commands get truncated.
  let chain = Promise.resolve();
  for (let offset = 0; offset < bytes.length; offset += 20) {
    const chunk = bytes.slice(offset, offset + 20);
    chain = chain.then(function () { return writeChunk(chunk); });
  }
  return chain;
}


function sendData(command) {
  const inputValue = command;
  if (!("TextEncoder" in window)) {
    console.log("Sorry, this browser does not support TextEncoder...");
    return;
  }
  if (!writeCharacteristic) {
    console.error('There is no writable characteristic, "' + inputValue.trim() + '" was not sent.');
    return;
  }
  var enc = new TextEncoder(); // always utf-8
  const bytes = enc.encode(inputValue);

  writeQueue = writeQueue.then(function () {
    return writeBytes(bytes);
  }).catch(function (error) {
    console.error('Could not send "' + inputValue.trim() + '": ', error);
  });
  return writeQueue;
}
