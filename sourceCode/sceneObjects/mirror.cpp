#include <mirror.h>
#include <simInternal.h>
#include <tt.h>
#include <simStrings.h>
#include <utils.h>
#include <app.h>
#ifdef SIM_WITH_GUI
#include <mirrorRendering.h>
#include <guiApp.h>
#endif

int CMirror::currentMirrorContentBeingRendered = -1;

CMirror::CMirror()
{
    _commonInit();
}

std::string CMirror::getObjectTypeInfo() const
{
    return ("Mirror");
}
std::string CMirror::getObjectTypeInfoExtended() const
{
    return ("Mirror");
}
bool CMirror::isPotentiallyCollidable() const
{
    return (false);
}
bool CMirror::isPotentiallyMeasurable() const
{
    return (false);
}
bool CMirror::isPotentiallyDetectable() const
{
    return (false);
}
bool CMirror::isPotentiallyRenderable() const
{
    return (true);
}

void CMirror::_commonInit()
{
    _objectType = sim_object_mirror_type;
    _mirrorWidth = 0.5;
    _mirrorHeight = 1.0;
    _mirrorReflectance = 0.75;
    mirrorColor[0] = 0.0;
    mirrorColor[1] = 0.0;
    mirrorColor[2] = 0.0;

    clipPlaneColor.setDefaultValues();
    clipPlaneColor.setColor(0.0f, 0.525f, 0.6f, sim_colorcomponent_ambient_diffuse);
    clipPlaneColor.setTranslucid(true);
    clipPlaneColor.setOpacity(0.4f);

    _active = true;
    _isMirror = true;
    _clippingObjectOrCollection = -1; // clipping all
    _visibilityLayer = CAMERA_LIGHT_LAYER;
    _localObjectSpecialProperty = sim_objectspecialproperty_renderable;

    _objectMovementPreferredAxes = 0x013;

    _objectAlias = IDSOGL_MIRROR;
    _objectName_old = IDSOGL_MIRROR;
    _objectAltName_old = tt::getObjectAltNameFromObjectName(_objectName_old.c_str());
    computeBoundingBox();
}

bool CMirror::getContainsTransparentComponent() const
{
    if (_isMirror)
        return (false);
    return (clipPlaneColor.getTranslucid());
}

CColorObject *CMirror::getClipPlaneColor()
{
    return (&clipPlaneColor);
}

void CMirror::computeBoundingBox()
{
    _setBB(C7Vector::identityTransformation, C3Vector(_mirrorWidth, _mirrorHeight, 0.001) * 0.5);
}

CMirror::~CMirror()
{
}

void CMirror::scaleObject(double scalingFactor)
{
    _mirrorWidth *= scalingFactor;
    _mirrorHeight *= scalingFactor;

    CSceneObject::scaleObject(scalingFactor);
}

void CMirror::setMirrorWidth(double w)
{
    _mirrorWidth = tt::getLimitedFloat(0.001, 100.0, w);
}

double CMirror::getMirrorWidth()
{
    return (_mirrorWidth);
}

void CMirror::setMirrorHeight(double h)
{
    _mirrorHeight = tt::getLimitedFloat(0.001, 100.0, h);
}

double CMirror::getMirrorHeight()
{
    return (_mirrorHeight);
}

void CMirror::setReflectance(double r)
{
    _mirrorReflectance = tt::getLimitedFloat(0.0, 1.0, r);
}

double CMirror::getReflectance()
{
    return (_mirrorReflectance);
}

void CMirror::setActive(bool a)
{
    _active = a;
}

bool CMirror::getActive()
{
    return (_active);
}

void CMirror::setIsMirror(bool m)
{
#ifdef SIM_WITH_GUI
    if (m != _isMirror)
        GuiApp::setRefreshHierarchyViewFlag();
#endif
    _isMirror = m;
}

bool CMirror::getIsMirror()
{
    return (_isMirror);
}

void CMirror::setClippingObjectOrCollection(int co)
{
    _clippingObjectOrCollection = co;
}

int CMirror::getClippingObjectOrCollection()
{
    return (_clippingObjectOrCollection);
}

void CMirror::removeSceneDependencies()
{
    CSceneObject::removeSceneDependencies();
}

void CMirror::addSpecializedObjectEventData(CCbor *ev) const
{
    ev->openKeyMap("mirror");
    ev->closeArrayOrMap(); // mirror
    // todo
}

CSceneObject *CMirror::copyYourself()
{
    CMirror *newMirror = (CMirror *)CSceneObject::copyYourself();

    // Various
    newMirror->_mirrorHeight = _mirrorHeight;
    newMirror->_mirrorWidth = _mirrorWidth;
    newMirror->_active = _active;
    newMirror->_isMirror = _isMirror;
    newMirror->_mirrorReflectance = _mirrorReflectance;
    newMirror->_clippingObjectOrCollection = _clippingObjectOrCollection;

    newMirror->mirrorColor[0] = mirrorColor[0];
    newMirror->mirrorColor[1] = mirrorColor[1];
    newMirror->mirrorColor[2] = mirrorColor[2];

    clipPlaneColor.copyYourselfInto(&newMirror->clipPlaneColor);

    newMirror->_initialMirrorActive = _initialMirrorActive;

    return (newMirror);
}

void CMirror::announceObjectWillBeErased(const CSceneObject *object, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    if (_clippingObjectOrCollection == object->getObjectHandle())
    {
        _clippingObjectOrCollection = -1;
        if (!_isMirror)
            _active = false;
    }
    CSceneObject::announceObjectWillBeErased(object, copyBuffer);
}

void CMirror::announceCollectionWillBeErased(int groupID, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    if (_clippingObjectOrCollection == groupID)
    {
        _clippingObjectOrCollection = -1;
        if (!_isMirror)
            _active = false;
    }
    CSceneObject::announceCollectionWillBeErased(groupID, copyBuffer);
}
void CMirror::announceCollisionWillBeErased(int collisionID, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    CSceneObject::announceCollisionWillBeErased(collisionID, copyBuffer);
}
void CMirror::announceDistanceWillBeErased(int distanceID, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    CSceneObject::announceDistanceWillBeErased(distanceID, copyBuffer);
}
void CMirror::announceIkObjectWillBeErased(int ikGroupID, bool copyBuffer)
{ // copyBuffer is false by default (if true, we are 'talking' to objects
    // in the copyBuffer)
    CSceneObject::announceIkObjectWillBeErased(ikGroupID, copyBuffer);
}

void CMirror::performObjectLoadingMapping(const std::map<int, int> *map, bool loadingAmodel)
{
    CSceneObject::performObjectLoadingMapping(map, loadingAmodel);
    if (_clippingObjectOrCollection <= SIM_IDEND_SCENEOBJECT)
        _clippingObjectOrCollection = CWorld::getLoadingMapping(map, _clippingObjectOrCollection);
}
void CMirror::performCollectionLoadingMapping(const std::map<int, int> *map, bool loadingAmodel)
{
    CSceneObject::performCollectionLoadingMapping(map, loadingAmodel);
    if (_clippingObjectOrCollection > SIM_IDEND_SCENEOBJECT)
        _clippingObjectOrCollection = CWorld::getLoadingMapping(map, _clippingObjectOrCollection);
}
void CMirror::performCollisionLoadingMapping(const std::map<int, int> *map, bool loadingAmodel)
{
    CSceneObject::performCollisionLoadingMapping(map, loadingAmodel);
}
void CMirror::performDistanceLoadingMapping(const std::map<int, int> *map, bool loadingAmodel)
{
    CSceneObject::performDistanceLoadingMapping(map, loadingAmodel);
}
void CMirror::performIkLoadingMapping(const std::map<int, int> *map, bool loadingAmodel)
{
    CSceneObject::performIkLoadingMapping(map, loadingAmodel);
}

void CMirror::performTextureObjectLoadingMapping(const std::map<int, int> *map)
{
    CSceneObject::performTextureObjectLoadingMapping(map);
}

void CMirror::performDynMaterialObjectLoadingMapping(const std::map<int, int> *map)
{
    CSceneObject::performDynMaterialObjectLoadingMapping(map);
}

void CMirror::initializeInitialValues(bool simulationAlreadyRunning)
{ // is called at simulation start, but also after object(s) have been copied into a scene!
    CSceneObject::initializeInitialValues(simulationAlreadyRunning);
    _initialMirrorActive = _active;
}

void CMirror::simulationAboutToStart()
{
    initializeInitialValues(false);
    CSceneObject::simulationAboutToStart();
}

void CMirror::simulationEnded()
{ // Remember, this is not guaranteed to be run! (the object can be copied during simulation, and pasted after it
  // ended). For thoses situations there is the initializeInitialValues routine!
    if (_initialValuesInitialized)
    {
        if (App::currentWorld->simulation->getResetSceneAtSimulationEnd() &&
            ((getCumulativeModelProperty() & sim_modelproperty_not_reset) == 0))
        {
            _active = _initialMirrorActive;
        }
    }
    CSceneObject::simulationEnded();
}

void CMirror::serialize(CSer &ar)
{
    CSceneObject::serialize(ar);
    if (ar.isBinary())
    {
        if (ar.isStoring())
        { // Storing
            ar.storeDataName("_sz");
            ar << _mirrorWidth << _mirrorHeight;
            ar.flush();

            ar.storeDataName("Cas");
            unsigned char nothing = 0;
            SIM_SET_CLEAR_BIT(nothing, 0, _active);
            SIM_SET_CLEAR_BIT(nothing, 1, !_isMirror);
            ar << nothing;
            ar.flush();

            ar.storeDataName("Clp");
            ar << _clippingObjectOrCollection;
            ar.flush();

            ar.storeDataName("Mcr");
            ar << _mirrorReflectance << mirrorColor[0] << mirrorColor[1] << mirrorColor[2];
            ar.flush();

            ar.storeDataName("Cpc");
            ar.setCountingMode();
            clipPlaneColor.serialize(ar, 0);
            if (ar.setWritingMode())
                clipPlaneColor.serialize(ar, 0);

            ar.storeDataName(SER_END_OF_OBJECT);
        }
        else
        { // Loading
            int byteQuantity;
            std::string theName = "";
            while (theName.compare(SER_END_OF_OBJECT) != 0)
            {
                theName = ar.readDataName();
                if (theName.compare(SER_END_OF_OBJECT) != 0)
                {
                    bool noHit = true;
                    if (theName.compare("Msz") == 0)
                    { // for backward comp. (flt->dbl)
                        noHit = false;
                        ar >> byteQuantity;
                        float bla, bli;
                        ar >> bla >> bli;
                        _mirrorWidth = (double)bla;
                        _mirrorHeight = (double)bli;
                    }

                    if (theName.compare("_sz") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _mirrorWidth >> _mirrorHeight;
                    }

                    if (theName == "Cas")
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        unsigned char nothing;
                        ar >> nothing;
                        _active = SIM_IS_BIT_SET(nothing, 0);
                        _isMirror = !SIM_IS_BIT_SET(nothing, 1);
                    }
                    if (theName.compare("Clp") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _clippingObjectOrCollection;
                    }
                    if (theName.compare("Mcr") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        ar >> _mirrorReflectance >> mirrorColor[0] >> mirrorColor[1] >> mirrorColor[2];
                    }
                    if (theName.compare("Cpc") == 0)
                    {
                        noHit = false;
                        ar >> byteQuantity;
                        clipPlaneColor.serialize(ar, 0);
                    }
                    if (noHit)
                        ar.loadUnknownData();
                }
            }
            if (ar.getSerializationVersionThatWroteThisFile() < 17)
            { // on 29/08/2013 we corrected all default lights. So we need to correct for that change:
                utils::scaleColorUp_(mirrorColor);
            }
            computeBoundingBox();
        }
    }
    else
    {
        if (ar.isStoring())
        {
            ar.xmlAddNode_2float("sizes", _mirrorWidth, _mirrorHeight);

            ar.xmlAddNode_int("clippingEntity", _clippingObjectOrCollection);

            ar.xmlPushNewNode("switches");
            ar.xmlAddNode_bool("active", _active);
            ar.xmlAddNode_bool("isMirror", _isMirror);
            ar.xmlPopNode();

            ar.xmlPushNewNode("mirror");
            ar.xmlAddNode_float("reflectance", _mirrorReflectance);
            ar.xmlAddNode_floats("color", mirrorColor, 3);
            ar.xmlPopNode();

            ar.xmlPushNewNode("color");
            clipPlaneColor.serialize(ar, 0);
            ar.xmlPopNode();
        }
        else
        {
            ar.xmlGetNode_2float("sizes", _mirrorWidth, _mirrorHeight);

            ar.xmlGetNode_int("clippingEntity", _clippingObjectOrCollection);

            if (ar.xmlPushChildNode("switches"))
            {
                ar.xmlGetNode_bool("active", _active);
                ar.xmlGetNode_bool("isMirror", _isMirror);
                ar.xmlPopNode();
            }

            if (ar.xmlPushChildNode("mirror"))
            {
                ar.xmlGetNode_float("reflectance", _mirrorReflectance);
                ar.xmlGetNode_floats("color", mirrorColor, 3);
                ar.xmlPopNode();
            }

            if (ar.xmlPushChildNode("color"))
            {
                clipPlaneColor.serialize(ar, 0);
                ar.xmlPopNode();
            }
            computeBoundingBox();
        }
    }
}

#ifdef SIM_WITH_GUI
void CMirror::display(CViewableBase *renderingObject, int displayAttrib)
{
    displayMirror(this, renderingObject, displayAttrib);
}
#endif
