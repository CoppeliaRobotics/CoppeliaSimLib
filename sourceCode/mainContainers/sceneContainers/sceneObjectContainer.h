#pragma once

#include <map>
#include <shape.h>
#include <proximitySensor.h>
#include <visionSensor.h>
#include <camera.h>
#include <graph.h>
#include <path_old.h>
#include <mirror.h>
#include <octree.h>
#include <pointCloud.h>
#include <mill.h>
#include <forceSensor.h>
#include <sceneObject.h>
#include <jointObject.h>
#include <sceneObject.h>

class CJoint;
class CDummy;
class CGraph;
class CLight;
class CCamera;
class CProxSensor;
class CVisionSensor;
class CShape;
class CForceSensor;
class COcTree;
class CPointCloud;
// Old objects:
class CMirror;
class CPath_old;
class CMill;

struct SSimpleXmlSceneObject
{
    CSceneObject *object;
    CSceneObject *parentObject;
    CScriptObject *childScript;
    CScriptObject *customizationScript;
};

class CSceneObjectContainer
{
  public:
    CSceneObjectContainer();
    virtual ~CSceneObjectContainer();

    bool doesObjectExist(const CSceneObject *obj) const;
    int getObjectSequence(const CSceneObject *object) const;
    size_t getObjectCount() const;
    CSceneObject *getObjectFromIndex(size_t index) const;
    CSceneObject *getObjectFromHandle(int objectHandle) const;
    CSceneObject *getObjectFromUid(long long int objectUid) const;
    CSceneObject *getObjectFromPath(const CSceneObject *emittingObject, const char *objectAliasAndPath,
                                    int index) const;
    CSceneObject *getObjectFromName_old(const char *objectName) const;
    CSceneObject *getObjectFromAltName_old(const char *objectAltName) const;
    int getObjectHandleFromName_old(const char *objectName) const;
    int getObjects_hierarchyOrder(std::vector<CSceneObject *> &allObjects);

    size_t getOrphanCount() const;
    size_t getJointCount() const;
    size_t getDummyCount() const;
    size_t getMirrorCount() const;
    size_t getGraphCount() const;
    size_t getLightCount() const;
    size_t getCameraCount() const;
    size_t getProximitySensorCount() const;
    size_t getVisionSensorCount() const;
    size_t getShapeCount() const;
    size_t getSimpleShapeCount() const;
    size_t getCompoundShapeCount() const;
    size_t getPathCount() const;
    size_t getMillCount() const;
    size_t getForceSensorCount() const;
    size_t getOctreeCount() const;
    size_t getPointCloudCount() const;
    CSceneObject *getOrphanFromIndex(size_t index) const;
    CJoint *getJointFromIndex(size_t index) const;
    CDummy *getDummyFromIndex(size_t index) const;
    CMirror *getMirrorFromIndex(size_t index) const;
    CGraph *getGraphFromIndex(size_t index) const;
    CLight *getLightFromIndex(size_t index) const;
    CCamera *getCameraFromIndex(size_t index) const;
    CProxSensor *getProximitySensorFromIndex(size_t index) const;
    CVisionSensor *getVisionSensorFromIndex(size_t index) const;
    CShape *getShapeFromIndex(size_t index) const;
    CPath_old *getPathFromIndex(size_t index) const;
    CMill *getMillFromIndex(size_t index) const;
    CForceSensor *getForceSensorFromIndex(size_t index) const;
    COcTree *getOctreeFromIndex(size_t index) const;
    CPointCloud *getPointCloudFromIndex(size_t index) const;
    CDummy *getDummyFromHandle(int objectHandle) const;
    CJoint *getJointFromHandle(int objectHandle) const;
    CMirror *getMirrorFromHandle(int objectHandle) const;
    COcTree *getOctreeFromHandle(int objectHandle) const;
    CPointCloud *getPointCloudFromHandle(int objectHandle) const;
    CShape *getShapeFromHandle(int objectHandle) const;
    CProxSensor *getProximitySensorFromHandle(int objectHandle) const;
    CVisionSensor *getVisionSensorFromHandle(int objectHandle) const;
    CCamera *getCameraFromHandle(int objectHandle) const;
    CLight *getLightFromHandle(int objectHandle) const;
    CGraph *getGraphFromHandle(int objectHandle) const;
    CPath_old *getPathFromHandle(int objectHandle) const;
    CMill *getMillFromHandle(int objectHandle) const;
    CForceSensor *getForceSensorFromHandle(int objectHandle) const;

    bool hasSelectionChanged();
    size_t getSelectionCount() const;
    int getObjectHandleFromSelectionIndex(size_t index) const;
    const std::vector<int> *getSelectedObjectHandlesPtr() const;
    bool isObjectSelected(int objectHandle) const;
    void getSelectedObjects(std::vector<CSceneObject *> &selection, int objectType = -1,
                            bool includeModelObjects = false, bool onlyVisibleModelObjects = false) const;
    void getSelectedObjectHandles(std::vector<int> &selection, int objectType = -1, bool includeModelObjects = false,
                                  bool onlyVisibleModelObjects = false) const;
    int getLastSelectionHandle(const std::vector<int> *selection = nullptr) const;
    bool isObjectInSelection(int objectHandle, const std::vector<int> *selection = nullptr) const;
    void popLastSelection();
    CSceneObject *getLastSelectionObject(const std::vector<int> *selection = nullptr) const;
    CMirror *getLastSelectionMirror() const;
    COcTree *getLastSelectionOctree() const;
    CPointCloud *getLastSelectionPointCloud() const;
    CShape *getLastSelectionShape() const;
    CJoint *getLastSelectionJoint() const;
    CGraph *getLastSelectionGraph() const;
    CCamera *getLastSelectionCamera() const;
    CLight *getLastSelectionLight() const;
    CDummy *getLastSelectionDummy() const;
    CProxSensor *getLastSelectionProxSensor() const;
    CVisionSensor *getLastSelectionVisionSensor() const;
    CPath_old *getLastSelectionPath() const;
    CMill *getLastSelectionMill() const;
    CForceSensor *getLastSelectionForceSensor() const;
    size_t getShapeCountInSelection(const std::vector<int> *selection = nullptr) const;
    size_t getSimpleShapeCountInSelection(const std::vector<int> *selection = nullptr) const;
    size_t getJointCountInSelection(const std::vector<int> *selection = nullptr) const;
    size_t getGraphCountInSelection(const std::vector<int> *selection = nullptr) const;
    size_t getDummyCountInSelection(const std::vector<int> *selection = nullptr) const;
    size_t getProxSensorCountInSelection(const std::vector<int> *selection = nullptr) const;
    size_t getVisionSensorCountInSelection(const std::vector<int> *selection = nullptr) const;
    size_t getPathCountInSelection(const std::vector<int> *selection = nullptr) const;
    size_t getMillCountInSelection(const std::vector<int> *selection = nullptr) const;
    size_t getForceSensorCountInSelection(const std::vector<int> *selection = nullptr) const;
    bool isLastSelectionAnOctree(const std::vector<int> *selection = nullptr) const;
    bool isLastSelectionAPointCloud(const std::vector<int> *selection = nullptr) const;
    bool isLastSelectionAShape(const std::vector<int> *selection = nullptr) const;
    bool isLastSelectionASimpleShape(const std::vector<int> *selection = nullptr) const;
    bool isLastSelectionAJoint(const std::vector<int> *selection = nullptr) const;
    bool isLastSelectionAGraph(const std::vector<int> *selection = nullptr) const;
    bool isLastSelectionADummy(const std::vector<int> *selection = nullptr) const;
    bool isLastSelectionAProxSensor(const std::vector<int> *selection = nullptr) const;
    bool isLastSelectionAVisionSensor(const std::vector<int> *selection = nullptr) const;
    bool isLastSelectionAPath(const std::vector<int> *selection = nullptr) const;
    bool isLastSelectionAMill(const std::vector<int> *selection = nullptr) const;
    bool isLastSelectionAForceSensor(const std::vector<int> *selection = nullptr) const;

    void buildOrUpdate_oldIk();
    void connect_oldIk();
    void remove_oldIk();

    void simulationAboutToStart();
    void simulationEnded();

    void announceObjectWillBeErased(const CSceneObject *object);
    void announceScriptWillBeErased(int scriptHandle, bool simulationScript, bool sceneSwitchPersistentScript);

    // Old:
    void announceIkGroupWillBeErased(int ikGroupHandle);
    void announceCollectionWillBeErased(int collectionHandle);
    void announceCollisionWillBeErased(int collisionHandle);
    void announceDistanceWillBeErased(int distanceHandle);

    int addObjectToScene(CSceneObject *newObject, bool objectIsACopy, bool generateAfterCreateCallback);
    int addObjectToSceneWithSuffixOffset(CSceneObject *newObject, bool objectIsACopy, int suffixOffset,
                                         bool generateAfterCreateCallback);
    void eraseObject(CSceneObject *it, bool generateBeforeAfterDeleteCallback);
    void eraseObjects(const std::vector<int> &objectHandles, bool generateBeforeAfterDeleteCallback);
    void eraseAllObjects(bool generateBeforeAfterDeleteCallback);
    void actualizeObjectInformation();
    void enableObjectActualization(bool e);
    void getMinAndMaxNameSuffixes(int &minSuffix, int &maxSuffix) const;
    bool canSuffix1BeSetToSuffix2(int suffix1, int suffix2) const;
    void setSuffix1ToSuffix2(int suffix1, int suffix2);
    int getObjectCreationCounter() const;
    int getObjectDestructionCounter() const;
    int getHierarchyChangeCounter() const;

    void setTextureDependencies();
    void removeSceneDependencies();

    void checkObjectIsInstanciated(CSceneObject *obj, const char *location) const;
    void pushGenesisEvents() const;

    void getAllCollidableObjectsFromSceneExcept(const std::vector<CSceneObject *> *exceptionObjects,
                                                std::vector<CSceneObject *> &objects);
    void getAllMeasurableObjectsFromSceneExcept(const std::vector<CSceneObject *> *exceptionObjects,
                                                std::vector<CSceneObject *> &objects);
    void getAllDetectableObjectsFromSceneExcept(const std::vector<CSceneObject *> *exceptionObjects,
                                                std::vector<CSceneObject *> &objects, int detectableMask);

    CSceneObject *readSceneObject(CSer &ar, const char *name, bool &noHit);
    void writeSceneObject(CSer &ar, CSceneObject *it);
    bool readAndAddToSceneSimpleXmlSceneObjects(CSer &ar, CSceneObject *parentObject,
                                                const C7Vector &localFramePreCorrection,
                                                std::vector<SSimpleXmlSceneObject> &simpleXmlObjects);
    void writeSimpleXmlSceneObjectTree(CSer &ar, const CSceneObject *object);

    bool setObjectAlias(CSceneObject *object, const char *newAlias, bool allowNameAdjustment);
    bool setObjectParent(CSceneObject *object, CSceneObject *newParent, bool keepInPlace);

    bool setObjectSequence(CSceneObject *object, int order);
    bool setSelectedObjectHandles(const std::vector<int> *v);
    bool setObjectName_old(CSceneObject *object, const char *newName, bool allowNameAdjustment);
    bool setObjectAltName_old(CSceneObject *object, const char *newAltName, bool allowNameAdjustment);

    void setObjectAbsolutePose(int objectHandle, const C7Vector &v, bool keepChildrenInPlace);
    void setObjectAbsoluteOrientation(int objectHandle, const C3Vector &euler);
    void setObjectAbsolutePosition(int objectHandle, const C3Vector &p);

    int getHighestObjectHandle() const;

    void addModelObjects(std::vector<int> &selection) const;

    // Selection:
    bool isSelectionSame(std::vector<int> &sel, bool actualize) const;

    void selectObject(int objectHandle);
    void selectAllObjects();
    void deselectObjects();
    void addObjectToSelection(int objectHandle);
    void removeObjectFromSelection(int objectHandle);
    void xorAddObjectToSelection(int objectHandle);
    void removeFromSelectionAllExceptModelBase(bool keepObjectsSelectedThatAreNotBuiltOnAModelBase);

  protected:
    void _handleOrderIndexOfOrphans();
    void _addToOrphanObjects(CSceneObject *object);
    void _removeFromOrphanObjects(CSceneObject *object);
    CSceneObject *_getObjectInTree(const CSceneObject *treeBase, const char *objectAliasAndPath, int &index) const;
    CSceneObject *_getObjectFromSimplePath(const CSceneObject *emittingObject, const char *objectAliasAndPath,
                                           int index) const;
    CSceneObject *_getObjectFromComplexPath(const CSceneObject *emittingObject, std::string &path, int index) const;

    void _addObject(CSceneObject *object);
    void _removeObject(CSceneObject *object);

  private:
    CShape *_readSimpleXmlShape(CSer &ar, C7Vector &desiredLocalFrame);
    CShape *_createSimpleXmlShape(CSer &ar, bool noHeightfield, const char *itemType, bool checkSibling);
    void _writeSimpleXmlShape(CSer &ar, CShape *shape);
    void _writeSimpleXmlSimpleShape(CSer &ar, const char *originalShapeName, CShape *shape, const C7Vector &frame);

    bool _objectActualizationEnabled;
    int _nextObjectHandle;

    int _objectCreationCounter;
    int _objectDestructionCounter;
    int _hierarchyChangeCounter;

    std::vector<CSceneObject *> _orphanObjects;

    std::vector<CSceneObject *> _allObjects;                  // only used for iterating in a RANDOM manner over objects
    std::map<int, CSceneObject *> _objectHandleMap;           // only used for fast access!
    std::map<std::string, CSceneObject *> _objectNameMap_old; // only used for fast access!
    std::map<std::string, CSceneObject *> _objectAltNameMap_old; // only used for fast access!

    // only used for iterating in a RANDOM manner over specific objects:
    std::vector<CJoint *> _jointList;
    std::vector<CDummy *> _dummyList;
    std::vector<CGraph *> _graphList;
    std::vector<CLight *> _lightList;
    std::vector<CCamera *> _cameraList;
    std::vector<CProxSensor *> _proximitySensorList;
    std::vector<CVisionSensor *> _visionSensorList;
    std::vector<CShape *> _shapeList;
    std::vector<CForceSensor *> _forceSensorList;
    std::vector<COcTree *> _octreeList;
    std::vector<CPointCloud *> _pointCloudList;
    // Old objects:
    std::vector<CMirror *> _mirrorList;
    std::vector<CPath_old *> _pathList;
    std::vector<CMill *> _millList;

    std::vector<int> _selectedObjectHandles;
    std::vector<int> _lastSelection; // to keep track of selection changes (async.)
};
