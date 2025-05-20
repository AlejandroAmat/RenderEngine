#define STB_IMAGE_IMPLEMENTATION

#include "Camera.h"
#include "Light.h"
#include "Mesh.h"
#include "PointLight.h"
#include "Shader.h"
#include "Texture.h"
#include "Window.h"
#include "chrono"
#include "cstdio"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "vector"

std::vector<Mesh *> objList;
std::vector<Shader> shadersList;
const float toRadians = 3.14159265f / 180.0f;
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

void computeNormals(unsigned int *indices, unsigned int indexCount,
                    GLfloat *vertices, unsigned int vcount, unsigned vLength,
                    unsigned int normalOffset) {

  for (size_t k = 0; k < indexCount; k += 3) {

    unsigned int in0 = indices[k] * vLength;
    unsigned int in1 = indices[k + 1] * vLength;
    unsigned int in2 = indices[k + 2] * vLength;

    glm::vec3 v1((vertices[in1] - vertices[in0]),
                 (vertices[in1 + 1] - vertices[in0 + 1]),
                 (vertices[in1 + 2] - vertices[in0 + 2]));
    glm::vec3 v2((vertices[in2] - vertices[in0]),
                 (vertices[in2 + 1] - vertices[in0 + 1]),
                 (vertices[in2 + 2] - vertices[in0 + 2]));

    glm::vec3 norm = glm::normalize(glm::cross(v1, v2));
    in0 += normalOffset;
    in1 += normalOffset;
    in2 += normalOffset;
    vertices[in0] += norm.x;
    vertices[in0 + 1] += norm.y;
    vertices[in0 + 2] += norm.z;
    vertices[in1] += norm.x;
    vertices[in1 + 1] += norm.y;
    vertices[in1 + 2] += norm.z;
    vertices[in2] += norm.x;
    vertices[in2 + 1] += norm.y;
    vertices[in2 + 2] += norm.z;
  }

  for (size_t m = 0; m < (vcount / vLength); m++) {
    unsigned int offsetN = m * vLength + normalOffset;
    glm::vec3 norm_avg(vertices[offsetN], vertices[offsetN + 1],
                       vertices[offsetN + 2]);
    norm_avg = glm::normalize(norm_avg);
    vertices[offsetN] = norm_avg.x;
    vertices[offsetN + 1] = norm_avg.y;
    vertices[offsetN + 2] = norm_avg.z;
  }
}

void CreateObjects() {
  unsigned int indices[] = {0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2};

  // unsigned int indices[] = {
  //	2,3,0,
  //	1,3,2,
  //	0,3,1,
  //	0,1,2
  // };

  GLfloat vertices[] = {
      //	x      y      z			u	  v         nx    ny nz
      -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,  0.0f, 0.0f, -1.0f, -1.0f,
      0.5f,  0.0f,  0.0f, 0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,  0.0f,
      0.0f,  0.0f,  0.0f, 1.0f, 0.0f, 0.5f, 1.0f,  0.0f, 0.0f, 0.0f,
  };
  computeNormals(indices, 12, vertices, 32, 8, 5);

  Mesh *obj1 = new Mesh();
  obj1->createMesh(vertices, indices, 32, 12);
  objList.push_back(obj1);

  Mesh *obj2 = new Mesh();
  obj2->createMesh(vertices, indices, 32, 12);
  objList.push_back(obj2);
}

void createShaders() {
  Shader *shader = new Shader();
  shader->createShader("shaders/shader.vert", "shaders/shader.frag");
  shadersList.push_back(*shader);
}
int main() {

  Window mainWindow(800, 600);
  mainWindow.Initialize();
  CreateObjects();
  createShaders();
  GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0,
         uniformLightDir = 0, unoformLightAmbient = 0, uniformLightColor = 0,
         uniformDiffuse = 0, uniformViewPos = 0, uniformLightPos = 0;
  glm::mat4 projection = glm::perspective(glm::radians(60.0f),
                                          (GLfloat)mainWindow.getBufferWidth() /
                                              mainWindow.getBufferHeight(),
                                          0.1f, 100.0f);
  Texture t1("../Textures/brick.png");
  t1.loadTexture();

  Texture t2("../Textures/dirt.png");
  t2.loadTexture();

  Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
                -180.0f, 0.0f, 5.0f, 0.5f);
  /*std::unique_ptr<Light> lightPtr = std::make_unique<Light>(
          glm::vec3(0.0f, 10.0f, 0.0f),
          glm::vec3(0.7f, 0.5f, 0.8f),
          0.3f,
          0.2f
  );*/

  std::unique_ptr<PointLight> pointLight = std::make_unique<PointLight>(
      glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.7f, 0.5f, 0.8f), 0.6f, 0.4f,
      glm::vec3(3.0f, 0.5f, 6.0f));

  float grad = 0;
  while (!mainWindow.getShouldClose()) {
    glfwPollEvents();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    GLfloat now = glfwGetTime();
    deltaTime =
        now - lastTime; // (now - lastTime)*1000/SDL_GetPerformanceFrequency();
    lastTime = now;
    printf("FPS: %f\n", 1 / deltaTime);
    camera.keyControl(mainWindow.getsKeys(), deltaTime);
    camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
    glfwSwapInterval(0);
    grad += deltaTime * 60;
    shadersList[0].useShader();

    uniformModel = shadersList[0].getModelUniform();
    uniformProjection = shadersList[0].getProjectionUniform();
    uniformView = shadersList[0].getViewUniform();
    uniformLightColor = shadersList[0].getLightColorUniform();
    uniformLightDir = shadersList[0].getLightDirectionUniform();
    unoformLightAmbient = shadersList[0].getLightAmbientUniform();
    uniformDiffuse = shadersList[0].getLightDiffuseUniform();
    uniformViewPos = shadersList[0].getViewPosition();
    uniformLightPos = shadersList[0].getLightPosUniform();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(
        model, glm::vec3(0.0f, 0.0f, -2.5f)); // Optional: Translate if needed

    model = glm::rotate(model, glm::radians(grad),
                        glm::vec3(0.0f, 1.0f, 0.0f)); // Optional: Rotate

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE,
                       glm::value_ptr(projection));
    glUniformMatrix4fv(uniformView, 1, GL_FALSE,
                       glm::value_ptr(camera.calculateViewMatrix()));
    glm::vec3 pos = camera.return_position();
    glUniform3f(uniformViewPos, pos.x, pos.y, pos.z);
    pointLight->useLight(uniformLightColor, uniformLightDir,
                         unoformLightAmbient, uniformDiffuse, uniformLightPos);
    t1.useTexture();
    objList[1]->RenderMesh();

    glm::mat4 model_0 = glm::mat4(1.0f);
    model_0 = glm::translate(model_0, glm::vec3(0.0f, 1.0f, -2.4f));
    model_0 = glm::rotate(model_0, glm::radians(grad),
                          glm::vec3(0.0f, 1.0f, 0.0f)); // Optional: Rotate

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model_0));
    t2.useTexture();
    objList[0]->RenderMesh();
    glUseProgram(0);
    mainWindow.swapBuffers();
  }
}
