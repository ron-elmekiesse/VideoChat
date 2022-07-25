# VideoChat

### Install OpenCV
* Go to this [link](https://opencv.org/releases/) and click on the Windows installler.
* Follow the instructions in the wizzard.
* Copy folder `<path_to_opencv>/build/include/opencv2` into `<repo>/Dev/ThirdParty/OpenCV/`.
* Copy file `<path_to_opencv>/build/x64/vc15/lib/opencv_world<version>d.lib` into `<repo>/Dev/ThirdParty/OpenCV/`.
* Modify proerties in Visual Studio `properties->Linker->Input->Additional Dependencies` and set the correct version of your OpenCV.
* That's it!

### Install SFML
* Go to this [link](https://www.sfml-dev.org/download.php) and download the latest version of SFML.
* Copy folder `<path_to_sfml>/SFML-<version>` into `<repo>/Dev/ThirdParty/`.
* Add `<path_to_sfml>/SFML-<version>/bin` to path.
* Modify proerties in Visual Studio `properties->Linker->General->Additional Library Dependencies` and set the correct version of your SFML.
* Modify `properties->C/C++->General->Additional Include Dependencies` and set the correct version of your SFML.
* Good to go.

