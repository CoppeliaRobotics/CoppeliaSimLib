#pragma once

#include <meshWrapper.h>
#include <textureProperty.h>

class CMesh : public CMeshWrapper
{
  public:
    CMesh();
    CMesh(const C7Vector &meshFrame, const std::vector<double> &vertices, const std::vector<int> &indices,
          const std::vector<double> *optNormals, const std::vector<float> *optTexCoords, int options);
    virtual ~CMesh();

    void prepareVerticesIndicesNormalsAndEdgesForSerialization();
    void performSceneObjectLoadingMapping(const std::map<int, int> *map);
    void performTextureObjectLoadingMapping(const std::map<int, int> *map);
    void announceSceneObjectWillBeErased(const CSceneObject *object);
    void setTextureDependencies(int shapeID);
    bool getContainsTransparentComponents() const;
    CMesh *copyYourself();
    void scale(double isoVal);
    void scale(double xVal, double yVal, double zVal);
    int getPurePrimitiveType() const;
    void setPurePrimitiveType(int theType, double xOrDiameter, double y, double zOrHeight);
    bool isMesh() const;
    bool isPure() const;
    bool isConvex() const;
    bool checkIfConvex();
    CMesh *getFirstMesh();
    int countTriangles() const;
    void getCumulativeMeshes(const C7Vector &parentCumulTr, std::vector<double> &vertices, std::vector<int> *indices,
                             std::vector<double> *normals);
    void getCumulativeMeshes(const C7Vector &parentCumulTr, const CMeshWrapper *wrapper, std::vector<double> &vertices,
                             std::vector<int> *indices, std::vector<double> *normals);
    void setColor(const CShape *shape, int &elementIndex, const char *colorName, int colorComponent,
                  const float *rgbData, int &rgbDataOffset);
    bool getColor(const char *colorName, int colorComponent, float *rgbData, int &rgbDataOffset) const;
    void getAllMeshComponentsCumulative(const C7Vector &parentCumulTr, std::vector<CMesh *> &shapeComponentList,
                                        std::vector<C7Vector> *OptParentCumulTrList = nullptr);
    CMesh *getMeshComponentAtIndex(const C7Vector &parentCumulTr, int &index, C7Vector *optParentCumulTrOut = nullptr);
    int getComponentCount() const;
    bool serialize(CSer &ar, const char *shapeName, const C7Vector &parentCumulIFrame, bool rootLevel);
    void flipFaces();
    double getShadingAngle() const;
    void setShadingAngle(double angle);
    double getEdgeThresholdAngle() const;
    void setEdgeThresholdAngle(double angle);
    void setHideEdgeBorders_OLD(bool v);
    bool getHideEdgeBorders_OLD() const;
    int getTextureCount() const;
    bool hasTextureThatUsesFixedTextureCoordinates() const;
    void removeAllTextures();
    void getColorStrings(std::string &colorStrings, bool onlyNamed) const;
    void setHeightfieldDiamonds(bool d);

    int getUniqueID() const;

    void setHeightfieldData(const std::vector<double> &heights, int xCount, int yCount);
    double *getHeightfieldData(int &xCount, int &yCount, double &minHeight, double &maxHeight);
    void getPurePrimitiveSizes(C3Vector &s) const;
    void setPurePrimitiveInsideScaling_OLD(double s);
    double getPurePrimitiveInsideScaling_OLD() const;

    CTextureProperty *getTextureProperty();
    void setTextureProperty(CTextureProperty *tp);

    void setVisibleEdges(bool v);
    bool getVisibleEdges() const;
    void setEdgeWidth_DEPRECATED(int w);
    int getEdgeWidth_DEPRECATED() const;
    void setCulling(bool c);
    bool getCulling() const;
    bool getDisplayInverted_DEPRECATED() const;
    void setDisplayInverted_DEPRECATED(bool di);

    void actualizeGouraudShadingAndVisibleEdges();

    void setInsideAndOutsideFacesSameColor_DEPRECATED(bool s);
    bool getInsideAndOutsideFacesSameColor_DEPRECATED() const;
    void setWireframe_OLD(bool w);
    bool getWireframe_OLD() const;

    std::vector<double> *getVertices();
    std::vector<int> *getIndices();
    std::vector<double> *getNormals();
    std::vector<unsigned char> *getEdges();

    std::vector<float> *getVerticesForDisplayAndDisk();
    std::vector<float> *getNormalsForDisplayAndDisk();

    void copyVisualAttributesTo(CMeshWrapper *target);
    void takeVisualAttributesFrom(CMesh *origin);

    bool reorientBB(const C4Vector *rot);
    void setBBFrame(const C7Vector &bbFrame);

    // Following few routines in order not to save duplicate data:
    static void clearTempVerticesIndicesNormalsAndEdges();
    static void serializeTempVerticesIndicesNormalsAndEdges(CSer &ar);
    static int getBufferIndexOfVertices(const std::vector<float> &vert);
    static int addVerticesToBufferAndReturnIndex(const std::vector<float> &vert);
    static void getVerticesFromBufferBasedOnIndex(int index, std::vector<float> &vert);
    static int getBufferIndexOfIndices(const std::vector<int> &ind);
    static int addIndicesToBufferAndReturnIndex(const std::vector<int> &ind);
    static void getIndicesFromBufferBasedOnIndex(int index, std::vector<int> &ind);
    static int getBufferIndexOfNormals(const std::vector<float> &norm);
    static int addNormalsToBufferAndReturnIndex(const std::vector<float> &norm);
    static void getNormalsFromBufferBasedOnIndex(int index, std::vector<float> &norm);
    static int getBufferIndexOfEdges(const std::vector<unsigned char> &edges);
    static int addEdgesToBufferAndReturnIndex(const std::vector<unsigned char> &edges);
    static void getEdgesFromBufferBasedOnIndex(int index, std::vector<unsigned char> &edges);

    CColorObject color;
    CColorObject insideColor_DEPRECATED;
    CColorObject edgeColor_DEPRECATED;

    std::vector<double> _heightfieldHeights;
    int _heightfieldXCount;
    int _heightfieldYCount;

  protected:
    void _updateNonDisplayAndNonDiskValues();
    void _updateDisplayAndDiskValues();
    void _transformMesh(const C7Vector &tr);
    void _commonInit();
    void _recomputeNormals();
    void _computeVisibleEdges();
    C3Vector _computeBBSize(C3Vector *optBBCenter = nullptr);

    static void _loadPackedIntegers_OLD(CSer &ar, std::vector<int> &data);

    std::vector<double> _vertices;
    std::vector<int> _indices;
    std::vector<double> _normals;
    std::vector<unsigned char> _edges;

    std::vector<float> _verticesForDisplayAndDisk;
    std::vector<float> _normalsForDisplayAndDisk;

    bool _visibleEdges;
    bool _hideEdgeBorders_OLD;
    bool _culling;
    bool _displayInverted_DEPRECATED;
    bool _insideAndOutsideFacesSameColor_DEPRECATED;
    bool _wireframe_OLD;
    int _edgeWidth_DEPRERCATED;
    double _shadingAngle;
    double _edgeThresholdAngle;
    bool _convex;

    CTextureProperty *_textureProperty;
    int _uniqueID;

    int _purePrimitive;
    double _purePrimitiveXSizeOrDiameter;
    double _purePrimitiveYSize;
    double _purePrimitiveZSizeOrHeight;
    double _purePrimitiveInsideScaling;

    int _tempVerticesIndexForSerialization;
    int _tempIndicesIndexForSerialization;
    int _tempNormalsIndexForSerialization;
    int _tempEdgesIndexForSerialization;

    unsigned int _extRendererObjectId;
    unsigned int _extRendererObject_lastMeshId;
    unsigned int _extRendererObject_lastTextureId;

    unsigned int _extRendererMeshId;
    int _extRendererMesh_lastVertexBufferId;

    unsigned int _extRendererTextureId;
    unsigned int _extRendererTexture_lastTextureId;

    static unsigned int _extRendererUniqueObjectID;
    static unsigned int _extRendererUniqueMeshID;
    static unsigned int _extRendererUniqueTextureID;

    static int _nextUniqueID;

    // temp, for serialization purpose:
    static std::vector<std::vector<float> *> _tempVerticesForDisk;
    static std::vector<std::vector<int> *> _tempIndicesForDisk;
    static std::vector<std::vector<float> *> _tempNormalsForDisk;
    static std::vector<std::vector<unsigned char> *> _tempEdgesForDisk;

#ifdef SIM_WITH_GUI
  public:
    void display(const C7Vector &cumulIFrameTr, CShape *geomData, int displayAttrib, CColorObject *collisionColor,
                 int dynObjFlag_forVisualization, int transparencyHandling, bool multishapeEditSelected);
    void display_colorCoded(const C7Vector &cumulIFrameTr, CShape *geomData, int objectId, int displayAttrib);
    void displayGhost(const C7Vector &cumulIFrameTr, CShape *geomData, int displayAttrib, bool originalColors,
                      bool backfaceCulling, double transparency, const float *newColors);

    void display_extRenderer(const C7Vector &cumulIFrameTr, CShape *geomData, int displayAttrib, const C7Vector &tr,
                             int shapeHandle, int &componentIndex);
    bool getNonCalculatedTextureCoordinates(std::vector<float> &texCoords);
    int *getVertexBufferIdPtr();
    int *getNormalBufferIdPtr();
    int *getEdgeBufferIdPtr();

  protected:
    int _vertexBufferId;
    int _normalBufferId;
    int _edgeBufferId;
#endif
};
