import Qt3D.Core 2.0
import Qt3D.Render 2.0
import Qt3D.Extras 2.0
import Qt3D.Input 2.0
Entity
{
    id: root
    Camera {
        id: camera
        projectionType: CameraLens.PerspectiveProjection
        fieldOfView: 45
        aspectRatio: 16/9
        nearPlane : 0.1
        farPlane : 100000.0
        position: Qt.vector3d( 0.0, 10.0, -800.0 )
        upVector: Qt.vector3d( 0.0, 1.0, 0.0 )
        viewCenter: Qt.vector3d( 0.0, 0.0, 0.0 )
    }
    Entity
    {
        SceneLoader {
            id: sceneLoader
            source: "qrc:/assets/SpaceShipModeling2.fbx"
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

    OrbitCameraController {
        camera: camera
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


