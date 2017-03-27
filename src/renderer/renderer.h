#pragma once
#include "GLUtil.h"
#include "model/Model.h"
#include "skybox/Skybox.h"
#include "camera.h"
#include "../input/input.h"
#include <memory>
#include "../entity/Light.h"
#include "../entity/Walls.h"
#include "model\Texture.h"
#include "text2D.h"
#include "../BuildFlags.h"

struct renderWindowData {
    int xPos = 0;
    int yPos = 0;
    int width = 0;
    int height = 0;
};

class Renderer {
	int index;
    Camera * cam; // 1 cam per renderer
    Skybox * skybox;

    // Light might need to be elsewhere
    Light * light;

    int stencil_bit = 0;

    void initSkybox();
    void drawSkybox(glm::mat4 &perspectiveMatrix);

    // Control model-rendering flow
    void renderModel(const Model& model, glm::mat4 &perspectiveMatrix, glm::mat4 scale, glm::mat4 rot, glm::mat4 trans);

    // Render black-border silhouettes
    void drawSil(const Model& model, glm::mat4 &perspectiveMatrix, glm::mat4 &mmatrix);

    // Actually draw each model using standard shading
    void drawShade(const Model& model, glm::mat4 &perspectiveMatrix, glm::mat4 scale, glm::mat4 rot, glm::mat4 trans, bool reflects = false, bool flipUv = false);

    // Control track-reflection rendering
    void reflectCar(Car* car, glm::mat4 &perspectiveMatrix, float reflectivity = 0.5f);
    void reflectWalls(Walls* walls, glm::mat4 &perspectiveMatrix, float reflectivity = 0.5f);

    // Draw reflections onto the track surface
    void drawTrack(const Model& model, glm::mat4 &perspectiveMatrix, glm::mat4 scale, glm::mat4 rot, glm::mat4 trans, float reflectivity = 0.0f);

    GLuint mm_frameBuffer;
    GLuint mm_tex;

    //Text rendering
    void Renderer::initText();
    Text2D * blueText;
    Text2D * blackText;
    Text2D * redText;
    Text2D * whiteText;
    Text2D * mmPips;
    Text2D * hookNotReady1;
    Text2D * hookNotReady2;
    Text2D * hookNotReady3;
    Text2D * hookReady;
    
    // Init a frame buffer for a depth map, used for shadow mapping + silhouetting
    bool initDepthFrameBuffer(GLuint &frameBuffer, GLuint &depthTex, int width, int height);
    bool initColorFrameBuffer(GLuint &frameBuffer, GLuint &colTex, int width, int height);

    int width;
    int height;
    float SM_res = 8192;
    void drawText();
    void drawDropShadowText(const char* string, Text2D* front, Text2D* back, int x, int y, int size, int offset);
    int frameCount = 0;
    bool alphaTest = false;
    int mmSize = 400;
    float UIScale = 1.0;
    int vpX, vpY = 0; // viewport dimensions
    

public:

    static bool shadowsInitialized;
    static bool shadowsFilled;

    // Shadow mapping functions
    void renderShadowMap(const std::vector<Entity*>& ents);
    void addToShadowMap(const Model& model, glm::mat4 model_matrix, int startElement);

    // The following are all required for shadow mapping 
    // We need to decide of we want to move them to a seperate location or not 
    GLuint SM_frameBuffer;
    static GLuint SM_depthTex;
    static glm::mat4 depthMVP;

	Renderer(int);
	~Renderer();
    void postGLInit(); // call init functions after Window's created the OpenGL env.
    void initFrameBuffer();
	void drawScene(const std::vector<Entity*>& ents);
    void renderMiniMap(const std::vector<Entity*>& ents, const std::vector<Car*>& cars, float height, int size, int xPos, int yPos, float sWidth, float sHeight, float alpha = 0.8);
    void setDims(renderWindowData& rwd);

    // Control a full screen draw
    void draw(const std::vector<Entity*>& ents, const std::vector<Car*>& cars);
    void drawCountDown(int time);
    int getMMSize();
    int getWidth();
    int getHeight();

    Camera* getCam();
};