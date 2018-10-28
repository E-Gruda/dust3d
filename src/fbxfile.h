#ifndef DUST3D_FBX_FILE_H
#define DUST3D_FBX_FILE_H
#include <fbxdocument.h>
#include <map>
#include <QString>
#include <QMatrix4x4>
#include <QQuaternion>
#include "outcome.h"
#include "document.h"

class FbxFileWriter : public QObject
{
    Q_OBJECT
public:
    FbxFileWriter(Outcome &outcome,
        const std::vector<RiggerBone> *resultRigBones,
        const std::map<int, RiggerVertexWeights> *resultRigWeights,
        const QString &filename,
        const std::vector<std::pair<QString, std::vector<std::pair<float, JointNodeTree>>>> *motions=nullptr);
    bool save();

private:
    void createFbxHeader();
    void createCreationTime();
    void createFileId();
    void createCreator();
    void createGlobalSettings();
    void createDocuments();
    void createReferences();
    void createDefinitions(size_t deformerCount,
        bool hasAnimtion=false,
        size_t animationStackCount=0,
        size_t animationLayerCount=0,
        size_t animationCurveNodeCount=0,
        size_t animationCurveCount=0);
    void createTakes();
    std::vector<double> matrixToVector(const QMatrix4x4 &matrix);
    void quaternionToFbxEulerAngles(const QQuaternion &q, double *pitch, double *yaw, double *roll);
    int64_t secondsToKtime(double seconds);
    
    int64_t to64Id(const QUuid &uuid);
    int64_t m_next64Id = 612150000;
    QString m_filename;
    fbx::FBXDocument m_fbxDocument;
    std::map<QString, int64_t> m_uuidTo64Map;
    static std::vector<double> m_identityMatrix;
};

#endif

