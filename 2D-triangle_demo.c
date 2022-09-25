/**
 * @file test.c
 * @author 0x15c l12212788889@live.com
 * @brief A 2-D render engine demo for commandline, which **should** draw a triangle
 * To run this demo, you should set terminal window buffer to column 80 and rows 30
 * @version 0.1
 * @date 2022-09-24
 * 
 * @copyright Nolicense
 * 
 */
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<windows.h>
#include<string.h>
#define CON_COLS 80//set by hand in windows terminal
#define CON_ROWS 30
#define PI 3.1416
#define LINE_CRIT -0.99
#define DEFAULT_FRESH_RATE 5
typedef struct vector2D
{
    float x;
    float y;
}vector2D;//2-Dimensional vector typedef
typedef struct pixel2D
{
    int x;
    int y;
}pixel2D;//2-Dimensional pixel plane, i.e. commandline window coordinate system.
typedef struct delta
{
    vector2D ptA;
    vector2D ptB;
    vector2D ptC;
}delta;//struct to hold a triangle
typedef struct dline_vldt
{
    vector2D ptP;
    vector2D pt1;
    vector2D pt2;
}dline_vldt;

int render_thread(dline_vldt *triangle_input);
void coord_rotate(vector2D *coord, float theta);//rotating makes it animated
int draw_vldt(dline_vldt *input);//evaluating if a pixel shoubld be filled
float dist_eval(vector2D ptA, vector2D ptB);
void align_coord(pixel2D *to_be_ali, vector2D *aligned);//align screen coordination into real plane

int main(int* argc, char* argv[1])//optional arguments support, you can set your own fps(just for fun).
{
    int refresh_rate = DEFAULT_FRESH_RATE;
    if (argv[1] != NULL)
    {
        refresh_rate = atoi(argv[1]);
    }
    pixel2D plain_pt={0,0};//the point need to be validate, pixel by pixel
    vector2D coord_pt={0.0f,0.0f};
    float alpha = PI/90;
    delta test_triangle={
        .ptA = {-0.2f , -0.2f},
        .ptB = {-0.2f , 0.2f},
        .ptC = {0.0f  , 0.3f},
    };
    dline_vldt validate;
    int crit=0;
    while(1)
    {
        coord_rotate(&test_triangle.ptA,alpha);
        coord_rotate(&test_triangle.ptB,alpha);
        coord_rotate(&test_triangle.ptC,alpha);
        //debug info
        printf("fps=%d,ptA=(%3.2f,%3.2f),ptB=(%3.2f,%3.2f),ptC=(%3.2f,%3.2f)\n",refresh_rate,test_triangle.ptA.x,test_triangle.ptA.y,test_triangle.ptB.x,test_triangle.ptB.y,test_triangle.ptC.x,test_triangle.ptC.y);
            
        //fream drawing begin, scanning from left top to right bottom
        for (plain_pt.y=1;plain_pt.y<=CON_ROWS-1;plain_pt.y++)
        {
            for(plain_pt.x=1;plain_pt.x<=CON_COLS;plain_pt.x++)
            {//no idea making those junk elegent
                crit=0;
                align_coord(&plain_pt,&validate.ptP);
                validate.pt1 = test_triangle.ptA;
                validate.pt2 = test_triangle.ptB;
                crit = crit+render_thread(&validate);
                //
                validate.pt1 = test_triangle.ptA;
                validate.pt2 = test_triangle.ptC;
                crit = crit+render_thread(&validate);
                //
                validate.pt1 = test_triangle.ptB;
                validate.pt2 = test_triangle.ptC;
                crit = crit+render_thread(&validate);
                if(crit==0){putchar(' ');}
                else putchar('.');
            }
        }
        //end drawing
        Sleep(1000/refresh_rate);//Throushold
    }

}
int render_thread(dline_vldt *triangle_input)
{
    if (draw_vldt(triangle_input) == 1)
        return 1;
    else
        return 0;
}
void coord_rotate(vector2D *coord, float theta)
{
    float x = coord->x;
    float y = coord->y;
    coord->x = x*cos(theta)-y*sin(theta);
    coord->y = x*sin(theta)+y*cos(theta);
}
int draw_vldt(dline_vldt *input)
{
    float dist2_12,dist2_1p,dist2_2p;
    float cos_triangle_ang;
    dist2_12 = dist_eval(input->pt1,input->pt2);
    dist2_1p = dist_eval(input->pt1,input->ptP);
    dist2_2p = dist_eval(input->pt2,input->ptP);
    cos_triangle_ang = (dist2_1p+dist2_2p-dist2_12)/(sqrt(dist2_1p*dist2_2p)*2);
    //by the criteria of cos(P), evaluate if should fill pixel a line
    //if ((cos_triangle_ang <= 0) && (cos_triangle_ang > LINE_CRIT))
    if(cos_triangle_ang<LINE_CRIT)
    {
        return 1;
    }
    else
    return 0;
}
float dist_eval(vector2D ptA, vector2D ptB)
{
    float dist2;
    dist2 = (ptA.x-ptB.x)*(ptA.x-ptB.x)+(ptA.y-ptB.y)*(ptA.y-ptB.y);
    return dist2;
}
void align_coord(pixel2D *to_be_ali, vector2D *aligned)
{
    aligned->x = -0.5f+(float)to_be_ali->x/(float)CON_COLS;
    aligned->y = 0.5f-(float)to_be_ali->y/(float)CON_ROWS;
    //printf("%f",aligned->x);
}