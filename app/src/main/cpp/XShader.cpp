//
// Created by liuqikang on 2018/6/25.
//

#include "XShader.h"
#include <GLES2/gl2.h>
#include "XLog.h"

#define GET_STR(x) #x

// 顶点着色器
static const char* vertexShader = GET_STR(
        attribute vec4 aPosition;//顶点坐标
        attribute vec2 aTexCoord;//材质顶点坐标
        varying vec2 vTexCoord;//输出的材质坐标
        void main(){
            vTexCoord = vec2(aTexCoord.x, 1.0-aTexCoord.y);
            gl_Position = aPosition;
        }
);

// 片元着色器,软解码和部分X86硬解码
static const char* fragYUV420P = GET_STR(
        precision mediump float;    //精度
        varying vec2 vTexCoord;     //顶点着色器传递的坐标
        uniform sampler2D yTexture; //输入的材质（不透明灰度，单像素）
        uniform sampler2D uTexture;
        uniform sampler2D vTexture;
        void main(){
            vec3 yuv;
            vec3 rgb;
            yuv.r = texture2D(yTexture,vTexCoord).r;
            yuv.g = texture2D(uTexture,vTexCoord).r - 0.5;
            yuv.b = texture2D(vTexture,vTexCoord).r - 0.5;
            // yuv转rgb(矩阵乘法公式)
            rgb = mat3(1.0,     1.0,    1.0,
                       0.0,-0.39465,2.03211,
                       1.13983,-0.58060,0.0)*yuv;
            // 输出像素颜色
            gl_FragColor = vec4(rgb, 1.0);
        }
);

//片元着色器,硬解码
static const char *fragNV12 = GET_STR(
        precision mediump float;    //精度
        varying vec2 vTexCoord;     //顶点着色器传递的坐标
        uniform sampler2D yTexture; //输入的材质（不透明灰度，单像素）
        uniform sampler2D uvTexture;
        void main(){
            vec3 yuv;
            vec3 rgb;
            yuv.r = texture2D(yTexture,vTexCoord).r;
            yuv.g = texture2D(uvTexture,vTexCoord).r - 0.5;
            yuv.b = texture2D(uvTexture,vTexCoord).a - 0.5;
            rgb = mat3(1.0,     1.0,    1.0,
                       0.0,-0.39465,2.03211,
                       1.13983,-0.58060,0.0)*yuv;
            //输出像素颜色
            gl_FragColor = vec4(rgb,1.0);
        }
);

//片元着色器,硬解码
static const char *fragNV21 = GET_STR(
        precision mediump float;    //精度
        varying vec2 vTexCoord;     //顶点着色器传递的坐标
        uniform sampler2D yTexture; //输入的材质（不透明灰度，单像素）
        uniform sampler2D uvTexture;
        void main(){
            vec3 yuv;
            vec3 rgb;
            yuv.r = texture2D(yTexture,vTexCoord).r;
            yuv.g = texture2D(uvTexture,vTexCoord).a - 0.5;
            yuv.b = texture2D(uvTexture,vTexCoord).r - 0.5;
            rgb = mat3(1.0,     1.0,    1.0,
                       0.0,-0.39465,2.03211,
                       1.13983,-0.58060,0.0)*yuv;
            //输出像素颜色
            gl_FragColor = vec4(rgb,1.0);
        }
);

// 着色器初始化
GLuint InitShader(const char* code, GLint type)
{
    // 创建shader
    GLuint sh = glCreateShader(type);
    if (sh == 0)
    {
        XLOGE("glCreateShader failed");
        return 0;
    }
    // 加载shader
    glShaderSource(sh,
                   1,// shader数量
                   &code,//shader代码
                   0);//shader长度
    // 编译shader
    glCompileShader(sh);

    // 获取编译情况
    GLint status;
    glGetShaderiv(sh, GL_COMPILE_STATUS, &status);
    if (status == 0)
    {
        XLOGE("glCompileShader failed");
        return 0;
    }
    XLOGI("glCompileShader success");
    return sh;
}

bool XShader::Init(XShaderType type)
{
    XLOGI("XShader Init() Start");

    ////////////////////////////////////////////////////
    //顶点和片元shader初始化
    vsh = InitShader(vertexShader, GL_VERTEX_SHADER);

    XLOGI("InitShader GL_VERTEX_SHADER success! %d",type);

    switch (type)
    {
        case XSHADER_YUV420P:
        {
            XLOGI("InitShader yuv420");
            //yuv420
            fsh = InitShader(fragYUV420P, GL_FRAGMENT_SHADER);
            break;
        }
        case XSHADER_NV12:
        {
            XLOGI("InitShader NV12");
            fsh = InitShader(fragNV12, GL_FRAGMENT_SHADER);
            break;
        }
        case XSHADER_NV21:
        {
            XLOGI("InitShader NV21");
            fsh = InitShader(fragNV21, GL_FRAGMENT_SHADER);
            break;
        }
        default:
            XLOGE("XShader::Init unknow shader type %d",type);
            break;
    }

    if (fsh == 0)
    {
        XLOGE("XShader::Init failed");
        return false;
    }

    ////////////////////////////////////////////////////
    // 创建渲染程序
    program = glCreateProgram();
    if (program == 0)
    {
        XLOGE("glCreateProgram failed");
        return false;
    }
    //绑定shader到渲染程序
    glAttachShader(program, vsh);
    glAttachShader(program, fsh);
    //链接
    glLinkProgram(program);
    GLint status = 0;
    glGetProgramiv(program,GL_LINK_STATUS,&status);
    if (status != GL_TRUE)
    {
        XLOGE("glLinkProgram failed");
        return false;
    }
    glUseProgram(program);
    XLOGI("glLinkProgram success");
    ////////////////////////////////////////////////////////

    //加入三维顶点数据 两个三角形组成正方形
    static float vers[] = {
            1.0f,-1.0f,0.0f,
            -1.0f,-1.0f,0.0f,
            1.0f,1.0f,0.0f,
            -1.0f,1.0f,0.0f,
    };
    GLuint apos = (GLuint)glGetAttribLocation(program,"aPosition");
    glEnableVertexAttribArray(apos);
    //传递顶点
    glVertexAttribPointer(apos,3,GL_FLOAT,GL_FALSE,12,vers);

    // 加入材质坐标数据
    static float txts[] = {
            1.0f,0.0f,
            0.0f,0.0f,
            1.0f,1.0f,
            0.0f,1.0f,
    };
    GLuint atex = (GLuint)glGetAttribLocation(program,"aTexCoord");
    glEnableVertexAttribArray(atex);
    glVertexAttribPointer(atex,2,GL_FLOAT,GL_FALSE,8,txts);

    //材质纹理初始化
    //设置纹理层
    glUniform1i(glGetUniformLocation(program, "yTexture"),0);//对于纹理1层
    switch (type)
    {
        case XSHADER_YUV420P:
        {
            glUniform1i(glGetUniformLocation(program, "uTexture"),1);//对于纹理2层
            glUniform1i(glGetUniformLocation(program, "vTexture"),2);//对于纹理3层
            break;
        }
        case XSHADER_NV12:
        case XSHADER_NV21:
        {
            glUniform1i(glGetUniformLocation(program, "uvTexture"),1);//对于纹理2层
            break;
        }
        default:
            break;
    }

    XLOGI("初始化 XShader Init() 成功");
    return true;
}

void XShader::GetTexture(unsigned int index, int width, int height, unsigned char *buf,bool isa)
{
    unsigned int format =GL_LUMINANCE;
    if(isa)
        format = GL_LUMINANCE_ALPHA;
    if (txts[index] == 0)
    {
        // 材质初始化
        glGenTextures(1,&txts[index]);

        //设置纹理属性
        glBindTexture(GL_TEXTURE_2D, txts[index]);
        //缩小过滤器
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        //设置文理的格式和大小
        glTexImage2D(GL_TEXTURE_2D,
                    0,                 //细节基本 默认0
                     format,     //gpu内部格式 亮度、灰度图
                    width,height,      //拉伸到全屏
                    0,                 //边框
                     format,     //数据的像素格式 亮度、灰度图 要与上面一致
                    GL_UNSIGNED_BYTE, //像素的数据类型
                    NULL                //纹理的数据
        );
    }

    // 激活第一层，绑定到创建的opengl纹理
    glActiveTexture(GL_TEXTURE0+index);
    glBindTexture(GL_TEXTURE_2D, txts[index]);
    // 替换纹理内存
    glTexSubImage2D(GL_TEXTURE_2D,0,0,0,width,height,format,GL_UNSIGNED_BYTE,buf);
}

void XShader::Draw()
{
    if (!program)
    {
        return;
    }
    //三维绘制
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
