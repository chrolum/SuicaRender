#include "lineDrawer.h"


// 以x轴为基础，按照直线方程算出t值 算出对于的y点
// 这种方法有一个问题，在像素级别上，在直线比较陡峭的时候, 一个x值会对应多个y值得，但是这个方法只会计算出一
// 机会造成直线不连续的现象
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
    for (int x = x0; x <= x1; x++)
    {
        float t = (x-x0) / (float)(x1 - x0);
        int y = y0 * (1.0f - t) + y1 * t;
        image.set(x, y, color);
    }
}


// 可以正确地绘制线段，不再
void line2(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
    bool steep = false;
    if (std::abs(x0-x1) < std::abs(y0-y1)) // 斜率大于1，改用y轴去循环
    {
        steep = true;
    }

    if (steep)
    {
        for (int y = y0; y <= y1; y++)
        {
            float t = (y-y0) / (float)(y1 - y0);
            int x = x0 * (1.0f - t) + x1 * t;
            image.set(x, y, color);
        }
    }
    else
    {
        for (int x = x0; x <= x1; x++)
        {
            float t = (x-x0) / (float)(x1 - x0); //有大量的除法 不效率
            int y = y0 * (1.0f - t) + y1 * t;
            image.set(x, y, color);
        }
    }
}

// Opt
void line3(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1))
    {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

    if (x0 > x1)
    {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;

    float derror = std::abs(dy / float(dx));
    float error = 0;

    int y = y0;
    for (int x = x0; x <= x1; x++)
    {
        if (steep)
        {
            image.set(y, x, color);
        }
        else
        {
            image.set(x, y, color);
        }
        error += derror;
        if (error > 0.5)
        {
            y += (y1 > y0 ? 1 : -1);
            error -= 1.0;
        }
    }
}

// more opt
void line4(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) { 
    bool steep = false; 
    if (std::abs(x0-x1)<std::abs(y0-y1)) { 
        std::swap(x0, y0); 
        std::swap(x1, y1); 
        steep = true; 
    } 
    if (x0>x1) { 
        std::swap(x0, x1); 
        std::swap(y0, y1); 
    } 
    int dx = x1-x0; 
    int dy = y1-y0; 
    int derror2 = std::abs(dy)*2; 
    int error2 = 0; 
    int y = y0; 
    for (int x=x0; x<=x1; x++) { 
        if (steep) { 
            image.set(y, x, color); 
        } else { 
            image.set(x, y, color); 
        } 
        error2 += derror2; 
        if (error2 > dx) { 
            y += (y1>y0?1:-1); 
            error2 -= dx*2; 
        } 
    } 
} 


