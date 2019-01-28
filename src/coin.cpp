#include "coin.h"
#include "main.h"
#include <math.h>

Coin::Coin(float x, float y, color_t color,int type) {
    this->position = glm::vec3(x, y, 0);
    this->speed = 0.05;
    this->type=type;
    int t=0;
	float pi=3.1415926;
	GLfloat vertex_buffer_data[500];
    if(type == 1)
    {
	   for(int i=0;i<9*50;i+=9)
	   {
		  vertex_buffer_data[i]=0.0f;
		  vertex_buffer_data[i+1]=0.0f;
		  vertex_buffer_data[i+2]=0.0f;
          vertex_buffer_data[i+3]=0.1*cos(2*pi/(float)50*(float)t);
		  vertex_buffer_data[i+4]=0.1*sin(2*pi/(float)50*(float)t);
		  vertex_buffer_data[i+5]=0.0f;
		  vertex_buffer_data[i+6]=0.1*cos(2*pi/(float)50*(float)(t+1));
		  vertex_buffer_data[i+7]=0.1*sin(2*pi/(float)50*(float)(t+1));
		  vertex_buffer_data[i+8]=0.0f;
		  t++;
    	}
        this->object = create3DObject(GL_TRIANGLES, 3*50, vertex_buffer_data, color, GL_FILL);
    }
    else if(type == 2)
    {
       for(int i=0;i<9*50;i+=9)
       {
          vertex_buffer_data[i]=0.0f;
          vertex_buffer_data[i+1]=0.0f;
          vertex_buffer_data[i+2]=0.0f;
          vertex_buffer_data[i+3]=0.05*cos(2*pi/(float)50*(float)t);
          vertex_buffer_data[i+4]=0.05*sin(2*pi/(float)50*(float)t);
          vertex_buffer_data[i+5]=0.0f;
          vertex_buffer_data[i+6]=0.05*cos(2*pi/(float)50*(float)(t+1));
          vertex_buffer_data[i+7]=0.05*sin(2*pi/(float)50*(float)(t+1));
          vertex_buffer_data[i+8]=0.0f;
          t++;
        }
        this->object = create3DObject(GL_TRIANGLES, 3*50, vertex_buffer_data, color, GL_FILL);
    }
    else if(type == 3)
    {
       for(int i=0;i<9*50;i+=9)
       {
          vertex_buffer_data[i]=0.0f;
          vertex_buffer_data[i+1]=0.0f;
          vertex_buffer_data[i+2]=0.0f;
          vertex_buffer_data[i+3]=0.2*cos(2*pi/(float)50*(float)t);
          vertex_buffer_data[i+4]=0.2*sin(2*pi/(float)50*(float)t);
          vertex_buffer_data[i+5]=0.0f;
          vertex_buffer_data[i+6]=0.2*cos(2*pi/(float)50*(float)(t+1));
          vertex_buffer_data[i+7]=0.2*sin(2*pi/(float)50*(float)(t+1));
          vertex_buffer_data[i+8]=0.0f;
          t++;
        }
        this->object = create3DObject(GL_TRIANGLES, 3*50, vertex_buffer_data, color, GL_FILL);
    }
}

void Coin::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.2f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Coin::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}
//coins
void Coin::tick() {
    this->position.x -= speed;
}
//ballons
void Coin::tick2() {
    this->position.x += 5*speed/6;
    this->position.y -= speed/4;
}
//shots
void Coin::fire() {
    this->position.x -= speed*2;
}
int x=0;
void Coin::powerup() {
    	//powerup
	if(this->position.y > 3)
	    x=0;
	else if(this->position.y < -3.3)
	    x=1;

	if(x==0)
		this->position.y-=speed;
	else
		this->position.y+=speed;

	this->position.x -= speed/1.6;
}