#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

/* Postavljam ID i interval tajmera */
#define TIMER_ID 0
#define TIMER_INTERVAL 400

/* Posstavljam dimenzije matrice */
#define MAX_X 12
#define  MAX_Y 21

/* Deklarisanje callback funkcija */
static void on_keyboard(unsigned char key, int x, int y);
static void on_specijalkey(int key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int value);

/* Deklarisanje pomocnih funkcija */
static void nacrtaj_okvir(void);
static void sakri_figuru(void);
static void iscrtaj_figuru(int x);
static void popuni_matricu(void);



/* Deklarisanje globalnih promenljivi */
static int window_width, window_height;
static animation_ongoing;
static int matrica[MAX_Y][MAX_X];
static int rotiraj_scenu = 0;
static int random_broj;


int main(int argc, char **argv){

	/* GLUT inicijalizacija */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

	/* Pravljenje prozora */
	glutInitWindowSize(400, 700);
	glutInitWindowPosition(500, 20);
	glutCreateWindow(argv[0]);

	/* Registracija callback funkcija */
	glutKeyboardFunc(on_keyboard);
	glutReshapeFunc(on_reshape);
	glutDisplayFunc(on_display);
	glutSpecialFunc(on_specijalkey);

	/* Inicijalizuje se seed za random broj */
	srand(time(NULL));

	random_broj = (rand() % 7) + 1;
	animation_ongoing = 0;

	/* OpenGL inicijalizacija */
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);

	/* Program ulazi u glavnu petlju */
	glutMainLoop();

	return 0;
}

static void on_keyboard(unsigned char key, int x, int y){
	switch(key){
		case 27:
			exit(0);
			break;
		case 's':
		case 'S':
			/* Pokretanje igre */
			if(!animation_ongoing){
				glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
				animation_ongoing = 1;
			}
			glutPostRedisplay();
			break;
		case 'p':
		case 'P':
			/* Pauziranje igre */
			animation_ongoing = 0;
			break;
		case 'r':
		case 'R':
			/* Restartovanje igre */
			break;
		/* Rotiranje scene */
		case 'q':
		case 'Q':
			rotiraj_scenu +=5;
			glutPostRedisplay();
			break;
		case 'w':
		case 'W':
			rotiraj_scenu -=5;
			glutPostRedisplay();
			break;
	}

}

static void on_specijalkey(int key, int x, int y){
	switch(key){
		case GLUT_KEY_UP:
			break;
		case GLUT_KEY_DOWN:
			break;
		case GLUT_KEY_LEFT:
			break;
		case GLUT_KEY_RIGHT:
			break;
	}
	glutPostRedisplay();
}

static void on_reshape(int width, int height){

	/* Postavlja se viewpost */
	glViewport(0, 0, width, height);

	/* Postavljaju se parametri projekcije */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float) width / height, 1, 30);
}

static void on_display(void){

	/* Brise se predhodni sadrzaj prozora */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Podeesava se tacka pogleda */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(	15, 15, 6,
				15, 15, 0,
				0, 1, 0);
	glTranslatef(15, 15, 0);
	glRotatef(rotiraj_scenu, 0, 1, 0);

	/* Iscrtavam okvir */
	glPushMatrix();
		nacrtaj_okvir();
	glPopMatrix();

	/* Iscrtavam figuru */
	glPushMatrix();
		iscrtaj_figuru(random_broj);
	glPopMatrix();

	glutSwapBuffers();
}

static void on_timer(int value){
	if(value != TIMER_ID)
		return;

	glutPostRedisplay();
	if(animation_ongoing)
		glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);

}
/* Crta se okvir. */
static void nacrtaj_okvir(void){
	glScalef(2, 4.2, 0.2);
	glColor3f(1, 1, 1);
	glutWireCube(1);
	/* sakri_figuru(); */
}

/* Sakrivam figuru na vrhu. */
static void sakri_figuru(void){
	glTranslatef(0, 2.5, 0);
	glScalef(100, 0.8, 0.3);
	glColor3f(0, 0, 0);
	glutSolidCube(1);
}

static void iscrtaj_figuru(int x){

}

static void popuni_matricu(void){

}