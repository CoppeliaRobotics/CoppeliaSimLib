#pragma once

#include <sceneObject.h>

class CLight : public CSceneObject
{
  public:
    CLight();
    CLight(int theType);
    virtual ~CLight();

    // Following functions are inherited from CSceneObject
    void addSpecializedObjectEventData(CCbor *ev) const;
    CSceneObject *copyYourself();
    void removeSceneDependencies();
    void scaleObject(double scalingFactor);
    void serialize(CSer &ar);
    void announceObjectWillBeErased(const CSceneObject *object, bool copyBuffer);
    void announceCollectionWillBeErased(int groupID, bool copyBuffer);
    void announceCollisionWillBeErased(int collisionID, bool copyBuffer);
    void announceDistanceWillBeErased(int distanceID, bool copyBuffer);
    void announceIkObjectWillBeErased(int ikGroupID, bool copyBuffer);
    void performObjectLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performCollectionLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performCollisionLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performDistanceLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performIkLoadingMapping(const std::map<int, int> *map, bool loadingAmodel);
    void performTextureObjectLoadingMapping(const std::map<int, int> *map);
    void performDynMaterialObjectLoadingMapping(const std::map<int, int> *map);
    void simulationAboutToStart();
    void simulationEnded();
    void initializeInitialValues(bool simulationAlreadyRunning);
    void computeBoundingBox();

    std::string getObjectTypeInfo() const;
    std::string getObjectTypeInfoExtended() const;
    bool isPotentiallyCollidable() const;
    bool isPotentiallyMeasurable() const;
    bool isPotentiallyDetectable() const;
    bool isPotentiallyRenderable() const;

    void setLightActive(bool active);
    bool getLightActive() const;
    double getAttenuationFactor(int type) const;
    void setAttenuationFactor(int type, double value);
    void setLightSize(double size);
    double getLightSize() const;
    void setSpotExponent(int e);
    int getSpotExponent() const;
    void setSpotCutoffAngle(double co);
    double getSpotCutoffAngle() const;
    int getLightType() const;

    void setLightIsLocal(bool l);
    bool getLightIsLocal() const;

    static void setMaxAvailableOglLights(int c);
    static int getMaxAvailableOglLights();

    CColorObject *getColor(bool getLightColor);

  protected:
    void _setDefaultColors();
    void _commonInit();

    // Variables which need to be serialized & copied
    CColorObject objectColor;
    CColorObject lightColor;
    bool lightActive;
    double constantAttenuation;
    double linearAttenuation;
    double quadraticAttenuation;
    int _spotExponent;
    double _spotCutoffAngle;
    double _lightSize;
    int _lightType;
    bool _lightIsLocal;

    // Variables which do not need to be serialized
    bool _initialLightActive;
    static int _maximumOpenGlLights;

#ifdef SIM_WITH_GUI
  public:
    void display(CViewableBase *renderingObject, int displayAttrib);
#endif
};
