#ifndef __TSUBAKI_CONTROLLER__
#define __TSUBAKI_CONTROLLER__

#include <unordered_map>
#include <stack>


class Object;
class LightBase;
class DirectionalLight;
class PointLight;
class AmbientLight;
class Camera;

class Controller{
public:
    static int InsertObject(const Object* object);
    static void RemoveObject(const int ID);
    static void InsertDirectionalLight(const int ID);
    static void InsertPointLight(const int ID);
    static void RemoveDirectionalLight(const int ID);
    static void RemovePointLight(const int ID);
    static void InsertAmbientLight(const int ID);
    static void RemoveAmbientLight(const int ID);
    static void InsertCamera(const int ID);
    static void RemoveCamera(const int ID);


    static int GetDirectionalLightNum();
    static int GetPointLightNum();
    static int GetAmbientLightNum();
    static int GetCameraNum();
    static PointLight* GetPointLight(const int index);
    static DirectionalLight* GetDirectionalLight(const int index);
    static AmbientLight* GetAmbientLight(const int index);
    static Camera* GetCamera(const int index);
    static void SetCurrCamera(const int ID);
    static Camera* GetCurrCamera();

    static void UpdateObject(float delta_time);
    virtual ~Controller();
private:
    Controller();
    static Controller* GetController();
    int GenID();
    void RemoveFromList(std::vector<int>& list,int ID);
    int InsertObject_(const Object* object);
    void RemoveObejct_(const int ID);
    void UpdateObject_(float delta_time);
    void InsertDirectionalLight_(const int ID);
    void InsertPointLight_(const int ID);
    void RemoveDirectionalLight_(const int ID);
    void RemovePointLight_(const int ID);
    static Controller* controller_instance;
    std::unordered_map<int,Object*> object_map;

    std::vector<int> directional_light_list;
    std::vector<int> point_light_list;
    std::vector<int> ambient_light_list;

    std::vector<int> camera_list;
    int curr_camera;

    std::stack<unsigned int> ID_stack;
};



#endif