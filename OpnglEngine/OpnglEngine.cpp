#include <GL/freeglut.h>

// Paddle variables
float paddle1Y = 0.0f;
float paddle2Y = 0.0f;
float paddleSpeed = 0.05f;

// Ball variables
float ballX = 0.0f;
float ballY = 0.0f;
float ballSpeedX = 0.03f;
float ballSpeedY = 0.02f;

void update(int value) {
    // Update ball position
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Ball collision with walls
    if (ballY > 1.0f || ballY < -1.0f) {
        ballSpeedY = -ballSpeedY;
    }

    // Ball collision with paddles
    if ((ballX > 0.9f && ballX < 1.0f) && (ballY > paddle2Y - 0.2f && ballY < paddle2Y + 0.2f)) {
        ballSpeedX = -ballSpeedX;
    }

    if ((ballX < -0.9f && ballX > -1.0f) && (ballY > paddle1Y - 0.2f && ballY < paddle1Y + 0.2f)) {
        ballSpeedX = -ballSpeedX;
    }

    // Update paddle position
    paddle1Y += paddleSpeed;

    // Keep paddles within the window
    if (paddle1Y > 0.8f || paddle1Y < -0.8f) {
        paddleSpeed = -paddleSpeed;
    }

    // Call update function after 16 milliseconds
    glutTimerFunc(16, update, 0);

    // Redraw the scene
    glutPostRedisplay();
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw paddles
    glBegin(GL_POLYGON);
    glVertex2f(0.95f, paddle2Y - 0.2f);
    glVertex2f(1.0f, paddle2Y - 0.2f);
    glVertex2f(1.0f, paddle2Y + 0.2f);
    glVertex2f(0.95f, paddle2Y + 0.2f);
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(-0.95f, paddle1Y - 0.2f);
    glVertex2f(-1.0f, paddle1Y - 0.2f);
    glVertex2f(-1.0f, paddle1Y + 0.2f);
    glVertex2f(-0.95f, paddle1Y + 0.2f);
    glEnd();

    // Draw ball
    glBegin(GL_POLYGON);
    glVertex2f(ballX - 0.02f, ballY - 0.02f);
    glVertex2f(ballX + 0.02f, ballY - 0.02f);
    glVertex2f(ballX + 0.02f, ballY + 0.02f);
    glVertex2f(ballX - 0.02f, ballY + 0.02f);
    glEnd();

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    // Exit the program when the 'Esc' key is pressed
    if (key == 27) {
        exit(0);
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Pong Game");
    glutInitWindowSize(800, 600);
    glutDisplayFunc(draw);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
