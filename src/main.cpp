#include "main.h"
#include "timer.h"
#include "ball.h"
#include "enemy.h"
#include "coin.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
**************************/

Ball ball;
vector<Enemy> e;
vector<Enemy> magnet;
vector<Enemy> ring;
vector<Enemy> beam;
vector<Enemy> ray;
vector<Enemy> boomer;
vector<Enemy> dragon;
vector<Coin> c;
vector<Coin> ballon;
vector<Coin> power;
vector<Coin> attrac;
vector<Coin> shot;


int magnet_on=0;
int ring_on=0;
int score=0;
int shoot=1;
int count=0;
int attraction=0;
int life=5;
int width  = 1900;
int height = 1600;
int dragon_alive = 0;
int dragon_kill = 0;
int level=1;
void detect_collision(Ball a);
char name[100],display[100];

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 90;

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
    glm::vec3 eye ( 5*cos(camera_rotation_angle*M_PI/180.0f), 0, 5*sin(camera_rotation_angle*M_PI/180.0f) );
    // Target - Where is the camera looking at.  Don't change unless you are sure!!
    glm::vec3 target (0, 0, 0);
    // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    glm::vec3 up (0, 1, 0);

    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    for(int i=0;i<c.size();i++)
	    c[i].draw(VP);
    for(int i=0;i<e.size();i++)
	    e[i].draw(VP);
    for(int i=0;i<magnet.size();i++)
        magnet[i].draw(VP);
    for(int i=0;i<ring.size();i++)
        ring[i].draw(VP);
    for(int i=0;i<beam.size();i++)
        beam[i].draw(VP);
    for(int i=0;i<ray.size();i++)
        ray[i].draw(VP);
    for(int i=0;i<boomer.size();i++)
        boomer[i].draw(VP);
    for(int i=0;i<power.size();i++)
        power[i].draw(VP);
    for(int i=0;i<attrac.size();i++)
        attrac[i].draw(VP);
	for(int i=0;i<ballon.size();i++)
        ballon[i].draw(VP);
    for(int i=0;i<dragon.size();i++)
        dragon[i].draw(VP);
    for(int i=0;i<shot.size();i++)
        shot[i].draw(VP);
    ball.draw(VP);
    e[0].draw(VP);
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    
    if(space && shoot==1)
    {
    	shoot=0;
    	ballon.push_back(Coin(ball.position.x,ball.position.y,COLOR_SKYBLUE,1));
    }
    if(left && up)
    	ball.tick(5);
    else if(right && up)
    	ball.tick(6);
    else if (left)
    	ball.tick(1);
    else if(right)
    	ball.tick(2);
    else if(up)
    	ball.tick(3);
    else if(down)
    	ball.tick(7);
    else if(!up && magnet_on==0 && ring_on==0)
    	ball.tick(4);
}

void tick_elements() {
    
    for(int i=1;i<e.size();i++)
	    e[i].tick();

    for(int i=0;i<c.size();i++)
		if(attraction==0 || (c[i].position.x >= 3 && c[i].position.x <= -3) )
		    c[i].tick();

	for(int i=0;i<shot.size();i++)
	    shot[i].fire();

    for(int i=0;i<ballon.size();i++)
	    ballon[i].tick2();

	for(int i=0;i<boomer.size();i++)
	    boomer[i].boom();

	for(int i=0;i<dragon.size();i++)
	    dragon[i].dragon();

	for(int i=0;i<power.size();i++)
	    power[i].powerup();
	for(int i=0;i<attrac.size();i++)
	    attrac[i].powerup();

	if(attraction==1)
		for(int i=0;i<c.size();i++)
		{
			if(c[i].position.x > -3.9)
			{
				if(ball.position.y - c[i].position.y > 0.05)
				    c[i].position.y += c[i].speed/3;
				else
		   			c[i].position.y -= c[i].speed/3;

				if(ball.position.x - c[i].position.x > 0.05)
				    c[i].position.x += c[i].speed/2;
				else
		    		c[i].position.x -= c[i].speed/2;
			}
		}

	if(ring_on==1)
	{
		ball.ring(ring[0].position.x,ring[0].position.y);
		if(ball.position.x - ring[0].position.x > 1.1 )
			ring_on=0;
		if(ring[0].position.x - ball.position.x > 1.1 )
			ring_on=0;
	}
	else if(magnet_on==1)
		ball.magnet(magnet[0].position.x,magnet[0].position.y);

    for(int i=0;i<c.size();i++)
    	if(c[i].position.x<-12)
    		c.erase(c.begin()+i);

    for(int i=1;i<e.size();i++)
    	if(e[i].position.x<-12)
    		e.erase(e.begin()+i);

    for(int i=0;i<power.size();i++)
    	if(power[i].position.x<-12)
    		power.erase(power.begin()+i);

    for(int i=0;i<shot.size();i++)
    	if(shot[i].position.x<-12)
    		shot.erase(shot.begin()+i);

    for(int i=0;i<ballon.size();i++)
        if(ballon[i].position.x>10)
            ballon.erase(ballon.begin()+i);

    for(int i=0;i<boomer.size();i++)
        if(boomer[i].position.x>15)
            boomer.erase(boomer.begin()+i);
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
	e.clear();
    c.clear();
    magnet.clear();
    ring.clear();
    ballon.clear();
    beam.clear();
    ray.clear();
    boomer.clear();
    power.clear();
    attrac.clear();
    dragon.clear();
    shot.clear();
    count=0;
    magnet_on=0;
    dragon_alive = 0;
    dragon_kill = 0;
    ring_on=0;
    attraction=0;
    ball = Ball(-3, -2.9, COLOR_PINK);
	e.push_back(Enemy(0,-3.2, COLOR_GREEN,30));

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth (1.0f);
    sprintf(display,"WELCOME  %s           YOUR SCORE : %d        YOUR LIVES : %d       LEVEL : %d",name,score,life,level);
    glfwSetWindowTitle(window,display);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    // cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    // cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    // cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    // cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}

void dead()
{
	if(ring_on==1)
		return;

	life--;
	if(life==0)
	{
		printf(" ___   _   __  _______    ___ _   _________\n");
        printf("/  _| /_\\ |  \\/  | __|   / _ \\ \\ / / __| _ \\\n");
        printf("| ( |/ _ \\| |\\/| | _|    | () \\ V /| _||   /\n");
        printf("\\___/_/ \\_\\_|  |_|___|   \\___/ \\_/ |___|_|_\\\n");
        printf("THANKS FOR PLAYING %s\n",name);
        printf("YOU COMPLETED %d levels\n",level-1);
		printf("HOPE YOU ENJOYED\nYOUR FINAL SCORE - %d\n",score);
		quit(window);
	}
	else
		initGL (window, width, height);
}

int main(int argc, char **argv) {
    srand(time(0));
    cout<<"WELCOME!!\n";
    cout<<"PLEASE ENTER YOUR NAME!!\n";
    cin>>name;

    window = initGLFW(width, height);

    initGL (window, width, height);
    int beamtime=0;
    int magtime=0;
    int ringtime=0;
    int attractime=0;
    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
        	if(dragon_alive==0){
        	//coins
        	if(count%10==0)
        	{
				if(rand()%10==0)
				    c.push_back(Coin(7,rand()%6-3, COLOR_GOLD,1));
				else
			    	c.push_back(Coin(7,rand()%6-3, COLOR_ORANGE,2));	
        	}
        	//coins

        	//powerup
        	if((count-10)%2000==0)
        	{
        		if(rand()%2==0)
		    		power.push_back(Coin(10,rand()%6-3, COLOR_BACKGROUND,3));
		    	else
		    	{
		    		attrac.push_back(Coin(10,rand()%6-3, COLOR_SILVER,3));
		    		attractime=rand()%3+9;
		    	}
        	}
        	//powerup
        	
        	//fire
        	if(count%155==0)
        	{
        		int x=rand()%3;
        		if(x==0)
	    			e.push_back(Enemy(15,rand()%6-3, COLOR_RED,1));
        		else if(x==1)
	    			e.push_back(Enemy(15,rand()%4-1.5, COLOR_RED,2));
				else if(x==2)
				{
			    	e.push_back(Enemy(15,3, COLOR_RED,11));
			    	e.push_back(Enemy(15,3, COLOR_RED,12));
				}
        	}
        	//fire

        	//magnet
            if((count+301)%1500==0)
            {
            	magnet_on=1;
            	magtime=rand()%3+5;
                magnet.push_back(Enemy(rand()%5-2,rand()%5-2,COLOR_RED,4));
            }
            //magnet

            //ring
            if((count+950)%1500==0)
            {
            	ringtime=rand()%3+8;
                ring.push_back(Enemy(rand()%3-1,1,COLOR_BROWN,9));
            }
            //ring

			//beam code
            if((count+61)%1000==0)
            {
            	int x=rand()%5-2;
            	beam.push_back(Enemy(-3.5,x,COLOR_BLUE,6));
            	beam.push_back(Enemy(-3.5,x-1,COLOR_BLUE,6));
            }

            if((count+61)%1000==60)
            {
            	ray.push_back(Enemy(-3.5,beam[beam.size()-1].position.y,COLOR_RED,7));
            	ray.push_back(Enemy(-3.5,beam[beam.size()-2].position.y,COLOR_RED,7));
            	beamtime=rand()%3+2;
            }
            //beam code

    		//boomerang
    		if(count%450==0)
			    boomer.push_back(Enemy(13, 4, COLOR_BROWN,8));
    		//boomerang
		}

			if((count-10)%2000==60*attractime)
        	{
        		attraction=0;
        		attrac.clear();
        	}
			if((count+61)%1000==60*(beamtime+1))
            {
            	ray.clear();
            	beam.clear();
            }
            if((count+1001)%1500==60*ringtime)
            {
            	ring_on=0;
            	ring.clear();
            	ringtime=0;
            }
            if((count+301)%1500==60*magtime)
            {
            	magnet_on=0;
            	magnet.clear();
            }
			if(count%20==0)
				shoot=1;

    		//dragon
    		if((count+1)%4100==0)
    		{
			    dragon.push_back(Enemy(3, 2, COLOR_ORANGE,10));
			    dragon_alive=1;
			    dragon_kill=5;
    		}

    		if(dragon_alive==1 && count%60==0 && (count+1)%4100 > 120)
    			shot.push_back(Coin(dragon[0].position.x,dragon[0].position.y,COLOR_BLUE,1));

    		if(dragon_alive==1 && dragon_kill==0)
    		{
    			level++;
    			score+=100;
    			dragon_alive=0;
    			dragon.clear();
    		}
    		//dragon

            
            draw();
            glfwSwapBuffers(window);
            tick_elements();
            tick_input(window);
            detect_collision(ball);
            usleep(10000);
            count++;
        }
        glfwPollEvents();
    }
    quit(window);
}

void detect_collision(Ball a) {
	//coins
	for(int i=0;i<c.size();i++)
	{
		if(c[i].type==1)
		{
			if(abs(a.position.x-c[i].position.x)<0.1 && abs(a.position.y-c[i].position.y-0.2)<0.5)
			{
				score+=2;
				c.erase(c.begin()+i);
 			    sprintf(display,"WELCOME  %s           YOUR SCORE : %d        YOUR LIVES : %d       LEVEL : %d",name,score,life,level);
    	        glfwSetWindowTitle(window,display);
			}
		}
		else
		{
			if(abs(a.position.x-c[i].position.x)<0.05 && abs(a.position.y-c[i].position.y-0.2)<0.45)
			{
				score+=1;
				c.erase(c.begin()+i);
    			sprintf(display,"WELCOME  %s           YOUR SCORE : %d        YOUR LIVES : %d       LEVEL : %d",name,score,life,level);
                glfwSetWindowTitle(window,display);
			}
		}	
	}

	//shot
	for(int i=0;i<shot.size();i++)
	{
		if(abs(a.position.x-shot[i].position.x)<0.1 && abs(a.position.y-shot[i].position.y-0.2)<0.5)
			dead();
	}

	//dragon-kill
	for(int j=0;j<ballon.size();j++)
	for(int i=0;i<dragon.size();i++)
	{
		if(abs(ballon[j].position.y-dragon[i].position.y)<=0.5 && abs(ballon[j].position.x - dragon[i].position.x - 0.45 )< 0.45)
		{
			ballon.erase(ballon.begin()+j);
			dragon_kill--;
		}
	}

	//powerups
	for(int i=0;i<power.size();i++)
	{
		if(abs(a.position.x-power[i].position.x)<0.2 && abs(a.position.y-power[i].position.y-0.2)<0.5)
		{
			score+=50;
			power.erase(power.begin()+i);
	    	sprintf(display,"WELCOME  %s        YOUR SCORE : %d  YOUR LIVES : %d",name,score,life);
    	    glfwSetWindowTitle(window,display);
		}
	}
	for(int i=0;i<attrac.size();i++)
	{
		if(abs(a.position.x-attrac[i].position.x)<0.2 && abs(a.position.y-attrac[i].position.y-0.2)<0.5)
		{
			attraction=1;
			attrac.erase(attrac.begin()+i);
		}
	}

	//firerays
	for(int i=0;i<e.size();i++)
	{
		if(e[i].type==1)
		{
			if(abs(a.position.x-e[i].position.x-1)<=0.8 && abs(a.position.y-e[i].position.y)<=0.5)
				dead();
		}
		else if(e[i].type==2)
		{
			if(abs(a.position.x-e[i].position.x)<=0.5 && abs(a.position.y-e[i].position.y-1)<=0.8)
				dead();
		}
		else if(e[i].type==11)
		{
			if(abs(a.position.x-e[i].position.x-0.6)<=0.6 && abs(a.position.x+a.position.y-e[i].position.x-e[i].position.y)<0.2)
				dead();
		}
		else if(e[i].type==12)
		{
			if(abs(a.position.x-e[i].position.x-0.6)<=0.6 && abs((a.position.x-e[i].position.x)-(a.position.y-e[i].position.y+6))<0.2)
				dead();
		}	
	}

	//ballon-fire
	for(int j=0;j<ballon.size();j++)
	for(int i=0;i<e.size();i++)
	{
		if(e[i].type==1)
		{
			if(abs(ballon[j].position.x-e[i].position.x-0.8)<=0.9 && abs(ballon[j].position.y-e[i].position.y+0.1)<=0.2)
			{
				ballon.erase(ballon.begin()+j);
				e.erase(e.begin()+i);
			}
		}
		else if(e[i].type==2)
		{
			if(abs(ballon[j].position.x-e[i].position.x+0.1)<=0.2 && abs(ballon[j].position.y-e[i].position.y-0.8)<=0.9)
			{
				ballon.erase(ballon.begin()+j);
				e.erase(e.begin()+i);
			}
		}
		else if(e[i].type==11)
		{
			if(abs(ballon[j].position.x-e[i].position.x-0.5)<=0.5 && abs(ballon[j].position.x+ballon[j].position.y-e[i].position.x-e[i].position.y)<0.1)
			{
				ballon.erase(ballon.begin()+j);
				e.erase(e.begin()+i);
			}
		}	
		else if(e[i].type==12)
		{
			if(abs(ballon[j].position.x-e[i].position.x-0.5)<=0.5 && abs((ballon[j].position.x-e[i].position.x)-(ballon[j].position.y-e[i].position.y+6.1))<0.1)
			{
				ballon.erase(ballon.begin()+j);
				e.erase(e.begin()+i);
			}
		}
	}

    //laser
    for(int i=0;i<ray.size();i++)
    	if(abs(a.position.y - ray[i].position.y - 0.35) < 0.35)
    		dead();

    //boomerang
    for(int i=0;i<boomer.size();i++)
    	if(abs(a.position.x-boomer[i].position.x-0.2)<=0.3 && abs(a.position.y-boomer[i].position.y-0.3)<=0.3)
			dead();

	//ring
	for(int i=0;i<ring.size();i++)
    	if(abs((ring[i].position.x - a.position.x)*(ring[i].position.x - a.position.x) + (ring[i].position.y - a.position.y)*(ring[i].position.y - a.position.y ) - 0.5) <=0.5 && a.position.y > ring[i].position.y)
    		ring_on=1;
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
