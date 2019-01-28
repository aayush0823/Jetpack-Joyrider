#include "enemy.h"
#include "main.h"
#include <math.h>

Enemy::Enemy(float x, float y, color_t color,int type) {
    this->position = glm::vec3(x, y, 0);
    this->speed = 0.03 + level*0.01;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    this->type=type;
    this->hit=0;

    //horizontal
    if(type==1)
    {
        GLfloat vertex_buffer_data_end[]={
             0.0f,0.1f,0.0f,
            -0.2f,0.1f,0.0f,
            -0.2f,-0.3f,0.0f,
             0.0f,0.1f,0.0f,
            -0.2f,-0.3f,0.0f,
             0.0f,-0.3f,0.0f,

             1.6f,0.1f,0.0f,
             1.4f,0.1f,0.0f,
             1.4f,-0.3f,0.0f,
             1.6f,0.1f,0.0f,
             1.4f,-0.3f,0.0f,
             1.6f,-0.3f,0.0f
        };
        this->object2 = create3DObject(GL_TRIANGLES, 3*4, vertex_buffer_data_end, COLOR_BLUE, GL_FILL);
        GLfloat vertex_buffer_data[]={
            0.0f,0.0f,0.0f,
            1.6f,0.0f,0.0f,
            0.0f,-0.2f,0.0f,
            1.6f,0.0f,0.0f,
            0.0f,-0.2f,0.0f,
            1.6f,-0.2f,0.0f
        };
        this->object1 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
    }

    //vertical
    if(type==2)
    {
       GLfloat vertex_buffer_data[]={
            0.0f,0.0f,0.0f,
            0.0f,1.6f,0.0f,
            -0.2f,0.0f,0.0f,
            0.0f,1.6f,0.0f,
            -0.2f,0.0f,0.0f,
            -0.2f,1.6f,0.0f
        };
        this->object1 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);

        GLfloat vertex_buffer_data_end[]={
             0.0f,0.1f,0.0f,
            -0.2f,0.1f,0.0f,
            -0.2f,-0.3f,0.0f,
             0.0f,0.1f,0.0f,
            -0.2f,-0.3f,0.0f,
             0.0f,-0.3f,0.0f,

              0.0f,1.7f,0.0f,
            -0.2f,1.7f,0.0f,
            -0.2f,1.4f,0.0f,
             0.0f,1.7f,0.0f,
            -0.2f,1.4f,0.0f,
             0.0f,1.4f,0.0f
        };
        this->object2 = create3DObject(GL_TRIANGLES, 3*4, vertex_buffer_data_end, COLOR_BLUE, GL_FILL);

    }

    //slant 1
    if(type==11)
    {
       GLfloat vertex_buffer_data[]={
            0.0f,0.0f,0.0f,
            0.1f,0.1f,0.0f,
            1.0f,-1.0f,0.0f,
            0.1f,0.1f,0.0f,
            1.0f,-1.0f,0.0f,
            1.1f,-0.9f,0.0f
        };
        this->object1 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);

            GLfloat vertex_buffer_data_end[]={
             -0.1f,0.2f,0.0f,
             0.1f,0.2f,0.0f,
             -0.1f,-0.2f,0.0f,
             0.1f,0.2f,0.0f,
            -0.1f,-0.2f,0.0f,
             0.1f,-0.2f,0.0f,

             1.2f,-0.7f,0.0f,
             1.0f,-0.7f,0.0f,
             1.0f,-1.1f,0.0f,
             1.2f,-0.7f,0.0f,
             1.0f,-1.1f,0.0f,
             1.2f,-1.1f,0.0f,
        };
        this->object2 = create3DObject(GL_TRIANGLES, 3*4, vertex_buffer_data_end, COLOR_BLUE, GL_FILL);

    }

    //slant 2
    if(type==12)
    {
       GLfloat vertex_buffer_data[]={
            0.0f,-6.0f,0.0f,
            0.1f,-6.1f,0.0f,
            1.0f,-5.0f,0.0f,
            0.1f,-6.1f,0.0f,
            1.0f,-5.0f,0.0f,
            1.1f,-5.1f,0.0f
        };
        this->object1 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);

            GLfloat vertex_buffer_data_end[]={

             0.2f,-5.8f,0.0f,
            -0.0f,-5.8f,0.0f,
            -0.0f,-6.2f,0.0f,
             0.2f,-5.8f,0.0f,
            -0.0f,-6.2f,0.0f,
             0.2f,-6.2f,0.0f,

             1.2f,-4.8f,0.0f,
             1.0f,-4.8f,0.0f,
             1.0f,-5.3f,0.0f,
             1.2f,-4.8f,0.0f,
             1.0f,-5.3f,0.0f,
             1.2f,-5.3f,0.0f,
        };
        this->object2 = create3DObject(GL_TRIANGLES, 3*4, vertex_buffer_data_end, COLOR_BLUE, GL_FILL);

    }

    //ground
    if(type == 30)
    {
         GLfloat vertex_buffer_data[]={
            -100.0f,-0.4f,0.0f,
            -100.0f,-100.0f,0.0f,
            100.0f,-0.4f,0.0f,
            -100.0f,-100.0f,0.0f,
            100.0f,-0.4f,0.0f,
            100.0f,-100.0f,0.0f
        };
        GLfloat vertex_buffer_data_end[]={
            -100.0f,6.5f,0.0f,
            -100.0f,100.0f,0.0f,
            100.0f,6.5f,0.0f,
            -100.0f,100.0f,0.0f,
            100.0f,6.5f,0.0f,
            100.0f,100.0f,0.0f
        };
        this->object1 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
        this->object2 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data_end, COLOR_LIGHTBLUE, GL_FILL);
    }
    
	float pi=3.1415926;
    //magnet
    if(type == 4)
    {
    	GLfloat vertex_buffer_data[135];
    	GLfloat vertex_buffer_data_end[135];
    	GLfloat vertex_buffer_data_end2[270];
    	int i=0;
    	int t=-15;
       for(i=0;i<9*15;i+=9)
       {
          vertex_buffer_data[i]=0.0f;
          vertex_buffer_data[i+1]=0.0f;
          vertex_buffer_data[i+2]=0.0f;
          vertex_buffer_data[i+3]=0.5*cos(2*pi/(float)60*(float)t);
          vertex_buffer_data[i+4]=0.5*sin(2*pi/(float)60*(float)t);
          vertex_buffer_data[i+5]=0.0f;
          vertex_buffer_data[i+6]=0.5*cos(2*pi/(float)60*(float)(t+1));
          vertex_buffer_data[i+7]=0.5*sin(2*pi/(float)60*(float)(t+1));
          vertex_buffer_data[i+8]=0.0f;
          t++;
        }
        for(i=0;i<9*15;i+=9)
        {
          vertex_buffer_data_end[i]=0.0f;
          vertex_buffer_data_end[i+1]=0.0f;
          vertex_buffer_data_end[i+2]=0.0f;
          vertex_buffer_data_end[i+3]=0.5*cos(2*pi/(float)60*(float)t);
          vertex_buffer_data_end[i+4]=0.5*sin(2*pi/(float)60*(float)t);
          vertex_buffer_data_end[i+5]=0.0f;
          vertex_buffer_data_end[i+6]=0.5*cos(2*pi/(float)60*(float)(t+1));
          vertex_buffer_data_end[i+7]=0.5*sin(2*pi/(float)60*(float)(t+1));
          vertex_buffer_data_end[i+8]=0.0f;
          t++;
        }
        this->object1 = create3DObject(GL_TRIANGLES, 3*15, vertex_buffer_data, COLOR_BLUE, GL_FILL);
        this->object2 = create3DObject(GL_TRIANGLES, 3*15, vertex_buffer_data_end, color, GL_FILL);
    }

    //firebeam spot
    if(type == 6)
    {
         GLfloat vertex_buffer_data[]={
            0.0f,0.0f,0.0f,
            -0.5f,0.5f,0.0f,
            -0.5f,-0.5f,0.0f,
            7.0f,0.0f,0.0f,
            7.5f,0.5f,0.0f,
            7.5f,-0.5f,0.0f
        };
        this->object1 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
        this->object2 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
    }

    //ray
    if(type == 7)
    {
         GLfloat vertex_buffer_data[]={
            0.0f,0.05f,0.0f,
            0.0f,-0.05f,0.0f,
            7.0f,0.05f,0.0f,
            0.0f,-0.05f,0.0f,
            7.0f,0.05f,0.0f,
            7.0f,-0.05f,0.0f
        };
        this->object1 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
        this->object2 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
    }

    //boomerang
    if(type == 8)
    {
         GLfloat vertex_buffer_data[]={
            0.0f,0.0f,0.0f,
            -0.2f,0.3f,0.0f,
            0.4f,0.0f,0.0f,
            0.0f,0.0f,0.0f,
            0.4f,0.0f,0.0f,
            -0.2f,-0.3f,0.0f
        };
        this->object1 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
        this->object2 = create3DObject(GL_TRIANGLES, 3*2, vertex_buffer_data, color, GL_FILL);
    }

    //ring
    if(type == 9)
    {
    	GLfloat vertex_buffer_data[270];
    	GLfloat vertex_buffer_data_end[270];
    	int i=0;
    	int t=0;
       for(i=0;i<9*30;i+=9)
       {
          vertex_buffer_data[i]=0.0f;
          vertex_buffer_data[i+1]=0.0f;
          vertex_buffer_data[i+2]=0.0f;
          vertex_buffer_data[i+3]=0.9*cos(2*pi/(float)60*(float)t);
          vertex_buffer_data[i+4]=0.9*sin(2*pi/(float)60*(float)t);
          vertex_buffer_data[i+5]=0.0f;
          vertex_buffer_data[i+6]=0.9*cos(2*pi/(float)60*(float)(t+1));
          vertex_buffer_data[i+7]=0.9*sin(2*pi/(float)60*(float)(t+1));
          vertex_buffer_data[i+8]=0.0f;
          t++;
        }
        t=0;
        for(i=0;i<9*30;i+=9)
        {
          vertex_buffer_data_end[i]=0.0f;
          vertex_buffer_data_end[i+1]=0.0f;
          vertex_buffer_data_end[i+2]=0.0f;
          vertex_buffer_data_end[i+3]=1.0*cos(2*pi/(float)60*(float)t);
          vertex_buffer_data_end[i+4]=1.0*sin(2*pi/(float)60*(float)t);
          vertex_buffer_data_end[i+5]=0.0f;
          vertex_buffer_data_end[i+6]=1.0*cos(2*pi/(float)60*(float)(t+1));
          vertex_buffer_data_end[i+7]=1.0*sin(2*pi/(float)60*(float)(t+1));
          vertex_buffer_data_end[i+8]=0.0f;
          t++;
        }
        this->object1 = create3DObject(GL_TRIANGLES, 3*30, vertex_buffer_data_end, COLOR_GREEN, GL_FILL);
        this->object2 = create3DObject(GL_TRIANGLES, 3*30, vertex_buffer_data, COLOR_BLACK, GL_FILL);
    }
    //dragon
    if(type == 10)
    {
    	GLfloat vertex_buffer_data[]={
    		0.1f,0.1f,0.0f,
    		0.4f,0.1f,0.0f,
    		0.1f,-0.1f,0.0f,
    		0.4f,0.1f,0.0f,
    		0.1f,-0.1f,0.0f,
    		0.4f,-0.1f,0.0f,
    		0.1f,0.0f,0.0f,
    		0.8f,-0.2f,0.0f,
    		0.8f,0.2f,0.0f,
    	};
    	GLfloat vertex_buffer_data_end[]={
    		0.0f,0.0f,0.0f,
    		0.1f,0.1f,0.0f,
    		0.1f,-0.1f,0.0f,
    		
    		0.4f,0.1f,0.0f,
    		0.3f,-0.3f,0.0f,
    		0.4f,-0.5f,0.0f,
    		0.4f,-0.1f,0.0f,
    		0.3f,0.3f,0.0f,
    		0.4f,0.5f,0.0f,

    		0.4f,0.1f,0.0f,
    		0.5f,-0.35f,0.0f,
    		0.4f,-0.4f,0.0f,
    		0.4f,-0.1f,0.0f,
    		0.5f,0.35f,0.0f,
    		0.4f,0.4f,0.0f,

    		0.4f,0.1f,0.0f,
    		0.6f,-0.2f,0.0f,
    		0.4f,-0.4f,0.0f,
    		0.4f,-0.1f,0.0f,
    		0.6f,0.2f,0.0f,
    		0.4f,0.4f,0.0f,
    	};
        this->object1 = create3DObject(GL_TRIANGLES, 3*3, vertex_buffer_data, COLOR_YELLOW, GL_FILL);
        this->object2 = create3DObject(GL_TRIANGLES, 3*7, vertex_buffer_data_end, COLOR_RED, GL_FILL);
    }
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.2f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
}

void Enemy::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Enemy::tick() {
    this->position.x -= speed;
}

void Enemy::boom() {
	if(this->position.x > -2.5 && this->hit==0)
	{
 	   this->position.x -= speed*2;
 	   this->position.y -= speed/2;
	}
	else
	{
		this->hit=1;
		this->position.x += speed*3;
 	   	this->position.y -= speed/2;
	}
}

void Enemy::dragon() {
	if(this->position.y < -2.95)
		this->hit=0;
	else if(this->position.y > 3 )
		this->hit=1;

	if(this->hit==0)
 	   this->position.y += speed/2;
	else
 	   this->position.y -= speed/2;

}