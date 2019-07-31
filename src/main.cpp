#include "main.h"
#include "timer.h"
#include "ball.h"
#include "brick.h"
#include "coins.h"
#include "firebeam.h"
#include "magnet.h"
#include "ring.h"
#include "rect.h"
#include "boom.h"
#include "dragon.h"
#include "life.h"

#define mp make_pair
#define ff first
#define ss second

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/
Ball ball1;
Brick B1;
int en=2;
int inv=0;
bool on_ring=0;
Ring outer,inner,outer2,inner2;
int tpr=0;
double phi=-1000;
double fric=0.001;
Brick B2;
int tgap=0;
vector<Dragon> D;
vector<Coins> IceBalls;
int score=0;
bool Protec=0;
int Shiel_on_time=0;
double curr=0;
vector<Coins> C;
vector<Rect> Ten,Unit;
vector<Rect> Beams;
Coins Sheild,Lf1,Os;
vector<Life> Hrt;
Boom E3;
vector< Coins > L;
vector< Coins> Finner,Pivot;
vector<Firebeam> F;
vector<Coins> Balloon;
vector<Magnet> Mag;
string digDisplay[10];
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    glm::vec3 eye ( cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    // Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    Matrices.view = glm::lookAt(glm::vec3(ball1.position.x, 0, 3), glm::vec3(ball1.position.x, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    outer.draw(VP);
    inner.draw(VP);
    for(int i=0;i<C.size();i++)
        C[i].draw(VP);
    for(auto fb:F)
        fb.draw(VP);
    for(int i=0;i<Balloon.size();i++)
        Balloon[i].draw(VP);
    for(int i=0;i<L.size();i++)
        L[i].draw(VP);
    for(int i=0;i<L.size();i++)
        Finner[i].draw(VP);
    for(int i=0;i<Pivot.size();i++)
     Pivot[i].draw(VP);
    for(int i=0;i<Mag.size();i++)
        Mag[i].draw(VP);
    for(int i=0;i<IceBalls.size();i++)
        IceBalls[i].draw(VP);
    for(int i=0;i<Hrt.size();i++)
        Hrt[i].draw(VP);
    B1.draw(VP);
    B2.draw(VP);
    E3.draw(VP);
    int x=score/10;
    int y=score%10;
    for(int i=0;i<7;i++)
        if(digDisplay[x][i]=='1')
            Ten[i].draw(VP);
    for(int i=0;i<7;i++)
        if(digDisplay[y][i]=='1')
            Unit[i].draw(VP);
    for(int i=0;i<D.size();i++)
        D[i].draw(VP);
    if(!Protec)
        Sheild.draw(VP);
    Lf1.draw(VP);
    if(Protec && Shiel_on_time<=290)
    {
        Coins os=Coins(ball1.position.x,ball1.position.y,0,0,0,COLOR_BACKGROUND,0,0.9,0.9);
        Coins os2=Coins(ball1.position.x,ball1.position.y,0,0,0,COLOR_SH,0,1,1);
        os2.draw(VP);
        os.draw(VP);
    }
    ball1.draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up    = glfwGetKey(window, GLFW_KEY_UP);
    int shoot = glfwGetKey(window, GLFW_KEY_A);
    tpr++;
    if (left)
    {
        if(!on_ring)
           ball1.speedx=-0.03;
        else
            phi-=0.03;
    }
    if(right)
    {
        if(!on_ring)
            ball1.speedx=0.03;
        else
            phi+=0.02;
    }
    if(ball1.position.y<=-2)
    {
        if(ball1.speedx>0.02)
            ball1.speedx-=fric;
        else
            ball1.speedx+=fric;
    }
    if(up)
    {
        ball1.speedy+=0.01;
        ball1.acc=-0.001;
        ball1.fft=1;
    }
    else
        ball1.fft=0;
    if(shoot && curr>tgap+30)
    {
        tgap=0;
        curr=0;
        Coins cn=Coins(ball1.position.x,ball1.position.y,0.03,0.1,-0.001,COLOR_BLACK,1);
        Balloon.push_back(cn);
    }
}
int igap=0,icurr=0;
void ThrowIce()
{
    icurr++;
    for(int i=0;i<D.size();i++)
    {
        float Dist=D[i].cx-ball1.position.x;
        if(abs(Dist)<=5 && icurr>igap+200)
        {
            igap=icurr;
            IceBalls.push_back(Coins(D[i].cx,D[i].cy,-0.04,0.01,-0.001,COLOR_ICEBALL,1));
        }
    }
}
int fl=0;
void tick_elements() {
    if(!on_ring)
    {
        ball1.tick();
    }
    else
    {
        phi+=0.01;
        ball1.position.x=outer.cx+outer.r*sin(phi);
        ball1.position.y=outer.cy-outer.r*cos(phi);
    }
    if(ball1.position.x>=22 && fl==0)
    {
        fl=1;
        E3=Boom(30,3,0,COLOR_FIRE);
    }
    if(ball1.position.x>=50 && fl==1)
    {
        fl=2;
        E3=Boom(58,3,0,COLOR_FIRE);
    }
    for(int i=0;i<F.size();i++)
    F[i].tick();
    for(int i=0;i<C.size();i++)
        C[i].tick();
    for(int i=0;i<Balloon.size();i++)
    Balloon[i].tick();
  
    if(Sheild.cy<=-2.2)
    {
        Sheild.cy=-2;
        Sheild.speedy=0.1;
    }
    if(Lf1.cy<=-2.2)
    {
        Lf1.cy=-2;
        Lf1.speedy=0.1;
    }
    for(int i=0;i<IceBalls.size();i++)
    {
        if(IceBalls[i].cy<=-2.2)
        {
            IceBalls[i].cy=-2;
            IceBalls[i].speedy=0.08;
        }
    }
    Sheild.tick();
    Lf1.tick();
    E3.tick();
    for(int i=0;i<D.size();i++)
    D[i].tick();
    for(int i=0;i<IceBalls.size();i++)
    IceBalls[i].tick();
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    // scaleF=1;
    ball1       = Ball(-2, -2.5, 0.02,0, 0,COLOR_RED);
    B1          = Brick(COLOR_TILE1,0);
    B2          = Brick(COLOR_TILE2,1);
    outer       = Ring(60,1,3,COLOR_RING);
    inner       = Ring(60,1,2.7,COLOR_BACKGROUND);
     outer2       = Ring(95,1,3,COLOR_RING);
    inner2      = Ring(95,1,2.7,COLOR_BACKGROUND);
    digDisplay[0]="1111110";
    digDisplay[1]="0110000";
    digDisplay[2]="1011011";
    digDisplay[3]="1111001";
    digDisplay[4]="0110101";
    digDisplay[5]="1101101";
    digDisplay[6]="1101111";
    digDisplay[7]="0111001";
    digDisplay[8]="1111111";
    digDisplay[9]="1111101";
    double prv=-1;
   for(int i=0;i<20;i++)
   {
       float x=prv+4+rand()%7;
       prv=x;
       if(x>=23 && x<=37 )
        continue;
       if(x>=53 && x<=67)
        continue;
       double y=2.5;
       for(double j=0;j<0.5;j+=0.05)
         F.push_back(Firebeam(x,y-j,1,0.01,COLOR_FIRE));
        vector<pair<float,float> > seg;
        seg.push_back(mp(x-1.2,y-1.2));
        seg.push_back(mp(x-0.2,y-1.2));
        seg.push_back(mp(x-1.2,y+0.2));
        seg.push_back(mp(x-0.2,y+0.2));
        Beams.push_back(Rect(seg,0,0,COLOR_BLACK,0.01));
        seg.clear();
        seg.push_back(mp(x-1.2,y-1.2));
        seg.push_back(mp(x-0.2,y-1.2));
        seg.push_back(mp(x-1.2,y+0.2));
        seg.push_back(mp(x-0.2,y+0.2));
        Beams.push_back(Rect(seg,1,0,COLOR_BLACK,0.01));
   }
   prv=-1;
   for(int i=0;i<1000;i++)
   {
       double x=prv+2.5+rand()%5;
       double y=rand()%3+1;
        C.push_back(Coins(x,y,0,0,0,COLOR_COIN,1));
        double a=rand()%2;
        if(a)
        C.push_back(Coins(x,y,0,0,0,COLOR_COIN2,1,0.35,0.35,1000));
        prv=x;
   }

   prv=-1;
   Sheild = Coins(-5,-2,0.04,0.1,-0.001,COLOR_BLACK,1,0.5,0.5,6);
   Lf1 = Coins(-20,-2,0.06,0.1,-0.001,COLOR_RED,1,0.5,0.5,6);
   
   for(int j=0;j<10;j++)
    {
       double x=prv+9+rand()%7; 
       prv=x;
       if(x>=23 && x<=37)
        continue;
       if(x>=53 && x<=67)
        continue;
       double y=2.5;
       double i=0;
       double Pi=3.1415;
       double theta=rand()%19;
       theta=(Pi*theta)/18;
       double r=2;
       L.push_back(Coins(x,y,0,0,0,COLOR_FIRE,0,0.35,0.40));
       Finner.push_back(Coins(x,y,0,0,0,COLOR_COIN,0,0.25,0.30));
       Pivot.push_back(Coins(x,y,0,0,0,COLOR_BLACK,0,0.20,0.20));
       for(double i=0.1;i<r;i+=0.2)
       {
            L.push_back(Coins(x+i*cos(theta),y+i*sin(theta),0,0,0,COLOR_FIRE,0,0.2,0.23));  
            Finner.push_back(Coins(x+i*cos(theta),y+i*sin(theta),0,0,0,COLOR_COIN,0,0.12,0.15));  
       }
       L.push_back(Coins(x+r*cos(theta),y+r*sin(theta),0,0,0,COLOR_FIRE,0,0.35,0.40));      
       Finner.push_back(Coins(x+r*cos(theta),y+r*sin(theta),0,0,0,COLOR_COIN,0,0.25,0.30));             
       Pivot.push_back(Coins(x+r*cos(theta),y+r*sin(theta),0,0,0,COLOR_BLACK,0,0.20,0.20));             
    }
    prv=0;
    Mag.push_back(Magnet(30,2,COLOR_RED,0));
    Mag.push_back(Magnet(75,2,COLOR_RED,0));
    E3=Boom(8,3,0,COLOR_FIRE);
    D.push_back(Dragon(13,COLOR_TILE2));
    D.push_back(Dragon(43,COLOR_TILE2));
    // Fl          = Floor(COLOR_BLACK)
    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLS outerL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}



bounding_box_t get_bounding_box_circle(Coins Cn)
{
    bounding_box_t a;
    a.x=Cn.position.x;
    a.y=Cn.position.y;
    a.width=a.height=2*Cn.rad;
    return a;
}

bounding_box_t get_bounding_box_boom(Boom B)
{
    bounding_box_t a;
    a.x=B.cx;
    a.y=B.cy;
    a.width=a.height=2;
    return a;
}

bounding_box_t get_bounding_box(Ball B)
{
    bounding_box_t a;
    a.x=B.position.x;
    a.y=B.position.y;
    a.width=a.height=1;
    return a;
}

bounding_box_t get_bounding_box_beam(Firebeam B)
{
    bounding_box_t a;
    a.x=B.cx+(B.len)/2;
    a.y=B.cy+(B.wid)/2;
    a.width=B.len;a.height=B.wid;
    return a;
}

void CollectCoins()
{
    bounding_box_t a=get_bounding_box(ball1);
    int j=0;
    for(auto cn:C)
    {
        bounding_box_t b=get_bounding_box_circle(cn);
        if(detect_collision(a,b))
        {
            C.erase(C.begin()+j);
            score++;
        }
        else
            j++;
    }
}

void checkOnRing()
{
    float dist=sqrt(pow(outer.cx-ball1.position.x,2)+pow(outer.cy-ball1.position.y,2));
    if(abs(dist-outer.r)<=0.2 && outer.cy+1>=ball1.position.y)
    {
        on_ring=1;
        if(phi==-1000)
        {
            phi=atan((ball1.position.x-outer.cx)/(outer.cy-ball1.position.y));
            if(ball1.position.x<outer.cx && phi>0)
                phi*=-1;
            if(ball1.position.x>outer.cx && phi<0)
                phi*=-1;
        }
    }
    else
    {
        on_ring=0;
        phi=-1000;
    }
}


void CheckLife()
{
    if(en==-1)
    {
        cout<<"GAME OVER"<<endl;
        quit(window);
    }
    bounding_box_t a=get_bounding_box(ball1);
    if(inv>=100)
    {
    for(auto beam:F)
    {
        bounding_box_t b=get_bounding_box_beam(beam);
        if(detect_collision(a,b))
        {
            inv=0;
            en--;
            return;
            quit(window);
        }
    }
    for(auto cn:Finner)
    {
        bounding_box_t b=get_bounding_box_circle(cn);
        if(detect_collision(a,b))
        {
           inv=0;
            en--;
            return;
            quit(window);
        }
    }
    bounding_box_t b=get_bounding_box_boom(E3);
    if(detect_collision(a,b))
    {
        inv=0;
            en--;
            return;
        quit(window);
    }
    for(auto I:IceBalls)
    {
        bounding_box_t b=get_bounding_box_circle(I);
        if(detect_collision(a,b))
        {
            inv=0;
            en--;
            return;
            quit(window);
        }
    }
    }
    bounding_box_t b=get_bounding_box_circle(Sheild);
    if(detect_collision(a,b))
    {
        Protec=1;
    }
}
void getLife()
{
    bounding_box_t a=get_bounding_box(ball1);
    bounding_box_t  b=get_bounding_box_circle(Lf1);
    if(detect_collision(a,b))
    {
        en++;
        Lf1 = Coins(ball1.position.x-30,-2,0.06,0.1,-0.001,COLOR_RED,1,0.5,0.5,6);     
    }
}

void MagnetInfluence()
{
    ball1.accx=0;
    ball1.accym=0;
    for(int i=0;i<Mag.size();i++)
    {
        double a=1/(pow(ball1.position.x-Mag[i].cx,8)+600);
        if(ball1.position.x>Mag[i].cx)
            ball1.accx-=a;
        else
            ball1.accx+=a;
        if(ball1.position.y>Mag[i].cy)
            ball1.accym-=a;
        else
            ball1.accym+=a;
    }
}

void DestroyBeams()
{
    int j=0;
    for(auto beam:F)
    {
        bool f=0;
        for(auto cn:Balloon)
        {
            bounding_box_t a=get_bounding_box_circle(cn);
            bounding_box_t b=get_bounding_box_beam(beam);
            if(detect_collision(a,b))
            {
                F.erase(F.begin()+j);
                f=1;
                break;
            }
        }
        if(f==0)
            j++;
    }
}

void DestroyBalloon()
{
    for(int i=0;i<Balloon.size();i++)
    {
        if(Balloon[i].cy<=-3)
        {
            Balloon.erase(Balloon.begin()+i);
            i--;
        }
    }
    for(int i=0;i<IceBalls.size();i++)
    {
        if(IceBalls[i].cx+10<=ball1.position.x)
        {
            IceBalls.erase(IceBalls.begin()+i);
            i--;
        }
    }
}

void CalScore()
{
    Ten.clear();
    Unit.clear();
    vector<pair<float,float> > seg;
    seg.push_back(mp(0,0));
    seg.push_back(mp(0.3,0));
    seg.push_back(mp(0,0.01));
    seg.push_back(mp(0.3,0.01));
    Ten.push_back(Rect(seg,ball1.position.x+2.5,3.2,COLOR_BLACK,0.0f));
    Unit.push_back(Rect(seg,ball1.position.x+2.9,3.2,COLOR_BLACK,0.0f));
    seg.clear();
    seg.push_back(mp(0.3,0));
    seg.push_back(mp(0.31,0));
    seg.push_back(mp(0.3,0.21));
    seg.push_back(mp(0.31,0.21));
    Ten.push_back(Rect(seg,ball1.position.x+2.5,3.2,COLOR_BLACK,0.0f));
    Unit.push_back(Rect(seg,ball1.position.x+2.9,3.2,COLOR_BLACK,0.0f));
    seg.clear();
    seg.push_back(mp(0.3,0.2));
    seg.push_back(mp(0.31,0.2));
    seg.push_back(mp(0.3,0.41));
    seg.push_back(mp(0.31,0.41));
    Ten.push_back(Rect(seg,ball1.position.x+2.5,3.2,COLOR_BLACK,0.0f));
    Unit.push_back(Rect(seg,ball1.position.x+2.9,3.2,COLOR_BLACK,0.0f));
    seg.clear();
     seg.push_back(mp(0,0.4));
    seg.push_back(mp(0.3,0.4));
    seg.push_back(mp(0,0.41));
    seg.push_back(mp(0.3,0.41));
    Ten.push_back(Rect(seg,ball1.position.x+2.5,3.2,COLOR_BLACK,0.0f));
    Unit.push_back(Rect(seg,ball1.position.x+2.9,3.2,COLOR_BLACK,0.0f));
    seg.clear();
     seg.push_back(mp(0,0.2));
    seg.push_back(mp(0.01,0.2));
    seg.push_back(mp(0,0.4));
    seg.push_back(mp(0.01,0.4));
    Ten.push_back(Rect(seg,ball1.position.x+2.5,3.2,COLOR_BLACK,0.0f));
    Unit.push_back(Rect(seg,ball1.position.x+2.9,3.2,COLOR_BLACK,0.0f));
    seg.clear();
     seg.push_back(mp(0,0));
    seg.push_back(mp(0.01,0));
    seg.push_back(mp(0,0.21));
    seg.push_back(mp(0.01,0.21));
    Ten.push_back(Rect(seg,ball1.position.x+2.5,3.2,COLOR_BLACK,0.0f));
    Unit.push_back(Rect(seg,ball1.position.x+2.9,3.2,COLOR_BLACK,0.0f));
    seg.clear();
     seg.push_back(mp(0,0.2));
    seg.push_back(mp(0.3,0.2));
    seg.push_back(mp(0,0.21));
    seg.push_back(mp(0.3,0.21));
    Ten.push_back(Rect(seg,ball1.position.x+2.5,3.2,COLOR_BLACK,0.0f));
    Unit.push_back(Rect(seg,ball1.position.x+2.9,3.2,COLOR_BLACK,0.0f));
    seg.clear();
    Hrt.clear();
    for(int i=0;i<en;i++)
       Hrt.push_back(Life(ball1.position.x-3.5+0.02+i,3.4));
}

Ball Boundary(Ball B)
{
    if(B.position.x >=3 && B.speedx>0)
        B.speedx=-0.01;
    if(B.position.y>=3 && B.speedy>0)
        B.speedy=-0.01;
    if(B.position.x<=-3 && B.speedx<0)
        B.speedx=0.01;
    if(B.position.y<=-3 && B.speedy<0)
        B.speedy=0.01;
    return B;
}

int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers
        if (t60.processTick()) {
            // 60 fps
            curr++;
            inv++;
            // screen_zoom=scaleF;
            // OpenGL Draw commands
            CalScore();
            checkOnRing();
            // cout<<on_ring<<endl;
            CollectCoins();
            DestroyBeams();
            MagnetInfluence();
            ThrowIce();
            getLife();
            if(Shiel_on_time==300)
            {
                Protec=0;
                Shiel_on_time=0;
                Sheild = Coins(ball1.position.x-10,-2,0.04,0.1,-0.001,COLOR_BLACK,1,0.5,0.5,6);
            }
            if(!Protec && !on_ring)
            {
                CheckLife();
            }
            else
                Shiel_on_time++;
            DestroyBalloon();
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
