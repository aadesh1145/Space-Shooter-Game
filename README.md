# SPACE SHOOTER GAME

## Introduction
This game is based on the popular 20's game named **Space Shooter** which we all enjoyed playing in our childhood. This game is developed by [**Aadesh Dahal**](https://www.facebook.com/profile.php?id=100086562643929), **Nishchal Pokhrel**, **Nandini Karn** and **Karuna Shrestha** as a first year project in the project demonstration organized by [ACES](https://www.facebook.com/acesdharan), Dharan. 


## Preview

![image](https://github.com/user-attachments/assets/cfe8ba14-5860-4d0e-889e-2436f05973d3)


## My process of development

The teachings in my college was enough to understand basics of the game that were used in the game. But I used a library called SFML to build the graphics and setup the controls in the game. To learn more about SFML, initially i watched few youtube videos to easily lay hand on the library. After I got to know more about the library it was a easy process. I took few help from the AI chatbots to debug my errors and bugs in my code. Code is being executed properly but there are some room for improvements in my code.


## Requirements and setup 

Primarily, you need [Visual Studio Code](https://code.visualstudio.com/Download) to run this program. Most importantly, you need SFML library compatible with your mingW. I recommend using the following SFML version and mingW version in your computer to execute this code and properly enjoy the game: 
* [SMFL-2.5.1-windows-gcc-7.3.0](https://sourceforge.net/projects/sfml.mirror/files/2.5.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip/download)
* [mingw-W64-possix-seh-rt-v6-rev0.7z](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z/download)
Caution:Use of other versions of mingW and SFML may cause unwanted errors and problems in my code so I strongly recommend using this version of SFML and mingW.

After this process, you need to download the game repository from my github profile (I recommend downloading this repository in your C:/ drive so that, you don't need to change the path of the assets(images/sprite, fonts and sfx) that were used in the development otherwise you need to change the path of the image file used in the code manually). After following the steps you are good to go.

This is a fully functioning code with all images, fonts and music tested in my computer. Strictly follow the above process to avoid any mistakes and unwanted error in the program.


## Running the program
This code cannot be run directly from the run button available in your Visual Studio Code. The following steps should be followed properly to run this program :
* First open the folder that has all the code, assets, MakeFile file.
![image](https://github.com/user-attachments/assets/ced94fa8-5a95-4767-91f7-478aad791d55)

* Open the coding folder and direct toward main.cpp file. (coding>>main.cpp)
![image](https://github.com/user-attachments/assets/a5d1cc49-226c-46fa-b887-9b759fac54fd)

*Now, open the terminal of your VS Code. Or simply hold CTRL+Shift+~ or CTRL+Shift+` in the code. Terminal will appear. In the terminal type the following commands.

1. mingw32-make -f MakeFile 
And hit enter. You may see the following message or output in your terminal box in the provided image below. If you don't get the following message or output then you have not properly followed the steps above.
![image](https://github.com/user-attachments/assets/5c9a2b9b-bcbf-47ae-a806-eabab0c8e773)

2. ./main
Again type ./main after you see the following output in your terminal box in your VS code. Now you are good to go and the game will be running in your computer if you have properly followed the steps above.
![image](https://github.com/user-attachments/assets/d3a8cbad-4cf8-4953-9ad3-403df7981afa)






