#include "Render.h"
#include <Windows.h>
#include <GL\GL.h>
#include <GL\GLU.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "GUItextRectangle.h"
#include "MyShaders.h"
#include "Texture.h"


#include "ObjLoader.h"


#include "debout.h"



//внутренняя логика "движка"
#include "MyOGL.h"
extern OpenGL gl;
#include "Light.h"
Light light;
#include "Camera.h"
Camera camera;


bool texturing = true;
bool lightning = true;
bool alpha = false;

double* normal(double* A, double* B, double* C, int size)
{

	double* u1 = new double[size];
	double* u2 = new double[size];

	for (int i = 0; i < size; i++)
	{
		u1[i] = B[i] - A[i];
		u2[i] = C[i] - A[i];
	}
	/* cout << u1[0] << "   " << u1[1] << "     " << u1[2];
	 cout << u2[0] << "   " << u2[1] << "     " << u2[2];*/


	double* norma = new double[3];

	norma[0] = u1[1] * u2[2] - u1[2] * u2[1];
	norma[1] = u1[2] * u2[0] - u1[0] * u2[2];
	norma[2] = u1[0] * u2[1] - u1[1] * u2[0];

	double dlina = sqrt((norma[0] * norma[0]) + (norma[1] * norma[1]) + (norma[2] * norma[2]));
	//cout << norma[0] << "   " << norma[1] << "     " << norma[2];

	if (dlina != 0) {
		norma[0] /= -dlina;
		norma[1] /= -dlina;
		norma[2] /= -dlina;
	}


	delete[] u1;
	delete[] u2;

	return norma;
}
GLuint texId;

void pyro()
{
	double A[]{ 4, 6, 0 };
	double B[]{ 10, -1, 0 };
	double C[]{ 3,-4, 0 };
	double D[]{ 0,-1, 0 };
	double E[]{ -4, -7, 0 };
	double F[]{ -2, -1, 0 };
	double G[]{ -5,2, 0 };
	double H[]{ 0, 1, 0 };

	double A1[]{ 4, 6, 5 };
	double B1[]{ 10, -1, 5 };
	double C1[]{ 3,-4, 5 };
	double D1[]{ 0,-1, 5 };
	double E1[]{ -4, -7, 5 };
	double F1[]{ -2, -1, 5 };
	double G1[]{ -5,2, 5 };
	double H1[]{ 0, 1, 5 };


	////////////////////////КРЫШКА//////////////////////////////////////////////////////

	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, -1);
	glColor3d(0, 255, 255);
	glVertex3dv(A);
	glVertex3dv(H);
	glVertex3dv(B);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, -1);
	glColor3d(102, 0, 204);
	glVertex3dv(H);
	glVertex3dv(F);
	glVertex3dv(B);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, -1);
	glColor3d(0, 0, 255);
	glVertex3dv(D);
	glVertex3dv(B);
	glVertex3dv(C);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, -1);
	glColor3d(0, 255, 0);
	glVertex3dv(H);
	glVertex3dv(F);
	glVertex3dv(G);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, -1);
	glColor3d(150, 150, 0);
	glVertex3dv(F);
	glVertex3dv(D);
	glVertex3dv(E);
	glEnd();



	//////////////////////////////////////////////////////////////////////////////////////



	///////////////////////////////ДНО///////////////////////////////////////////////////
	glBindTexture(GL_TEXTURE_2D, texId);
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, 6);
	glColor3d(0, 255, 255);
	glTexCoord2d(0.63, 1);
	glVertex3dv(A1);
	glTexCoord2d(0.35, 0.56);
	glVertex3dv(H1);
	glTexCoord2d(1, 0.42);
	glVertex3dv(B1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texId);
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, 6);
	glColor3d(102, 0, 204);
	glTexCoord2d(0.35, 0.56);
	glVertex3dv(H1);
	glTexCoord2d(0.21, 0.42);
	glVertex3dv(F1);
	glTexCoord2d(1, 0.42);
	glVertex3dv(B1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texId);
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, 6);
	glColor3d(0, 0, 255);
	glTexCoord2d(0.35, 0.42);
	glVertex3dv(D1);
	glTexCoord2d(1, 0.42);
	glVertex3dv(B1);
	glTexCoord2d(0.56, 0.21);
	glVertex3dv(C1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texId);
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, 6);
	glColor3d(0, 255, 0);
	glTexCoord2d(0.35, 0.56);
	glVertex3dv(H1);
	glTexCoord2d(0.21, 0.42);
	glVertex3dv(F1);
	glTexCoord2d(0, 0.63);
	glVertex3dv(G1);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, texId);
	glBegin(GL_TRIANGLES);
	glNormal3d(0, 0, 6);
	glColor3d(150, 150, 0);
	glTexCoord2d(0.21, 0.42);
	glVertex3dv(F1);
	glTexCoord2d(0.35, 0.42);
	glVertex3dv(D1);
	glTexCoord2d(0, 0);
	glVertex3dv(E1);
	glEnd();


	//////////////////////////////////////////////////////////////////////////////////


	///////////////////////ГРАНИ/////////////////////////////////////////////////////

	glBegin(GL_QUADS);
	double* norm1 = normal(A, B, B1, 3);
	glNormal3dv(norm1);
	glColor3d(0.1, 1, 0.1);
	glVertex3dv(A);
	glVertex3dv(B);
	glVertex3dv(B1);
	glVertex3dv(A1);
	glEnd();

	glBegin(GL_QUADS);
	double* norm = normal(C, D, C1, 3);
	glNormal3dv(norm);
	glColor3d(0.3, 0.6, 0.9);
	glVertex3dv(C);
	glVertex3dv(D);
	glVertex3dv(D1);
	glVertex3dv(C1);
	glEnd();

	glBegin(GL_QUADS);
	double* norm2 = normal(B, C, C1, 3);
	glNormal3dv(norm2);
	glColor3d(0, 0, 0);
	glVertex3dv(B);
	glVertex3dv(C);
	glVertex3dv(C1);
	glVertex3dv(B1);
	glEnd();

	glBegin(GL_QUADS);
	double* norm3 = normal(D, E, E1, 3);
	glNormal3dv(norm3);
	glColor3d(0.5, 0.5, 0.5);
	glVertex3dv(D);
	glVertex3dv(E);
	glVertex3dv(E1);
	glVertex3dv(D1);
	glEnd();

	glBegin(GL_QUADS);
	double* norm4 = normal(E, F, F1, 3);
	glNormal3dv(norm4);
	glColor3d(0.3, 0.2, 0.7);
	glVertex3dv(E);
	glVertex3dv(F);
	glVertex3dv(F1);
	glVertex3dv(E1);
	glEnd();

	glBegin(GL_QUADS);
	double* norm5 = normal(F, G, G1, 3);
	glNormal3dv(norm5);
	glColor3d(0.8, 0.3, 0.1);
	glVertex3dv(F);
	glVertex3dv(G);
	glVertex3dv(G1);
	glVertex3dv(F1);
	glEnd();

	glBegin(GL_QUADS);
	double* norm6 = normal(G, H, H1, 3);
	glNormal3dv(norm6);
	glColor3d(0.2, 0.3, 0);
	glVertex3dv(G);
	glVertex3dv(H);
	glVertex3dv(H1);
	glVertex3dv(G1);
	glEnd();

	glBegin(GL_QUADS);
	double* norm7 = normal(H, A, A1, 3);
	glNormal3dv(norm7);
	glColor3d(0.8, 0.4, 0);
	glVertex3dv(H);
	glVertex3dv(A);
	glVertex3dv(A1);
	glVertex3dv(H1);
	glEnd();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

//переключение режимов освещения, текстурирования, альфаналожения
void switchModes(OpenGL *sender, KeyEventArg arg)
{
	//конвертируем код клавиши в букву
	auto key = LOWORD(MapVirtualKeyA(arg.key, MAPVK_VK_TO_CHAR));

	switch (key)
	{
	case 'L':
		lightning = !lightning;
		break;
	case 'T':
		texturing = !texturing;
		break;
	case 'A':
		alpha = !alpha;
		break;
	}
}

//умножение матриц c[M1][N1] = a[M1][N1] * b[M2][N2]
template<typename T, int M1, int N1, int M2, int N2>
void MatrixMultiply(const T* a, const T* b, T* c)
{
	for (int i = 0; i < M1; ++i)
	{
		for (int j = 0; j < N2; ++j)
		{
			c[i * N2 + j] = T(0);
			for (int k = 0; k < N1; ++k)
			{
				c[i * N2 + j] += a[i * N1 + k] * b[k * N2 + j];
			}
		}
	}
}

//Текстовый прямоугольничек в верхнем правом углу.
//OGL не предоставляет возможности для хранения текста
//внутри этого класса создается картинка с текстом (через виндовый GDI),
//в виде текстуры накладывается на прямоугольник и рисуется на экране.
//Это самый простой способ что то написать на экране
//но ооооочень не оптимальный
GuiTextRectangle text;

//айдишник для текстуры
//GLuint texId;
//выполняется один раз перед первым рендером

ObjModel f;


Shader cassini_sh;
Shader phong_sh;
Shader vb_sh;
Shader simple_texture_sh;

Texture stankin_tex, vb_tex, monkey_tex;



void initRender()
{

	
	//==============НАСТРОЙКА ТЕКСТУР================
	//4 байта на хранение пикселя
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	

	//================НАСТРОЙКА КАМЕРЫ======================
	camera.caclulateCameraPos();

	//привязываем камеру к событиям "движка"
	gl.WheelEvent.reaction(&camera, &Camera::Zoom);
	gl.MouseMovieEvent.reaction(&camera, &Camera::MouseMovie);
	gl.MouseLeaveEvent.reaction(&camera, &Camera::MouseLeave);
	gl.MouseLdownEvent.reaction(&camera, &Camera::MouseStartDrag);
	gl.MouseLupEvent.reaction(&camera, &Camera::MouseStopDrag);
	//==============НАСТРОЙКА СВЕТА===========================
	//привязываем свет к событиям "движка"
	gl.MouseMovieEvent.reaction(&light, &Light::MoveLight);
	gl.KeyDownEvent.reaction(&light, &Light::StartDrug);
	gl.KeyUpEvent.reaction(&light, &Light::StopDrug);
	//========================================================
	//====================Прочее==============================
	gl.KeyDownEvent.reaction(switchModes);
	text.setSize(512, 180);
	//========================================================
	   

	camera.setPosition(2, 1.5, 1.5);
	
}
float view_matrix[16];
double full_time = 0;
int location = 0;
void Render(double delta_time)
{    
	

	full_time += delta_time;
	
	//натройка камеры и света
	//в этих функциях находятся OGLные функции
	//которые устанавливают параметры источника света
	//и моделвью матрицу, связанные с камерой.

	if (gl.isKeyPressed('F')) //если нажата F - свет из камеры
	{
		light.SetPosition(camera.x(), camera.y(), camera.z());
	}
	camera.SetUpCamera();
	//забираем моделвью матрицу сразу после установки камера
	//так как в ней отсуствуют трансформации glRotate...
	//она, фактически, является видовой.
	glGetFloatv(GL_MODELVIEW_MATRIX,view_matrix);

	

	light.SetUpLight();

	//рисуем оси
	gl.DrawAxes();

	

	glBindTexture(GL_TEXTURE_2D, 0);

	//включаем нормализацию нормалей
	//чтобв glScaled не влияли на них.

	glEnable(GL_NORMALIZE);  
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	
	//включаем режимы, в зависимости от нажания клавиш. см void switchModes(OpenGL *sender, KeyEventArg arg)
	if (lightning)
		glEnable(GL_LIGHTING);
	if (texturing)
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0); //сбрасываем текущую текстуру
	}
		
	if (alpha)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
		
	//=============НАСТРОЙКА МАТЕРИАЛА==============


	//настройка материала, все что рисуется ниже будет иметь этот метериал.
	//массивы с настройками материала
	float  amb[] = { 0.2, 0.2, 0.1, 1. };
	float dif[] = { 0.4, 0.65, 0.5, 1. };
	float spec[] = { 0.9, 0.8, 0.3, 1. };
	float sh = 0.2f * 256;

	//фоновая
	glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
	//дифузная
	glMaterialfv(GL_FRONT, GL_DIFFUSE, dif);
	//зеркальная
	glMaterialfv(GL_FRONT, GL_SPECULAR, spec); 
	//размер блика
	glMaterialf(GL_FRONT, GL_SHININESS, sh);

	//чтоб было красиво, без квадратиков (сглаживание освещения)
	glShadeModel(GL_SMOOTH); //закраска по Гуро      
			   //(GL_SMOOTH - плоская закраска)

	//============ РИСОВАТЬ ТУТ ==============

	pyro();

	

	
	
	//сбрасываем все трансформации
	glLoadIdentity();
	camera.SetUpCamera();	
	//рисуем источник света
	light.DrawLightGizmo();

	//================Сообщение в верхнем левом углу=======================
	
	//переключаемся на матрицу проекции
	glMatrixMode(GL_PROJECTION);
	//сохраняем текущую матрицу проекции с перспективным преобразованием
	glPushMatrix();
	//загружаем единичную матрицу в матрицу проекции
	glLoadIdentity();

	//устанавливаем матрицу паралельной проекции
	glOrtho(0, gl.getWidth() - 1, 0, gl.getHeight() - 1, 0, 1);

	//переключаемся на моделвью матрицу
	glMatrixMode(GL_MODELVIEW);
	//сохраняем матрицу
	glPushMatrix();
    //сбразываем все трансформации и настройки камеры загрузкой единичной матрицы
	glLoadIdentity();

	//отрисованное тут будет визуалзироватся в 2д системе координат
	//нижний левый угол окна - точка (0,0)
	//верхний правый угол (ширина_окна - 1, высота_окна - 1)

	
	std::wstringstream ss;
	ss << std::fixed << std::setprecision(3);
	ss << "T - " << (texturing ? L"[вкл]выкл  " : L" вкл[выкл] ") << L"текстур" << std::endl;
	ss << "L - " << (lightning ? L"[вкл]выкл  " : L" вкл[выкл] ") << L"освещение" << std::endl;
	ss << "A - " << (alpha ? L"[вкл]выкл  " : L" вкл[выкл] ") << L"альфа-наложение" << std::endl;
	ss << L"F - Свет из камеры" << std::endl;
	ss << L"G - двигать свет по горизонтали" << std::endl;
	ss << L"G+ЛКМ двигать свет по вертекали" << std::endl;
	ss << L"Коорд. света: (" << std::setw(7) <<  light.x() << "," << std::setw(7) << light.y() << "," << std::setw(7) << light.z() << ")" << std::endl;
	ss << L"Коорд. камеры: (" << std::setw(7) << camera.x() << "," << std::setw(7) << camera.y() << "," << std::setw(7) << camera.z() << ")" << std::endl;
	ss << L"Параметры камеры: R=" << std::setw(7) << camera.distance() << ",fi1=" << std::setw(7) << camera.fi1() << ",fi2=" << std::setw(7) << camera.fi2() << std::endl;
	ss << L"delta_time: " << std::setprecision(5)<< delta_time << std::endl;
	ss << L"full_time: " << std::setprecision(2) << full_time << std::endl;

	
	text.setPosition(10, gl.getHeight() - 10 - 180);
	text.setText(ss.str().c_str());
	
	text.Draw();

	//восстанавливаем матрицу проекции на перспективу, которую сохраняли ранее.
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	
	
}   



