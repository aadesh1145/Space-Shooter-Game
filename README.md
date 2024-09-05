# SPACE SHOOTER GAME

## Introduction
This game is based on the popular 1978 game named **Space Shooter** which we all enjoyed playing in our childhood. The original “Space Shooter” game, often referred to as “Space Invaders,” was released by Taito in 1978. It became one of the most iconic and influential arcade games of its time. This project is developed as a first year project in the project demonstration organized by [ACES](https://www.facebook.com/acesdharan), Dharan. 

## Team Members
* [**Aadesh Dahal**](https://www.facebook.com/profile.php?id=100086562643929) (Group Representative)
   * github: https://github.com/aadesh1145
   * contact: 9801993663
* [**Nishchal Pokhrel**](https://www.facebook.com/Nischalp97)
   * github: https://github.com/nischalp97
   * contact: 9842857102
* [**Nandini Karn**](https://www.facebook.com/karn.nandini)
   * github: https://github.com/Nandini18665
   * contact: 9702293175
* [**Karuna Shrestha**](https://www.facebook.com/karuna.shrestha.104855)
   * github: https://github.com/Karuna-0521
   * contact: 9762984455

## Preview
![image](https://github.com/user-attachments/assets/6bda6eab-d55b-4de0-8832-04d9d7b7a3d4)


## Process of Development
Learnings in university were enough to understand basics of the game that were used in the game. But I used a library called SFML to build the graphics and setup the controls in the game. To learn more about SFML, initially i watched few youtube videos to easily lay hand on the library. After I got to know more about the library it was a easy process. I took few help from the AI chatbots to debug my errors and bugs in my code. Code is being executed properly but there are some room for improvements in my code.


## Requirements and Setup 
* Primarily, you need [Visual Studio Code](https://code.visualstudio.com/Download) to run this program.
* Most importantly, you need SFML library compatible with your mingW. I recommend using the following SFML version and mingW version in your computer to execute this code without causing any setup errors: 
   * [SMFL-2.5.1-windows-gcc-7.3.0](https://sourceforge.net/projects/sfml.mirror/files/2.5.1/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip/download)
   * [mingw-W64-possix-seh-rt-v6-rev0.7z](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z/download)<br>
 (Caution:Use of other versions of mingW and SFML may cause unwanted errors and problems in the code so, I strongly recommend using this version of SFML and mingW.)

* After this process, you need to download the game repository from my github profile.
* I recommend downloading this repository directly in your (C:/space-shooter-game) drive without including this folder in any folder of C drive so that, you can easily render all the resources of this game and you don't need to manually change the path of the assets(images/sprite, fonts and sfx) that were used in the development otherwise you need to change the path of the resources(sprite, sfx, fonts) used in the code manually. The path that contains my space shooter game is C:\smfl-project. Here sfml-project contains all the folders like coding, src, font, sfx, sprit, MakeFile, all dll files, etc. The main.cpp file is inside the coding(coding>>main.cpp) which is the main file of my project.<br>
You can follow these steps to correctly download the folder to render all the game resources properly:
    * After entering inside my Space-Shooter-Game repository, tap on green button that has "code" written in it. Download the zip file. Or you can simply clone the given repository in C (cd /C:/Space-Shooter-Game-main).
      drive with following instructions.
     ![image](https://github.com/user-attachments/assets/54b8e3eb-ded9-4ae5-8638-0db0506fa093)
    * After downloading it, direct toward the folder and extract it inside the C drive. 
      ![image](https://github.com/user-attachments/assets/0fcf1e0c-2b64-4294-a1ee-66284b695651)
    * Open that extracted folder inside the Visual Studio Code.
     ![image](https://github.com/user-attachments/assets/78f53e56-3c2f-4f24-8255-180f6e41e088)
* After following the steps you are good to go.

Info: This is a fully functioning code with all images, fonts and music tested in my computer. Strictly follow the above process to avoid any mistakes and unwanted error in the program.All the required libraries and assets of this game are found in the folder so, no any external libraries and file need to be imported to run this program in your computer.


## Running the Program
This code cannot run directly from the run button available in your Visual Studio Code. The following steps should be followed properly to run this program :
* First open the folder that has all the code, assets, MakeFile file.
![image](https://github.com/user-attachments/assets/ced94fa8-5a95-4767-91f7-478aad791d55)

* Open the coding folder and direct toward main.cpp file. (coding>>main.cpp)
![image](https://github.com/user-attachments/assets/a5d1cc49-226c-46fa-b887-9b759fac54fd)

* Now, open the terminal of your VS Code. Or simply hold CTRL+Shift+~ or CTRL+Shift+` in the code to open the terminal. Terminal will appear. In the terminal type the following commands(Following command are case sensitive so, make sure to use the correct letter while writing the command in your terminal). 

  * mingw32-make -f MakeFile<br>
Type the given command and click enter. This will help build the project inside your system. You may see the following message or output in your terminal box. If you don't get the following message or output then you have not properly followed the steps above.<br>

Ouput:<br>
g++ -Isrc/include -c coding/*.cpp<br>
g++ *.o -o main -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lopengl32 -lsfml-audio<br>

This will ensure that the sfml library is properly setup in your system and you are eligible to run the code. If you don't get the above result than you may have caused an error in setup or made a mistake.

![image](https://github.com/user-attachments/assets/5c9a2b9b-bcbf-47ae-a806-eabab0c8e773)

  * ./main<br>
Again type the given command and click enter to run the game. This command helps you to run the program in your computer. Now you are good to go and the game will be running in your computer if you have properly followed the steps above.
![image](https://github.com/user-attachments/assets/d3a8cbad-4cf8-4953-9ad3-403df7981afa)

* Following window may open after you click enter. Now the game is being run on the computer system you can click on play button to play the game or exit to exit the game in your computer.
![image](https://github.com/user-attachments/assets/cfe8ba14-5860-4d0e-889e-2436f05973d3)


## How to Play
First, you need to go through the instructions which will provide you the basic knowledge of controls of the game. Now to return from the instructions page tap anywhere on your computer screen to return to homepage. Now tap on play and play the game with the help of instruction provided and enjoy the game. You can know the developers of the game in the about section and tap anywhere inside the about section to return to your homepage. Click on exit to exit the game.

## Shortcomings
This game is developed like a presentation and is still underdeveloped. There are many shortcomings in this game. Like, if you open the game 1st window will be created and after you click on play, write your game and click enter two windows will be opened simultaneously which is quite a disadvantage. After you play the game you cannot pause the game or exit while playing the game.To quit the game you might need to close the two windows rendered while executing the program. After you score high score the message should be displayed only once but it displays multiple message for every point after you score a high score. There is no seperate high score menu inside the game. These are the common and noticable shortcomings of this game.

## Our Personal Experience 
This is the first game project developed by me and my team in our coding journey. It has many shortcomings but also has very good features which you might feel while playing this game. There were many feature which we could not add due to our personal time scarcity. But this game has given us basic and advanced knowledge of game development and its process. This experience might help us in our future journey of development.


## Useful Resources
Some youtube channels that helped us build this project:
* [Vishal Saini](https://www.youtube.com/@vishalsaini3878)
  * [Video1](https://www.youtube.com/watch?v=AMDt1XWa40U)
  * [Video2](https://www.youtube.com/watch?v=EPwv30GWUOY&t=408s)
  * [Video3](https://www.youtube.com/watch?v=ifK5qDEvYtQ&t=929s)
  
* [Suraj Sharma](https://www.youtube.com/@SurajSharmaFourKnob)
  * [Video1](https://www.youtube.com/watch?v=sWYpNIrBr6U)
  * [Video2](https://www.youtube.com/watch?v=Ax0-srLD9ck)
  * [Video3](https://www.youtube.com/watch?v=J8VolRonMw0&t=6s)
  * [Video4](https://www.youtube.com/watch?v=w8sBCquJh0k)

Assets used in this game [ivanwidyan](https://github.com/ivanwidyan/spaceshooter-cpp-sfml) and also from many other webisites.


## Author
* Aadesh Dahal
* Facebook - [Aad Esh](https://www.facebook.com/profile.php?id=100086562643929)
* Github - [aadesh1145](https://github.com/aadesh1145)
