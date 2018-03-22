//
//  main.cpp
//  OpenGLTest
//
//  Created by 孟琦 on 2018/3/21.
//  Copyright © 2018年 孟琦. All rights reserved.
//

#include <stdio.h>
#include "GLTools.h"
#include <glut/glut.h>

GLBatch triangleBatch;
GLShaderManager shaderManager;
//窗口大小改变时接收新的宽度高度
void ChangeSize(int w,int h){
    glViewport(0, 0, w, h);
}

void SetupRC(){
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    shaderManager.InitializeStockShaders();
    GLfloat vVerts[] = {
        -0.5f,0.0f,0.0f,
        0.5f,0.0f,0.0f,
        0.0f,0.5f,0.0f,
    };
    triangleBatch.Begin(GL_TRIANGLES, 3);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
}
//开始渲染
void RenderScene(void){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    GLfloat vRed[] = {1.0f,0.0f,0.0f,1.0f};
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY,vRed);
    triangleBatch.Draw();
    glutSwapBuffers();
}

int main(int argc,char* argv[]){
    //设置当前工作目录，针对mac os x
    gltSetWorkingDirectory(argv[0]);
    //初始化GLUT库
    glutInit(&argc, argv);
    /*初始化双缓冲窗口，
     其中标志GLU_DOUBLE、GLUT_RGBA、GLUT_DEPTH、GLUT_STENCIL
     分别指：双缓冲窗口、RGBA颜色模式、深度测试、模版缓冲区*/
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    //GLUT窗口大小，标题窗口
    glutInitWindowSize(800, 600);
    glutCreateWindow("Triangle");
    //注册回调函数
    glutReshapeFunc(ChangeSize);
    glutDisplayFunc(RenderScene);
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "glew error:%s\n",glewGetErrorString(err));
        return 1;
    }
    SetupRC();
    glutMainLoop();
    return 0;
    
}
