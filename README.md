
# Otto Web App Control

  

This project is a web app that allows you to control [Otto DIY](https://www.ottodiy.com/) robots from a browser using Bluetooth connection. The application use the [p5js](https://p5js.org/) library to communicate with an Arduino board (connected to a BLE module) and [Sweetalert2](https://sweetalert2.github.io/) to make better popup boxes.

  

## Installation

  

You can use the **app online** visiting: https://ottodiy.github.io/OttoWebAppControl/

  

To use the **app offline**, install the project following these steps:

  

1. Clone the repository to your computer using the command: `git clone https://github.com/OttoDIY/OttoWebAppControl.git`

  

2. Install the dependencies by running `npm install` in the project folder.

  

3. __And that's it!__ Open the __index.html__ file with Google Chrome (Computers & Android) or [Bluefy](https://apps.apple.com/us/app/bluefy-web-ble-browser/id1492822055) (iOS) to start using the app.

  

## Usage

  

To use the application, follow these steps:

  

1. Upload the code to your robot depending which model you are using. [Otto Starter](https://github.com/OttoDIY/OttoWebAppControl/blob/main/OttoS_BLE.ino), [Otto Wheels](https://github.com/OttoDIY/OttoWebAppControl/blob/main/OttoW_BLE.ino), [Otto Ninja Starter](https://github.com/OttoDIY/OttoWebAppControl/blob/main/OttoNinja.ino).

**Note: Make sure that the connections of the robots (legs, feet, bluetooth, etc) are wired as specified in the code.**
  

2. Turn on your robot and make sure it is in pairing mode (the LED in the Bluetooth module should be blinking).

  

3. Open the application in your browser.

  

4. Select the robot from the list in the robot selector bar.

  

5. Click on __Connect__ button and select your robot from the list of available Bluetooth devices that will appear.

  

6. Once connected, you can control the robot using the controls on the screen or the keyboard shortcuts.

  

## Features

  

- ****Compatibility:**** with all Otto DIY robots but other biped and vehicle robots based on Arduino could be connected too

  

- ****Movement control:**** forward, backward, turn left and turn right

  

- ****Gestures:**** with Otto Starter you can execute some gestures like Happy, Sad, Angry, etc

  

- ****Functions:**** avoidance (biped & wheels) and line follower (only wheels) functions are available

  

- ****Sensor value display:**** depending on the robot you are using you will be able to view the values of some sensors like ultrasound and infrared

  

## Contributions

  

This project is open source and we welcome contributions. If you would like to help improve the project, please follow this process:

  

1. Clone or fork the repository

  

2. Create a branch for your feature (`git checkout -b my-new-feature`)

  

3. Commit your changes (`git commit -am 'Add some feature'`)

  

4. Push to the branch (`git push origin my-new-feature`)

  

5. Create a new pull request

  

If you are looking for something specific you could help, check the [issues section](https://github.com/OttoDIY/OttoWebAppControl/issues).

  

****If working with the app styles****, we are currently implementing [PostCSS](https://postcss.org/), so consider:

- When you are developing, you can run `npm run css:watch` to compile while you are working  

- For compiling styles run `npm run css:build` when your code is ready for deploy



  

## License

  

### GNU General Public License v3.0

  

Read it [here](https://github.com/OttoDIY/OttoWebAppControl/blob/main/LICENSE)

  

## System Requirements

  

- Browser compatible with [Web Bluetooth API.](https://developer.mozilla.org/en-US/docs/Web/API/Web_Bluetooth_API) Currently we strongly recommend Google Chrome for Computers (including Macbook) and Android devices, and [Bluefy](https://apps.apple.com/us/app/bluefy-web-ble-browser/id1492822055)  for iOS devices (iPhones and iPad).

  

## Known issues

  

Currently, Google Chrome is the only browser giving a good user experience for this app, **except on iOS devices**. For iOS devices (iPhones and iPad) we have confirmed that [Bluefy](https://apps.apple.com/us/app/bluefy-web-ble-browser/id1492822055) work good. In case you are having issues using this app with another browser, we strongly recommend to try it with Chrome and/or Bluefy to confirm if it is a general issue or something with the browser.

  

## Credits

  

Thanks to all these great people and open projects, it has been possible to make this software:

  

-  [Iván R. Artiles](https://github.com/IvanR3D)

  

-  [Camilo Parra](https://github.com/cparrapa)

  

-  [Alejandro Narmona](https://github.com/alenarmona)

  

-  [OttoDIY](https://www.ottodiy.com/)

  

-  [P5js](https://p5js.org/)

  

-  [SweetAlert](https://sweetalert2.github.io/)

  

## Screenshots

Easy to connect!

![enter image description here](https://ivanr3d.com/assets/img/screenshots/OttoWAC/OttoWAC_use-OttoStarter.gif)

  

Light/Dark mode available!

![enter image description here](https://ivanr3d.com/assets/img/screenshots/OttoWAC/OttoWAC_use-OttoWheels.gif)

  

Now Otto Wheels can be controlled using a joystick!

![enter image description here](https://ivanr3d.com/assets/img/screenshots/OttoWAC/wheels--joystick.gif)

  

## Additional links

  

- Official p5.js documentation: [https://p5js.org/](https://p5js.org/)

  

- Official Sweetalert2 documentation: [https://sweetalert2.github.io/](https://sweetalert2.github.io/)

  

- Official website of the Otto DIY robots: [https://www.ottodiy.com/](https://www.ottodiy.com/)

  

- Documentation for Otto DIY robots: [https://www.ottodiy.com/academy](https://www.ottodiy.com/academy)
