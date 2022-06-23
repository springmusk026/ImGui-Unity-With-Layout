 # ImGui Unity Template with Costumized Layout
 > 2022/06/16: Initial Comit.

ImGui Template that can addapt any Unity Games 
 ![image](https://github.com/springmusk026/ImGui-Unity-With-Layout/blob/master/main.jpg?raw=true)
 
# What is IMGUI?
   Imgui is basically a full stack GUI framework made with c++ which supports lots of operatinh systems

# Is it Easy to use Imgui on Android?
 If need to say correctly , I dont find it easy to use as i use on my pc

# Why IMGUI?
 As Its a full stack Framework we/you can easily make lots of things from it easily and it can save lot of time

# How it Works ?
   Yes , While Talking about its working method currently we use egl to hook with our EGLSurface
  or Simply It uses `eglSwapBuffers` with Dobby Hook
  
# How is it's touch Managed?  
   Currently it uses the touch from game itself ,like Unity structure for touch so it gets easy for us to Handle it

# How to inject / implement
  1. Extract the lib from your deired Architecture or simply `armeabi-v7a`
  2. Place your lib in correct path of the game.
  3. Load your Lib from `onCreate` of your Game's Mainactivity or UnityPlayerActivity
  
 The main activity of Unity is: ```com/unity/player/UnityPlayerActivity```
   
   ```
   const-string v0, "native-lib"

   invoke-static {v0}, Ljava/lang/System;->loadLibrary(Ljava/lang/String;)V
   ```
  Having Doubt?
 ![image](https://user-images.githubusercontent.com/80401984/145727071-26bb7d51-ae83-4fdc-94f5-aa3b9421ed4b.png)

# Recomendations

1. This Project Currently Uses CMake So Better you Use AndroidIDE or Android studio 
2. AIDE i will never recommend to use cause it's systems are not so good at all
3. If you find bugs relating to this project, simply mention on the same repo so that we can improve it

# Notice:
 I am not in any race of releasing first or last but yes i provide the cleaniest sources with proper credit of creators , those who dont have much mind let them keep it doing (your ego is useless in front of this world )
# Codes 
![image](https://github.com/springmusk026/ImGui-Unity-With-Layout/blob/master/a.jpg?raw=true)
![image](https://github.com/springmusk026/ImGui-Unity-With-Layout/blob/master/b.jpg?raw=true)
![image](https://github.com/springmusk026/ImGui-Unity-With-Layout/blob/master/c.jpg?raw=true)
![image](https://github.com/springmusk026/ImGui-Unity-With-Layout/blob/master/d.jpg?raw=true)
![image](https://github.com/springmusk026/ImGui-Unity-With-Layout/blob/master/e.jpg?raw=true)
# Credits

* Jackknobel/Ocornut - IMGUI : https://github.com/ocornut/imgui
* vvb2060 - DobbyHook - https://github.com/vvb2060/dobby-android
* Ztz - IMGUI template https://github.com/ZTzTopia
* xo1337 - Layout Base : https://www.youtube.com/watch?v=Sn3q7LjG-kA

