/****************************************
 * 		NDS NeHe Lesson 04    			*
 * 		Author: Dovoto					*
 ****************************************/

// include your ndslib
#include <nds.h>
#include <math.h>
#include "pikmin1.h"
#include "testScene.h"

int DrawGLScene();

float rtri;				// Angle For The Triangle ( NEW )
float rquad;				// Angle For The Quad ( NEW )

const float leafGreen = 1.0;

int main() {
    defaultExceptionHandler();
	// Setup the Main screen for 3D
	videoSetMode(MODE_0_3D);
    
	// initialize the geometry engine
	glInit();
	
	// enable antialiasing
	glEnable(GL_ANTIALIAS);
	
	// setup the rear plane
	glClearColor(0,0,0,31); // BG must be opaque for AA to work
	glClearPolyID(63); // BG must have a unique polygon ID for AA to work
	glClearDepth(0x7FFF);
    
	// Set our viewport to be the same size as the screen
	glViewport(0,0,255,191);
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, 256.0 / 192.0, 0.1, 100);
	
	//ds specific, several attributes can be set here
	glPolyFmt(POLY_ALPHA(31) | POLY_CULL_FRONT);
	
	// Set the current matrix to be the model matrix
	glMatrixMode(GL_MODELVIEW);
	float x,y,z;
    float yOrbit;
    glClearColor(255,0,255,255);
	while (1)
	{
		// draw the scene
        
        glPushMatrix();
        glTranslatef(x,y,z);
        //gluLookAt(x,y,z,x,y,z+10,0,1,0);
        glRotatef(yOrbit,0,1,0);

		DrawGLScene();
        
        glPopMatrix(1);
		
		// flush to screen
		glFlush(0);
		
        scanKeys();
        
        if(keysHeld() & (KEY_UP))
        {
            z+=.05;
        }else
        if(keysHeld() & (KEY_DOWN))
        {
            z-=.05;
        }
        
        if(keysHeld() & (KEY_X))
        {
            y-=.05;
        }else
            if(keysHeld() & (KEY_B))
            {
                y+=.05;
            }
        
        
        if(keysHeld() & (KEY_LEFT|KEY_Y))
        {
            x+=.05;
        }else
            if(keysHeld() & (KEY_RIGHT|KEY_A))
            {
                x-=.05;
            }
        if(keysHeld() & KEY_L)
        {
            yOrbit-=1;
        }
        if(keysHeld() & KEY_R)
        {
            yOrbit+=1;
        }
		// wait for the screen to refresh
		swiWaitForVBlank();
	}
	
	return 0;
}

//void drawVBO(float * verts,int* idx,int polyCount,int xOffset,int yOffset, int zOffset,int width)
//{
//    for (int i=0; i<polyCount; i++)
//    {
//        glBegin(GL_TRIANGLE);
//        for (int k=0; k<3; k++) {
//            
//            int vi1 = idx[i*3 +k];
//            
//            // glNormal3f (-Pickmin_vertex[vi1][2], -Pickmin_vertex[vi1][3],-Pickmin_vertex[vi1][4]);
//            glVertex3f(PikminLeaf_vertex[vi1*width +xOffset],
//                       PikminLeaf_vertex[vi1*width +yOffset],
//                       PikminLeaf_vertex[vi1*width +zOffset]
//                       );
//        }
//        glEnd();
//        
//    }
//}
void drawPikmin(int LOD)
{
    if(LOD >0)
    {
        for (int i=0; i<Pikmin_LOD1_polygoncount; i++)
        {
            glBegin(GL_TRIANGLE);
            for (int k=0; k<3; k++) {
                
                int vi1 = Pikmin_LOD1_index[i][k];
                glColor3f(1,
                          fmax(Pikmin_LOD1_vertex[vi1][3]*1.5 ,.1),
                          0
                          );
                // glNormal3f (-Pickmin_vertex[vi1][2], -Pickmin_vertex[vi1][3],-Pickmin_vertex[vi1][4]);
                glVertex3f(Pikmin_LOD1_vertex[vi1][5],
                           Pikmin_LOD1_vertex[vi1][6],
                           Pikmin_LOD1_vertex[vi1][7]
                           );
            }
            glEnd();
            
        }
    }
    else
    {
    for (int i=0; i<Pikmin_polygoncount; i++)
    {
        glBegin(GL_TRIANGLE);
        for (int k=0; k<3; k++) {
            
            int vi1 = Pikmin_index[i][k];
            glColor3f(1,
                      fmax(Pikmin_vertex[vi1][3]*1.5 ,.1),
                      0
                      );
            // glNormal3f (-Pickmin_vertex[vi1][2], -Pickmin_vertex[vi1][3],-Pickmin_vertex[vi1][4]);
            glVertex3f(Pikmin_vertex[vi1][5],
                       Pikmin_vertex[vi1][6],
                       Pikmin_vertex[vi1][7]
                       );
        }
        glEnd();
        
    }
    }
    
    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_NONE);
    glColor3f(.1,
              leafGreen,
              .1
              );
    for (int i=0; i<PikminLeaf_polygoncount; i++)
    {
        glBegin(GL_TRIANGLE);
        for (int k=0; k<3; k++) {
            
            int vi1 = PikminLeaf_index[i][k];
            
            // glNormal3f (-Pickmin_vertex[vi1][2], -Pickmin_vertex[vi1][3],-Pickmin_vertex[vi1][4]);
            glVertex3f(PikminLeaf_vertex[vi1][5],
                       PikminLeaf_vertex[vi1][6],
                       PikminLeaf_vertex[vi1][7]
                       );
        }
        glEnd();
        
    }
    
    glPolyFmt(POLY_ALPHA(31) | POLY_CULL_FRONT);
    glColor3f(1,1,1);
    for (int i=0; i<PikminEyes_polygoncount; i++)
    {
        glBegin(GL_TRIANGLE);
        for (int k=0; k<3; k++) {
            
            int vi1 = PikminEyes_index[i][k];
            
            // glNormal3f (-Pickmin_vertex[vi1][2], -Pickmin_vertex[vi1][3],-Pickmin_vertex[vi1][4]);
            glVertex3f(PikminEyes_vertex[vi1][5],
                       PikminEyes_vertex[vi1][6],
                       PikminEyes_vertex[vi1][7]
                       );
        }
        glEnd();
        
    }
    
//    //glTranslatef(0.0,,0.5f);
//    glColor3f(.01,.01,.01);
//    glScalef(.7,.7,.7);
//    for (int i=0; i<PikminEyes_polygoncount; i++)
//    {
//        glBegin(GL_TRIANGLE);
//        for (int k=0; k<3; k++) {
//            
//            int vi1 = PikminEyes_index[i][k];
//            
//            // glNormal3f (-Pickmin_vertex[vi1][2], -Pickmin_vertex[vi1][3],-Pickmin_vertex[vi1][4]);
//            glVertex3f(PikminEyes_vertex[vi1][5],
//                       PikminEyes_vertex[vi1][6],
//                       PikminEyes_vertex[vi1][7]
//                       );
//        }
//        glEnd();
//        
//    }
}

void drawTerrain()
{

    for (int i=0; i<Plane_polygoncount; i++)
    {
        glBegin(GL_TRIANGLES);
        for (int k=0; k<3; k++) {
            
            int vi1 = Plane_index[i][k];
//            glColor3f(.3,
//                      fmax(Plane_vertex[vi1][3]*1.5 ,.1),
//                      0
//                      );
            
            glVertex3f(Plane_vertex[vi1][5],
                       Plane_vertex[vi1][6],
                       Plane_vertex[vi1][7]
                       );
            glNormal3f (Plane_vertex[vi1][2], Plane_vertex[vi1][3],Plane_vertex[vi1][4]);
        }
        // glEnd();
        
    }

}
int DrawGLScene()											// Here's Where We Do All The Drawing
{
    const int PIKMIN_COUNT = 10;
    //drawTerrain();
    for (int j=0;j<4; j++) {
    
    for(int i=0; i<PIKMIN_COUNT;i++)
    {
        glPushMatrix();
	/*ds does this automagicaly*///glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
                                 //glLoadIdentity();// Reset The Current Modelview Matrix
	glTranslatef(-4.0f +i,0.0f,-3.5f-j);						// Move Left 1.5 Units And Into The Screen 6.0
	glRotatef(rtri,0.0f,fmax(((float)rand()/RAND_MAX),.2f),0.0f);						// Rotate The Triangle On The Y axis ( NEW )
	
    // set the vertex color
    drawPikmin(j);	// Start Drawing A
        glPopMatrix(1);
    }
    }
    

//    //glPopMatrix();
//    glPushMatrix();
//    // Done Drawing The Triangle
//	glLoadIdentity();									// Reset The Current Modelview Matrix
//	glTranslatef(1.5f,0.0f,-6.0f);						// Move Right 1.5 Units And Into The Screen 6.0
//	glRotatef(rquad,1.0f,0.0f,0.0f);					// Rotate The Quad On The X axis ( NEW )
//	glColor3f(0.5f,0.5f,1.0f);							// Set The Color To Blue One Time Only
//	glBegin(GL_QUADS);									// Draw A Quad
//    glVertex3f(-1.0f, 1.0f, 0.0f);					// Top Left
//    glVertex3f( 1.0f, 1.0f, 0.0f);					// Top Right
//    glVertex3f( 1.0f,-1.0f, 0.0f);					// Bottom Right
//    glVertex3f(-1.0f,-1.0f, 0.0f);					// Bottom Left
//	glEnd();											// Done Drawing The Quad
//    glPopMatrix(1);
	rtri+=2.0f;											// Increase The Rotation Variable For The Triangle ( NEW )
	rquad-=0.75f;										// Decrease The Rotation Variable For The Quad ( NEW )
	return TRUE;										// Keep Going
}


