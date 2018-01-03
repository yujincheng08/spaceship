import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.0
import Qt3D.Input 2.0
import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Scene3D 2.0
Item {
    Scene3D {
        id: scene3d
        anchors.fill: parent
        focus: true
        aspects: ["input", "logic"]
        cameraAspectRatioMode: Scene3D.AutomaticAspectRatio

        Entity
        {
            id: root
            Camera {
                id: camera
                projectionType: CameraLens.PerspectiveProjection
                fieldOfView: 45
                nearPlane : 0.1
                farPlane : 1000.0
                position: Qt.vector3d( 0.0, 10.0, -10.0 )
                upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
                viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
            }
            Entity {
                SceneLoader {
                    id: sceneLoader
                    source: "qrc:/assets/fj.obj"
                    onStatusChanged: {
                        console.log("SceneLoader status: " + status);
                        if (status === SceneLoader.Ready) {
                            console.log("Scene is ready");
                            console.log(sceneLoader.entityNames())
                        }
                    }
                }

                components: [sceneLoader]
                InputSettings { }
            }

            Transform {
                id: sphereTransform
                property real userAngle: 0.0
                matrix: {
                    var m = Qt.matrix4x4();
                    m.rotate(userAngle, Qt.vector3d(0, 1, 0))
                    m.translate(Qt.vector3d(20, 0, 0));
                    return m;
                }
            }

            CameraController {
                camera: camera
                linearSpeed: 10
            }
            components: [
                RenderSettings {
                    activeFrameGraph: ForwardRenderer {
                        clearColor: Qt.rgba(0, 0.5, 1, 1)
                        camera: camera
                    }
                }
            ]
        }
    }
    Button {
        text: "Fuck!"
        focus: false
        onFocusChanged: function() {
            scene3d.forceActiveFocus();
        }

        onClicked: function(){
            console.log("fuck!")
        }
    }
}
