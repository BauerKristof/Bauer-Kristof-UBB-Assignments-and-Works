#include "GLWidget.h"
#include "../Core/Materials.h"
#include "../Core/Lights.h"

#if !defined(__APPLE__)
#include <GL/glu.h>
#endif

#include <iostream>
#include "../Core/Matrices.h"
#include "../Test/TestFunctions.h"

using namespace std;

#include <Core/Exceptions.h>

namespace cagd
{
    //--------------------------------
    // special and default constructor
    //--------------------------------
    GLWidget::GLWidget(QWidget *parent, const QGLFormat &format): QGLWidget(format, parent)
    {
        _timer=new QTimer(this);
        _timer->setInterval(0);
        connect(_timer,SIGNAL(timeout()),this,SLOT(_animate()));
    }


    GLWidget::~GLWidget()
       {
           if (_pc) delete _pc;
           _pc = nullptr;

           if (_image_of_pc) delete _image_of_pc;
           _image_of_pc = nullptr;
       }

    //--------------------------------------------------------------------------------------
    // this virtual function is called once before the first call to paintGL() or resizeGL()
    //--------------------------------------------------------------------------------------
    void GLWidget::initializeGL()
    {
        // creating a perspective projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = (double)width() / (double)height();
        _z_near = 1.0;
        _z_far  = 1000.0;
        _fovy   = 45.0;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // setting the model view matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        _eye[0] = _eye[1] = 0.0; _eye[2] = 6.0;
        _center[0] = _center[1] = _center[2] = 0.0;
        _up[0] = _up[2] = 0.0; _up[1] = 1.0;

        gluLookAt(_eye[0], _eye[1], _eye[2], _center[0], _center[1], _center[2], _up[0], _up[1], _up[2]);

        // enabling the depth test
        glEnable(GL_DEPTH_TEST);

        // setting the background color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // initial values of transformation parameters
        _angle_x = _angle_y = _angle_z = 0.0;
        _trans_x = _trans_y = _trans_z = 0.0;
        _zoom = 1.0;

        // ...

        try
        {
            // initializing the OpenGL Extension Wrangler library
            GLenum error = glewInit();

            if (error != GLEW_OK)
            {
                throw Exception("Could not initialize the OpenGL Extension Wrangler Library!");
            }

            if (!glewIsSupported("GL_VERSION_2_0"))
            {
                throw Exception("Your graphics card is not compatible with OpenGL 2.0+! "
                                "Try to update your driver or buy a new graphics adapter!");
            }

            // create and store your geometry in display lists or vertex buffer objects
            // ...

            hazi=3; //TODO:paralelogramma, checkboxok lab2, triangulatedmeshes lab3gui

            glEnable(GL_POINT_SMOOTH);
            glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
            glEnable(GL_LINE_SMOOTH);
            glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
            glEnable(GL_POLYGON_SMOOTH);
            glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
            glEnable(GL_DEPTH_TEST);

            glewInit();

            if (_mouse.LoadFromOFF("Models/mouse.off", true)) {
                        if(_mouse.UpdateVertexBufferObjects(GL_DYNAMIC_DRAW)) {
                            _angle = 0.0;
                            _timer->start();
                        }
                    }
                    else {
                        std::cout << "Couldn't load OFF file!" << std::endl;
                    }

            if(hazi==1)
            {
            //Lab2
            _parametric_curve_index = 0;
            create_parametric_curves();
            load_parametric_curve(0);
            }

            //Lab3
            if(hazi==2)
            {
            _parametric_surface_index=0;
            create_parametric_surfaces();
            load_parametric_surfaces(0);
            }

            if(hazi==3)
             {
            //Lab3 - PlayGround
             create_playground();
             }

        }
        catch (Exception &e)
        {
            cout << e << endl;
        }
    }

    //-----------------------
    // the rendering function
    //-----------------------
    void GLWidget::paintGL()
    {
        // clears the color and depth buffers
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // stores/duplicates the original model view matrix
        glPushMatrix();

            // applying transformations
            glRotatef(_angle_x, 1.0, 0.0, 0.0);
            glRotatef(_angle_y, 0.0, 1.0, 0.0);
            glRotatef(_angle_z, 0.0, 0.0, 1.0);
            glTranslated(_trans_x, _trans_y, _trans_z);
            glScaled(_zoom, _zoom, _zoom);

            // render your geometry (this is oldest OpenGL rendering technique, later we will use some advanced methods)

            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_LINES);
                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(1.1f, 0.0f, 0.0f);

                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 1.1f, 0.0f);

                glVertex3f(0.0f, 0.0f, 0.0f);
                glVertex3f(0.0f, 0.0f, 1.1f);
            glEnd();


            //Lab2
            if(hazi==1)
            {
            render_parametric_curves();
            }

            //Lab3
            if(hazi==2)
            {
            glEnable(GL_LIGHT0);
            glEnable(GL_NORMALIZE);
            glEnable(GL_LIGHTING);

            //MatFBPearl.Apply();
            //_mouse.Render();

            //MatFBSilver.Apply();
            render_parametric_surfaces();


            glDisable(GL_LIGHTING);
            glDisable(GL_NORMALIZE);
            glDisable(GL_LIGHT0);
            }

            if(hazi==3)
            {
            //Lab3 PlayGround
            render_playground();
            }


        // pops the current matrix stack, replacing the current matrix with the one below it on the stack,
        // i.e., the original model view matrix is restored
        glPopMatrix();
    }

    //----------------------------------------------------------------------------
    // when the main window is resized one needs to redefine the projection matrix
    //----------------------------------------------------------------------------
    void GLWidget::resizeGL(int w, int h)
    {
        // setting the new size of the rendering context
        glViewport(0, 0, w, h);

        // redefining the projection matrix
        glMatrixMode(GL_PROJECTION);

        glLoadIdentity();

        _aspect = (double)w / (double)h;

        gluPerspective(_fovy, _aspect, _z_near, _z_far);

        // switching back to the model view matrix
        glMatrixMode(GL_MODELVIEW);

        updateGL();
    }
    void GLWidget::_animate() {
        GLfloat *vertex = _mouse.MapVertexBuffer(GL_READ_WRITE);
        GLfloat *normal = _mouse.MapNormalBuffer(GL_READ_ONLY);

        _angle += DEG_TO_RADIAN;
        if (_angle >= TWO_PI ) {
            _angle -= TWO_PI;
        }

        GLfloat scale = sin(_angle) / 3000.0;
        for(GLuint i = 0; i < _mouse.VertexCount(); i++) {
            for(GLuint coordinate = 0; coordinate < 3; ++coordinate, ++vertex, ++normal) {
                *vertex += scale * (*normal);
            }
        }

        _mouse.UnmapVertexBuffer();
        _mouse.UnmapNormalBuffer();

        updateGL();
    }

    //-----------------------------------
    // implementation of the public slots
    //-----------------------------------

    void GLWidget::set_angle_x(int value)
    {
        if (_angle_x != value)
        {
            _angle_x = value;
            updateGL();
        }
    }

    void GLWidget::set_angle_y(int value)
    {
        if (_angle_y != value)
        {
            _angle_y = value;
            updateGL();
        }
    }

    void GLWidget::set_angle_z(int value)
    {
        if (_angle_z != value)
        {
            _angle_z = value;
            updateGL();
        }
    }

    void GLWidget::set_zoom_factor(double value)
    {
        if (_zoom != value)
        {
            _zoom = value;
            updateGL();
        }
    }

    void GLWidget::set_trans_x(double value)
    {
        if (_trans_x != value)
        {
            _trans_x = value;
            updateGL();
        }
    }

    void GLWidget::set_trans_y(double value)
    {
        if (_trans_y != value)
        {
            _trans_y = value;
            updateGL();
        }
    }

    void GLWidget::set_trans_z(double value)
    {
        if (_trans_z != value)
        {
            _trans_z = value;
            updateGL();
        }
    }

    void GLWidget::create_parametric_curves() {

        _pcs.ResizeColumns(7);

        RowMatrix<ParametricCurve3::Derivative> derivative(3);

         derivative (0) = spiral_on_cone::d0;
         derivative (1) = spiral_on_cone::d1;
         derivative (2) = spiral_on_cone::d2;
         _pcs[0] = new ( nothrow ) ParametricCurve3(derivative, spiral_on_cone::u_min, spiral_on_cone::u_max);

         derivative(0)=viviani::d0;
         derivative(1)=viviani::d1;
         derivative(2)=viviani::d2;
         _pcs[1]=new ( nothrow ) ParametricCurve3(derivative,viviani::u_min,viviani::u_max);

         derivative(0)=lissajou::d0;
         derivative(1)=lissajou::d1;
         derivative(2)=lissajou::d2;
         _pcs[2] = new ( nothrow ) ParametricCurve3(derivative, lissajou::u_min, lissajou::u_max);


         derivative(0)=hypocycloid::d0;
         derivative(1)=hypocycloid::d1;
         derivative(2)=hypocycloid::d2;
         _pcs[3] = new ( nothrow ) ParametricCurve3(derivative, hypocycloid::u_min, hypocycloid::u_max);

         derivative(0)=cycloid::d0;
         derivative(1)=cycloid::d1;
         derivative(2)=cycloid::d2;
         _pcs[4] = new ( nothrow ) ParametricCurve3(derivative, cycloid::u_min, cycloid::u_max);

         derivative(0)=rose::d0;
         derivative(1)=rose::d1;
         derivative(2)=rose::d2;
         _pcs[5] = new ( nothrow ) ParametricCurve3(derivative, rose::u_min, rose::u_max);

         derivative(0)=spring::d0;
         derivative(1)=spring::d1;
         derivative(2)=spring::d2;
         _pcs[6] = new ( nothrow ) ParametricCurve3(derivative, spring::u_min, spring::u_max);
    }

    void GLWidget::create_parametric_surfaces() {
            //std::cout << "Creating parametric surface objects!" << std::endl;

            _pss.ResizeColumns(6);

            TriangularMatrix<ParametricSurface3::PartialDerivative> derivative(2);

            derivative (0, 0) = sphere::d00;
            derivative (1, 0) = sphere::d10;
            derivative (1, 1) = sphere::d01;
            _pss[0] = new ( nothrow ) ParametricSurface3(derivative, sphere::u_min, sphere::u_max, sphere::v_min, sphere::v_max);

            derivative (0, 0) = tube::d00;
            derivative (1, 0) = tube::d10;
            derivative (1, 1) = tube::d01;
            _pss[1] = new ( nothrow ) ParametricSurface3(derivative, tube::u_min, tube::u_max, tube::v_min, tube::v_max);

            derivative (0, 0) = paralelogram::d00;
            derivative (1, 0) = paralelogram::d10;
            derivative (1, 1) = paralelogram::d01;
            _pss[2] = new ( nothrow ) ParametricSurface3(derivative, paralelogram::u_min, paralelogram::u_max, paralelogram::v_min, paralelogram::v_max);

            derivative (0, 0) = revolvingCurve::d00;
            derivative (1, 0) = revolvingCurve::d10;
            derivative (1, 1) = revolvingCurve::d01;
            _pss[3] = new ( nothrow ) ParametricSurface3(derivative, revolvingCurve::u_min, revolvingCurve::u_max, revolvingCurve::v_min, revolvingCurve::v_max);

            derivative (0, 0) = torus::d00;
            derivative (1, 0) = torus::d10;
            derivative (1, 1) = torus::d01;
            _pss[4] = new ( nothrow ) ParametricSurface3(derivative, torus::u_min, torus::u_max, torus::v_min, torus::v_max);

            derivative (0, 0) = cone::d00;
            derivative (1, 0) = cone::d10;
            derivative (1, 1) = cone::d01;
            _pss[5] = new ( nothrow ) ParametricSurface3(derivative, cone::u_min, cone::u_max, cone::v_min, cone::v_max);
        }

    void GLWidget::load_parametric_curve(int index) {
           _parametric_curve_index = index;
           _pc = _pcs[_parametric_curve_index];

           if(!_pc) {
               std::cerr << "Not existing curve" << std::endl;
               exit(1);
           }

           GLuint div_point_count = 200;
           if(index == 2 || index == 6) {
               div_point_count = 1000;
           }
           GLenum usage_flag = GL_STATIC_DRAW;

           _image_of_pc = nullptr;
           _image_of_pc = _pc->GenerateImage(div_point_count, usage_flag);

           if(!_image_of_pc) {
               std::cerr << "Cannot generate image" << std::endl;
           }
           if(_image_of_pc->UpdateVertexBufferObjects(usage_flag)) {
               std::cout << "Could not create the vertex buffer object of the parametric curve!" << std::endl;
           }
           updateGL();
       }

    void GLWidget::load_parametric_surfaces(int index) {
        _parametric_surface_index = index;
        _ps = _pss[_parametric_surface_index];

        if(!_ps) {
            std::cerr << "Not existing surface" << std::endl;
            exit(1);
        }

        GLuint u_div_point_count = 200;
        GLuint v_div_point_count = 200;
        GLenum usage_flag = GL_STATIC_DRAW;

        _image_of_ps = nullptr;
        _image_of_ps = _ps->GenerateImage(u_div_point_count, v_div_point_count, usage_flag);

        if(!_image_of_ps) {
            std::cerr << "Cannot generate image" << std::endl;
        }
        if(!_image_of_ps->UpdateVertexBufferObjects(usage_flag)) {
            std::cout << "Could not create the vertex buffer object of the parametric surface!" << std::endl;
        }
        updateGL();
    }

    void GLWidget::render_parametric_curves() {
           glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

           glPushMatrix();

               if(_image_of_pc) {
                   glColor3f(1.0f, 0.0f, 0.0f);
                   _image_of_pc->RenderDerivatives(0, GL_LINE_STRIP);

                   glPointSize(5.0f);

                       // TODO: Check if derivatives are necessary

                       glColor3f(0.0f, 0.5f, 0.0f);
                       _image_of_pc->RenderDerivatives(1, GL_LINES);
                       _image_of_pc->RenderDerivatives(1, GL_POINTS);

                       glColor3f(0.1f, 0.5f, 0.9f);
                       _image_of_pc->RenderDerivatives(2, GL_LINES);
                       _image_of_pc->RenderDerivatives(2, GL_POINTS);

                   glPointSize(1.0f);
               }

           glPopMatrix();
       }

    void GLWidget::render_parametric_surfaces() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();

            glColor3f(1.0f, 0.0f, 0.0f);
            if(_image_of_ps) {
                _image_of_ps->Render(GL_TRIANGLES);
            }

        glPopMatrix();
    }


    void GLWidget::create_playground() {
        _platform.ResizeColumns(8);
        _platform.ResizeRows(8);

        // Create base platform of playground
        for(GLuint i = 0; i < _platform.GetRowCount(); i++) {
            for(GLuint j = 0; j < _platform.GetColumnCount(); j++) {
                _platform(i, j).LoadFromOFF("Models/cube.off", true);
                _platform(i, j).UpdateVertexBufferObjects();
            }
        }
        std::cout<<"The playground is succesfully created"<<std::endl;
    }


    void GLWidget::render_playground() {
        GLdouble offset_x = 0.0,
                 offset_y=0.0,
                 offset_z = 0.0;


        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);

        glPushMatrix();

            for(GLuint i = 0; i < 5; i++) {
                offset_z = 0.0;
                for(GLuint j = 0; j < 5; j++) {
                    glPushMatrix();
                        glTranslated(offset_x, 0.0, offset_z);

                            MatFBSilver.Apply();
                            _platform(i, j).Render();

                    glPopMatrix();
                    offset_z += 1.0;
                }
                offset_x += 1.0;
            }

            offset_x=2.0;
            offset_y=1.0;
                for(GLuint j = 5; j <_platform.GetColumnCount(); j++) {
                    glPushMatrix();
                        glTranslated(offset_x, offset_y, 4.0);

                            MatFBGold.Apply();
                            _platform(5, j).Render();

                    glPopMatrix();
                    offset_y += 1.0;
                }

                glTranslated(offset_x, offset_y, 4.0);
                MatFBGold.Apply();
                _mouse.Render();

        glPopMatrix();

        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
        glDisable(GL_NORMALIZE);
    }

}
