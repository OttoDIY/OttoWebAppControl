
# Otto Web App Control

This project is a web app that allows you to control [Otto DIY](https://www.ottodiy.com/) robots from a browser using Bluetooth connection. The application is built with pure HTML, CSS & JavaScript. Using the [p5js](https://p5js.org/) library to communicate with an Arduino board (connected to a BLE module) and [Sweetalert2](https://sweetalert2.github.io/) to make better popup boxes.

## Installation

To install the project, follow these steps:

1.  Clone the repository to your computer using the command: `git clone https://github.com/OttoDIY/OttoWebAppControl.git`
2.  Install the Sweetalert2 by running `npm install sweetalert2` in the project folder.
3.  _And that's it!_ Open the _index.html_ file with Google Chrome to start using the app.

## Usage

To use the application, follow these steps:

1. Upload the code to your robot depending which model you are using. [Otto Starter](https://ivanr3d.com/tools/ottocontroller/OttoS_BLE.ino), [Otto Wheels](https://ivanr3d.com/tools/ottocontroller/OttoW_BLE.ino), [Otto Ninja Starter](https://ivanr3d.com/tools/ottocontroller/OttoNinja.ino).
2. Turn on your robot and make sure it is in pairing mode (the LED in the Bluetooth module sure be blinking).
3.  Open the application in your Google Chrome.
4.  Select the robot from the list in the robot selector bar.
5.  Click on _Connect_ button and select your robot from the list of available Bluetooth devices that will appear.
6.  Once connected, you can control the robot using the controls on the screen or the keyboard shortcuts.

## Features

-   **Compatibility:** with all Otto DIY robots but other biped and vehicle robots based on Arduino could be connected too
-   **Movement control:** forward, backward, turn left and turn right
-   **Gestures:** with Otto Starter you can execute some gestures like Happy, Sad, Angry, etc 
- **Functions:** avoidance (biped & wheels) and line follower (only wheels) functions are available
- **Sensor value display:** depending on the robot you are using you will be able to view the values of some sensors like ultrasound and infrared

## Contributions

This project is open source and we welcome contributions. If you would like to help improve the project, please follow this process:

1.  Fork the repository.
2.  Create a branch for your feature (`git checkout -b my-new-feature`)
3.  Commit your changes (`git commit -am 'Add some feature'`)
4.  Push to the branch (`git push origin my-new-feature`)
5.  Create a new pull request

If you are looking for something specific you could help, here is a list of features we would love to implement: 

 - [ ] **Multi language**: a nice way to change the app texts from one language to another. 
 - [ ] **New Otto DIY robots support**: currently only Starter, Wheels & Ninja Starter are available. If you have experience coding Arduino you could help us by creating the code to control some of the other Otto robots or creating the UI for those robots.
 - [ ] **Responsive design**: improve the experience of using the app on different screen sizes.
 - [ ] **PWA implementation**: turn the app into a Progressive Web App.
 - [ ] **Testing**: test the app in different environments (different browsers for example) and send us your feedback about usability and/or User Experience.

## License

ToDo

## System Requirements

-   Browser compatible with [Web Bluetooth API.](https://developer.mozilla.org/en-US/docs/Web/API/Web_Bluetooth_API) Currently we strongly recommend Google Chrome.

## Known issues

-   Currently, Google Chrome is the only browser giving a good user experience for this app. In case you are having issues using this app with another browser, we strongly recommend to try it with Chrome to confirm if it is a general issue or something with the browser.

## Additional links

-   Official p5.js documentation: [https://p5js.org/](https://p5js.org/)
- Official Sweetalert2 documentation: [https://sweetalert2.github.io/](https://sweetalert2.github.io/)
-   Official website of the Otto DIY robots: [https://www.ottodiy.com/](https://www.ottodiy.com/)
-   Documentation for Otto DIY robots: [https://www.ottodiy.com/academy](https://www.ottodiy.com/academy)

## Screenshots
![enter image description here](https://ivanr3d.com/assets/img/screenshots/OttoWAC/OttoWAC_use-OttoStarter.gif)
![enter image description here](https://ivanr3d.com/assets/img/screenshots/OttoWAC/OttoWAC_use-OttoWheels.gif)