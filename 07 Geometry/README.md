OpenGL-exercise

- exercise about OpenGL         
- 基于C++，OpenGL 4.6以及cmake制作的。
- 主要内容是进行camera的练习。

目的：geometry  几何体 练习  
新建一个geometry类，可以创建立方体，给予立方体的边长，利用边长生成mesh的VBO数据。最后完成几何体数据的封装。

图示：<br>
<img src="https://github.com/hougexxx/OpenGL-exercises/blob/edf7fe7adfb4964377cede0f568291c35a89026f/07%20Geometry/README_picture/geometry.png" width=40%>
<img src="https://github.com/hougexxx/OpenGL-exercises/blob/edf7fe7adfb4964377cede0f568291c35a89026f/07%20Geometry/README_picture/geometry_1.png" width=40%>




其他内容如下：

main.cpp为主函数。

glad.c函数用于导入和OpenGL相关的函数。

Application是应用层的函数库，里面封装了init，update，destroy函数。此外，还有和相机相关的函数。

Wrapper中封装了OpenGL的错误检查函数。

assets中是项目所需要的资源文件。包括glsl文件，以及用于制作纹理的图片。

glframework是整个项目的框架，封装了关于shader着色器和texture纹理相关的函数。

thirdparty中是需要的第三方库。

