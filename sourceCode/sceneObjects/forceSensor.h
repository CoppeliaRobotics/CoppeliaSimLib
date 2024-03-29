#pragma once

#include <sceneObject.h>

class CForceSensor : public CSceneObject
{
  public:
    CForceSensor();
    virtual ~CForceSensor();

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

    // Overridden from CSceneObject:
    virtual C7Vector getIntrinsicTransformation(bool includeDynErrorComponent, bool *available = nullptr) const;
    virtual C7Vector getFullLocalTransformation() const;

    void commonInit();

    void setIntrinsicTransformationError(const C7Vector &tr);

    void addCumulativeForcesAndTorques(const C3Vector &f, const C3Vector &t, int countForAverage);
    void setForceAndTorqueNotValid();

    bool getDynamicForces(C3Vector &f, bool dynamicStepValue) const;
    bool getDynamicTorques(C3Vector &t, bool dynamicStepValue) const;

    double getDynamicPositionError() const;
    double getDynamicOrientationError() const;
    void getDynamicErrorsFull(C3Vector &linear, C3Vector &angular) const;

    bool getStillAutomaticallyBreaking();
    void setForceThreshold(double t);
    double getForceThreshold() const;
    void setTorqueThreshold(double t);
    double getTorqueThreshold() const;
    void setEnableForceThreshold(bool e);
    bool getEnableForceThreshold() const;
    void setEnableTorqueThreshold(bool e);
    bool getEnableTorqueThreshold() const;
    void setConsecutiveThresholdViolationsForBreaking(int count);
    int getConsecutiveThresholdViolationsForBreaking() const;

    void setValueCountForFilter(int c);
    int getValueCountForFilter() const;
    void setFilterType(int t);
    int getFilterType() const;

    // Various
    void setForceSensorSize(double s);
    double getForceSensorSize() const;

    CColorObject *getColor(bool part2);

  protected:
    void _computeFilteredValues();
    void _handleSensorBreaking();

    double _forceThreshold;
    double _torqueThreshold;
    int _valueCountForFilter;
    int _filterType; // 0=average, 1=median
    bool _forceThresholdEnabled;
    bool _torqueThresholdEnabled;
    bool _stillAutomaticallyBreaking;

    int _consecutiveThresholdViolationsForBreaking;
    int _currentThresholdViolationCount;

    C7Vector _intrinsicTransformationError; // from physics engine

    // Variables which need to be serialized & copied
    // Visual attributes:
    double _forceSensorSize;
    CColorObject _color;
    CColorObject _color_removeSoon;

    // Dynamic values:
    std::vector<C3Vector> _cumulatedForces;
    std::vector<C3Vector> _cumulatedTorques;

    C3Vector _cumulativeForcesTmp;
    C3Vector _cumulativeTorquesTmp;

    // Following are forces/torques acquired during a single dyn. calculation step:
    C3Vector _lastForce_dynStep;
    C3Vector _lastTorque_dynStep;
    bool _lastForceAndTorqueValid_dynStep;

    C3Vector _filteredDynamicForces;  // do not serialize! (but initialize appropriately)
    C3Vector _filteredDynamicTorques; // do not serialize! (but initialize appropriately)
    bool _filteredValuesAreValid;

#ifdef SIM_WITH_GUI
  public:
    void display(CViewableBase *renderingObject, int displayAttrib);
#endif
};
