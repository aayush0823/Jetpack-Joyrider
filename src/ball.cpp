#include "ball.h"
#include "main.h"
#include <math.h>

Ball::Ball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->speed = 0.06;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    
	GLfloat face[]={
		0.0f,0.0f,0.0f,
		-0.3f,0.0f,0.0f,
		-0.3f,-0.3f,0.0f,
		0.0f,0.0f,0.0f,
		-0.3f,-0.3f,0.0f,
		0.0f,-0.3f,0.0f,
	};
	GLfloat hair[]={
		0.0f,0.0f,0.0f,
		0.1f,0.1f,0.0f,
		-0.3f,0.1f,0.0f,
		0.0f,0.0f,0.0f,
		-0.3f,0.1f,0.0f,
		-0.3f,0.0f,0.0f,

		-0.3f,0.0f,0.0f,
		-0.4f,0.0f,0.0f,
		-0.4f,-0.5f,0.0f,
		-0.3f,0.0f,0.0f,
		-0.4f,-0.5f,0.0f,
		-0.3f,-0.4f,0.0f
	};
	GLfloat base[]={
		0.0f,-0.3f,0.0f,
		-0.3f,-0.3f,0.0f,
		0.0f,-0.6f,0.0f,
		-0.3f,-0.3f,0.0f,
		-0.3f,-0.6f,0.0f,
		0.1f,-0.6f,0.0f,
	};
	GLfloat goggles[]={
		0.0f,-0.1f,0.0f,
		-0.1f,-0.1f,0.0f,
		-0.1f,-0.2f,0.0f,
		0.0f,-0.1f,0.0f,
		-0.1f,-0.2f,0.0f,
		0.0f,-0.2f,0.0f,

		-0.1f,-0.14f,0.0f,
		-0.3f,-0.14f,0.0f,
		-0.3f,-0.16f,0.0f,
		-0.1f,-0.14f,0.0f,
		-0.3f,-0.16f,0.0f,
		-0.1f,-0.16f,0.0f,
	};
    this->object1 = create3DObject(GL_TRIANGLES, 3*2, face, COLOR_SKIN, GL_FILL);
    this->object2 = create3DObject(GL_TRIANGLES, 3*4, hair, COLOR_BROWN, GL_FILL);
    this->object3 = create3DObject(GL_TRIANGLES, 3*2, base, COLOR_MAROON, GL_FILL);
    this->object4 = create3DObject(GL_TRIANGLES, 3*4, goggles, COLOR_BLACK, GL_FILL);
}

void Ball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(0.2f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object1);
    draw3DObject(this->object2);
    draw3DObject(this->object3);
    draw3DObject(this->object4);
}

void Ball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Ball::tick(int move) {
    if(move==1)
    {
    	if(this->position.x>=-3.6)
		    this->position.x -= speed;
    }
	else if(move==2)
	{
		if(this->position.x<=3.8)
		    this->position.x += speed;
	}
	else if(move==3)
	{
		if(this->position.y<3.1)
 		   	this->position.y += speed;
	}
    else if(move==4)
    {
		if(this->position.y>=-2.95)
		    this->position.y -= speed/(3.5)*(-this->position.y+4);
    }
    else if(move==7)
    {
		if(this->position.y>=-2.95)
		    this->position.y -= speed;
    }
    else if(move==5)
	{
    	if(this->position.x>=-3.6)
		    this->position.x -= speed;
		if(this->position.y<3.1)
	    	this->position.y += speed;
	}
    else if(move==6)
    {
    	if(this->position.x<=3.8)
		    this->position.x += speed;
		if(this->position.y<3.1)
	    	this->position.y += speed;
    }
}

void Ball::magnet(int x,int y) {
    	//magnet
		if(this->position.y - y > 0.5)
		    this->position.y -= speed/2;
		else if(y - this->position.y > 0.5)
		    this->position.y += speed/2;

		if(this->position.x - x > 0.5)
		    this->position.x -= speed/2;
		else if(x - this->position.x > 0.1)
		    this->position.x += speed/2;
}

int up=1;
void Ball::ring(int x,int y) {

	if(this->position.x<=3.8)
		this->position.x += speed/7;

	this->position.y = sqrt(1.4-(this->position.x - x)*(this->position.x - x))+y;
}